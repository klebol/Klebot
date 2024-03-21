/*
 * parser_task.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_PARSER_TASK_H_
#define INC_PARSER_TASK_H_

#include "stdint.h"
#include "klebot_commands.h"

typedef enum
{
	RADIO_SOURCE,
	UART_SOURCE,
	MENU_SOURCE
}Parser_Origin_t;

typedef enum
{
	PARSER_OK,
	PARSER_FULL,
	PARSER_ERROR
}Parser_Error_t;


typedef struct
{
	uint8_t data[MAX_COMMAND_LENGTH];
	uint8_t length;
	Parser_Origin_t origin;
}Parser_Command_t;


/* Init parser task */
void Parser_TaskInit(void);
/* Put command into parses queue */
Parser_Error_t Parser_WriteCommand(Parser_Command_t* cmd, Parser_Origin_t source);



#endif /* INC_PARSER_TASK_H_ */
