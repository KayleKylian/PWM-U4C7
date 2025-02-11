#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// MACROS
#define SERVO_PIN 22 // Pino do PWM
#define PWM_FREQ 50 // Frequência do PWM em Hz
#define CLOCK_FREQ 125000000 // Frequência do clock em Hz
#define LED_PIN 12 // Pino do LED
#define LED_WRAP 255 // Número máximo de ciclos do PWM para o LED

// Variáveis globais
uint32_t wrap = CLOCK_FREQ / (PWM_FREQ * 64); // Número máximo de ciclos do PWM
uint servo_slice; // Número do slice do servomotor
uint led_slice; // Número do slice do LED

// Protótipos das funções
void init_pwm(void);
void set_servo_angle(float angle);
void init_led(void);
void set_led_brightness(float angle_brightness);

int main()
{
    // Inicialização
    stdio_init_all();
    init_led(); // Inicializa o LED
    init_pwm(); // Inicializa o PWM

    // Loop principal
    while (true) {
        // Gira o servo de 0 a 180 graus
        for (float angle = 0; angle <= 180; angle += 5) {
            set_servo_angle(angle); // Define o ângulo do servo
            set_led_brightness(angle); // Define o brilho do LED
            if (angle == 90) sleep_ms(5000); // Pausa de 5 segundos no ângulo de 90 graus
            sleep_ms(10); // Pausa de 10 ms entre cada incremento de ângulo
        }

        // Pausa de 5 segundos após completar o movimento de 0 a 180 graus
        sleep_ms(5000);

        // Gira o servo de 180 a 0 graus
        for (float angle = 180; angle >= 0; angle -= 5) {
            set_servo_angle(angle); // Define o ângulo do servo
            set_led_brightness(angle); // Define o brilho do LED
            if (angle == 90) sleep_ms(5000); // Pausa de 5 segundos no ângulo de 90 graus
            sleep_ms(10); // Pausa de 10 ms entre cada decremento de ângulo
        }

        // Pausa de 5 segundos após completar o movimento de 180 a 0 graus
        sleep_ms(5000);
    }

    return 0; // Retorno da função main (embora nunca seja alcançado)
}

/**
 * @brief Inicializa o PWM no pino especificado.
 */
void init_pwm(void)
{
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Configura o pino do PWM
    servo_slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o número do slice

    // Configura o PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 64.0f); // Divide o clock por 64
    pwm_config_set_wrap(&config, wrap); // Define o número máximo de ciclos
    
    pwm_init(servo_slice, &config, true); // Inicializa o PWM
}

/**
 * @brief Inicializa o LED no pino especificado.
 */
void init_led(void)
{
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM); // Configura o pino do PWM
    led_slice = pwm_gpio_to_slice_num(LED_PIN); // Obtém o número do slice

    pwm_config config = pwm_get_default_config(); // Configura o PWM
    pwm_config_set_clkdiv(&config, 1.0f); // Divide o clock por 1
    pwm_config_set_wrap(&config, LED_WRAP); // Define o número máximo de ciclos

    pwm_init(led_slice, &config, true); // Inicializa o PWM
}

/**
 * @brief Define o ângulo do servo motor.
 * 
 * @param angle Ângulo desejado em graus (0 a 180).
 */
void set_servo_angle(float angle)
{
    // Converte o ângulo para tempo em pulso (em microssegundos)
    uint16_t pulse_width = 500 + (angle / 180.0f) * 1900;

    // Converte o tempo de pulso para ciclos do PWM (Duty Cycle)
    uint32_t level = (pulse_width * wrap) / 20000;

    pwm_set_gpio_level(SERVO_PIN, level); // Define o Duty Cycle
}

/**
 * @brief Define o brilho do LED.
 * 
 * @param angle_brightness Brilho desejado (0 a 1).
 */
void set_led_brightness(float angle_brightness)
{
    uint brightness = (uint)(angle_brightness / 180.0f) * LED_WRAP;
    pwm_set_gpio_level(LED_PIN, brightness); // Define o Duty Cycle
}