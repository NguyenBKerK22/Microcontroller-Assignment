/*
 * fsm_autorun.c
 *
 *  Created on: Oct 31, 2024
 *      Author: ADMIN
 */
#include "global.h"
#include "fsm_autorun.h"
int status_fsm = INIT;
void fsm_autorun(){
	if(button_flag[0] && status_fsm < INIT){
			status_fsm += 5;
			button_flag[0] = 0;
			lcd_clear_display();
	}
	switch(status_fsm){
	case INIT:
		status_fsm = RED_GREEN;
		setTimer(1, 1000*red_time);
		setTimer(2, 1000*green_time);
		setTimer(3, 1000);
		break;
	case RED_GREEN:
		led_red_and_green();
		if(flag_timer[2] == 1){
			status_fsm = RED_YELLOW;
			setTimer(2, 1000*yellow_time);

			lcd_yellow_time = yellow_time;
			setTimer(3,1000);
		}
		break;
	case RED_YELLOW:
		led_red_and_yellow();
		if(flag_timer[2] == 1){
			status_fsm = GREEN_RED;
			setTimer(1,1000*green_time);
			setTimer(2, 1000*red_time);

			lcd_green_time = green_time;
			lcd_red_time = red_time;
			setTimer(3,1000);
		}
		break;
	case YELLOW_RED:
		led_yellow_and_red();
		if(flag_timer[1] ==1){
			status_fsm = RED_GREEN;
			setTimer(1,1000*red_time);
			setTimer(2,1000*green_time);

			lcd_red_time = red_time;
			lcd_green_time = green_time;
			setTimer(3,1000);
		}
		break;
	case GREEN_RED:
		led_green_and_red();
		if(flag_timer[1] == 1){
			status_fsm = YELLOW_RED;
			setTimer(1,1000*yellow_time);

			lcd_yellow_time = yellow_time;
			setTimer(3,1000);
		}
		break;
	default:
		break;
	}
}

