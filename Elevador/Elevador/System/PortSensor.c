/*
 * Display.c
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PortSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>

PORT_MOVIE Port_movie; 
SENSOR_STATUS Sensor_status;
SENSOR_STATUS People;
PORT_STATUS Port_status;

void PortSensor__Initialize(void)
{
	Hal__SetLed(LED_2,APAGA_LED);
	Port_status = PORT_CLOSED;
}

void PortSensor__Movie(PORT_MOVIE action)
{
	Port_movie = action; 
	if (Port_movie == OPEN)
	{
		Hal__SetLed(LED_2,ACENDE_LED);
		Port_status = PORT_OPEN;
	}
	else
	{
		Hal__SetLed(LED_2,APAGA_LED);
		Port_status = PORT_CLOSED;
	}
}

SENSOR_STATUS ReadSensor(void)
{
	Sensor_status = Hal__ReadKey(KEY_3); 
	return(Sensor_status);
}

PORT_STATUS PortStatus(void)
{
	return(Port_status);
}