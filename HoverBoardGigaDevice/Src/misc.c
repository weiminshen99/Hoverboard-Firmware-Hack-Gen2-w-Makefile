/**
  * This file has some EXPRIMENTAL functions by WMS
  *
  * This file is part of the hoverboard-sideboard-hack project.
  *
  * Copyright (C) 2020-2021 Emanuel FERU <aerdronix@gmail.com>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Includes
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "defines.h"
#include "setup.h"
#include "it.h"

// --------- Misc GD functions (implemented by STM functions) ------------

void gpio_bit_write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
//   gpio_bit_write(LED_GREEN_PORT, LED_GREEN, SET);
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}


// From
// ~/GD32/hover-GD//Drivers/GD32F1x0_standard_peripheral/Source/gd32f1x0_gpio.c
/*!
void gpio_mode_set(uint32_t gpio_periph,uint32_t mode,uint32_t pull_up_down,uint32_t pin)
    \brief      set GPIO output mode
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,F)
    \param[in]  mode: gpio pin mode
      \arg        GPIO_MODE_INPUT: input mode
      \arg        GPIO_MODE_OUTPUT: output mode
      \arg        GPIO_MODE_AF: alternate function mode
      \arg        GPIO_MODE_ANALOG: analog mode
    \param[in]  pull_up_down: gpio pin with pull-up or pull-down resistor
      \arg        GPIO_PUPD_NONE: without weak pull-up and pull-down resistors
      \arg        GPIO_PUPD_PULLUP: with weak pull-up resistor
      \arg        GPIO_PUPD_PULLDOWN:with weak pull-down resistor
    \param[in]  pin: GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/

// From hal_gpio.h
/** @defgroup GPIO_mode_define GPIO mode define
  * @brief GPIO Configuration Mode
  *        Elements values convention: 0xX0yz00YZ
  *           - X  : GPIO mode or EXTI Mode
  *           - y  : External IT or Event trigger detection
  *           - z  : IO configuration on External IT or Event
  *           - Y  : Output type (Push Pull or Open Drain)
  *           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
  * @{
*/
//#define  GPIO_MODE_INPUT              0x00000000U   /*!< Input Floating Mode                   */
//#define  GPIO_MODE_OUTPUT_PP          0x00000001U   /*!< Output Push Pull Mode                 */
//#define  GPIO_MODE_OUTPUT_OD          0x00000011U   /*!< Output Open Drain Mode                */
//#define  GPIO_MODE_AF_PP              0x00000002U   /*!< Alternate Function Push Pull Mode     */
//#define  GPIO_MODE_AF_OD              0x00000012U   /*!< Alternate Function Open Drain Mode    */
//#define  GPIO_MODE_AF_INPUT           GPIO_MODE_INPUT          /*!< Alternate Function Input Mode         */
//#define  GPIO_MODE_ANALOG             0x00000003U   /*!< Analog Mode  */
//#define  GPIO_MODE_IT_RISING          0x10110000U   /*!< External Interrupt Mode with Rising edge trigger detection          */
//#define  GPIO_MODE_IT_FALLING         0x10210000U   /*!< External Interrupt Mode with Falling edge trigger detection         */
//#define  GPIO_MODE_IT_RISING_FALLING  0x10310000U   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
//#define  GPIO_MODE_EVT_RISING         0x10120000U   /*!< External Event Mode with Rising edge trigger detection              */
//#define  GPIO_MODE_EVT_FALLING        0x10220000U   /*!< External Event Mode with Falling edge trigger detection             */
//#define  GPIO_MODE_EVT_RISING_FALLING 0x10320000U   /*!< External Event Mode with Rising/Falling edge trigger detection      */

/** @defgroup GPIO_speed_define  GPIO speed define
  * @brief GPIO Output Maximum frequency
  * @{
  */
//#define  GPIO_SPEED_FREQ_LOW              (GPIO_CRL_MODE0_1) /*!< Low speed */
//#define  GPIO_SPEED_FREQ_MEDIUM           (GPIO_CRL_MODE0_0) /*!< Medium speed */
//#define  GPIO_SPEED_FREQ_HIGH             (GPIO_CRL_MODE0)   /*!< High speed */

 /** @defgroup GPIO_pull_define GPIO pull define
   * @brief GPIO Pull-Up or Pull-Down Activation
   * @{
   */
//#define  GPIO_NOPULL        0x00000000U   /*!< No Pull-up or Pull-down activation  */
//#define  GPIO_PULLUP        0x00000001U   /*!< Pull-up activation                  */
//#define  GPIO_PULLDOWN      0x00000002U   /*!< Pull-down activation                */

// WMS: translating GD to STM:
void stm32_gpio_init(GPIO_TypeDef* GPIOx, uint32_t mode, uint32_t speed, uint16_t GPIO_Pin)
{
  	GPIO_InitTypeDef GPIO_InitStruct;

 	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = mode;
 	GPIO_InitStruct.Speed = speed;
	//GPIO_InitStruct.Pull = pull;

 	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void rcu_periph_clock_enable(GPIO_TypeDef* GPIOx)
// rcu_periph_clock_enable(RCU_GPIOF)
{
}

void intro_demo_led(uint32_t tDelay)
{
    int i;

    for (i = 0; i < 3; i++) {
        gpio_bit_write(LED_GREEN_PORT, LED_GREEN, SET);
        gpio_bit_write(LED_RED_PORT, LED_RED, RESET);
        HAL_Delay(tDelay);
        gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, SET);
        gpio_bit_write(LED_GREEN_PORT, LED_GREEN, RESET);
        HAL_Delay(tDelay);
        gpio_bit_write(LED_RED_PORT, LED_RED, SET);
        gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, RESET);
        HAL_Delay(tDelay);
    }

    for (i = 0; i < 2; i++) {
        gpio_bit_write(LED_GREEN_PORT, LED_GREEN, SET);
        gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, SET);
        gpio_bit_write(LED_RED_PORT,   LED_RED, SET);
        gpio_bit_write(UPPER_LED_PORT, UPPER_LED_PIN, SET);
        gpio_bit_write(LOWER_LED_PORT, LOWER_LED_PIN, SET);
        HAL_Delay(tDelay);
        gpio_bit_write(LED_GREEN_PORT,  LED_GREEN, RESET);
        gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, RESET);
        gpio_bit_write(LED_RED_PORT,    LED_RED, RESET);
        gpio_bit_write(UPPER_LED_PORT,  UPPER_LED_PIN, RESET);
        gpio_bit_write(LOWER_LED_PORT,  LOWER_LED_PIN, RESET);
    }
}

