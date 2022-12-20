/*
 * button4.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Admin
 */

#ifndef INC_BUTTON4_H_
#define INC_BUTTON4_H_

#include "global.h"
#define NORMAL_STATE 	GPIO_PIN_SET //-> 0 Nhan
#define PRESSED_STATE 	GPIO_PIN_RESET // -> Nhan

extern int KeyReg4Counter;

//function prototype
void KeyInputHandler4();
void LongKeyInputHandler4();
void getKeyInput4();

#endif /* INC_BUTTON4_H_ */
