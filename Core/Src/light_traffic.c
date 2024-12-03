/*
 * light_traffic.c
 *
 *  Created on: Oct 30, 2024
 *      Author: ADMIN
 */
#include "main.h"
#include "light_traffic.h"

void led_red_and_yellow(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,SET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,SET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,SET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, SET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,RESET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,SET);
}
void led_red_and_green(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,SET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,SET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,RESET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, SET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,SET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,RESET);
}
void led_yellow_and_red(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,RESET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,SET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,SET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, SET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,SET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,SET);
}
void led_green_and_red(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,SET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,RESET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,SET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, RESET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,SET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,SET);
}
void all_led_red_on(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,SET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,SET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,SET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, SET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,SET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,SET);
}
void all_led_red_off(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,RESET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,RESET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,RESET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, RESET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,RESET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,RESET);
}
void all_led_green_on(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,SET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,RESET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,RESET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, RESET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,SET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,RESET);
}
void all_led_yellow_on(){
	HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,RESET);
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,SET);

	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,SET);

	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);
	HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, SET);

	HAL_GPIO_WritePin(D9_GPIO_Port,D9_Pin,RESET);
	HAL_GPIO_WritePin(D10_GPIO_Port,D10_Pin,SET);
}

