/*
 * esp_at.h
 *
 *  Created on: Nov 29, 2024
 *      Author: ADMIN
 */

#ifndef INC_ESP_AT_H_
#define INC_ESP_AT_H_
#include "stm32f1xx_hal.h"
#include "string.h"
#include "global.h"

extern char SSID[];
extern char Pass[];

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern uint8_t data_byte_receive[1];
extern uint8_t ESP_Response[1000];

extern char buffer[50];
extern char Link_ID;
extern char store_char;

extern int count_data_come;
extern int command_size;
extern int Flag_Response;
extern int idx;

extern char* page1;
extern char *page2_Top;
extern char *page2_end;
extern char *table;

extern int Server_State;

extern UART_HandleTypeDef huart3;
#define ON_SERVER 0
#define OFF_SERVER 1

void ESP_INIT();
void SendCommand(char* str);
void WaitForResponse(int timeout,char* OKE_response,char* Error_response);
void Server_Send(int linkID,char* str);
void server_on();
#endif /* INC_ESP_AT_H_ */
