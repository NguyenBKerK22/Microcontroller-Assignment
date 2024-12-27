/*
 * fsm_manual.c
 *
 *  Created on: Nov 1, 2024
 *      Author: ADMIN
 */
#include "fsm_setting.h"
#include "global.h"
int status_ld = 1;
int red_time_increase = 0;
int green_time_increase = 0;
int yellow_time_increase = 0;
void fsm_setting(){
	switch(status_fsm){
	case INIT_SETTING:
		red_time_increase = 0;
		green_time_increase = 0;
		yellow_time_increase = 0;

		status_fsm = RED_SETTING;

		setTimer(4,500);

		all_led_red_off();
		all_led_red_on();

		lcd_goto_XY(1, 0);
		lcd_send_string("    SETTING    ");
		break;
	case RED_SETTING:
		if(isButtonPressed(0)){
			status_fsm = GREEN_SETTING;

			all_led_red_off();
			all_led_green_on();
			status_ld = 1;
		}
		if(isButtonPressed(1)){
			red_time_increase++;
			if(red_time_increase + red_time > 99) {
				red_time_increase = 0 - red_time;
			}
		}
		if(isButtonPressed(2)){
			red_time += red_time_increase;
			red_time_increase = 0;
		}
		if(flag_timer[4] == 1){
			if(status_ld == 1){
				all_led_red_off();
				status_ld = 0;
			}
			else{
				all_led_red_on();
				status_ld = 1;
			}
			setTimer(4,500);
		}
		break;
	case GREEN_SETTING:
		if(isButtonPressed(0)){
			status_fsm = YELLOW_SETTING;

			all_led_red_off();
			all_led_yellow_on();

		}
		if(isButtonPressed(1)){
			green_time_increase++;
			if(green_time_increase + green_time > 99) {
				green_time_increase = 0 - green_time;
			}
		}
		if(isButtonPressed(2)){
			green_time += green_time_increase;
			green_time_increase = 0;
		}
		if(flag_timer[4] == 1){
			if(status_ld == 1){
				all_led_red_off();
				//all_led_green_off();
				status_ld = 0;
			}
			else{
				all_led_green_on();
				status_ld = 1;
			}
			setTimer(4,500);
		}
		break;
	case YELLOW_SETTING:
		if(isButtonPressed(0)){
			all_led_red_off();
			status_fsm = INIT;
		}
		if(isButtonPressed(1)){
			yellow_time_increase++;
			if(yellow_time_increase + yellow_time > 99) {
				yellow_time_increase = 0 - yellow_time;
			}
		}
		if(isButtonPressed(2)){
			yellow_time += yellow_time_increase;
			yellow_time_increase = 0;

		}
		if(flag_timer[4] == 1){
			if(status_ld == 1){
				all_led_red_off();
				//all_led_yellow_off();
				status_ld = 0;
			}
			else{
				all_led_yellow_on();
				status_ld = 1;
			}
			setTimer(4,500);
		}
		break;
	case INIT_REMOTE_SETTING:
		lcd_clear_display();
		lcd_goto_XY(1,0);
		lcd_send_string("RED=");
		lcd_goto_XY(1,8);
		lcd_send_string("GREEN=");
		lcd_goto_XY(2,5);
		lcd_send_string("YELLOW=");
		status_fsm = REMOTE_SETTING;
		break;
	case REMOTE_SETTING:

		break;
	default:
		break;
	}
}

