/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Display.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PositionSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PortSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\OvenPositionControl.h>

//-------------------------------------- Global Variables ----------------------------------------------------------------

OVEN_POSITION_CONTROL_STATE_TYPE Oven_PositionControl_State; //Variável que indica se o elevador está fora de posição 
OVEN_POSITION_CONTROL_SOLICITATION_TYPE Oven_PositionControl_Solicitation; //Variável com a posição que o elevador precisa estar 
DOOR_STATE Door_state; //Status da porta do elevador 

//-------------------------------------- Private Variables ----------------------------------------------------------------

unsigned short int current_position;

//---------------------------------------------------------------------------------------------------------------------
void OvenPositionControl__Initialize(void) //Inicia sem eventos de controle de posição do elevador 
{
	Oven_PositionControl_State = OVEN_OFF;
}

void OvenPosition__SetSolicitation(OVEN_POSITION_CONTROL_SOLICITATION_TYPE state) //Esta rotina é responsável por verificar se o elevador está no andar correto 
{
	Oven_PositionControl_Solicitation = state; //Andar solicitado pelo usuário 
	
	current_position = PositionSensor__GetMeters(POSITION_SENSOR_1); //Leitura do sensor de posição do elevador 
	if(Oven_PositionControl_Solicitation == GROUND)
	{
		if(POSITION_GROUND_MAX >= current_position)
		{
			Oven_PositionControl_State = OVEN_INSIDE; //Entra nesta condição se a solicitação foi do térreo e o elevador já estava no térreo 
		}
		else
		{
			Oven_PositionControl_State = OVEN_OUTSIDE_UP; //Caso não esteja no térreo, o elevador se encontra fora de posição 
		}
	}
	if(Oven_PositionControl_Solicitation == FIRST)
	{	
		if(current_position >= POSITION_FIRST_MIN)
		{
			Oven_PositionControl_State = OVEN_INSIDE; //Entra nesta condição se a solicitação foi do primeiro piso e o elevador se encontra no primeiro piso 
		}
		else
		{
			Oven_PositionControl_State = OVEN_OUTSIDE_DOWN; //Caso esteja no térreo, o elevador se encontra fora de posição 
		}		
	}
}

void OvenPositionControl__Handler(void) //Esta rotina é chamada pelo slot 4 e dependendo da posição do elevador e do tipo de solicitação, faz o acionamento dos motores 
{
	OvenPosition__SetSolicitation(Oven_PositionControl_Solicitation); //Atualiza se o elevador já chegou no andar desejado 
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