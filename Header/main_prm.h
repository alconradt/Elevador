/*
 * main_prm.h
 *
 *  Created on: 04/09/2017
 *      Author: MAASDN
 */

#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_
//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\C_Types.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Appl.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Display.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Gpio.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Adc.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Timer.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\TempSensor.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\OvenTempControl.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Pwm.h>
#include <D:\Materias_UDESC\AAM\AAM_EXP4\LAB4_TIMER\Header\Sounds.h>
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
	TempSensor__Initialize();\
	OvenTempControl__Initialize();\
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
	TempSensor__ConversionHandler();\
}
	
#define SLOT_4_TASKS()\
{\
	OvenTempControl__Handler();\
}
	
#define SLOT_5_TASKS()\
{\	
}




	



#endif /* MAIN_PRM_H_ */
