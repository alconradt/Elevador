/*
 * Display.c
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

OVEN_POSITION_CONTROL_STATE_TYPE Oven_PositionControl_State;
OVEN_POSITION_CONTROL_SOLICITATION_TYPE Oven_PositionControl_Solicitation;
DOOR_STATE Door_state; 

//-------------------------------------- Private Variables ----------------------------------------------------------------

unsigned short int current_position;

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


//---------------------------------------------------------------------------------------------------------------------
void OvenPositionControl__Initialize(void)
{
	Oven_PositionControl_State = OVEN_OFF;
}

void OvenPosition__SetSolicitation(OVEN_POSITION_CONTROL_SOLICITATION_TYPE state)
{
	Oven_PositionControl_Solicitation = state;
	
	current_position = PositionSensor__GetMeters(POSITION_SENSOR_1);
	if(Oven_PositionControl_Solicitation == GROUND)
	{
		if(POSITION_GROUND_MAX >= current_position)
		{
			Oven_PositionControl_State = OVEN_INSIDE;
		}
		else
		{
			Oven_PositionControl_State = OVEN_OUTSIDE_UP;
		}
	}
	if(Oven_PositionControl_Solicitation == FIRST)
	{	
		if(current_position >= POSITION_FIRST_MIN)
		{
			Oven_PositionControl_State = OVEN_INSIDE;
		}
		else
		{
			Oven_PositionControl_State = OVEN_OUTSIDE_DOWN;
		}		
	}
}

void OvenPositionControl__Handler(void)
{
	OvenPosition__SetSolicitation(Oven_PositionControl_Solicitation);
	switch(Oven_PositionControl_State)
	{
		case OVEN_INSIDE:
			Display__SetState(STOPED);
			PortSensor__Movie(OPEN);
			if (Door_state = SECOND_OPEN)
			{
				PortSensor__Movie(CLOSED);
			}
			else
			{
				Door_state = SECOND_OPEN;
			}
			Oven_PositionControl_State = OVEN_OFF;
		break;
		
		case OVEN_OUTSIDE_DOWN:
			Display__SetState(MOTOR_UP);		
		break;
		
		case OVEN_OUTSIDE_UP:
			Display__SetState(MOTOR_DOWN);
		break;
		
		case OVEN_OFF:
		
		break;
		
		default:
		break;
	}
}