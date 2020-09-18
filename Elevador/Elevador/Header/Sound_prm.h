/*
 * Sound_prm.h
 *
 * Created: 21/08/2020 10:52:14
 *  Author: Ana Watanabe
 */ 


#ifndef SOUND_PRM_H_
#define SOUND_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------

#include <D:\Materias_UDESC\AAM\Testes\Elevador-master\Elevador\Elevador\Header\C_types.h>
//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

#define USE_BUZZER       ENABLED

//POWER ON Sounds Parameters
#define POWER_ON_STEP1_ON_TIME	800 //ms
#define POWER_ON_STEP2_OFF_TIME	100 //ms
#define POWER_ON_STEP3_ON_TIME  500 //ms
#define POWER_ON_STEP4_OFF_TIME	100 //ms
#define POWER_ON_STEP5_ON_TIME  1000 //ms

#define POWER_ON_BUZZER_FREQ1	4000 //Hz
#define POWER_ON_BUZZER_FREQ2	4000 //Hz
#define POWER_ON_BUZZER_FREQ3	4000 //Hz


//KEY PRESS Sound Parameters
#define KEY_PRESS_SOUND_TIME	100  //ms
#define KEY_PRESS_BUZZER_FREQ	4000 //Hz

//END OF CYCLE Sounds Parameters
#define END_CYCLE_SOUND_ON_TIME		1000 	//ms
#define END_CYCLE_SOUND_OFF_TIME	400  	//ms
#define MAX_END_CYCLE_SOUND_COUNTER	6
#define END_CYCLE_BUZZER_FREQ1		4000	//Hz
#define END_CYCLE_BUZZER_FREQ2		4000	//Hz





#endif /* SOUND_PRM_H_ */