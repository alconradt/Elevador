/*
 * OvenPositionControl.h
 *
 * Created: 13/09/2020 16:09:13
 *  Author: andre
 */ 


#ifndef OVENPOSITIONCONTROL_H_
#define OVENPOSITIONCONTROL_H_


//-------------------------------------- Include Files ----------------------------------------------------------------

#include <Z:\Elevador\Elevador\Elevador\Header\OvenPositionControl_prm.h>

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	OVEN_INSIDE = 0,
	OVEN_OUTSIDE
}OVEN_POSITION_CONTROL_STATE_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void OvenPositionControl__Initialize(void);
void OvenPositionControl__Handler(void);

#endif /* OVENPOSITIONCONTROL_H_ */