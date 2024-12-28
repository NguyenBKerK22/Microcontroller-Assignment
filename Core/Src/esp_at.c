/*
 * esp_at.c
 *
 *  Created on: Dec 13, 2024
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
<link rel =\"icon\" href=\"data:,\">\n\
<title>TRAFFIC LIGHT ASSIGNMENT</title>\n\
<style>\n\
body{font-family:Arial,sans-serif;text-align:center;margin-top:50px;background:#f9f9f9;color:#333}\n\
h1{color:#2c3e50}\n\
form{margin:15px}\n\
input[type=\"submit\"]{background:#3498db;color:#fff;border:none;padding:10px 25px;font-size:18px;border-radius:5px;cursor:pointer;transition:.3s}\n\
input[type=\"submit\"]:hover{background:#2980b9}\n\
</style>\n\
		<script>\n\
		  const links = document.querySelectorAll('link[rel*=\"icon\"]');\n\
		  links.forEach(link => link.remove());\n\
		</script>\n\
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
<link rel =\"icon\" href=\"data:,\">\n\
<title>TRAFFIC LIGHT ASSIGNMENT</title>\n\
<style>\n\
body{text-align:center;margin-top:50px;background:#f4f4f4;color:#333;font-family:Arial,sans-serif}\n\
h1{color:#2c3e50;margin-bottom:30px}\n\
form{margin:15px}\n\
input[type=\"submit\"]{background:#3498db;color:#fff;border:none;padding:10px 20px;font-size:16px;border-radius:5px;cursor:pointer;transition:.3s;transform:scale(1)}\n\
input[type=\"submit\"]:hover{background:#2980b9;transform:scale(1.05)}\n\
input[type=\"submit\"]:active{background:#1c6a94}\n\
</style>\n\
<script>\n\
  const links = document.querySelectorAll('link[rel*=\"icon\"]');\n\
  links.forEach(link => link.remove());\n\
</script>\n\
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
char *setting = "<!DOCTYPE html><html><head><style>*{font-family:Arial,Helvetica,sans-serif;font-size:medium}h1{font-size:30px}input[type=number]{border-radius:3px;border:1px gray solid}.btn1,.btn2,.btn3{border-radius:5px;border:none;color:#000;font-weight:700;padding:5px 10px 5px 10px;cursor:pointer}.btn1{background-color:#a7d477}.btn2{background-color:#ffb200}.btn3{background-color:#0d92f4}form{margin-top:40px;width:300px;min-height:150px;display:flex;flex-direction:column;justify-content:space-around}.roww{display:flex;justify-content:space-between}</style></head><body style=\"display:flex;flex-direction:column;align-items:center;justify-content:center\"><h1>LIGHT TRAFFICT SETTING</h1><form action=\"/save\"><div class=\"roww\"><label for=\"redtime\">Light red time (s):</label><input type=\"number\" id=\"redtime\" name=\"redtime\" min=\"0\" max=\"99\" required></div><div class=\"roww\"><label for=\"greentime\">Light green time (s):</label><input type=\"number\" id=\"greentime\" name=\"greentime\" min=\"0\" max=\"99\" required></div><div class=\"roww\"><label for=\"yellowtime\">Light yellow time (s):</label><input type=\"number\" id=\"yellowtime\" name=\"yellowtime\" min=\"0\" max=\"99\" required></div><div style=\"display:flex;justify-content:space-around;margin-top:10px\"><input type=\"submit\" class=\"btn1\" value=\"Save\"> <input type=\"reset\" class=\"btn2\" value=\"Clear Form\"></div></form><button class=\"btn3\" onclick=\"location.href='/run'\">Run</button></body></html>";
//--------------------------------------------------------------------------------------

int Server_State = OFF_SERVER;

void SendCommand(char* str){
	command_size = strlen(str);
	HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),HAL_MAX_DELAY);
	if(Server_State == OFF_SERVER) HAL_UART_Receive_IT(&huart1, data_byte_receive,1);
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
	if(Flag_Response == 0||Server_State==ON_SERVER) HAL_UART_Receive_IT(&huart1, data_byte_receive, 1);
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
	if(Flag_Response == 1){
		HAL_UART_Transmit(&huart3, (uint8_t*)"OKE", 3, 100);
	}
	else if(Flag_Response == 2){
		HAL_UART_Transmit(&huart3, (uint8_t*)"ERR", 3, 100);
	}
	Flag_Response = 0;
	SendCommand("AT+CWMODE=1\r\n");
	WaitForResponse(5000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
	if(Flag_Response == 1){
		HAL_UART_Transmit(&huart3, (uint8_t*)"OKE", 3, 100);
	}
	else if(Flag_Response == 2){
		HAL_UART_Transmit(&huart3, (uint8_t*)"ERR", 3, 100);
	}
	Flag_Response = 0;
	sprintf(buffer,"AT+CWJAP=%s,%s\r\n",SSID,Pass);
	SendCommand(buffer);
	memset(buffer,0,sizeof(buffer));
	WaitForResponse(20000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
	if(Flag_Response == 1){
		HAL_UART_Transmit(&huart3, (uint8_t*)"OKE", 3, 100);
	}
	else if(Flag_Response == 2){
		HAL_UART_Transmit(&huart3, (uint8_t*)"ERR", 3, 100);
	}
	Flag_Response = 0;
	SendCommand("AT+CIPMUX=1\r\n");
	WaitForResponse(5000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
	if(Flag_Response == 1){
			HAL_UART_Transmit(&huart3, (uint8_t*)"OKE", 3, 100);
		}
		else if(Flag_Response == 2){
			HAL_UART_Transmit(&huart3, (uint8_t*)"ERR", 3, 100);
		}
	Flag_Response = 0;
	SendCommand("AT+CIPSERVER=1,80\r\n");
	WaitForResponse(5000,"OK\r\n","ERROR\r\n");
	memset(ESP_Response,0,sizeof(ESP_Response));
	if(Flag_Response == 1){
			HAL_UART_Transmit(&huart3, (uint8_t*)"OKE", 3, 100);
		}
		else if(Flag_Response == 2){
			HAL_UART_Transmit(&huart3, (uint8_t*)"ERR", 3, 100);
		}
	Server_State = ON_SERVER;
	HAL_UART_Receive_IT(&huart1, data_byte_receive, 1);
}
void Server_Send(int linkID,char* str){
	Flag_Response = 0;
	sprintf(buffer,"AT+CIPSEND=%d,%d\r\n",linkID,strlen(str));
	SendCommand(buffer);
	memset(buffer,0,sizeof(buffer));
	WaitForResponse(10000,">","ERROR");
	memset(ESP_Response,0,sizeof(ESP_Response));

	Flag_Response = 0;
	HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),HAL_MAX_DELAY);
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
				Server_Send(Link_ID-48,manual);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!man#", 5, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/redgreen")!=NULL){
				Server_Send(Link_ID-48,manual);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!rg#", 4, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/redyellow")!=NULL){
				Server_Send(Link_ID-48,manual);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!ry#", 4, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/greenred")!=NULL){
				Server_Send(Link_ID-48,manual);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!gr#", 4, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/yellowred")!=NULL){
				Server_Send(Link_ID-48,manual);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!yr#", 4, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/run")!=NULL){
				Server_Send(Link_ID-48, home);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!run#", 5, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"/setting")!=NULL){
				Server_Send(Link_ID-48,setting);
				HAL_UART_Transmit(&huart3, (uint8_t*)"!set#", 5, 100);
				Flag_Response = 0;
				WaitForResponse(10000, "\r\n", "ERROR\r\n");
				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
			}
			else if(strstr((char*)ESP_Response,"redtime")!=NULL){
				char* substr = strstr((char*)ESP_Response,"redtime");
				while(strstr((char*)ESP_Response,"HTTP")==NULL);
				strtok(substr," ");
				char* infor_red = strtok(substr,"&");
				char* infor_green = strtok(NULL,"&");
				char *infor_yellow = strtok(NULL, "&");
				int time_red;
				int time_green;
				int time_yellow;
				infor_red = strstr(infor_red, "=") + 1;
				infor_green = strstr(infor_green, "=") + 1;
				infor_yellow = strstr(infor_yellow, "=") + 1;
				if(strlen(infor_red) == 1){
					time_red = infor_red[0]-48;
				}
				else{
					time_red = (infor_red[0]-48)*10 + (infor_red[1]-48);
				}
				if(strlen(infor_yellow) == 1){
					time_yellow = infor_yellow[0]-48;
				}
				else{
					time_yellow = (infor_yellow[0]-48)*10 + (infor_yellow[1]-48);
				}
				if(strlen(infor_green) == 1){
					time_green = infor_green[0]-48;
				}
				else{
					time_green = (infor_green[0]-48)*10 + (infor_green[1]-48);
				}
				sprintf(buffer,"!*r%d%d&y%d%d&g%d%d#",time_red/10,time_red%10,time_yellow/10,time_yellow%10,time_green/10,time_green%10);
				HAL_UART_Transmit(&huart3,(uint8_t*)buffer,14, 100);
				memset(buffer,0,sizeof(buffer));
				Server_Send(Link_ID-48,setting);
//				Flag_Response = 0;
//				WaitForResponse(10000, "\r\n", "ERROR\r\n");
//				if(Flag_Response == 1) memset(ESP_Response,0,sizeof(ESP_Response));
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
