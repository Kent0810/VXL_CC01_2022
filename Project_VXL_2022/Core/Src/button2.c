/*
 * button2.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */
#include "button2.h"


static int KeyReg0 = NORMAL_STATE;
static int KeyReg1 = NORMAL_STATE;
static int KeyReg2 = NORMAL_STATE;

static int KeyReg3 = NORMAL_STATE; //previous




static int TimerForKeyPress = 200;
//FIRST TRAFFIC LIGHT
int setRed0 = Red_Countdown;
int setYellow0 = Yellow_Countdown;
int setGreen0 = Green_Countdownn;

int tempRed0 = Red_Countdown;
int tempYellow0 = Yellow_Countdown;
int tempGreen0 = Green_Countdownn;
//END FIRST TRAFFIC LIGHT

//SECOND TRAFFIC LIGHT
int setRed1 = Red_Countdown;
int setYellow1 = Yellow_Countdown;
int setGreen1 = Green_Countdownn;

int tempRed1 = Red_Countdown;
int tempYellow1 = Yellow_Countdown;
int tempGreen1 = Green_Countdownn;
//END SECOND TRAFFIC LIGHT

int KeyReg2Counter = 0;


void KeyInputHandler2(){
	if(KeyReg1Counter == 1){
		//INCREASE FIRST TRAFFIC LIGHT RED & SECOND TRAFFIC LIGHT GREEN
		tempRed0 = (tempRed0 + 1000) % 100000 ;
		//tempRed1 = (tempRed1 + 1000) % 100000 ;
		tempGreen1 = (tempGreen1 + 1000) % 100000;
	}
	else if(KeyReg1Counter == 2){
		//INCREASE BOTH TRAFFIC LIGHT YELLOW
		tempYellow0 = (tempYellow0 + 1000) % 100000 ;
		tempYellow1 = (tempYellow1 + 1000) % 100000 ;
		tempRed0 = (tempRed0 + 1000) % 100000;
		tempRed1 = (tempRed1 + 1000) % 100000;
	}
	else if(KeyReg1Counter == 3){
		//INCREASE FIRST TRAFFIC LIGHT GREEN & SECOND TRAFFIC LIGHT RED
		tempGreen0 = (tempGreen0 + 1000) % 100000;
		//tempGreen1 = (tempGreen1 + 1000) % 100000;
		tempRed1 = (tempRed1 + 1000) % 100000 ;
	}
	status1 = TUNING_MODE;
	status2 = TUNING_MODE;

}
void LongKeyInputHandler2(){
	KeyInputHandler2();
}

void getKeyInput2(){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);
	if((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)){
		if(KeyReg3 != KeyReg2){
			KeyReg3 = KeyReg2;
			if(KeyReg2 == PRESSED_STATE){
				KeyInputHandler2();
				TimerForKeyPress = 200;
			}
		}
		else {
			TimerForKeyPress--;
			if(TimerForKeyPress == 0){
				if(KeyReg2 == PRESSED_STATE){
					LongKeyInputHandler2();
				}
				TimerForKeyPress = 200;
			}
		}
	}
}

