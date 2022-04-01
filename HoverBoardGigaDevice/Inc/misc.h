#include "config.h"
#include "defines.h"

void intro_demo_led(uint32_t tDelay);

void delay(uint16_t ms);

void gpio_bit_write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

void gpio_mode_set(GPIO_TypeDef* GPIOx, uint32_t mode, uint32_t pull, uint16_t GPIO_Pin);

void gpio_output_options_set(GPIO_TypeDef* GPIOx, uint16_t otype, uint16_t speed, uint16_t GPIO_Pin);


//void rcu_periph_clock_enable(GPIO_TypeDef* GPIOx);


