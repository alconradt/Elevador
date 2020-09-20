/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 


#ifndef OVENPOSITIONCONTROL_PRM_H_
#define OVENPOSITIONCONTROL_PRM_H_

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

//Configures the related sensor to be used on Position Control
#define OVEN_RELATED_SENSOR		POSITION_SENSOR_1      // TEMP_SENSOR_1

//GROUND FLOOR Set Point
#define POSITION_GROUND_MIN	    0 //mm
#define POSITION_GROUND_MAX	  500 //mm

//FIRST FLOOR Set Point
#define POSITION_FIRST_MIN	  501 //mm
#define POSITION_FIRST_MAX	  1024 //mm


#endif /* OVENPOSITIONCONTROL_PRM_H_ */