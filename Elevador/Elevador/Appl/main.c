/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\main_prm.h>

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
typedef enum
{
	SLOT_1,
	SLOT_2,
	SLOT_3,
	SLOT_4,
	SLOT_5,
	NUM_OF_MAIN_SLOTS
}MAIN_SLOT_TYPE;


#define _1MS  	0x08
#define _4MS 	0x0A
#define _10MS 	0x0B
//-------------------------------------- Global Variables ----------------------------------------------------------------

MAIN_SLOT_TYPE Slot;


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

void main(void)
{
	Slot = SLOT_1;
	
	TCCR1A = 0;                        //confira timer para opera��o normal pinos OC1A e OC1B desconectados
	TCCR1B = 0;                        //limpa registrador
	TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
	
	TCNT1 = 62500;      //para contar a cada 250ms
	//TCNT1 = 0xC2F7;                    //inicia timer com valor para que estouro ocorra em 1 segundo
	//TCNT1 = 34186;                   // Para contar 2s=> 65536 - 31330
	// 65536-(16MHz/1024/1Hz) =  65536 - 15.625 = 49911(0xC2F7)=> 15.625 � o per�odo desejado.
	// Usa-se a diferen�a porque o contador � crescente e estoura de 0xffff a 0.
	TIMSK1 |= (1 << TOIE1);
	sei();
	
	
	// Functions Initialization
	INITIALIZE_TASKS();
		
	//Main Loop
	for(;;)
	{
		ALL_SLOTS_TASKS();
		switch(Slot)
		   {
			case SLOT_1:
			   SLOT_1_TASKS();
			   break;

			case SLOT_2:
			   SLOT_2_TASKS();
			   break;

			case SLOT_3:
			  SLOT_3_TASKS();
			  break;

			case SLOT_4:
			  SLOT_4_TASKS();
			  break;

			case SLOT_5:
			  SLOT_5_TASKS();
			  break;

			default:
			  Slot = SLOT_1;
			  break;
	       }
	Slot++;
	if(Slot >= NUM_OF_MAIN_SLOTS)
		Slot = SLOT_1;
	}
}

