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
#include "Programs/klebot_programs.h"
#include "hw_manager.h"

/* Programs */
#include "Programs/klebot_programs.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebug_Prog.h"
#include "Programs/CalibPID_Prog.h"



//TODO: PROGRAMS MODULE WHICH WILL START AND STOP NEW MASTER TASKS, ITS OWN PARSER WILL BE INTEGRATED INSIDE, AND CALLED HERE
//TODO: THE SAME FOR HARDWARE BUT HARDWARE TASKS! WILL BE ALWAYS ON.
//TODO: DATA TO CONTROLLER WILL BE SEND ONLY AFTER QUERY. QUERING HARDWARE WILL BE ALWAYS POSSIBLE, BUT SETTING THE VALUES CAN BE DONE ONLY IF NO PROGRAM HAVE CONTROLL OVER HW
//TODO: COMMAND -> HARDWARE -> SET -> CHECK IF ITS FREE
//TODO: COMMAND -> HARDWARE -> GET -> ALWAYS POSSIBLE
//TODO: COMMAND -> PROGRAM -> CHECK IF ITS RUNNING

QueueHandle_t QueueParser;



//
// Programs side Parsers
//
void Parser_ParseProgramLaunchCommand(uint8_t ProgramID)
{
	uint8_t status;
	/* Launch proper program */
	/* When another program is currently running, launch function will return error */
	switch(ProgramID)
	{
	case DIODE_TEST:
		status = Prog_DiodeTest_Launch();
		break;

	case MOTORS_DEBUG:
		status = Prog_MotorsDebug_Launch();
		break;

	case PID_CALIBRATION:
		status = Prog_CalibPID_Launch();

	default:
		status = PROGRAMS_ERROR;
		break;
	}

	/* Send ACK to controller */
	if(status == PROGRAMS_OK)
	{
		Programs_SendProgramStartedACK(ProgramID, ACK);		//TODO: Maybe ACK should be sent after each program Init function ?
	}
	else
	{
		Programs_SendProgramStartedACK(ProgramID, NACK);
	}
}

Parser_Error_t Parser_ProgramParser(uint8_t* cmd, uint8_t length)
{
	uint8_t *CurrentByte = cmd;
	uint8_t Length = length;
	Programs_Program_t* CurrentProgram = Programs_GetProgram();

	switch(*CurrentByte)
	{
	case PROGRAM_COMMAND:
		/* Frame: [PROGRAM_CMD, PROGRAM_COMMAND, PROGRAM_ID, Specific program commands...] */
		CurrentByte++;
		Length--;

		/* Check if there is any program running */
		if(NULL == CurrentProgram)
		{
			/* No program running, send NACK */
			break;
		}
		/* Check if the command matches currently running program ID */
		if(*CurrentByte == CurrentProgram->ProgramID)
		{
			CurrentByte++;
			Length--;
			/* Pass the command to program's parser */
			CurrentProgram->ProgramParser(CurrentByte, Length);
		}
		else
		{
			/* Another program running, send NACK */
			Programs_SendInvalidProgramNACK(*CurrentByte);
		}
		break;

	case START_PROGRAM:
		/* Frame: [PROGRAM_CMD, START_PROGRAM, PROGRAM_ID] */
		uint8_t ProgramToLaunch = *(CurrentByte + 1);
		/* This takes care if some program is already running or not */
		Parser_ParseProgramLaunchCommand(ProgramToLaunch);
		break;

	case EXIT_PROGRAM:
		/* Frame: [PROGRAM_CMD, PROGRAM_EXIT] */
		if(Programs_ExitProgram() == PROGRAMS_OK)
		{
			Programs_SendProgramExitACK(ACK);
		}
		else
		{
			Programs_SendProgramExitACK(NACK);
		}
		break;

	default:
		/* Incorrect command! */
		break;
	}

	return PARSER_OK;
}

//
// Hardware side parsers
//

Parser_Error_t Parser_HardwareParser(uint8_t* cmd, uint8_t length)
{
	//uint8_t *Command = cmd;
	return PARSER_OK;



}


//
// The Task
//
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
		case PROGRAM_FRAME:
			Parser_ProgramParser((CommandBuffer.data) + 1, CommandBuffer.length - 1 );
			break;
		case HARDWARE_FRAME:
			HW_Manager_Parser((CommandBuffer.data) + 1, CommandBuffer.length - 1 );
			break;

		default:
			break;
		}
	}
}

void Parser_TaskInit(void)
{
	xTaskCreate(vTaskParser, "Parser Task", 512, NULL, 1, NULL);
}


//
// API for other modules
//

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
	cmd->origin = source;

	if(xQueueSendToBack( QueueParser, cmd, (TickType_t)10 ) != pdTRUE )
	{
		/* If put to queue failed */
		return PARSER_ERROR;
	}

	return PARSER_OK;
}

