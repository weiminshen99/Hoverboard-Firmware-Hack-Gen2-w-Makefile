/*
* Adopted from Florian Staeblein's hoverboard-hack-Gen2 by WMS
*
* This file is part of the hoverboard-firmware-hack-V2 project. The
* firmware is used to hack the generation 2 board of the hoverboard.
* These new hoverboards have no mainboard anymore. They consist of
* two Sensorboards which have their own BLDC-Bridge per Motor and an
* ARM Cortex-M3 processor GD32F130C8.
*
* Copyright (C) 2018 Florian Staeblein
* Copyright (C) 2018 Jakob Broemauer
* Copyright (C) 2018 Kai Liebich
* Copyright (C) 2018 Christoph Lehnert
*
* The program is based on the hoverboard project by Niklas Fauth. The
* structure was tried to be as similar as possible, so that everyone
* could find a better way through the code.
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

#define ARM_MATH_CM3

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "../Inc/config.h"
#include "../Inc/defines.h"
#include "../Inc/gpio.h"
#include "../Inc/setup.h"
#include "../Inc/it.h"
#include "../Inc/bldc.h"
#include "../Inc/commsMasterSlave.h"
#include "../Inc/commsSteering.h"
#include "../Inc/commsBluetooth.h"
//#include "../Inc/util.h"
//#include "../Inc/misc.h"
#include "../Inc/blink.h"

//#define BIT(x) ((uint32_t) 1 << (x))

//----------------------------------------------------------------------------
// MAIN function
//----------------------------------------------------------------------------
int main (void)
{
  	//SystemClock_Config();
//	SystemInit();
//  	SystemCoreClockUpdate();
//  	SysTick_Config(SystemCoreClock / 100);

	// Init watchdog
	// if (Watchdog_init() == ERROR)
//	if (HAL_IWDG_Init() == ERROR)
//	{ // If an error accours with watchdog initialization do not start device
//		while(1);
//	}

	// Init Interrupts
//	Interrupt_init();

	// Init timeout timer
//	TimeoutTimer_init();

	// Init GPIOs
	GPIO_init();	// defined in setup.c
//	GPIO_Init();	// defined in gpio.c

	// Activate self hold direct after GPIO-init
	// gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET);
        // HAL_GPIO_WritePin(SELF_HOLD_PORT, SELF_HOLD_PIN, GPIO_PIN_SET);

	// Init usart master slave
//	USART_MasterSlave_init();

	// Init ADC
//	ADC_init();

	// Init PWM
//	PWM_init();

	// Device has 1,6 seconds to do all the initialization
	// afterwards watchdog will be fired
	//fwdgt_counter_reload();   	// gd32
	//HAL_IWDG_Refresh();		// stm32

	// Init usart steer/bluetooth
//	USART_Steer_COM_init();


  //led_init(); // defined in blink.h

  // 1. Enable GPIO Port C
  // RCC registers, TRM section 7.3: RCC_Base 0x40021000 + APB2ENR_offset 0x18
//  volatile uint32_t* RCC_APB2ENR = (volatile uint32_t*) 0x40021018;
//  *RCC_APB2ENR |= (0b1<<4);   // set bit4=1 to enable Port C

  // 2. Set Mode of PC13 to Output_2
  // GPIO registers, TRM section 9.2: GPIO_Base 0x40011000 + CRH_offset 0x04
//  volatile uint32_t* GPIOC_CRH = (volatile uint32_t*) 0x40011004;
//  *GPIOC_CRH &= ~(0b1111<<20);  // clear bits 23..20
//  *GPIOC_CRH |=  (0b0110<<20);  // set them to 0110 for Mode Output 2

  // 3. Set PC13=0
  // GPIO_Base 0x40011000, BSRR_offset 0x10
  volatile uint32_t* GPIOC_BSRR = (volatile uint32_t*) 0x40011010;
  *GPIOC_BSRR |= BIT(13 + 0);  // turn LED on

  while(1)
	{
		//HAL_Delay(DELAY_IN_MAIN_LOOP);

		// Reload watchdog (watchdog fires after 1,6 seconds)
		//fwdgt_counter_reload();	// gd32
		//HAL_IWDG_Refresh();		// stm32

		//HAL_Delay(DELAY_IN_MAIN_LOOP);
		delay(); // defined in blink.c

		//HAL_GPIO_WritePin(GPIOC, LED_RED, GPIO_PIN_RESET);
		//HAL_GPIO_TogglePin(GPIOC, LED_RED);
		//intro_demo_led(100);	// defined in misc.c, testing
		led_on();
		//*GPIOC_BSRR |= BIT(13 + 0);  // turn LED on

		//HAL_Delay(100);
		delay(); // defined in blink.c

		//HAL_GPIO_WritePin(GPIOC, LED_RED, GPIO_PIN_SET);
		//HAL_GPIO_TogglePin(GPIOC, LED_RED);
	        //*GPIOC_BSRR |= BIT(13 + 16); // turn LED off
		led_off(); // defined in blink.c
  	}
}

