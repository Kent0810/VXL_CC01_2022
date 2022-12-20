/*
 * button2.h
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */

#ifndef INC_BUTTON2_H_
#define INC_BUTTON2_H_

#include "global.h"

#define NORMAL_STATE 	GPIO_PIN_SET //-> 0 Nhan
#define PRESSED_STATE 	GPIO_PIN_RESET // -> Nhan

extern int KeyReg2Counter;

extern int setRed0;
extern int setYellow0;
extern int setGreen0;

extern int tempRed0;
extern int tempYellow0;
extern int tempGreen0;


extern int setRed1;
extern int setYellow1;
extern int setGreen1;

extern int tempRed1;
extern int tempYellow1;
extern int tempGreen1;

//function prototype
void KeyInputHandler2();
void LongKeyInputHandler2();
void getKeyInput2();



#endif /* INC_BUTTON2_H_ */
