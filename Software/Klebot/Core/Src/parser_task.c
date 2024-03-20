/*
 * parser_task.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Michal Klebokowski
 */
#include "parser_task.h"
/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* HAL */

/* Other */
#include "klebot_commands.h"



//TODO: PROGRAMS MODULE WHICH WILL START AND STOP NEW MASTER TASKS, ITS OWN PARSER WILL BE INTEGRATED INSIDE, AND CALLED HERE
//TODO: THE SAME FOR HARDWARE BUT HARDWARE TASK WILL BE ALWAYS ON.
//TODO: DATA TO CONTROLLER WILL BE SEND ONLY AFTER QUERY. QUERING HARDWARE WILL BE ALWAYS POSSIBLE, BUT SETTING THE VALUES CAN BE DONE ONLY IF NO PROGRAM HAVE CONTROLL OVER HW
//TODO: COMMAND -> HARDWARE -> SET -> CHECK IF ITS FREE
//TODO: COMMAND -> HARDWARE -> GET -> ALWAYS POSSIBLE
//TODO: COMMAND -> PROGRAM -> CHECK IF ITS RUNNING

QueueHandle_t QueueParser;

Parser_Error_t Parser_ProgramParser(uint8_t* cmd, uint8_t length)
{
	uint8_t *Command = cmd;

	switch(*Command)
	{
	case PID_CALIBRATION:

		break;

	}
}

Parser_Error_t Parser_HardwareParser(uint8_t* cmd, uint8_t length)
{

}

void vTaskParser(void *pvParameters)
{
	QueueParser = xQueueCreate(10, sizeof(Parser_Command_t));
	Parser_Command_t CommandBuffer;

	for(;;)
	{
		/* Wait for frame to parse */
		xQueueReceive(QueueParser, &CommandBuffer, portMAX_DELAY);
		/* Check header */
		switch(CommandBuffer.data[0])
		{
		case PROGRAM_CMD:
			Parser_ProgramParser((CommandBuffer.data) + 1, CommandBuffer.length - 1 );
			break;
		case HARDWARE_CMD:
			Parser_HardwareParser((CommandBuffer.data) + 1, CommandBuffer.length - 1 );
			break;

		default:
			break;
		}
	}
}





/* Put data on next free slot in cmd */
Parser_Error_t Parser_AddElementToCmd(Parser_Command_t* cmd, uint8_t element)
{
	if(cmd->length > MAX_COMMAND_LENGTH)
	{
		return PARSER_ERROR;
	}
	/* Put data on next slot */
	cmd->data[cmd->length] = element;
	cmd->length++;
	return PARSER_OK;
}

/* Put command into queue for parser to execute */
Parser_Error_t Parser_WriteCommand(Parser_Command_t* cmd, Parser_Origin_t source)
{

	if(xQueueSendToBack( QueueParser, cmd, (TickType_t)10 ) != pdTRUE )
	{
		/* If put to queue failed */
		return PARSER_ERROR;
	}

	return PARSER_OK;
}


