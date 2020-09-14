/*
 * Display.c
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 


#ifndef OVENPOSITIONCONTROL_H_
#define OVENPOSITIONCONTROL_H_


//-------------------------------------- Include Files ----------------------------------------------------------------
#include <util/delay.h>
#include <Z:\Elevador\Elevador\Elevador\Header\OvenPositionControl_prm.h>

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	OVEN_OFF = 0,
	OVEN_INSIDE,
	OVEN_OUTSIDE_DOWN,
	OVEN_OUTSIDE_UP
}OVEN_POSITION_CONTROL_STATE_TYPE;

typedef enum
{
	GROUND = 0,
	FIRST
}OVEN_POSITION_CONTROL_SOLICITATION_TYPE;

typedef enum
{
	FIRST_OPEN = 0,
	SECOND_OPEN
}DOOR_STATE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void OvenPositionControl__Initialize(void);
void OvenPositionControl__Handler(void);
void OvenPosition__SetSolicitation(OVEN_POSITION_CONTROL_SOLICITATION_TYPE state);

#endif /* OVENPOSITIONCONTROL_H_ */