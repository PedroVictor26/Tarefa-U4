#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

// Estado do semáforo (0 - Vermelho, 1 - Amarelo, 2 - Verde)
int estado_semaforo = 0;

// Função de call-back do temporizador
bool repeating_timer_callback(repeating_timer_t *rt)
{

    // Desliga todos os LEDs
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Lógica da alteração do estado
    if (estado_semaforo == 0)
    {
        gpio_put(LED_VERMELHO, 1);
    }
    else if (estado_semaforo == 1)
    {
        gpio_put(LED_AMARELO, 1);
    }
    else if (estado_semaforo == 2)
    {
        gpio_put(LED_VERDE, 1);
    }

    estado_semaforo = (estado_semaforo + 1) % 3;

    return true;
}

int main()
{
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

    while (true)
    {
        printf("Tempo decorrido...\n");
        sleep_ms(1000);
    }
}