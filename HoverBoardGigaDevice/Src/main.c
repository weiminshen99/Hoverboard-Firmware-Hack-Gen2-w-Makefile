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
#include "../Inc/setup.h"
#include "../Inc/it.h"
#include "../Inc/led.h"
#include "../Inc/bldc.h"
//#include "../Inc/commsMasterSlave.h"
//#include "../Inc/commsSteering.h"
//#include "../Inc/commsBluetooth.h"


extern uint32_t uwTick;

//#define BIT(x) ((uint32_t) 1 << (x))

/* Private function prototypes -----------------------------------------------*/

// this is needed for HAL_Delay(), see it.c
/* void SysTick_Handler(void)   // this SysTick Timer is running at _MHZ
{
	HAL_IncTick();
} */

void SystemClock_Config(void);


void PC13_led_init(void)
{
  volatile uint32_t* RCC_APB2ENR = (volatile uint32_t*) 0x40021018;     // RCC
  volatile uint32_t* GPIOC_CRH =  (volatile uint32_t*) 0x40011004;      // Port C

  *RCC_APB2ENR |= (0b1<<4);     // set bit4=1 to enable Port C
  *GPIOC_CRH &= ~(0b1111<<20);  // clear PC13, bits 23..20
  *GPIOC_CRH |=  (0b0110<<20);  // set the bits to 0110 for Mode Output 2
}

//----------------------------------------------------------------------------
// MAIN function
//----------------------------------------------------------------------------
int main (void)
{

#ifdef USE_GD32F130C8
//SystemInit();
//SystemCoreClockUpdate();
//SysTick_Config(SystemCoreClock / 100);
#endif

#ifdef USE_STM32F103C8

//  volatile uint32_t* GPIOC_BSRR = (volatile uint32_t*) 0x40011010;      // Port C

  HAL_Init();

  __HAL_RCC_AFIO_CLK_ENABLE();  // WHAT IS THIS?
  // Configure the SysTick to have interrupt in 1ms time basis
  HAL_SYSTICK_Config(SystemCoreClock/1000U);
  /* System interrupt init*/
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  SystemClock_Config();

#endif

	// Init watchdog
	// if (Watchdog_init() == ERROR)
//	if (HAL_IWDG_Init() == ERROR)
//	{ // If an error accours with watchdog initialization do not start device
//		while(1);
//	}

	// Init Interrupts
	Interrupt_init();

	// Init GPIOs
	GPIO_init();		// see setup.c
	//PC13_led_init();

	// Init timeout timer
//	TimeoutTimer_init();	// see setup.c

	// Activate self hold direct after GPIO-init
	// gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET);
        // HAL_GPIO_WritePin(SELF_HOLD_PORT, SELF_HOLD_PIN, GPIO_PIN_SET);

	// Init usart master slave
//	USART_MasterSlave_init();

	// Init ADC
//	ADC_init();

	// Init PWM
	PWM_init();

	// Device has 1,6 seconds to do all the initialization
	// afterwards watchdog will be fired
	//fwdgt_counter_reload();   	// gd32
	//HAL_IWDG_Refresh();		// stm32

	// Init usart steer/bluetooth
//	USART_Steer_COM_init();

  while(1)
	{
		//HAL_Delay(DELAY_IN_MAIN_LOOP);

		// Reload watchdog (watchdog fires after 1,6 seconds)
		//fwdgt_counter_reload();	// gd32
		//HAL_IWDG_Refresh();		// stm32

		//HAL_Delay(250);
		//Delay(250);	// for gd32, defined in it.c
		//delay(250); // defined in misc.c

		//HAL_GPIO_TogglePin(DEBUG_PORT, DEBUG_PIN);

		// led_on();
		//HAL_GPIO_WritePin(GPIOC, MOSFET_OUT_PIN, GPIO_PIN_RESET);
		//intro_demo_led(100);	// defined in misc.c, testing
	        // *GPIOC_BSRR |= ((uint32_t) 1 << (13 + 0)); // turn LED on

		//HAL_Delay(250);
		//delay(250); // defined in misc.c

		// led_off(); // defined in blink.c
		// HAL_GPIO_WritePin(GPIOC, MOSFET_OUT_PIN, GPIO_PIN_SET);
	        // *GPIOC_BSRR |= ((uint32_t) 1 << (13 + 16)); // turn LED off
  	}
}


void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  // Initializes the CPU, AHB and APB busses clocks

  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL16;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  // Initializes the CPU, AHB and APB busses clocks
  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1| RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection    = RCC_ADCPCLK2_DIV8;  // 8 MHz
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
