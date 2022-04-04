
#include "../Inc/config.h"
#include "../Inc/defines.h"
//#include "../Inc/setup.h"
//#include "../Inc/it.h"

//----------------------------------------------------------------------------
// Initializes the GPIOs for LEDs
//----------------------------------------------------------------------------
void STM_LED_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  // Configure GPIO Port B pins for the LEDs there
  GPIO_InitStruct.Pin = LED_GREEN|UPPER_LED_PIN|LOWER_LED_PIN|LED_ORANGE;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Configure LED_RED on Port A
  GPIO_InitStruct.Pin = LED_RED;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure Port C for MOSFET_OUT on PC13
  GPIO_InitStruct.Pin = MOSFET_OUT_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // exampels for Turn on/off  LEDs.
  //HAL_GPIO_WritePin(GPIOB, LED_GREEN|UPPER_LED_PIN|LOWER_LED_PIN|LED_ORANGE, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(GPIOC, LED_RED, GPIO_PIN_RESET);    	// turn PC13 on
  //HAL_GPIO_WritePin(GPIOC, LED_RED, GPIO_PIN_SET);    // turn PC13 off
  //HAL_GPIO_WritePin(GPIOC, MOSFET_OUT_PIN, GPIO_PIN_RESET);    	// turn PC13 on
  //HAL_GPIO_WritePin(GPIOC, MOSFET_OUT_PIN, GPIO_PIN_RESET);    	// turn PC13 off
}
