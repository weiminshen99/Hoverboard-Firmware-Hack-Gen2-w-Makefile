//defines the main program loop

#define ARM_MATH_CM3

#include "gd32f1x0.h"

#include "../Inc/setup.h"
#include "../Inc/defines.h"
#include "../Inc/config.h"
#include "../Inc/it.h"
#include "../Inc/bldc.h"
#include "../Inc/commsMasterSlave.h"
#include "../Inc/commsRemote.h"
#include "../Inc/commsSteeringPWM.h"
#include "../Inc/commsInterlocks.h"
#include "../Inc/commsBluetooth.h"
#include "../Inc/commsAccelerometer.h"
#include "../Inc/navigator.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <math.h>
//#include "arm_math.h"	// for PID

#ifdef MASTER

	//int32_t steer = 0; 												// global variable for steering. -1000 to 1000
	//int32_t speed = 0; 												// global variable for speed.    -1000 to 1000
	int16_t speed_mm_per_second_MasterWheel=(int16_t)0;						// global variable for speed in mm per second -6000 +6000 (21,6km/h)
	int16_t speed_mm_per_second_SlaveWheel=(int16_t)0;						// global variable for speed in mm per second -6000 +6000 (21,6km/h)
	int16_t speed_mm_per_second=(int16_t)0;						// global variable for speed in mm per second -6000 +6000 (21,6km/h)

	int16_t steerAngle = 0;  //angle pf steer between 180 and 0 degrees. 90 degrees to go straight

	int32_t actuatorSpeed = 0;								// actuator(lawnmower motor blade) speed. 0 to 1000

	float logImuArray[400]; 									//array of array for logging purposes
	int16_t logImuArrayCurrentIndex=0; // set by GetAcceData(), -1 means fall

	float pitchAngle=0;
	float rollAngle=0;
	float yawAngle=0;

	bool recordAccelerometerLog = TRUE;
	bool printAccelerometerLog = TRUE;

	FlagStatus panicButtonPressed = SET;	//global variable. RESET when pressed.
	FlagStatus it_is_Raining = RESET;	//global variable. SET when raining.

	FlagStatus activateWeakening = RESET;	// global variable for weakening
	FlagStatus beepsBackwards = RESET; 	// global variable for beeps backwards

	extern uint8_t buzzerFreq;	// global variable for the buzzer pitch. can be 1, 2, 3, 4, 5, 6, 7...
	extern uint8_t buzzerPattern;	// global variable for the buzzer pattern. can be 1, 2, 3, 4, 5, 6, 7...

	extern float batteryVoltage; 		// global variable for battery voltage
	extern float currentDC; 		// global variable for current dc
	extern float realSpeed_mm_per_second; 	// global variable for real Speed
	extern bool moveBySteps;		// global variable for movements controlled in steps(=1) or classic movements controlled by speed and steer (=0)
	extern bool moveByStepsCompleted;	// global variable 1= movement completed.
	extern int16_t remainingSteps;
	extern FlagStatus timedOut;		// Timeoutvariable set by timeout timer

	bool robotReversed=FALSE;

	uint32_t inactivity_timeout_counter = 0;	// Inactivity counter
	uint32_t steerCounter = 0;			// Steer counter for setting update rate

	void ShowBatteryState(uint32_t pin);
	void BeepsBackwards(FlagStatus beepsBackwards);
	void ShutOff(void);

	extern float PID_PARAM_KP;
	extern float PID_PARAM_KI;
	extern float PID_PARAM_KD;
#endif

const float lookUpTableAngle[181] =  {
  -1,
  -0.937202577,
  -0.878193767,
  -0.822607884,
  -0.770124422,
  -0.720461266,
  -0.673369096,
  -0.628626737,
  -0.58603728,
  -0.545424828,
  -0.506631749,
  -0.46951635,
  -0.433950895,
  -0.399819915,
  -0.367018754,
  -0.335452314,
  -0.30503398,
  -0.275684674,
  -0.24733204,
  -0.219909731,
  -0.193356783,
  -0.167617063,
  -0.142638788,
  -0.118374098,
  -0.094778672,
  -0.071811398,
  -0.049434068,
  -0.027611115,
  -0.006309372,
  0.014502141,
  0.03485241,
  0.054768601,
  0.074276213,
  0.093399224,
  0.112160212,
  0.130580478,
  0.148680146,
  0.166478264,
  0.183992885,
  0.201241154,
  0.218239378,
  0.235003093,
  0.251547129,
  0.267885663,
  0.284032276,
  0.3,
  0.315801365,
  0.331448439,
  0.34695287,
  0.362325923,
  0.377578512,
  0.392721236,
  0.407764409,
  0.422718089,
  0.437592106,
  0.45239609,
  0.467139493,
  0.48183162,
  0.496481645,
  0.511098642,
  0.5256916,
  0.540269454,
  0.554841097,
  0.569415411,
  0.584001283,
  0.598607627,
  0.613243408,
  0.627917665,
  0.642639528,
  0.657418247,
  0.672263213,
  0.687183982,
  0.702190301,
  0.717292134,
  0.732499689,
  0.747823448,
  0.763274197,
  0.778863056,
  0.794601516,
  0.810501473,
  0.826575268,
  0.842835728,
  0.859296209,
  0.875970644,
  0.892873598,
  0.910020317,
  0.927426794,
  0.94510983,
  0.963087109,
  0.981377271,
  1,
  1.018976116,
  1.038327677,
  1.058078086,
  1.07825222,
  1.098876565,
  1.119979359,
  1.141590767,
  1.163743061,
  1.186470823,
  1.209811179,
  1.23380405,
  1.258492439,
  1.283922754,
  1.310145166,
  1.33721402,
  1.365188293,
  1.394132116,
  1.42411537,
  1.455214362,
  1.487512601,
  1.521101681,
  1.556082309,
  1.592565485,
  1.630673867,
  1.670543366,
  1.712325006,
  1.7561871,
  1.802317825,
  1.85092826,
  1.902255998,
  1.956569473,
  2.014173151,
  2.075413814,
  2.140688197,
  2.210452351,
  2.28523318,
  2.365642792,
  2.452396478,
  2.546335439,
  2.648455802,
  2.75994605,
  2.882235846,
  3.01706052,
  3.166547428,
  3.333333333,
  3.520726642,
  3.732935875,
  3.97539819,
  4.255263139,
  4.582124498,
  4.96916252,
  5.434992778,
  6.006790189,
  6.72584757,
  7.658112588,
  8.915817681,
  10.70672711,
  13.46326037,
  18.25863694,
  28.69242032,
  68.95533643,
  -158.4943784,
  -36.21729907,
  -20.22896451,
  -13.92536607,
  -10.55089693,
  -8.447794056,
  -7.010715755,
  -5.965979741,
  -5.171786508,
  -4.547320366,
  -4.043147824,
  -3.62733258,
  -3.278323283,
  -2.981049637,
  -2.72465641,
  -2.501126036,
  -2.304408198,
  -2.129851283,
  -1.973820239,
  -1.833433222,
  -1.706376086,
  -1.590769119,
  -1.485069639,
  -1.387999671,
  -1.29849148,
  -1.21564602,
  -1.138700863,
  -1.067005175,
  -1
};


//----------------------------------------------------------------------------
// MAIN function
//----------------------------------------------------------------------------
int main (void)
{
#ifdef MASTER
	FlagStatus enable = RESET;
	FlagStatus enableSlave = RESET;
	FlagStatus chargeStateLowActive = SET;

	int16_t sendSlaveValue = 0;
	uint8_t sendSlaveIdentifier = 0;
	int8_t index = 8;
 	//int16_t pwmSlave = 0;
	//int16_t pwmMaster = 0;
	//int16_t scaledSpeed = 0;
	//int16_t scaledSteer  = 0;
	//float expo = 0;

	float xScale = 0;
#endif

	//SystemClock_Config();
  	SystemCoreClockUpdate();
  	SysTick_Config(SystemCoreClock / 100);

	// Init watchdog
	if (Watchdog_init() == ERROR)
	{
		// If an error accours with watchdog initialization do not start device
		while(1);
	}

	// Init Interrupts
	Interrupt_init();

	// Init timeout timer
	TimeoutTimer_init();

	// Init GPIOs
	GPIO_init();

	// Activate self hold direct after GPIO-init
	gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET);

	// Init usart master slave
	USART_MasterSlave_init();

	#ifdef MASTER
		//init i2c that communicates with accelerometer
		I2C_IMU_init();
	#endif
	// Init ADC
	ADC_init();

	// Init PWM
	PWM_init();

	#ifdef SLAVE
	//PID_init();
	#endif
	// Device has 1,6 seconds to do all the initialization
	// afterwards watchdog will be fired
	fwdgt_counter_reload();

	// Init remote usart
	USART_REMOTE_COM_init();

#ifdef MASTER
	// Startup-Sound
	for (; index >= 0; index--)
	{
    		buzzerFreq = index;
    		Delay(10);
  	}
  	buzzerFreq = 0;

	// Wait until button is pressed
	while (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN))
	{
		// Reload watchdog while button is pressed
		fwdgt_counter_reload();
	}
#endif

  while(1)
	{

#ifdef MASTER
		steerCounter++;
		Send_Data_over_REMOTE_serialPort_of_MasterBoard();

		// Read charge state
		chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
		// Enable is depending on charger is connected or not
		enable = chargeStateLowActive;

		//mainLoopPeriodMilliseconds=(halfMillisecondsCount+1)/2;
		//halfMillisecondsCount=0;

		if(moveBySteps){ //movements controlled in number of steps forward or backward
			// Reset the pwm timout to avoid stopping motors
			ResetTimeout();
			// do not shutdown if movement by steps is in progress
			inactivity_timeout_counter = 0;


		}else{ //classic movements controlled by speed and steer

			// Calculate expo rate for less steering with higher speeds
			//expo = MAP((float)ABS(speed), 0, 1000, 1, 0.5);

			// Each speedvalue or steervalue between 50 and -50 means absolutely no pwm
			// -> to get the device calm 'around zero speed'
			//scaledSpeed = speed < 50 && speed > -50 ? 0 : CLAMP(speed, -1000, 1000) * SPEED_COEFFICIENT;
			//scaledSteer = steer < 50 && steer > -50 ? 0 : CLAMP(steer, -1000, 1000) * STEER_COEFFICIENT * expo;



			// Map to an angle of 180 degress to 0 degrees for array access (means angle -90 to 90 degrees)
			//steerAngle = MAP((float)scaledSteer, -1000, 1000, 180, 0);
			xScale = lookUpTableAngle[(uint16_t)steerAngle];


				// Mix steering and speed value for right and left speed
				if(steerAngle >= 90){
					speed_mm_per_second_MasterWheel= CLAMP(speed_mm_per_second,-1000,1000);
					speed_mm_per_second_SlaveWheel = CLAMP(speed_mm_per_second / xScale,-1000,1000);
				}else{
					speed_mm_per_second_MasterWheel= CLAMP(speed_mm_per_second * xScale,-1000,1000);
					speed_mm_per_second_SlaveWheel = CLAMP(speed_mm_per_second,-1000,1000);
				}




			// Enable channel output
			SetEnable(enable);


			// Set output
			SetSpeed(speed_mm_per_second_MasterWheel);


			// Calculate inactivity timeout (Except, when charger is active -> keep device running)
			if (!chargeStateLowActive || ABS(speed_mm_per_second)>40){
				inactivity_timeout_counter = 0;
			}else{
				inactivity_timeout_counter++;
			}


		}

		// Decide if slave will be enabled
		enableSlave = (enable == SET && timedOut == RESET) ? SET : RESET;

		// Decide which process value has to be sent
		switch(sendSlaveIdentifier)
		{
			case 5:
				#ifdef TERMINAL_ENABLED_PID_TUNING
					sendSlaveValue = PID_PARAM_KP*10000.0;
					break;
				#else
					sendSlaveIdentifier=0;
				#endif
			case 6:
				#ifdef TERMINAL_ENABLED_PID_TUNING
					sendSlaveValue = PID_PARAM_KI*10000.0;
					break;
				#else
					sendSlaveIdentifier=0;
				#endif
			case 7:
				#ifdef TERMINAL_ENABLED_PID_TUNING
					sendSlaveValue = PID_PARAM_KD*10000.0;
					break;
				#else
					sendSlaveIdentifier=0;
				#endif
			case 0:
				sendSlaveValue = currentDC * 100;
				break;
			case 1:
				sendSlaveValue = batteryVoltage * 100;
				break;
			case 2:
				sendSlaveValue = realSpeed_mm_per_second * 1000;
				break;
			case 3:
				sendSlaveIdentifier++; //we jump case 3 since it is used just on navigator
			case 4:
				sendSlaveValue = remainingSteps;
				break;

			default:
				break;
		}
		//send data to slave board
		SendSlave(-speed_mm_per_second_SlaveWheel, enableSlave, RESET, chargeStateLowActive, sendSlaveIdentifier, sendSlaveValue);

		// Increment identifier
		sendSlaveIdentifier++;
		if (sendSlaveIdentifier > 7)
		{
			sendSlaveIdentifier = 0;
		}

		if((ABS(pitchAngle)>20) ||  (ABS(rollAngle)>20) ){
			robotReversed=TRUE;
			//actuatorSpeed=0;
			gpio_bit_write(LED_GREEN_PORT, LED_GREEN, RESET); //(inverted logic since it uses npn transistor)

			speed_mm_per_second=0;
			stopNavigator();
			ShutOff();

		}
		// Show green battery symbol when battery level BAT_LOW_LVL1 is reached
    		if (batteryVoltage > BAT_LOW_LVL1)
		{
			// Show green battery light
			//ShowBatteryState(LED_GREEN); //green led is used by the actuator (blade motor) inside commsActuator.c

			// Beeps backwards
			BeepsBackwards(beepsBackwards);
		}
		// Make silent sound and show orange battery symbol when battery level BAT_LOW_LVL2 is reached
    		else if (batteryVoltage > BAT_LOW_LVL2 && batteryVoltage < BAT_LOW_LVL1)
		{
			// Show orange battery light
			ShowBatteryState(LED_ORANGE);

      		buzzerFreq = 5;
      		buzzerPattern = 8;
    		}
		// Make even more sound and show red battery symbol when battery level BAT_LOW_DEAD is reached
		else if  (batteryVoltage > BAT_LOW_DEAD && batteryVoltage < BAT_LOW_LVL2)
		{
			// Show red battery light
			ShowBatteryState(LED_RED);

      		buzzerFreq = 5;
      		buzzerPattern = 1;
    		}
		// Shut device off, when battery is dead
		else if (batteryVoltage < BAT_LOW_DEAD)
		{
      		ShutOff();
    		}
		else
		{
			ShutOff();
    		}

		if(panicButtonPressed==RESET){
			ShutOff();
    		}

		// Shut device off when button is pressed
		if (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN))
		{
      			while (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN)) {}
			ShutOff();
    		}


		// Shut off device after INACTIVITY_TIMEOUT in minutes
    		if (inactivity_timeout_counter > (INACTIVITY_TIMEOUT * 60 * 1000) / (DELAY_IN_MAIN_LOOP + 1))
		{
      			ShutOff();
    		}
#endif


#ifdef SLAVE
		SetEnable(SET);
		SetSpeed(250);
		ResetTimeout();
#endif


		Delay(DELAY_IN_MAIN_LOOP);

		// Reload watchdog (watchdog fires after 1,6 seconds)
		fwdgt_counter_reload();
  }
}

#ifdef MASTER
//----------------------------------------------------------------------------
// Turns the device off
//----------------------------------------------------------------------------
void ShutOff(void){
	int index = 0;
	buzzerPattern = 0;
	for (; index < 8; index++)
	{
		buzzerFreq = index;
		Delay(10);
	}
	buzzerFreq = 0;

	// Send shut off command to slave
	SendSlave(0, RESET, SET, RESET, RESET, RESET);

	// Disable usart
	usart_deinit(USART_MASTERSLAVE);

	// Set pwm and enable to off
	SetEnable(RESET);
	//SetPWM(0);
	speed_mm_per_second_MasterWheel=0;

	gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, RESET);
	while(1)
	{
		// Reload watchdog until device is off
		fwdgt_counter_reload();
	}
}

//----------------------------------------------------------------------------
// Shows the battery state on the LEDs
//----------------------------------------------------------------------------
void ShowBatteryState(uint32_t pin)
{
	#ifndef DEBUG_WITH_TRACE_ENABLED
		// gpio_bit_write(LED_GREEN_PORT, LED_GREEN, pin == LED_GREEN ? SET : RESET); //commented cause this pin is used to activate the motor with the blade of the lawnmower
		gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, pin == LED_ORANGE ? SET : RESET);
		gpio_bit_write(LED_RED_PORT, LED_RED, pin == LED_RED ? SET : RESET);
	#endif
}

//----------------------------------------------------------------------------
// Beeps while driving backwards
//----------------------------------------------------------------------------
void BeepsBackwards(FlagStatus beepsBackwards)
{
	// If the speed is less than -40, beep while driving backwards
	if (beepsBackwards == SET && speed_mm_per_second < -40)
	{
		buzzerFreq = 5;
    buzzerPattern = 4;
	}
	else
	{
		buzzerFreq = 0;
		buzzerPattern = 0;
	}
}
#endif
