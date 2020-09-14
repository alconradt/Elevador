/*
 * Display.c
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <Z:\Elevador\Elevador\Elevador\Header\C_Types.h>
#include <Z:\Elevador\Elevador\Elevador\Header\PortSensor.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Hal.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Sounds.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Timer.h>

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
		Timer__HMSSet(TIMER_HMS_POWER_ON_SOUND, 0,0,1);
		Hal__SetLed(LED_2,APAGA_LED);
		Port_status = PORT_OPEN;
	}
	else
	{
		People = ReadSensor();
		if (People==NO_PEOPLE && Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SOUND) == TIMER_EXPIRED)
		{
			Hal__SetLed(LED_2,ACENDE_LED);
			Port_status = PORT_CLOSED;
		}
		else
		{
			//Hal__SetBuzzerFreq(2000);
			//Sounds__PlaySounds(SOUND_KEY_PRESS);
		}
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