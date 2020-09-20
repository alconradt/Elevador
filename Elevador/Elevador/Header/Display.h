/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

#ifndef DISPLAY_H_
#define DISPLAY_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Display_prm.h>


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	STOPED = 0,
	MOTOR_UP,
	MOTOR_DOWN,
	DOOR_OPEN,
	DOOR_CLOSE,
	NUM_OF_OVEN_STATES
}OVEN_DISPLAY_STATE_TYPE;

typedef enum
{
	KEY_GROUND_FLOOR = 0,
	KEY_FIRST_FLOOR,
	KEY_NEXT_FLOOR,
	NUM_OF_KEYS_EVENTS
}KEY_SOLICITATION_TYPE;

typedef enum
{
	GROUND_FLOOR = 0,
	FIRST_FLOOR
}FLOOR_TYPE;

#define KEY_NONE		0xAA
#define EVENTS_NO_EVENT 0xFF




//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void Display__Initialize(void);
void Display__Handler(void);
void Display__SetState(OVEN_DISPLAY_STATE_TYPE state);
KEY_SOLICITATION_TYPE Display__GetEvent(void);



#endif /* DISPLAY_H_ */
