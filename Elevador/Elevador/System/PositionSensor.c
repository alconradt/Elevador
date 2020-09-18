/*
 * Display.c
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PositionSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

unsigned short int Position[NUM_OF_POSITION_SENSOR];

const unsigned char PositionSensorTable[NUM_OF_POSITION_SENSOR] = POSITION_SENSOR_CONFIG;
const unsigned char PositionSensor_Enable_Table[NUM_OF_POSITION_SENSOR]= {USE_POSITION_SENSOR_1, USE_POSITION_SENSOR_2};
	
//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

void PositionSensor__Initialize(void)
{
	POSITION_SENSOR_TYPE sensor_id;

	for (sensor_id = 0; sensor_id < NUM_OF_POSITION_SENSOR; sensor_id++)
	{
		Position[sensor_id] = 0;

	}
}

//---------------------------------------------------------------------------------------------------------------------
void PositionSensor__ConversionHandler(void)
{
	unsigned short int ad_value;      // variavel para calculos
	POSITION_SENSOR_TYPE sensor_id;   // identificador do sensor
	
	for (sensor_id = 0; sensor_id < NUM_OF_POSITION_SENSOR; sensor_id++)
	{
		if(PositionSensor_Enable_Table[sensor_id] == ENABLED)
		{
			ad_value = Hal__GetAnalogInput(PositionSensorTable[sensor_id]); //ad_value em valor digital
			Position[sensor_id] = ad_value;
		}
		
	}
	
}

//---------------------------------------------------------------------------------------------------------------------
unsigned short int PositionSensor__GetMeters(POSITION_SENSOR_TYPE sensor_id)
{
	if (sensor_id < NUM_OF_POSITION_SENSOR)
	{
		return Position[sensor_id];
	}
	else
	{
		return 0;
	}
	
}