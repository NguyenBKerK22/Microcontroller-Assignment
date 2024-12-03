/*
 * esp_at.c
 *
 *  Created on: Nov 29, 2024
 *      Author: ADMIN
 */


/*
 * esp_config.c
 *
 *  Created on: Nov 28, 2024
 *      Author: ADMIN
 */
#include "esp_at.h"
uint8_t data_byte_receive[1];
uint8_t ESP_Response[1000];
//----------------------------------
char buffer[50]="";
char SSID[]="\"v\"";
char Pass[]="\"12345678\"";
char Link_ID = '\n';
char store_char ='\n';
//----------------------------------
int count_data_come = 0;
int command_size = 0;
int Flag_Response = 0;
int idx = 0;
// HTML USED FOR WEBSERVER
//-------------------------------------------------------------------------------------
char *home = "<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
<title>TRAFFIC LIGHT ASSIGNMENT</title>\n\
<style>\n\
body{font-family:Arial,sans-serif;text-align:center;margin-top:50px;background:#f9f9f9;color:#333}\n\
h1{color:#2c3e50}\n\
form{margin:15px}\n\
input[type=\"submit\"]{background:#3498db;color:#fff;border:none;padding:10px 25px;font-size:18px;border-radius:5px;cursor:pointer;transition:.3s}\n\
input[type=\"submit\"]:hover{background:#2980b9}\n\
</style>\n\
</head>\n\
<body>\n\
<h1>TRAFFIC LIGHT ASSIGNMENT</h1>\n\
<form action=\"/home\"><input type=\"submit\" value=\"HOME\"></form>\n\
<form action=\"/manual\"><input type=\"submit\" value=\"MANUAL\"></form>\n\
<form action=\"/setting\"><input type=\"submit\" value=\"SETTING\"></form>\n\
</body>\n\
</html>"
;

char *manual = "<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head>\n\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
<title>TRAFFIC LIGHT ASSIGNMENT</title>\n\
<style>\n\
body{text-align:center;margin-top:50px;background:#f4f4f4;color:#333;font-family:Arial,sans-serif}\n\
h1{color:#2c3e50;margin-bottom:30px}\n\
form{margin:15px}\n\
input[type=\"submit\"]{background:#3498db;color:#fff;border:none;padding:10px 20px;font-size:16px;border-radius:5px;cursor:pointer;transition:.3s;transform:scale(1)}\n\
input[type=\"submit\"]:hover{background:#2980b9;transform:scale(1.05)}\n\
input[type=\"submit\"]:active{background:#1c6a94}\n\
</style>\n\
</head>\n\
<body>\n\
<h1>TRAFFIC LIGHT ASSIGNMENT</h1>\n\
<form action=\"/redgreen\"><input type=\"submit\" value=\"RED_GREEN\"></form>\n\
<form action=\"/redyellow\"><input type=\"submit\" value=\"RED_YELLOW\"></form>\n\
<form action=\"/yellowred\"><input type=\"submit\" value=\"YELLOW_RED\"></form>\n\
<form action=\"/greenred\"><input type=\"submit\" value=\"GREEN_RED\"></form>\n\
<form action=\"/run\"><input type=\"submit\" value=\"RUN\"></form>\n\
</body>\n\
</html>";
char *setting = "<!DOCTYPE html>\n\
<html>\n\
<head>\n\
  <title>ESP8266 USER DATA COLLECTION</title>\n\
</head>\n\
<body>\n\
  <h1>ESP8266 USER DATA COLLECTION</h1>\n\
  <p>Enter the details in the form below:</p>\n\
  <form action=\"/save\">\n\
    <label for=\"redtime\">RED TIME (seconds):</label>\n\
    <input type=\"number\" id=\"redtime\" name=\"redtime\" min=\"0\" max=\"99\" required><br><br>\n\
    <label for=\"greentime\">GREEN TIME (seconds):</label>\n\
    <input type=\"number\" id=\"greentime\" name=\"greentime\" min=\"0\" max=\"99\" required><br><br>\n\
    <label for=\"yellowtime\">YELLOW TIME (seconds):</label>\n\
    <input type=\"number\" id=\"yellowtime\" name=\"yellowtime\" min=\"0\" max=\"99\" required><br><br>\n\
    <input type=\"submit\" value=\"Save\">\n\
    <input type=\"reset\" value=\"Clear Form\">\n\
  </form>\n\
</body>\n\
</html>";
//--------------------------------------------------------------------------------------
unsigned char UID[5];
unsigned char store_UID[5] = "";

int Server_State = OFF_SERVER;

void SendCommand(char* str){
	command_size = strlen(str);
	HAL_UART_Transmit(&huart3,(uint8_t*)str,strlen(str),HAL_MAX_DELAY);
	if(Server_State == OFF_SERVER) HAL_UART_Receive_IT(&huart3, data_byte_receive,1);
}
void WaitForResponse(int timeout,char* OKE_response,char* Error_response){
	uint32_t tickStart = HAL_GetTick();
		while(Flag_Response == 0){
			if(HAL_GetTick()-tickStart > timeout){
				count_data_come = 0;
				idx=0;
				command_size=0;
				return;
			}
			if(strstr((char*)ESP_Response,OKE_response) != NULL){
				Flag_Response = 1;
			}
			else if(strstr((char*)ESP_Response,Error_response) != NULL){
				Flag_Response = 2;
			}
		}
		idx=0;
		command_size =0;
		count_data_come = 0;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){
	if(Flag_Response == 0||Server_State==ON_SERVER) HAL_UART_Receive_IT(&huart3, data_byte_receive, 1);
		count_data_come++;
		if(count_data_come > command_size){
			ESP_Response[idx++] = data_byte_receive[0];
			if(idx>=1000){ //+IPD
				idx = 0;
			}
		}
}
void ESP_INIT(){
	SendCommand("AT+RESTORE\r\n");
	WaitForResponse(20000,"ready\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
//	if(Flag_Response==1){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT rst OKE\r",sizeof("AT rst OKE\r"),HAL_MAX_DELAY);
//	}
//	else if(Flag_Response==2){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT rst ERROR\r",sizeof("AT rst ERROR\r"),HAL_MAX_DELAY);
//	}
	Flag_Response = 0;
	SendCommand("AT+CWMODE=1\r\n");
	WaitForResponse(5000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
//	if(Flag_Response==1){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CWMODE OKE\r",sizeof("AT CWMODE OKE\r"),HAL_MAX_DELAY);
//	}
//	else if(Flag_Response==2){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CWMODE ERROR\r",sizeof("AT CWMODE ERROR\r"),HAL_MAX_DELAY);
//	}
	Flag_Response = 0;
	sprintf(buffer,"AT+CWJAP=%s,%s\r\n",SSID,Pass);
	SendCommand(buffer);
	memset(buffer,0,sizeof(buffer));
	WaitForResponse(20000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
//	if(Flag_Response==1){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CWJAP OKE\r",sizeof("AT CWJAP OKE\r"),HAL_MAX_DELAY);
//	}
//	else if(Flag_Response==2){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CWJAP ERROR\r",sizeof("AT CWJAP ERROR\r"),HAL_MAX_DELAY);
//	}

	Flag_Response = 0;
	SendCommand("AT+CIPMUX=1\r\n");
	WaitForResponse(5000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
//	if(Flag_Response==1){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CIPMUX OKE\r",sizeof("AT CIPMUX OKE\r"),HAL_MAX_DELAY);
//		}
//	else if(Flag_Response==2){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CIPMUX ERROR\r",sizeof("AT CIPMUX ERROR\r"),HAL_MAX_DELAY);
//	}

	Flag_Response = 0;
	SendCommand("AT+CIPSERVER=1,80\r\n");
	WaitForResponse(5000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
//	if(Flag_Response==1){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CIPSERVER OKE\r",sizeof("AT CIPSERVER OKE\r"),HAL_MAX_DELAY);
//	}
//	else if(Flag_Response==2){
//		HAL_UART_Transmit(&huart3,(uint8_t*)"AT CIPSERVER ERROR\r",sizeof("AT CIPSERVER ERROR\r"),HAL_MAX_DELAY);
//	}
	Server_State = ON_SERVER;
	HAL_UART_Receive_IT(&huart3, data_byte_receive, 1);
}
void Server_Send(int linkID,char* str){
	Flag_Response = 0;
	sprintf(buffer,"AT+CIPSEND=%d,%d\r\n",linkID,strlen(str));
	SendCommand(buffer);
	memset(buffer,0,sizeof(buffer));
	WaitForResponse(10000,">","ERROR");
	memset(ESP_Response,0,sizeof(ESP_Response));

	Flag_Response = 0;
	HAL_UART_Transmit(&huart3,(uint8_t*)str,strlen(str),HAL_MAX_DELAY);
	WaitForResponse(20000,"SEND OK","SEND FAIL");
	memset(ESP_Response,0,sizeof(ESP_Response));

	Flag_Response = 0;
	sprintf(buffer,"AT+CIPCLOSE=%d\r\n",linkID);
	SendCommand(buffer);
	memset(buffer,0,sizeof(buffer));
	WaitForResponse(10000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
}
void server_on(){
	char* pos = strstr((char*)ESP_Response,"+IPD,");
	if(pos!=NULL){
			store_char = Link_ID;
			Link_ID = (*(pos+5));
	}
	if(store_char == Link_ID && Link_ID >='0' && Link_ID <= '4'){
		if(strstr((char*)ESP_Response,"GET")!=NULL){
		   if(strstr((char*)ESP_Response,"/home")!=NULL){
			    Server_Send(Link_ID-48, home);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/manual")!=NULL){
				status_fsm = RED_GREEN_MANUAL;
				lcd_clear_display();
				Server_Send(Link_ID-48,manual);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/redgreen")!=NULL){
				status_fsm = RED_GREEN_MANUAL;
				Server_Send(Link_ID-48,manual);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/redyellow")!=NULL){
				status_fsm = RED_YELLOW_MANUAL;
				Server_Send(Link_ID-48,manual);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/greenred")!=NULL){
				status_fsm = GREEN_RED_MANUAL;
				Server_Send(Link_ID-48,manual);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));

			}
			else if(strstr((char*)ESP_Response,"/yellowred")!=NULL){
				status_fsm = YELLOW_RED_MANUAL;
				Server_Send(Link_ID-48,manual);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/run")!=NULL){
				lcd_clear_display();
				status_fsm = INIT;
				Server_Send(Link_ID-48, home);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/ ")!=NULL){
				Server_Send(Link_ID-48, home);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
		}
	}
}
