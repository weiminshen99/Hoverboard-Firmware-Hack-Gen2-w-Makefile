
#include "../Inc/config.h"
#include "../Inc/defines.h"

#define TIMEOUT_FREQ  1000

TIM_HandleTypeDef htim_bldc;

//----------------------------------------------------------------------------
// Initializes the PWM
//----------------------------------------------------------------------------

//
// THIS IS A COPY FROM FAUTH, but may be different from Staeblein's
// NEED TO CHECK THEM.

void STM32_PWM_Init(void)
{
  __HAL_RCC_TIM1_CLK_ENABLE();

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim_bldc.Instance               = TIMER_BLDC;
  htim_bldc.Init.Prescaler         = 0;
  htim_bldc.Init.CounterMode       = TIM_COUNTERMODE_CENTERALIGNED1;
  htim_bldc.Init.Period            = 64000000 / 2 / PWM_FREQ;
  htim_bldc.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim_bldc.Init.RepetitionCounter = 0;
  htim_bldc.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_PWM_Init(&htim_bldc);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim_bldc, &sMasterConfig);

  sConfigOC.OCMode       = TIM_OCMODE_PWM1;
  sConfigOC.Pulse        = 0;
  sConfigOC.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;
  HAL_TIM_PWM_ConfigChannel(&htim_bldc, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim_bldc, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_ConfigChannel(&htim_bldc, &sConfigOC, TIM_CHANNEL_3);

  sBreakDeadTimeConfig.OffStateRunMode  = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel        = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime         = DEAD_TIME;
  sBreakDeadTimeConfig.BreakState       = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity    = TIM_BREAKPOLARITY_LOW;
  sBreakDeadTimeConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim_bldc, &sBreakDeadTimeConfig);

  TIMER_BLDC->BDTR &= ~TIM_BDTR_MOE;

  HAL_TIM_PWM_Start(&htim_bldc, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim_bldc, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim_bldc, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim_bldc, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim_bldc, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim_bldc, TIM_CHANNEL_3);

  __HAL_TIM_ENABLE(&htim_bldc);
}


// set up the gpio pins for BLDC
void STM_PWM_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  // Init PINs whose mode = INPUT
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	// ======== MODE = INPUT ========
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = HALL_A_PIN | HALL_B_PIN | HALL_C_PIN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

#ifdef MASTER
  GPIO_InitStruct.Pin = CHARGE_STATE_PIN;
  HAL_GPIO_Init(CHARGE_STATE_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUTTON_PIN;
  HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
#endif

  // For PINs whose Mode = OUTPUT_PP
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	// ====== MODE = OUTPUT ======

#ifdef MASTER
  GPIO_InitStruct.Pin = BUZZER_PIN;
  HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
#endif

  GPIO_InitStruct.Pin = SELF_HOLD_PIN;
  HAL_GPIO_Init(SELF_HOLD_PORT, &GPIO_InitStruct);

  //GPIO_InitStruct.Pin = OFF_PIN;	// IS OFF_PIN =?= SELF_HOLD_PIN
  //HAL_GPIO_Init(OFF_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DEBUG_PIN;
  HAL_GPIO_Init(DEBUG_PORT, &GPIO_InitStruct);

  // how to do this? gpio_output_options_set(DEBUG_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, D$

  // For PINs whose Mode = ANALOG
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

  GPIO_InitStruct.Pin = CURRENT_DC_PIN;
  HAL_GPIO_Init(CURRENT_DC_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = VBATT_PIN;
  HAL_GPIO_Init(VBATT_PORT, &GPIO_InitStruct);

  // For PINs whose Mode = AF_PP
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // MODE = AF_PP

  GPIO_InitStruct.Pin = TIMER_BLDC_GH_PIN;
  HAL_GPIO_Init(TIMER_BLDC_GH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TIMER_BLDC_BH_PIN;
  HAL_GPIO_Init(TIMER_BLDC_BH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TIMER_BLDC_YH_PIN;
  HAL_GPIO_Init(TIMER_BLDC_YH_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TIMER_BLDC_GL_PIN;
  HAL_GPIO_Init(TIMER_BLDC_GL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TIMER_BLDC_BL_PIN;
  HAL_GPIO_Init(TIMER_BLDC_BL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TIMER_BLDC_YL_PIN;
  HAL_GPIO_Init(TIMER_BLDC_YL_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN;
  HAL_GPIO_Init(TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT, &GPIO_InitStruct);

#ifdef MASTER
        // Init charge state
        //gpio_mode_set(CHARGE_STATE_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, CHA$
#endif

}
