
//===================================================
#ifdef USE_STM32F103C8

// GPIO LED

#define LED_GREEN GPIO_PIN_9
#define LED_GREEN_PORT GPIOB
#define LED_ORANGE GPIO_PIN_8
#define LED_ORANGE_PORT GPIOB
#define LED_RED GPIO_PIN_0
#define LED_RED_PORT GPIOA
#define UPPER_LED_PIN GPIO_PIN_4
#define UPPER_LED_PORT GPIOB
#define LOWER_LED_PIN GPIO_PIN_5
#define LOWER_LED_PORT GPIOB

// Mosfet output
#define MOSFET_OUT_PIN GPIO_PIN_13
#define MOSFET_OUT_PORT GPIOC

// Brushless Control DC (BLDC) defines

#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIM1

// Channel G					// = CCR3, Channel W in FAUTH
#define TIMER_BLDC_CHANNEL_G CCR3
#define TIMER_BLDC_GH_PIN GPIO_PIN_10
#define TIMER_BLDC_GH_PORT GPIOA
#define TIMER_BLDC_GL_PIN GPIO_PIN_15
#define TIMER_BLDC_GL_PORT GPIOB

// Channel B					// = CCR2, Channel V in FAUTH
#define TIMER_BLDC_CHANNEL_B CCR2
#define TIMER_BLDC_BH_PIN GPIO_PIN_9
#define TIMER_BLDC_BH_PORT GPIOA
#define TIMER_BLDC_BL_PIN GPIO_PIN_14
#define TIMER_BLDC_BL_PORT GPIOB

// Channel Y					// = CCR1, Channel U in FAUTH
#define TIMER_BLDC_CHANNEL_Y CCR1
#define TIMER_BLDC_YH_PIN GPIO_PIN_8
#define TIMER_BLDC_YH_PORT GPIOA
#define TIMER_BLDC_YL_PIN GPIO_PIN_13
#define TIMER_BLDC_YL_PORT GPIOB

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN GPIO_PIN_12
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT GPIOB

// ADC defines
#define VBATT_PIN GPIO_PIN_4
#define VBATT_PORT GPIOA
#define VBATT_CHANNEL ADC_CHANNEL_4

#define CURRENT_DC_PIN GPIO_PIN_6
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Hall sensor defines.
#define HALL_A_PIN GPIO_PIN_10	// = RIGHT_HALL_U_PIN in FAUTH
#define HALL_A_PORT GPIOC
#define HALL_B_PIN GPIO_PIN_11	// = RIGHT_HALL_V_PIN in FAUTH
#define HALL_B_PORT GPIOC
#define HALL_C_PIN GPIO_PIN_12	// = RIGHT_HALL_W_PIN in FAUTH
#define HALL_C_PORT GPIOC

// Button
#define BUTTON_PIN GPIO_PIN_1
#define BUTTON_PORT GPIOA

#define SWITCH_PIN GPIO_PIN_1
#define SWITCH_PORT GPIOA

#define OFF_PIN GPIO_PIN_5
#define OFF_PORT GPIOA
// Self hold defines =?= OFF_PIN
#define SELF_HOLD_PIN GPIO_PIN_5
#define SELF_HOLD_PORT GPIOA

// Debug pin defines (use PC13 in STM32)
#define DEBUG_PIN GPIO_PIN_13
#define DEBUG_PORT GPIOC

#ifdef MASTER
// Buzzer defins
#define BUZZER_PIN GPIO_PIN_4
#define BUZZER_PORT GPIOA
// Charge state defines
#define CHARGE_STATE_PIN GPIO_PIN_12
#define CHARGE_STATE_PORT GPIOA
#endif

#define DELAY_TIM_FREQUENCY_US 1000000

#define MILLI_R (R * 1000)
#define MILLI_PSI (PSI * 1000)
#define MILLI_V (V * 1000)

#define NO 0
#define YES 1
#define ABS(a) (((a) < 0.0) ? -(a) : (a))
#define LIMIT(x, lowhigh) (((x) > (lowhigh)) ? (lowhigh) : (((x) < (-lowhigh)) ? (-lowhigh) : (x)))
#define SAT(x, lowhigh) (((x) > (lowhigh)) ? (1.0) : (((x) < (-lowhigh)) ? (-1.0) : (0.0)))
#define SAT2(x, low, high) (((x) > (high)) ? (1.0) : (((x) < (low)) ? (-1.0) : (0.0)))
#define STEP(from, to, step) (((from) < (to)) ? (MIN((from) + (step), (to))) : (MAX((from) - (step),(to))))
#define DEG(a) ((a)*M_PI / 180.0)
#define RAD(a) ((a)*180.0 / M_PI)
#define SIGN(a) (((a) < 0.0) ? (-1.0) : (((a) > 0.0) ? (1.0) : (0.0)))
#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define SCALE(value, high, max) MIN(MAX(((max) - (value)) / ((max) - (high)), 0.0), 1.0)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN3(a, b, c) MIN(a, MIN(b, c))
#define MAX3(a, b, c) MAX(a, MAX(b, c))

#endif // USE_STM32F103C8 -------------------------------


#ifdef USE_GD32F130C8 // -----------------------

// LED defines
#define LED_GREEN GPIO_PIN_15
#define LED_GREEN_PORT GPIOA
#define LED_ORANGE GPIO_PIN_12
#define LED_ORANGE_PORT GPIOA
#define LED_RED GPIO_PIN_3
#define LED_RED_PORT GPIOB

#define UPPER_LED_PIN GPIO_PIN_1
#define UPPER_LED_PORT GPIOA
#define LOWER_LED_PIN GPIO_PIN_0
#define LOWER_LED_PORT GPIOA

// Mosfet output
#define MOSFET_OUT_PIN GPIO_PIN_13
#define MOSFET_OUT_PORT GPIOC

// Brushless Control DC (BLDC) defines
// Channel G
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2		// = CCR3 ?
#define TIMER_BLDC_GH_PIN GPIO_PIN_10
#define TIMER_BLDC_GH_PORT GPIOA
#define TIMER_BLDC_GL_PIN GPIO_PIN_15
#define TIMER_BLDC_GL_PORT GPIOB
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1		// = CCR2 ?
#define TIMER_BLDC_BH_PIN GPIO_PIN_9
#define TIMER_BLDC_BH_PORT GPIOA
#define TIMER_BLDC_BL_PIN GPIO_PIN_14
#define TIMER_BLDC_BL_PORT GPIOB
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0		// = CCR1 ?
#define TIMER_BLDC_YH_PIN GPIO_PIN_8
#define TIMER_BLDC_YH_PORT GPIOA
#define TIMER_BLDC_YL_PIN GPIO_PIN_13
#define TIMER_BLDC_YL_PORT GPIOB

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN GPIO_PIN_12
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT GPIOB

// Hall sensor defines
#define HALL_A_PIN GPIO_PIN_11
#define HALL_A_PORT GPIOB
#define HALL_B_PIN GPIO_PIN_1
#define HALL_B_PORT GPIOF
#define HALL_C_PIN GPIO_PIN_14
#define HALL_C_PORT GPIOC

// Usart master slave defines
#define USART_MASTERSLAVE USART1
#define USART_MASTERSLAVE_TX_PIN GPIO_PIN_2
#define USART_MASTERSLAVE_TX_PORT GPIOA
#define USART_MASTERSLAVE_RX_PIN GPIO_PIN_3
#define USART_MASTERSLAVE_RX_PORT GPIOA

// ADC defines
#define VBATT_PIN GPIO_PIN_4
#define VBATT_PORT GPIOA
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_6
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines
#define SELF_HOLD_PIN GPIO_PIN_2
#define SELF_HOLD_PORT GPIOB

// Button defines
#define BUTTON_PIN GPIO_PIN_15
#define BUTTON_PORT GPIOC

// Usart steer defines
#define USART_STEER_COM USART0
#define USART_STEER_COM_TX_PIN GPIO_PIN_6
#define USART_STEER_COM_TX_PORT GPIOB
#define USART_STEER_COM_RX_PIN GPIO_PIN_7
#define USART_STEER_COM_RX_PORT GPIOB

#ifdef MASTER
// Buzzer defins
#define BUZZER_PIN GPIO_PIN_10
#define BUZZER_PORT GPIOB

// Charge state defines
#define CHARGE_STATE_PIN GPIO_PIN_0
#define CHARGE_STATE_PORT GPIOF
#endif

// Debug pin defines
#define DEBUG_PIN GPIO_PIN_4
#define DEBUG_PORT GPIOB

// Useful math function defines
#define ABS(a) (((a) < 0.0) ? -(a) : (a))
#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define MAX(x, high) (((x) > (high)) ? (high) : (x))
#define MAP(x, xMin, xMax, yMin, yMax) ((x - xMin) * (yMax - yMin) / (xMax - xMin) + yMin)


#endif // USE_GD32130C8 --------------------------


// Common use of STM32 and GD32

// ADC value conversion defines
#define MOTOR_AMP_CONV_DC_AMP 0.201465201465  // 3,3V * 1/3 - 0,004Ohm * IL(ampere) = (ADC-Data/4095) *3,3V
// #define MOTOR_AMP_CONV_DC_AMP 0.02  // A per bit (12) on ADC. (by FAUTH)

#define ADC_BATTERY_VOLT      0.024169921875 	// V_Batt to V_BattMeasure = factor 30: ( (ADC-Data/4095) *3,3V *30 )

// ADC buffer struct
typedef struct
{
  uint16_t v_batt;
  uint16_t current_dc;
} adc_buf_t;

