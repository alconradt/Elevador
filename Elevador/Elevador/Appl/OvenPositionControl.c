/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Display.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PositionSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PortSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\OvenPositionControl.h>

//-------------------------------------- Global Variables ----------------------------------------------------------------

OVEN_POSITION_CONTROL_STATE_TYPE Oven_PositionControl_State; //Vari�vel que indica se o elevador est� fora de posi��o 
OVEN_POSITION_CONTROL_SOLICITATION_TYPE Oven_PositionControl_Solicitation; //Vari�vel com a posi��o que o elevador precisa estar 
DOOR_STATE Door_state; //Status da porta do elevador 

//-------------------------------------- Private Variables ----------------------------------------------------------------

unsigned short int current_position;

//---------------------------------------------------------------------------------------------------------------------
void OvenPositionControl__Initialize(void) //Inicia sem eventos de controle de posi��o do elevador 
{
	Oven_PositionControl_State = OVEN_OFF;
}

void OvenPosition__SetSolicitation(OVEN_POSITION_CONTROL_SOLICITATION_TYPE state) //Esta rotina � respons�vel por verificar se o elevador est� no andar correto 
{
	Oven_PositionControl_Solicitation = state; //Andar solicitado pelo usu�rio 
	
	current_position = PositionSensor__GetMeters(POSITION_SENSOR_1); //Leitura do sensor de posi��o do elevador 
	if(Oven_PositionControl_Solicitation == GROUND)
	{
		if(POSITION_GROUND_MAX >= current_position)
		{
			Oven_PositionControl_State = OVEN_INSIDE; //Entra nesta condi��o se a solicita��o foi do t�rreo e o elevador j� estava no t�rreo 
		}
		else
		{
			Oven_PositionControl_State = OVEN_OUTSIDE_UP; //Caso n�o esteja no t�rreo, o elevador se encontra fora de posi��o 
		}
	}
	if(Oven_PositionControl_Solicitation == FIRST)
	{	
		if(current_position >= POSITION_FIRST_MIN)
		{
			Oven_PositionControl_State = OVEN_INSIDE; //Entra nesta condi��o se a solicita��o foi do primeiro piso e o elevador se encontra no primeiro piso 
		}
		else
		{
			Oven_PositionControl_State = OVEN_OUTSIDE_DOWN; //Caso esteja no t�rreo, o elevador se encontra fora de posi��o 
		}		
	}
}

void OvenPositionControl__Handler(void) //Esta rotina � chamada pelo slot 4 e dependendo da posi��o do elevador e do tipo de solicita��o, faz o acionamento dos motores 
{
	OvenPosition__SetSolicitation(Oven_PositionControl_Solicitation); //Atualiza se o elevador j� chegou no andar desejado 
	switch(Oven_PositionControl_State)
	{
		case OVEN_INSIDE: //Atualiza o status do elevador caso tenha chegado no andar desejado 
			Display__SetState(STOPED);
			/*PortSensor__Movie(OPEN);
			if (Door_state = SECOND_OPEN)
			{
				PortSensor__Movie(CLOSED);
			}
			else
			{
				Door_state = SECOND_OPEN;
			}*/
			Oven_PositionControl_State = OVEN_OFF;
		break;
		
		case OVEN_OUTSIDE_DOWN:
			Display__SetState(MOTOR_UP); //Aciona motor de subida	
		break;
		
		case OVEN_OUTSIDE_UP:
			Display__SetState(MOTOR_DOWN); //Aciona motor de decida
		break;
		
		case OVEN_OFF:
			Display__SetState(STOPED);
		break;
		
		default:
		break;
	}
}