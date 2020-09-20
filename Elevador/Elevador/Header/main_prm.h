/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 

#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_
//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Appl.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Display.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Gpio.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Adc.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Timer.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\PositionSensor.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\OvenPositionControl.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Pwm.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>
//-------------------------------------- Defines ----------------------------------------------------------------

// Select ENALBED to use a fixed slot time duration for each main slot, otherwise select DISABLED
// If ENALBED, need to define the slot time duration in SLOT_TIME parameters below
#define USE_FIXED_TIME_SLOT	ENABLED //ENABLED//

// Define the fixed time slot duration
// Each slot in main loop will take SLOT_TIME before switch to next slot 
// Use _1MS for 1ms, _5MS for 5ms or _10MS for 10ms 
#define SLOT_TIME	 _1MS	//_1MS  // _4MS  // _10MS  

// ENABLED or DISABLED the Watchdog
#define WATCHDOG_ENABLE  	 ENABLED// //DISABLED

//#define INITIALIZE_TASKS()\
{\
	Pwm__Initialize();\
}


#define INITIALIZE_TASKS()\
{\
	ADC__Initialize();\
	Pwm__Initialize();\
	Hal__Initialize();\
	Display__Initialize();\
	Timer__Initialize();\
	Sounds__Initialize();\
	PositionSensor__Initialize();\
	OvenPositionControl__Initialize();\
	Appl__Initialize();\
	}

//#define ALL_SLOTS_TASKS()\
{\
	Hal__FastHandler();\
}


#define ALL_SLOTS_TASKS()\
{\
	Timer__HMSHandler();\
	Hal__FastHandler();\
}


#define SLOT_1_TASKS()\
{\
	Sounds__Background();\
	Hal__BackgroundHandler();\
}

#define SLOT_2_TASKS()\
{\
	Appl__Handler();\
}
	
#define SLOT_3_TASKS()\
{\
	ADC__Handler();\
	PositionSensor__ConversionHandler();\
}
	
#define SLOT_4_TASKS()\
{\
	OvenPositionControl__Handler();\
}
	
#define SLOT_5_TASKS()\
{\	
	UpdateDisplaySevenSeg();\
	UpdateDisplayLeds();\
}




	



#endif /* MAIN_PRM_H_ */
