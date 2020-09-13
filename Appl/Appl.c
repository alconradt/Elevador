/*
 * Appl.c
 *
 *  Created on: 13/05/2019
 *      Author: MAASDN
 */

//-------------------------------------- Include Files ----------------------------------------------------------------

#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Appl.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Display.h>
//#include <alloca.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Gpio.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Adc.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Timer.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\OvenTempControl.h>

#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Pwm.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Sounds.h>

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_EVENT_TYPE User_Action;

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define EXP_ADC                ENABLED
#define EXP_OVEN               ENABLED

#define EXP_TIMER               DISABLED       // TEMPO em ms
#define EXP_TIMER1              DISABLED       // TEMPO em HMS
#define TIME_IN_50MS_BASE	20 //1s in 50ms time base (20*50ms = 1s)

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
	Toggle = OFF;
	Sounds__PlaySounds(SOUND_POWER_ON);   //buzzer de power on
	Trigger = FALSE;
}


void Appl__Handler(void)
{//unsigned short int ad_value;
	
#if (EXP_OVEN == ENABLED)
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
				//case KEY_NONE:
				//     Sounds__PlaySounds(PLAY_NO_SOUND);    //buzzer de key press
				//	 Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, 0,0,0);
				//	 Trigger = FALSE;  
			  	//	 break;
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

#endif //(EXP_OVEN == ENABLED)

#if (EXP_TIMER == ENABLED)
Timer_Counter--;
switch(Toggle)
{
	case ON:
	Hal__SetLed(LED_0, LED_ON);  
	Hal__SetLed(LED_1, LED_ON); 
	Hal__SetLed(LED_2, LED_ON); 
	if(Timer_Counter == 0)
		{
		Timer_Counter = TIME_IN_50MS_BASE;
		Toggle = OFF;
		}
	break;

	case OFF:
	Hal__SetLed(LED_0, LED_OFF);
	Hal__SetLed(LED_1, LED_OFF);
	Hal__SetLed(LED_2, LED_OFF);
	if(Timer_Counter == 0)
		{
		Timer_Counter = TIME_IN_50MS_BASE;
		Toggle = ON;
		}
	break;
	default:
	Toggle = ON;
	break;
}
#endif //(EXP_TIMER == ENABLED)

#if (EXP_TIMER1 == ENABLED)

switch(Toggle)
{
	case ON:
	
	if(Timer__HMSGetStatus(TIMER_HMS_TEST1)== TIMER_EXPIRED )
		{
		Timer__HMSSet(TIMER_HMS_TEST1,0,0,60);
		Toggle = OFF;
		Hal__SetBuzzer(OFF);
		Hal__SetLed(LED_0, LED_ON);
		Hal__SetLed(LED_1, LED_ON);
		Hal__SetLed(LED_2, LED_ON);
		}
	break;

	case OFF:
	//Hal__SetBuzzer(ON);
	
	if(Timer__HMSGetStatus(TIMER_HMS_TEST1)== TIMER_EXPIRED )
		{
		Timer__HMSSet(TIMER_HMS_TEST1,0,0,60);
		Toggle = ON;
		Hal__SetBuzzerFreq(4000);
		Hal__SetBuzzer(ON);
		Hal__SetLed(LED_0, LED_OFF);
		Hal__SetLed(LED_1, LED_OFF);
		Hal__SetLed(LED_2, LED_OFF);
		}
	break;
	default:
	Toggle = ON;
	break;

}
#endif	//(EXP_TIMER1 == ENABLED)

}   // fim do Appl_Handler()

//---------------------------------------------------------------------------------------------------------------------



