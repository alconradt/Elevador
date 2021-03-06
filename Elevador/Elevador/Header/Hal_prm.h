/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 

#ifndef HAL_PRM_H_
#define HAL_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_Types.h>


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

//-------------------------------------------------------------------------------------------
// --------------------------------- ON BOARD LEDs CONFIGURATION ----------------------------
//-------------------------------------------------------------------------------------------
//On board LEDs configuration
// Select ENABLED for LEDs that will be used otherwise DISABLED

#define USE_LED_0		ENABLED
#define USE_LED_1		ENABLED
#define USE_LED_2		ENABLED
#define USE_LED_3		ENABLED


//-------------------------------------------------------------------------------------------
// ---------------------------------  KEYS CONFIGURATION ----------------------------------
//-------------------------------------------------------------------------------------------
//On board Keys configuration
// Select ENABLED for Keys that will be used otherwise DISABLED
#define USE_KEY_0		ENABLED	
#define USE_KEY_1		ENABLED	
#define USE_KEY_2		ENABLED	
#define USE_KEY_3		ENABLED

//-------------------------------------------------------------------------------------------
// ---------------------------------  AD CONFIGURATION ------------------------------------
//-------------------------------------------------------------------------------------------
#define USE_POT_IN		DISABLED
#define USE_POT_OUT     ENABLED

#define HAL_ANALOG_MODE	    	MODE_10BITS//MODE_8BITS //MODE_10BITS //MODE_12BITS
#define HAL_CONVERSION_METHOD	AD_CONTINUOUS_CONVERSION//AD_SINGLE_CONVERSION //AD_CONTINUOUS_CONVERSION


//On board Analog configuration
// Select ENABLED for analog that will be used otherwise DISABLED
//PTB2 AD CH0 (Analog 0 - Pot)
//PTD1 AD CH1 (Analog 1 - Pot)


//#define USE_POT_INPUT_1		
//#define USE_ACCEL_AXIS_X	ENABLED
//#define USE_ACCEL_AXIS_Y	ENABLED
//#define USE_ACCEL_AXIS_Z	ENABLED


//Use table below to link each analog input configured as enabled with its respective AD channel (AD_CHx) as per 
// enumeration defined in ADC.h
#define HAL_ANALOG_CHANNEL_CONFIG\
	{\
	AD_CH0,\
	AD_CH1,\
	AD_CH2,\
	AD_CH3,\
	AD_CH4,\
	AD_CH5\
	}	

//-------------------------------------------------------------------------------------------
// --------------------------------- BUZZER CONFIGURATION ------------------------------------
//-------------------------------------------------------------------------------------------

#define USE_BUZZER				ENABLED  //	DISABLED		 
#define BUZZER_DEFAULT_ON_DUTY	50 //100%
#define BUZZER_OFF_DUTY	    0 //0%	
#define BUZZER_DEFAULT_FREQ		6000 //Hz
//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

#endif /* HAL_PRM_H_ */
