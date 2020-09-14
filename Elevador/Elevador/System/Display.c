/*
 * Display.c
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */


//-------------------------------------- Include Files ----------------------------------------------------------------
#include <Z:\Elevador\Elevador\Elevador\Header\C_Types.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Display.h>
#include <Z:\Elevador\Elevador\Elevador\Header\Hal.h>S
#include <Z:\Elevador\Elevador\Elevador\Header\PositionSensor.h>
#include <Z:\Elevador\Elevador\Elevador\Header\OvenPositionControl.h>
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

#define NUM_EVENTS     	   50
#define ACENDE_LED          0
#define APAGA_LED           1
#define NUM_OF_SEG			4      // número de segmentos do Display 7 segmentos
#define TRUE				1


//-------------------------------------- Global Variables ----------------------------------------------------------------

OVEN_DISPLAY_STATE_TYPE Oven_Display_State;      // variável global  de display

KEY_SOLICITATION_TYPE Display_Keys_Map;                  // variável global  de keys

FLOOR_TYPE Segment_Floor_State; // variável global  de 7 segmentos
	
char GROUD_DIGIT[NUM_OF_SEG] = {0xC0,0xC0,0xC0,0xC0};   //# 0190
char FIRST_DIGIT[NUM_OF_SEG] =  {0xC0,0xC0,0xC0,0xF9};  //# 0290


//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------

void UpdateDisplayLeds(void);
void UpdateDisplaySevenSeg(void);
void ReadDisplayKeys(void);


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void Display__Initialize(void)
{
	Oven_Display_State = STOPED; //Inicialmente o elevador encontra-se parado
	//Display_Keys_Map = KEY_OFF_EVENT;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void Display__Handler(void)
{
ReadDisplayKeys();
UpdateDisplayLeds();
UpdateDisplaySevenSeg();
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void Display__SetState(OVEN_DISPLAY_STATE_TYPE state)
{
	if(state < NUM_OF_OVEN_STATES)
	{
		Oven_Display_State = state;
	}
	
}

KEY_SOLICITATION_TYPE Display__GetEvent(void)
{
	KEY_SOLICITATION_TYPE event;
	ReadDisplayKeys();    // Lê as chaves e coloca valor na variável global Display_Keys_Map
	event = Display_Keys_Map;
	return (event);
	
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
//=====================================================================================================================
//-------------------------------------- PRIVATE Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *  Atualiza  Leds 
 */
void UpdateDisplayLeds(void)
{
	unsigned short int ad_value;
	switch(Oven_Display_State)
	{
		case STOPED:
			Hal__SetLed(LED_0, APAGA_LED);
			Hal__SetLed(LED_1, APAGA_LED);
			Hal__SetLed(LED_2, ACENDE_LED);
	    break;
		
		case MOTOR_UP:
			Hal__SetLed(LED_0, ACENDE_LED);
			Hal__SetLed(LED_1, APAGA_LED);
			Hal__SetLed(LED_2, ACENDE_LED);
	    break;
		
		case MOTOR_DOWN:
			Hal__SetLed(LED_0, APAGA_LED);
			Hal__SetLed(LED_1, ACENDE_LED);
			Hal__SetLed(LED_2, ACENDE_LED);
		break;
		
		case DOOR_OPEN:
			Hal__SetLed(LED_0, APAGA_LED);
			Hal__SetLed(LED_1, APAGA_LED);
			Hal__SetLed(LED_2, APAGA_LED);
		break;
		case DOOR_CLOSE:
			Hal__SetLed(LED_0, APAGA_LED);
			Hal__SetLed(LED_1, APAGA_LED);
			Hal__SetLed(LED_2, ACENDE_LED);
		break;
		
		default:
		break;
 }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void ReadDisplayKeys(void)
{
        unsigned char leitura;
		
		Display_Keys_Map = KEY_NONE;
       		   	
		leitura = Hal__ReadKey(KEY_0);
		if(leitura  == TRUE)
		{
			Display_Keys_Map = KEY_GROUND_FLOOR;
		}
		leitura = Hal__ReadKey(KEY_1);
		if(leitura == TRUE)
		{
			Display_Keys_Map = KEY_FIRST_FLOOR;
		}
		leitura = Hal__ReadKey(KEY_2);
		if(leitura == TRUE)
		{
			Display_Keys_Map =  KEY_NEXT_FLOOR;
		}
}

/**************************************************
 *  Atualiza  7 Segmentos
 **************************************************/
void UpdateDisplaySevenSeg(void)
{
	char i;
	char *p_digito;
	unsigned short int current_floor;
	
	current_floor = PositionSensor__GetMeters(POSITION_SENSOR_1);
	if(POSITION_GROUND_MAX >= current_floor)
	{
		Segment_Floor_State = GROUND_FLOOR;
	}
	else
	{
		Segment_Floor_State = FIRST_FLOOR;
	}
	
	switch(Segment_Floor_State)
	{
	case GROUND_FLOOR:
		p_digito = &GROUD_DIGIT[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
	break;
	case FIRST_FLOOR:
		p_digito = &FIRST_DIGIT[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
	break;
	default:
	break;
   }
}

		

		
