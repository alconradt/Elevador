/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 


#ifndef POSITIONSENSOR_H_
#define POSITIONSENSOR_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PositionSensor_prm.h>

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	POSITION_SENSOR_1 = 0,
	POSITION_SENSOR_2,
	NUM_OF_POSITION_SENSOR
}POSITION_SENSOR_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void PositionSensor__Initialize(void);
unsigned short int PositionSensor__GetMeters(POSITION_SENSOR_TYPE sensor_id);
void PositionSensor__ConversionHandler(void); 





#endif /* POSITIONSENSOR_H_ */