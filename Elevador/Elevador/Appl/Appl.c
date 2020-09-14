/*
 * Appl.c
 *
 *  Created on: 13/05/2019
 *      Author: MAASDN
 */

//-------------------------------------- Include Files ----------------------------------------------------------------

#include <Z:\Elevador\Elevador\Elevador\Header\C_Types.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Appl.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Display.h>
//#include <alloca.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Gpio.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Adc.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Timer.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Hal.h>
#include <Z:\Elevador\Elevador\Elevador\Header\OvenPositionControl.h>
#include <Z:\Elevador\Elevador\Elevador\Header\PortSensor.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Pwm.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Sounds.h>

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_SOLICITATION_TYPE User_Action;
FLOOR_STATE Floor_position; 

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define EXP_ADC                ENABLED
#define EXP_OVEN               ENABLED

#define EXP_TIMER               DISABLED       // TEMPO em ms
#define EXP_TIMER1              DISABLED       // TEMPO em HMS
#define TIME_IN_50MS_BASE	    20 //1s in 50ms time base (20*50ms = 1s)

//Oven Min time parameters
#define OVEN_MIN_ON_TIME_SEC	10
#define OVEN_MIN_ON_TIME_MIN	0
#define OVEN_MIN_ON_TIME_HRS	0

//Oven Med time parameters
#define OVEN_MED_ON_TIME_SEC	15
#define OVEN_MED_ON_TIME_MIN	0
#define OVEN_MED_ON_TIME_HRS	0

//Oven Max time parameters
#define OVEN_MAX_ON_TIME_SEC	20
#define OVEN_MAX_ON_TIME_MIN	0
#define OVEN_MAX_ON_TIME_HRS	0



#define ACENDE_LED               0
#define APAGA_LED                1

//-------------------------------------- Global Variables ----------------------------------------------------------------

unsigned char Timer_Counter;
unsigned char Toggle;             // VARIÁVEL PARA PISCAR TODOS OS LEDS QUANDO INICIA CONTAGEM DE TEMPO DE FORNO LIGADO
unsigned char Trigger;            // INDICA SE O FORNO ESTÁ LIGADO
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


void Appl__Initialize(void)
{
	User_Action = EVENTS_NO_EVENT;
	Timer_Counter = TIME_IN_50MS_BASE;
}

void Appl__Handler(void)
{
	User_Action = Display__GetEvent();
	if (User_Action != EVENTS_NO_EVENT)
	{
		switch(User_Action)
		{
			case KEY_GROUND_FLOOR:
				Hal__SetBuzzerFreq(4000);
				Sounds__PlaySounds(SOUND_KEY_PRESS);
				Floor_position = GROUND_STATE;
				OvenPosition__SetSolicitation(GROUND);
			break;
		
			case KEY_FIRST_FLOOR:
				Hal__SetBuzzerFreq(4000);
				Sounds__PlaySounds(SOUND_KEY_PRESS);
				Floor_position = FIRST_STATE;
				OvenPosition__SetSolicitation(FIRST);
			break;
			
			case KEY_NEXT_FLOOR:
				Hal__SetBuzzerFreq(4000);
				Sounds__PlaySounds(SOUND_KEY_PRESS);
				if (Floor_position == GROUND_STATE)
				{
					PortSensor__Movie(CLOSED);
					OvenPosition__SetSolicitation(FIRST);
				}
				if (Floor_position == FIRST_STATE)
				{
					PortSensor__Movie(CLOSED);
					OvenPosition__SetSolicitation(GROUND);
				}
			break;
			
			default:
			break;
		}//fim do switch
	}
}// fim do Appl_Handler


/*void Appl__Handler(void)
{//unsigned short int ad_value;
	
	User_Action = Display__GetEvent();
	if (User_Action != EVENTS_NO_EVENT)
	{
		switch(User_Action)
		{
			case KEY_OFF_EVENT:
			Display__SetState(OVEN_OFF);
			OvenTempControl__SetLevel(TEMP_LEVEL_OVEN_OFF);
		    Hal__SetBuzzerFreq(4000);
			Sounds__PlaySounds(SOUND_KEY_PRESS);    //buzzer de key press
			Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, 0,0,0);
			Trigger = FALSE;
			break;
				
			case KEY_MIN_EVENT:
			Display__SetState(OVEN_MIN);
			OvenTempControl__SetLevel(TEMP_LEVEL_MIN);
			Hal__SetBuzzerFreq(2000);
			Sounds__PlaySounds(SOUND_KEY_PRESS);    //buzzer de key press
					  Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, OVEN_MIN_ON_TIME_HRS, OVEN_MIN_ON_TIME_MIN, OVEN_MIN_ON_TIME_SEC);
					  Trigger = TRUE;
				      break;
							
				 case KEY_MED_EVENT:
					  Display__SetState(OVEN_MED);
					  OvenTempControl__SetLevel(TEMP_LEVEL_MED);
				      Hal__SetBuzzerFreq(3000);
					  Sounds__PlaySounds(SOUND_KEY_PRESS);    //buzzer de key press
					  Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, OVEN_MED_ON_TIME_HRS, OVEN_MED_ON_TIME_MIN, OVEN_MED_ON_TIME_SEC);
					  Trigger = TRUE;
					  break;
				
			     case KEY_MAX_EVENT:
				      Display__SetState(OVEN_MAX);
					  OvenTempControl__SetLevel(TEMP_LEVEL_MAX);
					  Hal__SetBuzzerFreq(5000);
					  Sounds__PlaySounds(SOUND_KEY_PRESS);    //buzzer de key press
					  Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, OVEN_MAX_ON_TIME_HRS, OVEN_MAX_ON_TIME_MIN, OVEN_MAX_ON_TIME_SEC);
					  Trigger = TRUE;
				      break;
			     default:
				    break;

			}  //fim switch
		} // fim do if(USER_ACTION...
Display__Handler();

if( (Trigger == TRUE ) &&
((Timer__HMSGetStatus(TIMER_HMS_CYCLE_DURATION) == TIMER_EXPIRED)))
	{
	Sounds__PlaySounds(SOUND_END_CYCLE);
	Display__SetState(OVEN_OFF);
	OvenTempControl__SetLevel(TEMP_LEVEL_OVEN_OFF);
	Trigger = FALSE;
	}

}   // fim do Appl_Handler()*/

//---------------------------------------------------------------------------------------------------------------------



