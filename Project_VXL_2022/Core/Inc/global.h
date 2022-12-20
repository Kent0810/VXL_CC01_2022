/*
 * global.h
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "button1.h"
#include "button2.h"
#include "button3.h"
#include "button4.h"
#include "fsm_run.h"
#include "note.h"
#include "buzzer.h"

extern int status1;
extern int status2;
extern int pes_status;
extern int buzzer_status;

#define Red_Countdown		10000
#define Yellow_Countdown	2000
#define Green_Countdownn	8000



#define INIT		0
#define RED			1
#define YELLOW		2
#define GREEN		3

#define MAN_RED		4
#define MAN_YELLOW	5
#define MAN_GREEN	6



#define PES_OFF		7
#define PES_ON		8

#define AUTOMATIC_MODE	19
#define MANUAL_MODE		20

#define TUNING_MODE		21
#define TUNING_WAIT		22

#define BUZZER_ON		23
#define BUZZER_WAIT		24
#define BUZZER_OFF		25


#endif /* INC_GLOBAL_H_ */
