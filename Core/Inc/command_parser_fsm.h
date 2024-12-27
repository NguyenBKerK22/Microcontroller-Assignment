#ifndef _COMMAND_PARSER_H
#define _COMMAND_PARSER_H

#include <main.h>
#include <global.h>

#define MAX_BUFFER_SIZE 30

#define CMD_PARSER_INIT 20

#define CMD_PARSER_IDLE 0
#define CMD_PARSER_MARK 1
#define CMD_PARSER_R 2
#define CMD_PARSER_RU 3
#define CMD_PARSER_RUN 4
#define CMD_PARSER_RY 5
#define CMD_PARSER_RG 6
#define CMD_PARSER_Y 7
#define CMD_PARSER_YR 8
#define CMD_PARSER_G 9
#define CMD_PARSER_GR 10
#define CMD_PARSER_M 11
#define CMD_PARSER_MA 12
#define CMD_PARSER_MAN 13
#define CMD_PARSER_S 14
#define CMD_PARSER_SE 15
#define CMD_PARSER_SET 16
#define CMD_PARSER_SHARP 17
#define CMD_PARSER_STAR 18

extern uint8_t buffer[MAX_BUFFER_SIZE];
extern UART_HandleTypeDef huart3;
extern int process_idx;
extern int old_process_idx;

void command_parser_init();
void command_parser_fsm();

uint8_t getRunFlag();
void setRunFlag(uint8_t value);
uint8_t getRYFlag();
void setRYFlag(uint8_t value);
uint8_t getRGFlag();
void setRGFlag(uint8_t value);
uint8_t getYRFlag();
void setYRFlag(uint8_t value);
uint8_t getGRFlag();
void setGRFlag(uint8_t value);
uint8_t getSetFlag();
void setSetFlag(uint8_t value);
uint8_t getManFlag();
void setManFlag(uint8_t value);
uint8_t getDataFlag();
void setDataFlag(uint8_t value);

uint8_t getBufferFlag();
void setBufferFlag(uint8_t value);

#endif
