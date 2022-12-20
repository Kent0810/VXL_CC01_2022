/*
 * button4.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Admin
 */

#include "button4.h"

static int KeyReg0 = NORMAL_STATE;
static int KeyReg1 = NORMAL_STATE;
static int KeyReg2 = NORMAL_STATE;

static int KeyReg3 = NORMAL_STATE; //previous

static int TimerForKeyPress = 200;


void KeyInputHandler4(){

	if(pes_status == PES_OFF) pes_status = PES_ON;
	else {
		pes_status = PES_OFF;
		buzzer_status = BUZZER_OFF;
	}
	setTimer4((setRed0 + setYellow0 + setGreen0)*2);
	buzzer_status = BUZZER_ON;
}
void LongKeyInputHandler4(){
	KeyInputHandler4();
}

void getKeyInput4(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(Button4_GPIO_Port, Button4_Pin);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2){
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){
				KeyInputHandler4();
				TimerForKeyPress = 200;
			}
		}
		else {
			TimerForKeyPress--;
			if(TimerForKeyPress == 0){
				if(KeyReg2 == PRESSED_STATE){
					LongKeyInputHandler4();
				}
				TimerForKeyPress = 200;
			}
		}
	}
}

