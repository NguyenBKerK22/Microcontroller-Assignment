/*
 * i2c_lcd.c
 *
 *  Created on: Nov 8, 2024
 *      Author: ADMIN
 */


#include "i2c_lcd.h"
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 0x21 << 1 // change this according to ur setup

//int lcd_red_time = 0;
//int lcd_green_time = 0;
//int lcd_yellow_time = 0;
char lcd_buf[16];
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd&0xf0);
    data_l = ((cmd<<4)&0xf0);
    data_t[0] = data_u|0x0C;  //en=1, rs=0
    data_t[1] = data_u|0x08;  //en=0, rs=0
    data_t[2] = data_l|0x0C;  //en=1, rs=0
    data_t[3] = data_l|0x08;  //en=0, rs=0
    HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data&0xf0);
    data_l = ((data<<4)&0xf0);
    data_t[0] = data_u|0x0D;  //en=1, rs=0
    data_t[1] = data_u|0x09;  //en=0, rs=0
    data_t[2] = data_l|0x0D;  //en=1, rs=0
    data_t[3] = data_l|0x09;  //en=0, rs=0
    HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void)
{
    lcd_send_cmd (0x33); /* set 4-bits interface */
    lcd_send_cmd (0x32);
    HAL_Delay(50);
    lcd_send_cmd (0x28); /* start to set LCD function */
    HAL_Delay(50);
    lcd_send_cmd (0x01); /* clear display */
    HAL_Delay(50);
    lcd_send_cmd (0x06); /* set entry mode */
    HAL_Delay(50);
    lcd_send_cmd (0x0c); /* set display to on */
    HAL_Delay(50);
    lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
    HAL_Delay(50);
    lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
    while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
    lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
    uint8_t pos_Addr;
    if(row == 1)
    {
        pos_Addr = 0x80 + row - 1 + col;
    }
    else
    {
        pos_Addr = 0x80 | (0x40 + col);
    }
    lcd_send_cmd(pos_Addr);
}
void lcd_run(){
	if(button_flag[0] && status_fsm < INIT){
				lcd_clear_display();
				return;
	}
	switch(status_fsm){
	case INIT:
		lcd_red_time = red_time;
		lcd_yellow_time = yellow_time;
		lcd_green_time = green_time;

		lcd_goto_XY(1,0);
		lcd_send_string("TIME 01:");
		lcd_goto_XY(2,0);
		lcd_send_string("TIME 02:");
		break;
	case RED_GREEN:
		lcd_goto_XY(1,8);
		lcd_send_data(lcd_red_time/10 + 48);
		lcd_goto_XY(1,9);
		lcd_send_data(lcd_red_time%10 + 48);

		lcd_goto_XY(2,8);
		lcd_send_data(lcd_green_time/10 + 48);
		lcd_goto_XY(2,9);
		lcd_send_data(lcd_green_time%10 + 48);
		if(flag_timer[3] == 1){
			if(lcd_red_time > 0) lcd_red_time--;
			if(lcd_green_time >0) lcd_green_time--;
			setTimer(3,1000);
		}
		break;
	case RED_YELLOW:
		lcd_goto_XY(1,8);
		lcd_send_data(lcd_red_time/10 + 48);
		lcd_goto_XY(1,9);
		lcd_send_data(lcd_red_time%10 + 48);

		lcd_goto_XY(2,8);
		lcd_send_data(lcd_yellow_time/10 + 48);
		lcd_goto_XY(2,9);
		lcd_send_data(lcd_yellow_time%10 + 48);

		if(flag_timer[3] == 1){
			if(lcd_red_time > 0) lcd_red_time--;
			if(lcd_yellow_time >0) lcd_yellow_time--;
			setTimer(3,1000);
		}
		break;
	case GREEN_RED:
		lcd_goto_XY(1,8);
		lcd_send_data(lcd_green_time/10 + 48);
		lcd_goto_XY(1,9);
		lcd_send_data(lcd_green_time%10 + 48);

		lcd_goto_XY(2,8);
		lcd_send_data(lcd_red_time/10 + 48);
		lcd_goto_XY(2,9);
		lcd_send_data(lcd_red_time%10 + 48);

		if(flag_timer[3] == 1){
			if(lcd_red_time > 0) lcd_red_time--;
			if(lcd_green_time >0) lcd_green_time--;
			setTimer(3,1000);
		}
		break;
	case YELLOW_RED:
		lcd_goto_XY(1,8);
		lcd_send_data(lcd_yellow_time/10 + 48);
		lcd_goto_XY(1,9);
		lcd_send_data(lcd_yellow_time%10 + 48);

		lcd_goto_XY(2,8);
		lcd_send_data(lcd_red_time/10 + 48);
		lcd_goto_XY(2,9);
		lcd_send_data(lcd_red_time%10 + 48);
		if(flag_timer[3] == 1){
			if(lcd_red_time > 0) lcd_red_time--;
			if(lcd_yellow_time >0) lcd_yellow_time--;
			setTimer(3,1000);
		}
		break;
	case RED_GREEN_MANUAL:
		lcd_goto_XY(1,0);
		lcd_send_string("    RED GREEN   ");
		lcd_goto_XY(2,0);
		lcd_send_string("                ");
		break;
	case RED_YELLOW_MANUAL:
		lcd_goto_XY(1,0);
		lcd_send_string("    RED YELLOW  ");
		lcd_goto_XY(2,0);
		lcd_send_string("                ");
		break;
	case GREEN_RED_MANUAL:
		lcd_goto_XY(1,0);
		lcd_send_string("    GREEN RED   ");
		lcd_goto_XY(2,0);
		lcd_send_string("                ");
		break;
	case YELLOW_RED_MANUAL:
		lcd_goto_XY(1,0);
		lcd_send_string("    YELLOW RED  ");
		lcd_goto_XY(2,0);
		lcd_send_string("                ");
		break;
	case INIT_SETTING:
		break;
	case RED_SETTING:
		lcd_goto_XY(2,0);
		sprintf(lcd_buf,"   TIME RED: %d ",red_time+red_time_increase);
		lcd_send_string(lcd_buf);
		break;
	case YELLOW_SETTING:
		lcd_goto_XY(2,0);
		sprintf(lcd_buf,"TIME YELLOW: %d ",yellow_time+yellow_time_increase);
		lcd_send_string(lcd_buf);
		break;
	case GREEN_SETTING:
		lcd_goto_XY(2,0);
		sprintf(lcd_buf," TIME GREEN: %d ",green_time+green_time_increase);
		lcd_send_string(lcd_buf);
		break;
	case INIT_REMOTE_SETTING:
		break;
	case REMOTE_SETTING:
		lcd_goto_XY(1,4);
		lcd_send_data(red_time/10+48);
		lcd_goto_XY(1,5);
		lcd_send_data(red_time%10+48);
		lcd_goto_XY(1,14);
		lcd_send_data(green_time/10+48);
		lcd_goto_XY(1,15);
		lcd_send_data(green_time%10+48);
		lcd_goto_XY(2,10);
		lcd_send_data(yellow_time/10+48);
		lcd_goto_XY(2,11);
		lcd_send_data(yellow_time%10+48);
		break;
	default:
		break;
	}
}
