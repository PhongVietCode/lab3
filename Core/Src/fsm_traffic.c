/*
 * fsm_traffic.c
 *
 *  Created on: Nov 3, 2023
 *      Author: PhongTran
 */
#include "fsm_traffic.h"
#include "button.h"
#include "7segmentLED.h"
int current_state = RED1_GREEN2;

int road1_timer = 0;
int road2_timer = 0;

int RED_TIME = 5;
int GREEN_TIME = 3;
int YELLOW_TIME = 2;

// Time for traffic led
int time_array[3] = {0, 0, 0};

// Traffic led array
GPIO_TypeDef* led1_array_port[3] = {RED1_GPIO_Port,YELLOW1_GPIO_Port, GREEN1_GPIO_Port };
GPIO_TypeDef* led2_array_port[3] = {RED2_GPIO_Port,YELLOW2_GPIO_Port, GREEN2_GPIO_Port };

uint16_t led1_array_pin[3] ={RED1_Pin, YELLOW1_Pin, GREEN1_Pin};
uint16_t led2_array_pin[3] ={RED2_Pin, YELLOW2_Pin, GREEN2_Pin};

// Enable ports and pins
GPIO_TypeDef* en_port[4] ={EN0_GPIO_Port,EN1_GPIO_Port, EN2_GPIO_Port, EN3_GPIO_Port};
uint16_t en_pin[4] = {EN0_Pin,EN1_Pin, EN2_Pin, EN3_Pin};

// for display the led
int led_buffer[4] ={0,0,0,0};
// for change the led
int dumb_val[4] = {0,0,0,0};
// current mode
int mode = -1;
// traverse the 7segment led
int led_index = 0;
int isModify = 0;
void clearAllLED(){
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);
}

void run_traffic(){
	clearAllLED();
	switch(current_state){
		case RED1_GREEN2:
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);
			if(road1_timer < 0){
				current_state = RED1_YELLOW2;
				road1_timer = RED_TIME;
			}
			if(road2_timer < 0){
				current_state = RED1_YELLOW2;
				road2_timer = YELLOW_TIME;
			}
			break;
		case RED1_YELLOW2:
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port,YELLOW2_Pin, 0);
			if(road1_timer < 0){
				current_state = GREEN1_RED2;
				road1_timer = GREEN_TIME;
			}
			if(road2_timer < 0){
				current_state = GREEN1_RED2;
				road2_timer = RED_TIME;
			}
			break;
		case GREEN1_RED2:
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 0);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
			if(road1_timer < 0){
				current_state = YELLOW1_RED2;
				road1_timer = YELLOW_TIME;
			}
			if(road2_timer < 0){
				current_state = YELLOW1_RED2;
				road2_timer = RED_TIME;
			}
			break;
		case YELLOW1_RED2:
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port,YELLOW2_Pin, 1);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
			if(road1_timer < 0){
				current_state = RED1_GREEN2;
				road1_timer = RED_TIME;
			}
			if(road2_timer < 0){
				current_state = RED1_GREEN2;
				road2_timer = GREEN_TIME;
			}
			break;

		default:
			break;
	}
}

void update7SEG(int index)
{
  switch (index)
  {
  case 0:
    display7Seg(led_buffer[0]);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
    break;
  case 1:
    display7Seg(led_buffer[1]);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
    break;
  case 2:
    display7Seg(led_buffer[2]);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
    break;
  case 3:
    display7Seg(led_buffer[3]);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
    break;
  default:
    break;
  }
}
void set_up_led_buffer(int num1, int num2){
	led_buffer[0] = num1 / 10;
	led_buffer[1] = num1 % 10;
	led_buffer[2] = num2 / 10;
	led_buffer[3] = num2 % 10;
}

void display_4LED(){
	update7SEG(led_index);
	led_index++;
	if(led_index > 3) led_index = 0;
}

void blinking_led_mode(int index){
	HAL_GPIO_TogglePin(led1_array_port[mode], led1_array_pin[mode]);
	HAL_GPIO_TogglePin(led2_array_port[mode], led2_array_pin[mode]);
}
void checkButton(){
	if(isButtonPress(0)){
		mode++;
		mode%=3;
		isModify++;
		isModify%=4;
		if(isModify == 0) mode = -1;
		clearAllLED();
	}
	if(isButtonPress(1)){
		dumb_val[mode]++;
	}
	if(isButtonPress(2)){
		time_array[mode] += dumb_val[mode];
		RED_TIME = time_array[0];
		YELLOW_TIME = time_array[1];
		GREEN_TIME = time_array[2];
		dumb_val[mode] = 0;
	}
}
void run_led_traffic(){
	if(isModify == 0){
		set_up_led_buffer(road1_timer,road2_timer);
		road1_timer--;
		road2_timer--;
	}
}

void modify_mode(){
	if(isModify != 0)
		blinking_led_mode(mode);
}

void fsm(){
	if(isModify == 0)
		run_traffic();
	else {
		set_up_led_buffer(time_array[mode] + dumb_val[mode], mode);
	}
}
void init(){
	time_array[0] = RED_TIME;
	time_array[1] = YELLOW_TIME;
	time_array[2] = GREEN_TIME;
	clearAllLED();
	road1_timer = RED_TIME;
	road2_timer = GREEN_TIME;
	run_traffic();
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
	display_4LED();
}


