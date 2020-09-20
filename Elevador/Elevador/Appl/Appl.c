/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------

#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Appl.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Display.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Gpio.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Adc.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Timer.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\OvenPositionControl.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PortSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Pwm.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_SOLICITATION_TYPE User_Action; //A��o solicitada pelo usu�rio 
FLOOR_STATE Floor_position; //Piso onde o usu�rio fez a solicita��o de acesso ao elevador
SENSOR_STATUS People; //V�riavel que indica o status do sensor da porta (Se a porta est� aberta e algu�m est� manuseando o elevador ou n�o)
PORT_STATUS Port_status; //Status da porta -> Aberta ou Fechada 

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

//=====================================================================================================================
//-------------------------------------- Fun��o de inicializa��o ------------------------------------------------------
//=====================================================================================================================


void Appl__Initialize(void)
{
	User_Action = EVENTS_NO_EVENT; //Inicializa sem solicita��es de eventos pelo usu�rio
}

//=====================================================================================================================
//-------------------------------------- Fun��o Handler------------------------------------------------------
//=====================================================================================================================

void Appl__Handler(void)
{
	User_Action = Display__GetEvent(); //Verifica se houve solicita��o do usu�rio
	People = ReadSensor(); //Verifica se a pessoas operando o elevador de cargas no momento
	if (User_Action != EVENTS_NO_EVENT && People==NO_PEOPLE) //Se houve solicita��o e o elevador n�o est� em uso no momento...
	{
		switch(User_Action)
		{
			case KEY_GROUND_FLOOR:
				Hal__SetBuzzerFreq(4000); //Configura frequ�ncia do buzzer
				Sounds__PlaySounds(SOUND_KEY_PRESS); //Aciona som de button precionado
				Floor_position = GROUND_STATE; //Atualiza o andar da solicita��o
				OvenPosition__SetSolicitation(GROUND); //Atualiza o andar em que o elevador deve estar 
			break;
		
			case KEY_FIRST_FLOOR:
				Hal__SetBuzzerFreq(4000); //Configura frequ�ncia do buzzer
				Sounds__PlaySounds(SOUND_KEY_PRESS); //Aciona som de button precionado
				Floor_position = FIRST_STATE; //Atualiza o andar da solicita��o
				OvenPosition__SetSolicitation(FIRST); //Atualiza o andar em que o elevador deve estar 
			break;
			
			case KEY_NEXT_FLOOR: //Solicita��o de iniciar a passagem para o pr�ximo andar, este evento ocorre ap�s o elevador chegar no andar solicitado em KEY_GROUND_FLOOR / KEY_FIRST_FLOOR
				Hal__SetBuzzerFreq(4000);
				Sounds__PlaySounds(SOUND_KEY_PRESS);
				if (Floor_position == GROUND_STATE) //Se a solicita��o foi do t�rreo, o elevador ir� para o primeiro andar
				{
					//PortSensor__Movie(CLOSED); //Chama rotina para fechar a porta (N�O USADO) -> O elevador de carga n�o possui porta automatizada 
					OvenPosition__SetSolicitation(FIRST); //Chama rotina que acionar� os motores
				}
				if (Floor_position == FIRST_STATE)
				{
					//PortSensor__Movie(CLOSED); //Chama rotina para fechar a porta (N�O USADO)
					OvenPosition__SetSolicitation(GROUND); //Chama rotina que acionar� os motores
				}
			break;
			
			default:
			break;
		}//fim do switch
		
		//Atualiza o status da porta
		if(People==NO_PEOPLE)
		{
			Hal__SetLed(LED_2,ACENDE_LED);
			Port_status = PORT_CLOSED;
		}
		else
		{
			Hal__SetLed(LED_2,APAGA_LED);
			Port_status = PORT_OPEN;
		}
	}
}// fim do Appl_Handler


//---------------------------------------------------------------------------------------------------------------------



