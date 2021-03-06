/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Micro.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Timer.h>
#include <util/delay.h>   //para incluir rotina _delay_ms()

//--------------------defines---------------------
#define POWER_ON_SOUND   0
#define KEY_PRESS        1
#define END_CYCLE        2


typedef enum
{
	SOUND_DONE =0,
	SOUND_PLAYING=1 
}SOUND_STATUS;


typedef enum
{
	POWER_ON_SOUND_STEP1 = 0,
	POWER_ON_SOUND_STEP2,
	POWER_ON_SOUND_STEP3,
	POWER_ON_SOUND_STEP4,
	POWER_ON_SOUND_STEP5,
	POWER_ON_SOUND_STEP6
}POWER_ON_SOUND_STEPS;

typedef enum
{
	KEY_PRESS_SOUND_STEP1 = 0,
	KEY_PRESS_SOUND_STEP2
}KEY_PRESS_SOUND_STEPS;

typedef enum
{
	END_CYCLE_SOUND_STEP_OFF = 0,
	END_CYCLE_SOUND_STEP_ON
}END_CYCLE_SOUND_STEPS;




//-----------------------Globais -----------------

SOUNDS_TYPE PlaySound;
KEY_PRESS_SOUND_STEPS Key_Press_Sound_Step;
POWER_ON_SOUND_STEPS PowerON_Sound_Step;
END_CYCLE_SOUND_STEPS End_Cycle_Sound_Step;

unsigned char EndCycleSound_Counter = 0;

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------
SOUND_STATUS PowerOnSoundHandler(void);
SOUND_STATUS KeyPressSoundHandler(void);
SOUND_STATUS EndCycleSoundHandler(void);

//*********************************************************
//
//   Esta rotina inicializa a vari�vel global Playsound
//   para sem som
//
//*********************************************************
 void Sounds__Initialize(void)
{
PlaySound = PLAY_NO_SOUND;   // vari�vel global => sem som no in�cio
PowerON_Sound_Step = POWER_ON_SOUND_STEP1;
Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
}

//*********************************************************
//
//   Esta rotina  roda no SLOT1 e verifica se j� finalizou o tempo do som
//   em fun��o do tipo de som
//
//*********************************************************
 
void Sounds__Background(void)
{
switch (PlaySound)
	{
	case SOUND_POWER_ON:
		if(PowerOnSoundHandler() == SOUND_DONE)
			{
			PlaySound = PLAY_NO_SOUND;
			}
		break;

	case SOUND_KEY_PRESS:
		if(KeyPressSoundHandler() == SOUND_DONE)
			{
			//	Hal__SetAllLeds(LED_ON);  // depura��o
			PlaySound = PLAY_NO_SOUND;    
			}
		break;

	case SOUND_END_CYCLE:
		if(EndCycleSoundHandler() == SOUND_DONE)
			{
			PlaySound = PLAY_NO_SOUND;  
			}
		break;
	
	case PLAY_NO_SOUND:
		Hal__SetBuzzer(OFF);
		break;
	default:
	   	break;

	}
}






//*********************************************************
//
//   Esta rotina  atualiza a vari�vel global PlaySound
//
//*********************************************************
 

void Sounds__PlaySounds( SOUNDS_TYPE sound_id)
{
PlaySound = PLAY_NO_SOUND;

if(sound_id < NUM_OF_SOUNDS)
   	PlaySound = sound_id;
}

//*********************************************************
//
//   Esta rotina  devolve o valor da vari�vel global PlaySound
//
//*********************************************************
 SOUNDS_TYPE Sounds__GetSounds( void)
{
	return (PlaySound);
}





//=====================================================================================================================
//-------------------------------------- Private Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/*
SOUND_STATUS PowerOnSoundHandler(void)
{
SOUND_STATUS status;
status = SOUND_PLAYING;
Hal__SetBuzzerFreq(4000);
Hal__SetBuzzer(ON);
_delay_ms(2000);
Hal__SetBuzzer(OFF);

status = SOUND_DONE;
return status;
}
*/


SOUND_STATUS PowerOnSoundHandler(void)
{
SOUND_STATUS status;
status = SOUND_PLAYING;
Hal__SetBuzzerFreq(5000);

switch (PowerON_Sound_Step)
{
case POWER_ON_SOUND_STEP1:
	Hal__SetBuzzer(ON);  // aqui entra
	//_delay_ms(2000);
    Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
	PowerON_Sound_Step = POWER_ON_SOUND_STEP2;
	break;

case POWER_ON_SOUND_STEP2:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
		Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);	
		//	Hal__SetBuzzer(ON);    // n�o entra aqui  !!!
		//_delay_ms(2000);
		PowerON_Sound_Step = POWER_ON_SOUND_STEP3;
		Hal__SetBuzzer(OFF);
		}
	break;  

case POWER_ON_SOUND_STEP3:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
	    Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
		PowerON_Sound_Step = POWER_ON_SOUND_STEP4;
		//Hal__SetBuzzerFreq(4000);   //mudar frequencia do PWM
		Hal__SetBuzzer(ON);
		//Hal__SetLed(LED_1, LED_ON);   //depura��o
		//_delay_ms(2000);
	    }
	break;
	
case POWER_ON_SOUND_STEP4:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
	    Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
		PowerON_Sound_Step = POWER_ON_SOUND_STEP5;
		Hal__SetBuzzer(OFF);
		//Hal__SetLed(LED_1, LED_OFF);
		//_delay_ms(2000);
		}
	break;
	
case POWER_ON_SOUND_STEP5:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
	    Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
		PowerON_Sound_Step = POWER_ON_SOUND_STEP6;
		//Hal__SetBuzzerFreq(4000);
		Hal__SetBuzzer(ON);
		//Hal__SetLed(LED_1, LED_ON);
		//_delay_ms(2000);
		}
	break;
	
case POWER_ON_SOUND_STEP6:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
		PowerON_Sound_Step = POWER_ON_SOUND_STEP1;
		Hal__SetBuzzer(OFF);
		//Hal__SetLed(LED_1, LED_OFF);
		status = SOUND_DONE;
		}
	break;

default:
	PowerON_Sound_Step = POWER_ON_SOUND_STEP1;
	status = SOUND_DONE;
	break;
}
return status;
}




/*
SOUND_STATUS KeyPressSoundHandler(void)
{
SOUND_STATUS status;

status = SOUND_PLAYING;
Hal__SetBuzzerFreq(4000);
Hal__SetBuzzer(ON);
_delay_ms(1000);
Hal__SetBuzzer(OFF);
status = SOUND_DONE;
return status;
}
*/

//---------------------------------------------------------------------------------------------------------------------
SOUND_STATUS KeyPressSoundHandler(void)
{
SOUND_STATUS status;
status = SOUND_PLAYING;
//Hal__SetBuzzerFreq(4000);
	
switch(Key_Press_Sound_Step)
	{
	case KEY_PRESS_SOUND_STEP1:
		Timer__HMSSet(TIMER_HMS_KEY_PRESS_SOUND, 0,0,1);
		Hal__SetBuzzer(ON);
		Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP2;
		break;

	case KEY_PRESS_SOUND_STEP2:
		if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_SOUND) == TIMER_EXPIRED)
		{
			Hal__SetBuzzer(OFF);
			Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
			status = SOUND_DONE;
		}
		break;
	default:
		Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
		status = SOUND_DONE;
		break;
	}
	
return status;
}


/*
SOUND_STATUS EndCycleSoundHandler(void)
{
SOUND_STATUS status;

status = SOUND_PLAYING;
Hal__SetBuzzerFreq(4000);
Hal__SetBuzzer(ON);
_delay_ms(2000);
Hal__SetBuzzer(OFF);

status = SOUND_DONE;
return status;
}
*/


/*
SOUND_STATUS EndCycleSoundHandler(void)
{
	SOUND_STATUS status;
	status = SOUND_PLAYING;
	Hal__SetBuzzerFreq(4000);
	//if(EndCycleSound_Counter%2 == 0)
	//{
		//Hal__SetBuzzerFreq(END_CYCLE_BUZZER_FREQ1);
	//}
	//else
	//{
	//	Hal__SetBuzzerFreq(END_CYCLE_BUZZER_FREQ2);
	//}
	
	switch(End_Cycle_Sound_Step)
	{
		case END_CYCLE_SOUND_STEP_ON:
		Hal__SetBuzzer(ON);
		_delay_ms(2000);
		if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
		    Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,10);
			Hal__SetBuzzer(ON);
			End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_OFF;
		}
		break;

		case END_CYCLE_SOUND_STEP_OFF:
		if(Timer__HMSGetStatus(TIMER_HMS_END_CYCLE_SOUND) == TIMER_EXPIRED)
		{
		Timer__HMSSet(TIMER_HMS_END_CYCLE_SOUND, 0,0,20);
			Hal__SetBuzzer(OFF);
			End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
			//EndCycleSound_Counter++;
		}
		break;
		
		default:
		Key_Press_Sound_Step = KEY_PRESS_SOUND_STEP1;
		status = SOUND_DONE;
		//EndCycleSound_Counter = 0;
		break;
	}
	
	//if(EndCycleSound_Counter >= MAX_END_CYCLE_SOUND_COUNTER)
	//{
	//	EndCycleSound_Counter = 0;
	//	Hal__SetBuzzer(OFF);
	//	status = SOUND_DONE;
	//}
	
	return status;
}
*/

SOUND_STATUS EndCycleSoundHandler(void)
{
SOUND_STATUS status;
status = SOUND_PLAYING;
//Hal__SetBuzzerFreq(4000);
	
switch(End_Cycle_Sound_Step)
	{
	case END_CYCLE_SOUND_STEP_ON:
		Timer__HMSSet(TIMER_HMS_END_CYCLE_SOUND, 0,0,3);
		Hal__SetBuzzer(ON);
		//_delay_ms(2000);
		End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_OFF;
		break;

	case END_CYCLE_SOUND_STEP_OFF:
	//Hal__SetBuzzer(ON);
	//_delay_ms(2000);
		if(Timer__HMSGetStatus(TIMER_HMS_END_CYCLE_SOUND) == TIMER_EXPIRED)
			{
			Hal__SetBuzzer(OFF);
			End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
			status = SOUND_DONE;
			}
		break;
	default:
		End_Cycle_Sound_Step = END_CYCLE_SOUND_STEP_ON;
		status = SOUND_DONE;
		break;
	}
	
return status;
}