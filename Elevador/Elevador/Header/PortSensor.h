/*
 * PortSensor.h
 *
 * Created: 13/09/2020 21:58:32
 *  Author: andre
 */ 


#ifndef PORTSENSOR_H_
#define PORTSENSOR_H_

#include <Z:\Elevador\Elevador\Elevador\Header\PortSensor_prm.h>

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	PORT_OPEN,
	PORT_CLOSED
}PORT_STATUS;

typedef enum
{
	OPEN = 0,
	CLOSED
}PORT_MOVIE;

typedef enum
{
	NO_PEOPLE = 0,
	PEOPLE	
}SENSOR_STATUS;


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void PortSensor__Initialize(void);
void PortSensor__Movie(PORT_MOVIE action);
SENSOR_STATUS ReadSensor(void); 
PORT_STATUS PortStatus(void);

#endif /* PORTSENSOR_H_ */