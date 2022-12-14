/*
 * button3.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */
#include "button3.h"


static int KeyReg0 = NORMAL_STATE;
static int KeyReg1 = NORMAL_STATE;
static int KeyReg2 = NORMAL_STATE;

static int KeyReg3 = NORMAL_STATE; //previous

static int TimerForKeyPress = 200;


void KeyInputHandler3(){

	setRed0 = tempRed0;
	setRed1 = tempRed1;

	setYellow0 = tempYellow0;
	setYellow1 = tempYellow1;

	setGreen0 = tempGreen0;
	setGreen1 = tempGreen1;

	KeyReg1Counter = 0;
	status1 = INIT;
	status2 = INIT;
}
void LongKeyInputHandler3(){
	KeyInputHandler3();
}

void getKeyInput3(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(Button3_GPIO_Port, Button3_Pin);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2){
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){
				KeyInputHandler3();
				TimerForKeyPress = 200;
			}
		}
		else {
			TimerForKeyPress--;
			if(TimerForKeyPress == 0){
				if(KeyReg2 == PRESSED_STATE){
					LongKeyInputHandler3();
				}
				TimerForKeyPress = 200;
			}
		}
	}
}


