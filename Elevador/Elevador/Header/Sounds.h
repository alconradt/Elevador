/*
 *
 *  Created on: 13/09/2020
 *  Authors: Andr� Conradt, Matheus Gasperin and Matheus Knop
 */ 

#ifndef Sounds_H_
#define Sounds_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\Sound_prm.h>


typedef enum {
	SOUND_POWER_ON = 0,
	SOUND_KEY_PRESS,
	SOUND_END_CYCLE,
	PLAY_NO_SOUND,   // N�O RETIRE ESTA LINHA
	NUM_OF_SOUNDS,
} SOUNDS_TYPE;

//Prot�tipos
void Sounds__Initialize(void);
void Sounds__Background(void);
void Sounds__PlaySounds( SOUNDS_TYPE sound_id);
SOUNDS_TYPE Sounds__GetSounds( void);   //novo

#endif /* Sounds_H_ */