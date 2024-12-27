#include <command_parser_fsm.h>

//#define STATE_INIT 8
//#define STATE_IDLE 0
//#define STATE_MARK 1
//#define STATE_R 2
//#define STATE_S 3
//#define STATE_T 4
//#define STATE_O 5
//#define STATE_K 6
//#define STATE_SHARP 7

//int status = CMD_PARSER_IDLE;
int status = INIT;

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE] = {1};
uint8_t index_buffer = 0;
uint8_t idx = 0;
uint8_t buffer_flag = 0;

uint8_t run_flag = 0;
uint8_t ry_flag = 0;
uint8_t rg_flag = 0;
uint8_t yr_flag = 0;
uint8_t gr_flag = 0;
uint8_t set_flag = 0;
uint8_t man_flag = 0;
uint8_t data_flag = 0;


uint8_t request_flag = 0;
uint8_t ok_flag = 0;


void command_parser_init() {
	HAL_UART_Receive_IT(&huart3, &temp, 1);
}
;
uint8_t getRunFlag() {
	return run_flag;
}
;
void setRunFlag(uint8_t value) {
	run_flag = value;
}
;
uint8_t getRYFlag() {
	return ry_flag;
}
;
void setRYFlag(uint8_t value) {
	ry_flag = value;
}
;
uint8_t getRGFlag() {
	return rg_flag;
}
;
void setRGFlag(uint8_t value) {
	rg_flag = value;
}
;
uint8_t getYRFlag() {
	return yr_flag;
}
;
void setYRFlag(uint8_t value) {
	yr_flag = value;
}
;
uint8_t getGRFlag() {
	return gr_flag;
}
;
void setGRFlag(uint8_t value) {
	gr_flag = value;
}
;
uint8_t getSetFlag() {
	return set_flag;
}
;
void setSetFlag(uint8_t value) {
	set_flag = value;
}
;
uint8_t getManFlag() {
	return man_flag;
}
;
void setManFlag(uint8_t value) {
	man_flag = value;
}
;
uint8_t getDataFlag() {
	return data_flag;
}
;
void setDataFlag(uint8_t value) {
	data_flag = value;
}
;
uint8_t getBufferFlag() {
	return buffer_flag;
}
;
void setBufferFlag(uint8_t value) {
	buffer_flag = value;
}
;

int process_idx = 0;
int old_process_idx = 0;
void command_parser_fsm() {
	switch (status) {
	case CMD_PARSER_INIT:
		status = CMD_PARSER_IDLE;
		break;
	case CMD_PARSER_IDLE:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
	case CMD_PARSER_MARK: // this is !
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			HAL_UART_Transmit(&huart3, (unsigned char*)'N', 1, 1000);
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'r') {
			status = CMD_PARSER_R;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'y') {
			status = CMD_PARSER_Y;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'g') {
			status = CMD_PARSER_G;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 's') {
			status = CMD_PARSER_S;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'm') {
			status = CMD_PARSER_M;
			buffer_flag = 0;
			break;
		}
		;
		if(buffer[idx] == '*'){
			status = CMD_PARSER_STAR;
			buffer_flag = 0;
			break;

		};
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_STAR:
			idx = process_idx % 30;
			if (buffer[idx] == '!') {
				status = CMD_PARSER_MARK;
				buffer_flag = 0;
				break;
			}
			;
			if (buffer[idx] == '#') { // !*r00&y00&g00#
				old_process_idx = process_idx;
				data_flag = 1;
				break;
			}
			;
			buffer_flag = 0;
			break;
	case CMD_PARSER_R:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'g') {
			status = CMD_PARSER_RG;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'u') {
			status = CMD_PARSER_RU;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'y') {
			status = CMD_PARSER_RY;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_RU:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'n') {
			status = CMD_PARSER_RUN;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_RY:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			ry_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_RG:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			rg_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_RUN:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			run_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_Y:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'r') {
			status = CMD_PARSER_YR;
			buffer_flag = 0;
			break;
		}
		;

		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_YR:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			yr_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_G:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'r') {
			status = CMD_PARSER_GR;
			buffer_flag = 0;
			break;
		}
		;

		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_GR:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			gr_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_M:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'a') {
			status = CMD_PARSER_MA;
			HAL_UART_Transmit(&huart3, (unsigned char*)'N', 1, 1000);
			buffer_flag = 0;
			break;
		}
		;

		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_S:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'e') {
			status = CMD_PARSER_SE;
			buffer_flag = 0;
			break;
		}
		;

		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_MA:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 'n') {
			status = CMD_PARSER_MAN;
			buffer_flag = 0;
			break;
		}
		;

		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_SE:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == 't') {
			status = CMD_PARSER_SET;
			buffer_flag = 0;
			break;
		}
		;

		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_MAN:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			man_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
	case CMD_PARSER_SET:
		idx = process_idx % 30;
		if (buffer[idx] == '!') {
			status = CMD_PARSER_MARK;
			buffer_flag = 0;
			break;
		}
		;
		if (buffer[idx] == '#') {
			status = CMD_PARSER_IDLE;
			// do something like set flag, timer 3s ...
			set_flag = 1;
			buffer_flag = 0;
			break;
		}
		;
		status = CMD_PARSER_IDLE;
		buffer_flag = 0;
		break;
//	case STATE_SHARP:
//		status = IDLE;
//		break;
	default:
		break;
	};
	if(process_idx >= index_buffer){

		}else{
			process_idx += 1;
		};
}
;





void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART3) {
		buffer[index_buffer++%30] = temp;

		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart3, &temp, 1);
	};
}
;
