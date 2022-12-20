/*
 * buzzer.c
 *
 *  Created on: Dec 20, 2022
 *      Author: Admin
 */






//
//void BuzzerOn(void) {
//	int counter = sizeof(music1)/sizeof(music1[0]);
//	if (buzzerCounter < counter){
//		__HAL_TIM_SET_AUTORELOAD(&htim3, 1000000/music1[buzzerCounter]);
//		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 15);
//		buzzerCounter++;
//	} else {
//		buzzerCounter = 0;
//	}
//}
//void BuzzerOff(void) {
//	__HAL_TIM_SET_AUTORELOAD(&htim3, 0);
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//}
