/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "defines.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/

/*
#define LED_GREEN GPIO_PIN_9            // LED2 by FERU
#define LED_GREEN_PORT GPIOB

#define LED_ORANGE GPIO_PIN_8           // LED3 by FERU
#define LED_ORANGE_PORT GPIOB

//#define LED_RED GPIO_PIN_0            // LED1 by FERU
//#define LED_RED_PORT GPIOA
#define LED_RED GPIO_PIN_13     // testing on Bluepill
#define LED_RED_PORT GPIOC      // for testing on Bluepill

#define UPPER_LED_PIN GPIO_PIN_4        // LED5 in PERU
#define UPPER_LED_PORT GPIOB

#define LOWER_LED_PIN GPIO_PIN_5        // LED4 in FERU
#define LOWER_LED_PORT GPIOB

*/


void GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = LED_GREEN|UPPER_LED_PIN|LOWER_LED_PIN|LED_RED|LED_ORANGE;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = LED_RED;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  //HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_GREEN|UPPER_LED_PIN|LOWER_LED_PIN|LED_ORANGE, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(GPIOA, LED_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, LED_RED, GPIO_PIN_RESET);	// turn PC13 on
//  HAL_GPIO_WritePin(GPIOC, LED_RED, GPIO_PIN_SET);	// turn PC13 off

/*
  // Configure GPIO pins : PCPin PCPin
  GPIO_InitStruct.Pin = SENSOR2_Pin|AUX1_PU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // Configure GPIO pin : PtPin
  GPIO_InitStruct.Pin = SENSOR1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SENSOR1_GPIO_Port, &GPIO_InitStruct);

  // Configure GPIO pin : PtPin
  GPIO_InitStruct.Pin = AUX3_PU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AUX3_PU_GPIO_Port, &GPIO_InitStruct);
*/

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
