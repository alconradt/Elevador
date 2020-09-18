/*
 * Pwm.c
 *
 * Created: 05/11/2019 22:50:57
 *  Author: Ana Watanabe
 */ 

#include <avr/io.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Gpio.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Hal.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Pwm.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Micro.h>

//*********************************************************
//
//   Esta rotina  faz a configuração do PWM (buzzer)
//
//*********************************************************
 
// Inicialização do módulo PWM ( Buzzer está no PD3 OC2B !!)
void Pwm__Initialize(void){
volatile TC2_REG_TYPE *pwm_pt2;

pwm_pt2 = TC2_REGISTERS;

// porta de  saida para buzina
bitWrite(DDRD, 3, OUTPUT_DIGITAL);
//bitWrite(PORTD, 3, 0);
// saida Buzzer para OC2B
pwm_pt2->TCCR2A_REG.byte =  0b00110001; //MODO 1 para PWM fase corrigida, 
                       // saida  OC2B  INVERTIDA TOP = 0xFF, OC2B habilitado
//pwm_pt2->TCCR2B_REG.byte =  0b00000010; //TC2 parado

Pwm__SetTCFrequency(PWM_TC2, BUZZER_DEFAULT_FREQ);
Pwm__SetDutyCycle(PWM5, BUZZER_OFF_DUTY);  //desliga o buzzer
// desligar a buzina com duty cycle igual a 0
//pwm_pt2->OCR2B_REG.byte =  0;	
}

//*********************************************************
//
//   Esta rotina configura o TC numa determinada frequência 
//   ( verifcar no livro para cada TC)
//
//*********************************************************
 
void Pwm__SetTCFrequency( PWM_TC_TYPE tc, unsigned short int frequency){
volatile TC0_REG_TYPE *pwm_pt0;
volatile TC1_REG_TYPE *pwm_pt1;
volatile TC2_REG_TYPE *pwm_pt2;

pwm_pt0 = TC0_REGISTERS;
pwm_pt1 = TC1_REGISTERS;
pwm_pt2 = TC2_REGISTERS;

if((frequency > 1900) && frequency  < 2100 ){
	switch(tc){
		case PWM_TC0:
		pwm_pt0->TCCR0B_REG.byte = 0b00100010;
		break;
		case PWM_TC1:
		pwm_pt1->TCCR1B_REG.byte = 0b00100010;
		break;
		case PWM_TC2:
		//pwm_pt2->TCCR2A_REG.byte = 0b00100001; //MODO 1 para PWM fase corrigida,
		//pwm_pt2->TCCR2A_REG.byte = 0b00110001; //MODO 1 para PWM fase corrigida,
		pwm_pt2->TCCR2B_REG.byte = 0b00100010;
		break;

		default:
		break;
	}
}

if((frequency > 2900) && frequency  < 3100 ){
	switch(tc){
		case PWM_TC0:
		pwm_pt0->TCCR0B_REG.byte = 0b00100011;
		break;
		case PWM_TC1:
		pwm_pt1->TCCR1B_REG.byte = 0b00100011;
		break;
		case PWM_TC2:
		//pwm_pt2->TCCR2A_REG.byte =  0b00100001; //MODO 1 para PWM fase corrigida,
		//pwm_pt2->TCCR2A_REG.byte = 0b00110001; //MODO 1 para PWM fase corrigida,
		pwm_pt2->TCCR2B_REG.byte = 0b00100011;
		break;

		default:
		break;
	}
}

if((frequency > 3900) && frequency  < 4100 ){
switch(tc){
case PWM_TC0:
   pwm_pt0->TCCR0B_REG.byte = 0x02; //prescaler = 8 dando frequencia de 4000Hz
   break;   
case PWM_TC1:
	pwm_pt1->TCCR1B_REG.byte = 0x02; //prescaler = 8 dando frequencia de 4000Hz
	break;
case PWM_TC2:
    //pwm_pt2->TCCR2A_REG.byte =  0b00100001; //MODO 1 para PWM fase corrigida,
	pwm_pt2->TCCR2B_REG.byte = 0x02; //prescaler = 8 dando frequencia de 4000Hz   	
	break;

default:
	break;
}
}

if((frequency > 4900) && frequency  < 5100 ){
	switch(tc){
		case PWM_TC0:
		pwm_pt0->TCCR0B_REG.byte = 0b00100101;
		break;
		case PWM_TC1:
		pwm_pt1->TCCR1B_REG.byte = 0b00100101;
		break;
		case PWM_TC2:
		//pwm_pt2->TCCR2A_REG.byte =  0b00100001; //MODO 1 para PWM fase corrigida,
		//pwm_pt2->TCCR2A_REG.byte = 0b00110001; //MODO 1 para PWM fase corrigida,
		pwm_pt2->TCCR2B_REG.byte = 0b00100101;
		break;

		default:
		break;
	}
}
}  // fim da função

//*********************************************************
//
//   Esta rotina configura o PWM TC num determinado 
//   ciclo de trabalho ( 0 a 100)
//
//*********************************************************
void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty){
volatile TC0_REG_TYPE *pwm_pt0;
volatile TC1_REG_TYPE *pwm_pt1;
volatile TC2_REG_TYPE *pwm_pt2;

pwm_pt0 = TC0_REGISTERS;
pwm_pt1 = TC1_REGISTERS;
pwm_pt2 = TC2_REGISTERS;
if (duty >100)
   duty = 100;
switch (pwm){
case PWM0:
	pwm_pt0->OCR0A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;
case PWM1:
	pwm_pt0->OCR0B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;
case PWM2:
	pwm_pt1->OCR1AH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
 	break;    // tem que checar para 16 bits
case PWM3:
	 pwm_pt1->OCR1BH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	 break;    // tem que checar para 16 bits
case PWM4:
	 pwm_pt2->OCR2A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	 break;    // tem que checar para 16 bits
case PWM5:
	pwm_pt2->OCR2B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;    // tem que checar para 16 bits
default:
	break;	
}
}

