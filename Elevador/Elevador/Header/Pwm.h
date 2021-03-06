/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 


#ifndef Pwm_H_
#define Pwm_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Micro.h>
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sounds.h>
//**********ver SE n�o � Sounds_prm.h ********


typedef enum {
	PWM0 = 0,   // OC0A
	PWM1,       // OC0B
	PWM2,       // OC1A
	PWM3,       // OC1B
	PWM4,       // OC2A
	PWM5,       // OC2B
	NUM_OF_PWM,
} PWM_ID_TYPE;

typedef enum {
	PWM_TC0 = 0,
	PWM_TC1,
	PWM_TC2,
	NUM_OF_PWM_TC,
} PWM_TC_TYPE;

//prot�tipos
// Inicializa��o do m�dulo PWM                                                                                           
void Pwm__Initialize(void);
// Configura o TC numa determinada frequ�ncia ( verificar no livro para cada TC)                    
void Pwm__SetTCFrequency( PWM_TC_TYPE tc, unsigned short int frequency);
// Configura o PWM TC num determinado ciclo de trabalho ( 0 a 100%)                        
void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty);




#endif /* Pwm_H_ */