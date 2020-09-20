/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 


#ifndef POSITIONSENSOR_PRM_H_
#define POSITIONSENSOR_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
//On board Temp Sensor configuration
// Select ENABLED for sensor that will be used otherwise DISABLED
#define USE_POSITION_SENSOR_1		ENABLED
#define USE_POSITION_SENSOR_2		DISABLED


//Use table below to link each Temperature Sensor input configured as enabled with its respective Analog Input) as per
// enumeration defined in HAL.h
#define POSITION_SENSOR_CONFIG \
{\
	POT_INT, 	/*POSITION_SENSOR_1*/\
	POT_EXT,  	/*POSITION_SENSOR_2*/\
}




#endif /* POSITIONSENSOR_PRM_H_ */