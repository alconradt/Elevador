

/*
 * Gpio.c
 *
 * Created: 02/04/2019 21:57:55
 *  Author: Ana Watanabe
 */ 


//-------------------------------------- Include Files ----------------------------------------------------------------
#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> /*biblioteca para o uso das rotinas de
//_delay_ms() e _delay_us()*/

// #include "C_Types.h"   // vamos inserir depois!!!!!

//Definições de macros - empregadas para o trabalho com os bits
#include <Z:\Elevador\Elevador\Elevador\Header\Gpio.h>

#include <Z:\Elevador\Elevador\Elevador\Header\Micro.h>
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
const unsigned char GPIO_PIN_SET_MASK[] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};

const unsigned char GPIO_PIN_CLR_MASK[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};


volatile GPIO_DATA_TYPE *GPIO_DATA_LIST[NUM_OF_PORTS] = GPIO_DATA;   //está no Micro.h:  GPIO_DATA_TYPE  e #define GPIO_DATA {PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG};
//volatile GPIO_MISC_TYPE *GPIO_MISC_LIST[NUM_OF_PORTS] = GPIO_MISC;


/*

void GPio(void)
{
DDRB = 0xFF; //configura todos os pinos do PORTB como saídas
DDRC = 0x00; // configura todos os pins da PORTC como entradas	
PORTC = 0b11111111; // configura pull up ativado na porta C
//Apaga todos os leds
set_bit(PORTB,LED1); //desliga LED
set_bit(PORTB,LED2); //desliga LED
set_bit(PORTB,LED3); //desliga LED
set_bit(PORTB,LED4); //desliga LED
}
*/

/*            ************PARTE USADA NO TESTE1 PARA TESTAR LEDS/BOTÕES **************************

if(!tst_bit(PINC,SW3))   // pressionado = 0
  {
	//while(!tst_bit(PINC,SW1));
	//_delay_ms(10);
	//{
	clr_bit(PORTB,LED1); //liga LED
	set_bit(PORTB,LED2); //desliga LED
	set_bit(PORTB,LED3); //desliga LED
	
	set_bit(PORTB,LED4); //desliga LED
	_delay_ms(2000); //atraso de 200 ms
	set_bit(PORTB,LED1); //desliga LED
	clr_bit(PORTB,LED2); //liga LED
	set_bit(PORTB,LED3); //desliga LED
	set_bit(PORTB,LED4); //desliga LED
	_delay_ms(2000); //atraso de 200 ms	
	set_bit(PORTB,LED1); //desliga LED
	set_bit(PORTB,LED2); //desliga LED
	clr_bit(PORTB,LED3); //liga LED
	set_bit(PORTB,LED4); //desliga LED
	_delay_ms(2000); //atraso de 200 ms
	set_bit(PORTB,LED1); //desliga LED
	set_bit(PORTB,LED2); //desliga LED
	set_bit(PORTB,LED3); //desliga LED
	clr_bit(PORTB,LED4); //liga LED
	_delay_ms(2000); //atraso de 200 ms
	//}
 }
 */


// *******************PARTE DO DANIEL MODIFICADO PELA ANA ******************

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================



//---------------------------------------------------------------------------------------------------------------------

/*******************************************************************************
Configura  a porta
*******************************************************************************/
void Gpio__PinConfig(GPIO_PORT port,unsigned char pin,GPIO_PIN_TYPE type)
{
	volatile GPIO_DATA_TYPE *pt_data;
	//volatile GPIO_MISC_TYPE *pt_misc;
	unsigned char set_bit_mask;
	unsigned char clr_bit_mask;
	
	set_bit_mask = GPIO_PIN_SET_MASK[pin];
	clr_bit_mask = GPIO_PIN_CLR_MASK[pin];
	
	
	switch(port)
	{
	case	PORT_B:
		pt_data = PORTB;   // Está no Micro.h: #define PORTA &GPIOA_DATA   => endereço 0x0000 00000
		break;
	case	PORT_C:
		pt_data = PORTC;
		break;
	case	PORT_D:
		pt_data = PORTD;
		break;
	default:
		break;
	}
if(type == OUTPUT_DIGITAL)    // setar 1 para saída
{
	//var = pt_data->DIRECION_REG.byte;
	//BIT_SET(var,pin);      // Está no C_types.h =>  #define BIT_SET(mem,bit)    ((mem)|=(1UL<<(bit))) //This macro is used to set the bit of the data
	//pt_data->DIRECION_REG.byte = var;  
	//   OU
	pt_data = GPIO_DATA_LIST[port];		 	
	pt_data->DIRECION_REG.byte |= set_bit_mask;	// Config Output
}

if(type == INPUT_DIGITAL_PULLUP)
{
	pt_data = GPIO_DATA_LIST[port];		 	
	pt_data->DIRECION_REG.byte &= clr_bit_mask; 	// Config Input
	
	pt_data->DATA_OUT_PULL_REG.byte |= set_bit_mask;   // Config Input Pull up
}

}
	
/**********************************************************************************
 * Writes a specific port pin
 **********************************************************************************/
void Gpio__PinWrite(GPIO_PORT port,unsigned char pin,unsigned char value)
{
	volatile GPIO_DATA_TYPE *pt_data;
	
	  if (value == 0)
        {
        	pt_data = GPIO_DATA_LIST[port];		 	
        	pt_data->DATA_OUT_PULL_REG.byte &= GPIO_PIN_CLR_MASK[pin];
        }
        else
        {
        	pt_data = GPIO_DATA_LIST[port];
        	pt_data->DATA_OUT_PULL_REG.byte |= GPIO_PIN_SET_MASK[pin];
        }
   

}

/***********************************************************************************
 * Reads a specific port pin
 ***********************************************************************************/
unsigned char Gpio__PinRead(GPIO_PORT port,unsigned char pin)
{
	volatile GPIO_DATA_TYPE *pt_data;
	unsigned char pin_state = SW_OFF;       // pin_state = OFF  não pressionado  
	
		pt_data = GPIO_DATA_LIST[port];
    	if (pt_data->DATA_IN_REG.byte & GPIO_PIN_SET_MASK[pin])     // if(leitura != 0)   ou if(leitura)
           pin_state = SW_OFF;     // pin_state = SW_OFF   não acionado
        else
		   pin_state = SW_ON;
   
    return (pin_state);
    
}




