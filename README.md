# PWM-U4C7

## Descrição da Atividade

Esta atividade consiste no controle de um servomotor utilizando PWM (Pulse-Width Modulation). O objetivo é demonstrar como a modulação por largura de pulso pode ser aplicada para controlar a posição de um servomotor de forma precisa.

## Objetivo do Projeto

O projeto propõe a implementação de um sistema de controle de servomotor, onde a largura do pulso do sinal PWM determina a posição do eixo do motor. Este tipo de controle é amplamente utilizado em robótica e automação, permitindo movimentos precisos e repetíveis.

## Instruções de Uso e Execução do Código

### Pré-requisitos

- Raspberry Pi Pico
- Pico SDK instalado
- CMake instalado
- Compilador GCC para ARM

### Passos para Compilar e Executar

1. Clone o repositório do projeto:
    ```sh
    git clone https://github.com/KayleKylian/PWM-U4C7.git
    cd PWM-U4C7
    ```

2. Crie um diretório de build e navegue até ele:
    ```sh
    mkdir build
    cd build
    ```

3. Gere os arquivos de build com CMake:
    ```sh
    cmake ..
    ```

4. Compile o projeto:
    ```sh
    make
    ```

5. Carregue o binário gerado no Raspberry Pi Pico:
    - Conecte o Pico ao computador enquanto mantém pressionado o botão BOOTSEL.
    - Copie o arquivo `.uf2` gerado para a unidade de armazenamento do Pico.

## Demonstração

[![Demonstração do Projeto](https://img.youtube.com/vi/1giwwCtjkps/0.jpg)](https://www.youtube.com/watch?v=1giwwCtjkps)