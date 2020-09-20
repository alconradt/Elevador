/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
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
KEY_SOLICITATION_TYPE User_Action; //Ação solicitada pelo usuário 
FLOOR_STATE Floor_position; //Piso onde o usuário fez a solicitação de acesso ao elevador
SENSOR_STATUS People; //Váriavel que indica o status do sensor da porta (Se a porta está aberta e alguém está manuseando o elevador ou não)
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
//-------------------------------------- Função de inicialização ------------------------------------------------------
//=====================================================================================================================


void Appl__Initialize(void)
{
	User_Action = EVENTS_NO_EVENT; //Inicializa sem solicitações de eventos pelo usuário
}

//=====================================================================================================================
//-------------------------------------- Função Handler------------------------------------------------------
//=====================================================================================================================

void Appl__Handler(void)
{
	User_Action = Display__GetEvent(); //Verifica se houve solicitação do usuário
	People = ReadSensor(); //Verifica se a pessoas operando o elevador de cargas no momento
	if (User_Action != EVENTS_NO_EVENT && People==NO_PEOPLE) //Se houve solicitação e o elevador não está em uso no momento...
	{
		switch(User_Action)
		{
			case KEY_GROUND_FLOOR:
				Hal__SetBuzzerFreq(4000); //Configura frequência do buzzer
				Sounds__PlaySounds(SOUND_KEY_PRESS); //Aciona som de button precionado
				Floor_position = GROUND_STATE; //Atualiza o andar da solicitação
				OvenPosition__SetSolicitation(GROUND); //Atualiza o andar em que o elevador deve estar 
			break;
		
			case KEY_FIRST_FLOOR:
				Hal__SetBuzzerFreq(4000); //Configura frequência do buzzer
				Sounds__PlaySounds(SOUND_KEY_PRESS); //Aciona som de button precionado
				Floor_position = FIRST_STATE; //Atualiza o andar da solicitação
				OvenPosition__SetSolicitation(FIRST); //Atualiza o andar em que o elevador deve estar 
			break;
			
			case KEY_NEXT_FLOOR: //Solicitação de iniciar a passagem para o próximo andar, este evento ocorre após o elevador chegar no andar solicitado em KEY_GROUND_FLOOR / KEY_FIRST_FLOOR
				Hal__SetBuzzerFreq(4000);
				Sounds__PlaySounds(SOUND_KEY_PRESS);
				if (Floor_position == GROUND_STATE) //Se a solicitação foi do térreo, o elevador irá para o primeiro andar
				{
					//PortSensor__Movie(CLOSED); //Chama rotina para fechar a porta (NÃO USADO) -> O elevador de carga não possui porta automatizada 
					OvenPosition__SetSolicitation(FIRST); //Chama rotina que acionará os motores
				}
				if (Floor_position == FIRST_STATE)
				{
					//PortSensor__Movie(CLOSED); //Chama rotina para fechar a porta (NÃO USADO)
					OvenPosition__SetSolicitation(GROUND); //Chama rotina que acionará os motores
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



