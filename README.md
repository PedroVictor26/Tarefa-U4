
*   **LED Vermelho:** Conectado ao pino GP11 do Raspberry Pi Pico através de um resistor de 330Ω, e o cátodo ao GND.
*   **LED Amarelo:** Conectado ao pino GP12 do Raspberry Pi Pico através de um resistor de 330Ω, e o cátodo ao GND.
*   **LED Verde:** Conectado ao pino GP13 do Raspberry Pi Pico através de um resistor de 330Ω, e o cátodo ao GND.

## Funcionamento

1.  **Inicialização:**
    *   O programa inicializa as portas GPIO conectadas aos LEDs como saídas.
    *   O temporizador periódico é configurado com um intervalo de 3 segundos e uma função de callback.

2.  **Loop Principal (While):**
    *   O loop principal imprime uma mensagem na porta serial a cada segundo, através da função `printf`.
    *   O loop espera 1 segundo usando `sleep_ms(1000)`.

3.  **Função de Callback (`repeating_timer_callback`):**
    *   Esta função é chamada a cada 3 segundos pelo temporizador.
    *   A função gerencia a mudança de estado dos LEDs:
        *   Desliga todos os LEDs.
        *   Liga o LED correspondente ao estado atual do semáforo.
        *   Atualiza o estado do semáforo.

4.  **Sequência do Semáforo:**
    *   Vermelho -> Amarelo -> Verde -> Vermelho (ciclo contínuo).

## Como Compilar e Executar

### 1. Ambiente de Desenvolvimento

*   Certifique-se de ter o ambiente de desenvolvimento do Raspberry Pi Pico SDK configurado.
*   Recomenda-se utilizar o VS Code com a extensão do Wokwi para facilitar a simulação.

### 2. Compilação

1.  Abra o projeto no VS Code.
2.  Crie um novo arquivo chamado `semaforo.c` e cole o código C fornecido.
3.  Configure o arquivo `CMakeLists.txt` com as informações do seu projeto.
4.  Compile o projeto usando o comando `CMake` e `Make`, ou através das ferramentas do VS Code.

### 3. Simulação (Wokwi)

1.  Certifique-se de ter a extensão do Wokwi instalada no VS Code.
2.  Adicione o arquivo `wokwi.json` fornecido à raiz do seu projeto.
3.  Clique no botão "Play" para simular o código no Wokwi.

### 4. Execução (Raspberry Pi Pico)

1.  Conecte o Raspberry Pi Pico ao seu computador via USB.
2.  Carregue o arquivo `.uf2` gerado durante a compilação no Raspberry Pi Pico.
3.  Abra um terminal serial para verificar a saída de texto do programa.

## Código-Fonte

O código-fonte principal está no arquivo `semaforo.c`. Veja a seguir:

```c
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

// Estado do semáforo (0 - Vermelho, 1 - Amarelo, 2 - Verde)
int estado_semaforo = 0;

// Função de call-back do temporizador
bool repeating_timer_callback(repeating_timer_t *rt) {
  // Desliga todos os LEDs
  gpio_put(LED_VERMELHO, 0);
  gpio_put(LED_AMARELO, 0);
  gpio_put(LED_VERDE, 0);

  // Lógica da alteração do estado
  if (estado_semaforo == 0) {
    gpio_put(LED_VERMELHO, 1);
  } else if (estado_semaforo == 1) {
    gpio_put(LED_AMARELO, 1);
  } else if (estado_semaforo == 2) {
    gpio_put(LED_VERDE, 1);
  }

  estado_semaforo = (estado_semaforo + 1) % 3;

  return true;
}

int main() {
  stdio_init_all();
  gpio_init(LED_VERMELHO);
  gpio_init(LED_AMARELO);
  gpio_init(LED_VERDE);
  gpio_set_dir(LED_VERMELHO, GPIO_OUT);
  gpio_set_dir(LED_AMARELO, GPIO_OUT);
  gpio_set_dir(LED_VERDE, GPIO_OUT);

  // Configura o temporizador periódico
  repeating_timer_t timer;
  add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

  while (true) {
    printf("Tempo decorrido...\n");
    sleep_ms(1000);
  }
}
