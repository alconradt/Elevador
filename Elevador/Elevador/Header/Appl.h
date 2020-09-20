/*
 *
 *  Created on: 13/09/2020
 *  Authors: André Conradt, Matheus Gasperin and Matheus Knop
 */ 


#ifndef APPL_H_
#define APPL_H_

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	GROUND_STATE = 0,
	FIRST_STATE
}FLOOR_STATE;

//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void Appl__Handler(void);
void Appl__Initialize(void);




#endif /* APPL_H_ */