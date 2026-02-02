#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <string>
#include <fstream>
#include <atomic>
#include <mutex>


std::atomic<bool> botaoPedestreApertado(false);
std::mutex mtxTempos;

void MonitorarBotao() {
while (true) {
    char c;
    std::cin >> c; // Trava aqui até digitar algo
    if (c == 'p') {
        std::cout << "\n[!] SINAL DE PEDESTRE SOLICITADO!" << std::endl;
        botaoPedestreApertado = true;
    }
}
}

enum Estado { VERDE, AMARELO, VERMELHO };


class Semaforo {
private:
Estado estadoAtual;
std::map<std::string, int> tempos;

public:
Semaforo() : estadoAtual(VERDE) {
    carregarDados();
}

void carregarDados() {
    // LOCK: Pegamos a chave antes de mexer nos dados
    std::lock_guard<std::mutex> lock(mtxTempos);

    std::ifstream arquivo("config.txt");
    if (!arquivo.is_open()) {
        tempos["verde"] = 5; tempos["amarelo"] = 2; tempos["vermelho"] = 5;
        return;
    }

    tempos.clear();
    std::string cor;
    int tempo;
    while (arquivo >> cor >> tempo) {
        tempos[cor] = tempo;
    }
    std::cout << "[SISTEMA] Dados carregados com seguranca (Mutex Ativo)." << std::endl;
    // O UNLOCK acontece automaticamente quando a função termina (lock_guard)
}

void sleepInteligente(std::string cor) {
    int segundos;

    // Protegemos a leitura: Garantimos que ninguém mude o tempo enquanto lemos
    {
        std::lock_guard<std::mutex> lock(mtxTempos);
        segundos = tempos[cor];
    }

    for (int i = 0; i < segundos * 10; ++i) {
        if (botaoPedestreApertado && estadoAtual == VERDE) {
            botaoPedestreApertado = false;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void rodar() {
    while (true) {
        switch (estadoAtual) {
        case VERDE:
            std::cout << "[V] VERDE" << std::endl;
            sleepInteligente("verde");
            estadoAtual = AMARELO;
            break;
        case AMARELO:
            std::cout << "[A] AMARELO" << std::endl;
            sleepInteligente("amarelo");
            estadoAtual = VERMELHO;
            break;
        case VERMELHO:
            std::cout << "[R] VERMELHO" << std::endl;
            sleepInteligente("vermelho");
            estadoAtual = VERDE;
            break;
        }
    }
}
};

int main() {
std::thread threadBotao(MonitorarBotao);
threadBotao.detach(); 

Semaforo meuSemaforo;
meuSemaforo.rodar(); 

return 0;
}