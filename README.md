# 🚦 Smart Traffic Control System

Este projeto é um simulador de semáforo inteligente desenvolvido em **C++**. O objetivo principal é demonstrar a aplicação prática de **Máquina de Estados Finita (FSM)** e **Sincronismo de Threads**, conceitos fundamentais em sistemas embarcados e de missão crítica.

## 🧠 Arquitetura do Projeto

O sistema foi projetado para ser reativo e thread-safe, utilizando:

1.  **FSM (Finite State Machine):** Gerencia as transições entre os estados VERDE, AMARELO e VERMELHO.
2.  **Concorrência:** Uma thread de monitoramento (Sensor) funciona em paralelo à lógica principal para detectar solicitações de pedestres.
3.  **Sincronismo de Dados:** * `std::atomic` para sinalização rápida entre threads.
    * `std::mutex` com `std::lock_guard` para proteção do mapa de configurações durante a leitura/escrita.
4.  **Configuração Externa:** Leitura dinâmica de tempos de ciclo via arquivo `config.txt`, permitindo ajustes sem recompilação.

## 🛠️ Tecnologias e Conceitos

* **Linguagem:** C++11 ou superior.
* **Multithreading:** `std::thread` para tarefas assíncronas.
* **Thread-Safety:** Implementação de exclusão mútua (Mutex) para evitar Race Conditions.
* **I/O de Arquivos:** Persistência de dados e carregamento dinâmico com `fstream`.

## 🚀 Como Executar

### Pré-requisitos
- Compilador G++ (GCC) ou similar.
- Arquivo `config.txt` no diretório raiz.

### Compilação
```bash
g++ main.cpp -o traffic_control -lpthread
