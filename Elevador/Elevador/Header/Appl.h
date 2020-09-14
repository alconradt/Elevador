/*
 * Appl.h
 *
 * Created: 02/04/2019 21:49:38
 *  Author: Ana Watanabe
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