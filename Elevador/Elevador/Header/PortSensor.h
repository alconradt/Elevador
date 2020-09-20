/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

#ifndef PORTSENSOR_H_
#define PORTSENSOR_H_

#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PortSensor_prm.h>

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