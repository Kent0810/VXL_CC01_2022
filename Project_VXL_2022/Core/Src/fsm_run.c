/*
 * fsm_run.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Admin
 */

#include "fsm_run.h"
#include "tim.h"

int buzzerCounter = 0;

void buzzer_run(){
	switch(buzzer_status){
	case BUZZER_OFF:
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		break;
	case BUZZER_WAIT:
		if(pulse_flag == 1){
			buzzer_status = BUZZER_ON;
		}
		break;
	case BUZZER_ON:
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzerCounter);
		setPulse(1000);
		buzzerCounter+=1;
		buzzer_status =BUZZER_WAIT;
		break;
	}
}


void pes_run(){
	switch (pes_status){
	case PES_OFF:
//		BuzzerOff();
		buzzer_status = BUZZER_OFF;
		HAL_GPIO_WritePin(PES_LED_0_GPIO_Port, PES_LED_0_Pin, RESET);
		HAL_GPIO_WritePin(PES_LED_1_GPIO_Port, PES_LED_1_Pin, RESET);
		break;
	case PES_ON:
		if(status1 == RED || status1 == MAN_RED){
			if(status1 == RED){
				buzzer_status = BUZZER_OFF;
			}
			HAL_GPIO_WritePin(PES_LED_0_GPIO_Port, PES_LED_0_Pin, SET);
			HAL_GPIO_WritePin(PES_LED_1_GPIO_Port, PES_LED_1_Pin, RESET);
		}
		if(status1 == GREEN || status1 == MAN_GREEN || status1 == YELLOW || status1 == MAN_YELLOW){
			if(status1 == GREEN || status1 == YELLOW){
				buzzer_status = BUZZER_ON;
			}
			HAL_GPIO_WritePin(PES_LED_0_GPIO_Port, PES_LED_0_Pin, RESET);
			HAL_GPIO_WritePin(PES_LED_1_GPIO_Port, PES_LED_1_Pin, SET);
		}
		if(timer4_flag == 1){
			pes_status = PES_OFF;
		}
		break;
	default:
		break;
	}
}


int counter0 = 50;
//STATE MACHINE FOR THE TRAFFIC LIGHT
void fsm_run0(){
	switch (status1){
	case INIT:
		HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
		HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
		status1 = AUTOMATIC_MODE;
		break;
	case AUTOMATIC_MODE:
		setTimer1(setRed0);
		status1 = RED;
		break;
	case MANUAL_MODE:
		if(KeyReg1Counter == 1){
			status1 = MAN_RED;
		}
		else if(KeyReg1Counter == 2){
			status1 = MAN_YELLOW;
		}
		else if(KeyReg1Counter == 3){
			status1 = MAN_GREEN;
		}
		else {
			status1 = AUTOMATIC_MODE;
		}
		break;
	case MAN_RED:
		HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
		HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
		if(counter0 > 0){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
		}
		if(counter0 < 0){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
			if(counter0 == -50){
				counter0 = 50;
			}
		}
		counter0--;
		break;
	case MAN_YELLOW:
		if(counter0 > 0){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, SET);
		}
		if(counter0 < 0){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
			if(counter0 == -50){
				counter0 = 50;
			}
		}
		counter0--;
		break;
	case MAN_GREEN:
		if(counter0 > 0){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, SET);
		}
		if(counter0 < 0){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
			if(counter0 == -50){
				counter0 = 50;
			}
		}
		counter0--;
		break;
	case TUNING_WAIT:
		if(timer3_flag == 1){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
		}
		break;
	case TUNING_MODE:
		if(KeyReg1Counter == 1){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
			setTimer3(500);
			status1 = TUNING_WAIT;
		}
		else if(KeyReg1Counter == 2){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, SET);
			setTimer3(500);
			status1 = TUNING_WAIT;
		}
		else if(KeyReg1Counter == 3){
			HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, SET);
			setTimer3(500);
			status1 = TUNING_WAIT;
		}
		break;
	//1-0
	case RED:
		HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, SET);
		HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, RESET);
		if(timer1_flag == 1){
			status1 = GREEN;
			setTimer1(setGreen0);
		}
		break;
	//0-1
	case GREEN:
		HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, RESET);
		HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, SET);
		if(timer1_flag == 1){
			status1 = YELLOW;
			setTimer1(setYellow0);
		}
		break;
	case YELLOW:
		HAL_GPIO_WritePin(Traffic0_a_GPIO_Port, Traffic0_a_Pin, SET);
		HAL_GPIO_WritePin(Traffic0_b_GPIO_Port, Traffic0_b_Pin, SET);
		if(timer1_flag == 1){
			status1 = RED;
			setTimer1(setRed0);
		}
		break;
	default:
		break;
	}

}


int counter1 = 50;
void fsm_run1(){
	switch (status2){
	case INIT:
		HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
		HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
		status2 = AUTOMATIC_MODE;
		break;
	case AUTOMATIC_MODE:
		status2 = GREEN;
		setTimer2(setGreen1);
		break;
	case MANUAL_MODE:
		if(KeyReg1Counter == 1){
			status2 = MAN_RED;
		}
		else if(KeyReg1Counter == 2){
			status2 = MAN_YELLOW;
		}
		else if(KeyReg1Counter == 3){
			status2 = MAN_GREEN;
		}
		else {
			status2 = AUTOMATIC_MODE;
		}
		break;
	case MAN_RED:
		if(counter1 > 0){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, SET);
		}
		if(counter1 < 0){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
			if(counter1 == -50){
				counter1 = 50;
			}
		}
		counter1--;
		break;
	case MAN_YELLOW:
		if(counter1 > 0){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, SET);
		}
		if(counter1 < 0){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
			if(counter1 == -50){
				counter1 = 50;
			}
		}
		counter1--;
		break;
	case MAN_GREEN:
		if(counter1 > 0){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
		}
		if(counter1 < 0){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
			if(counter1 == -50){
				counter1 = 50;
			}
		}
		counter1--;
		break;
	case TUNING_WAIT:
		if(timer3_flag == 1){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
		}
		break;
	case TUNING_MODE:
		if(KeyReg1Counter == 1){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, SET);
			setTimer3(500);
			status2 = TUNING_WAIT;
		}
		else if(KeyReg1Counter == 2){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, SET);
			setTimer3(500);
			status2 = TUNING_WAIT;
		}
		else if(KeyReg1Counter == 3){
			HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, SET);
			HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
			setTimer3(500);
			status2 = TUNING_WAIT;
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, SET);
		HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, RESET);
		if(timer2_flag == 1){
			status2 = YELLOW;
			setTimer2(setYellow1);
		}
		break;
	case YELLOW:
		HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, SET);
		HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, SET);
		if(timer2_flag == 1){
			status2 = RED;
			setTimer2(setRed1);
		}
		break;
	case RED:
		HAL_GPIO_WritePin(Traffic1_a_GPIO_Port, Traffic1_a_Pin, RESET);
		HAL_GPIO_WritePin(Traffic1_b_GPIO_Port, Traffic1_b_Pin, SET);
		if(timer2_flag == 1){
			status2 = GREEN;
			setTimer2(setGreen1);
		}
		break;
	default:
		break;
	}
}
