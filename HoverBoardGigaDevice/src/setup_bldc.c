
#include "../Inc/config.h"
#include "../Inc/defines.h"

#define TIMEOUT_FREQ  1000

TIM_HandleTypeDef htim_bldc;

//----------------------------------------------------------------------------
// Initializes the PWM (Based on the logics from Steablein
//----------------------------------------------------------------------------
void STM_PWM_Init(void)
{

   HAL_GPIO_TogglePin(DEBUG_PORT, DEBUG_PIN);

   // Enable timer clock
   //rcu_periph_clock_enable(RCU_TIMER_BLDC);

  __HAL_RCC_TIM1_CLK_ENABLE();	// is this the same as above line?

   // Initial deinitialize of the timer
   //timer_deinit(TIMER_BLDC);
   {
   // how do I do this?
   }

/* // Set up the basic parameter struct for the timer
   timerBldc_paramter_struct.counterdirection = TIMER_COUNTER_UP;
   timerBldc_paramter_struct.prescaler    = 0;
   timerBldc_paramter_struct.alignedmode  = TIMER_COUNTER_CENTER_$
   timerBldc_paramter_struct.period  = 72000000 / 2 / PWM_FR$
   timerBldc_paramter_struct.clockdivision   = TIMER_CKDIV_DIV1;
   timerBldc_paramter_struct.repetitioncounter = 0;
   timer_auto_reload_shadow_disable(TIMER_BLDC); */
   htim_bldc.Instance               = TIMER_BLDC;
   htim_bldc.Init.Prescaler         = 0;
   htim_bldc.Init.CounterMode       = TIM_COUNTERMODE_CENTERALIGNED1;
   htim_bldc.Init.Period            = 72000000 / 2 / PWM_FREQ;
   htim_bldc.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
   htim_bldc.Init.RepetitionCounter = 0;
   htim_bldc.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

   // Initialize timer with basic parameter struct
   // timer_init(TIMER_BLDC, &timerBldc_paramter_struct);
   HAL_TIM_PWM_Init(&htim_bldc);

   /*   // Deactivate output channel fastmode
        timer_channel_output_fast_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, TIMER_OC_FAST_$
        timer_channel_output_fast_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, TIMER_OC_FAST_$
        timer_channel_output_fast_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, TIMER_OC_FAST_$

        // Deactivate output channel shadow function
        timer_channel_output_shadow_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, TIMER_OC_SHA$
        timer_channel_output_shadow_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, TIMER_OC_SHA$
        timer_channel_output_shadow_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, TIMER_OC_SHA$

        // Set output channel PWM type to PWM1
        timer_channel_output_mode_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, TIMER_OC_MODE_$
        timer_channel_output_mode_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, TIMER_OC_MODE_$
        timer_channel_output_mode_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, TIMER_OC_MODE_$

        // Initialize pulse length with value 0 (pulse duty factor = zero)
        timer_channel_output_pulse_value_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, 0);
        timer_channel_output_pulse_value_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, 0);
        timer_channel_output_pulse_value_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, 0);  */
  {
  // HOW DO I DO THE ABOVE LINES?
  }

  TIM_MasterConfigTypeDef sMasterConfig;
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim_bldc, &sMasterConfig);

  /* // Set up the output channel parameter struct
     timerBldc_oc_parameter_struct.ocpolarity   = TIMER_OC_POLARITY_HIGH;
     timerBldc_oc_parameter_struct.ocnpolarity  = TIMER_OCN_POLARITY_LOW;
     timerBldc_oc_parameter_struct.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
     timerBldc_oc_parameter_struct.ocnidlestate = TIMER_OCN_IDLE_STATE_HIGH;
     // Configure all three output channels with the output channel parameter struct
     timer_channel_output_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, &timerBldc_oc_param$
     timer_channel_output_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, &timerBldc_oc_param$
     timer_channel_output_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, &timerBldc_oc_param$*/
  TIM_OC_InitTypeDef sConfigOC;
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

  /* // Set up the break parameter struct
    timerBldc_break_parameter_struct.runoffstate       = TIMER_ROS_STATE_ENABLE;
    timerBldc_break_parameter_struct.ideloffstate      = TIMER_IOS_STATE_DISABLE;
    timerBldc_break_parameter_struct.protectmode       = TIMER_CCHP_PROT_OFF;
    timerBldc_break_parameter_struct.deadtime          = DEAD_TIME;
    timerBldc_break_parameter_struct.breakstate        = TIMER_BREAK_ENABLE;
    timerBldc_break_parameter_struct.breakpolarity     = TIMER_BREAK_POLARITY_LOW;
    timerBldc_break_parameter_struct.outputautostate   = TIMER_OUTAUTO_ENABLE;
    // Configure the timer with the break parameter struct
    timer_break_config(TIMER_BLDC, &timerBldc_break_parameter_struct); */
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
  sBreakDeadTimeConfig.OffStateRunMode  = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel        = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime         = DEAD_TIME;
  sBreakDeadTimeConfig.BreakState       = TIM_BREAK_ENABLE;
  sBreakDeadTimeConfig.BreakPolarity    = TIM_BREAKPOLARITY_LOW;
  sBreakDeadTimeConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim_bldc, &sBreakDeadTimeConfig);

  // Disable until all channels are set for PWM output
  // timer_disable(TIMER_BLDC);
  TIMER_BLDC->BDTR &= ~TIM_BDTR_MOE;

/* // Enable all three channels for PWM output
   timer_channel_output_state_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, TIMER_CCX_ENABLE);
   timer_channel_output_state_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, TIMER_CCX_ENABLE);
   timer_channel_output_state_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, TIMER_CCX_ENABLE);*/
  HAL_TIM_PWM_Start(&htim_bldc, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim_bldc, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim_bldc, TIM_CHANNEL_3);

/*  // Enable all three complemenary channels for PWM output
  timer_channel_complementary_output_state_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_G, TIMER_CCXN_ENABLE);
  timer_channel_complementary_output_state_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_B, TIMER_CCXN_ENABLE);
  timer_channel_complementary_output_state_config(TIMER_BLDC, TIMER_BLDC_CHANNEL_Y, TIMER_CCXN_ENABLE);*/
  HAL_TIMEx_PWMN_Start(&htim_bldc, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim_bldc, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim_bldc, TIM_CHANNEL_3);

/* // Enable TIMER_INT_UP interrupt and set priority
  nvic_irq_enable(TIMER0_BRK_UP_TRG_COM_IRQn, 0, 0);
  timer_interrupt_enable(TIMER_BLDC, TIMER_INT_UP); */
  __HAL_TIM_ENABLE_IT(&htim_bldc, TIM_IT_BREAK);
  __HAL_TIM_ENABLE_IT(&htim_bldc, TIM_IT_UPDATE);
  __HAL_TIM_ENABLE_IT(&htim_bldc, TIM_IT_TRIGGER);
  //TIM1->DIER = 0x0003;

  // Enable the timer and start PWM
  //timer_enable(TIMER_BLDC);
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
