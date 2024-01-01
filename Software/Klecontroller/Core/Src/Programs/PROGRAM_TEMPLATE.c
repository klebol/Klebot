/*
 * PROGRAM_TEMPLATE.c
 *
 *  Created on: Dec 14, 2023
 *      Author: miqix
 */

#include "Programs/PROGRAM_TEMPLATE.h"
#include "Programs/controller_programs.h"
#include "klebot_radio.h"
#include "klebot_commands.h"
#include "ssd1106.h"
#include "controller_inputs.h"

TEMPLATEProgramData_t TEMPLATEDatabase;



//
// -- Setting LED on/off --
//
static void Programs_TEMPLATE_CommandSend(void)
{
	uint8_t Buffer[2];
	Buffer[0] = DIODE_TEST;
	Buffer[1] = DIODE_SET_ON;
	Radio_TxBufferPut(Buffer, 2);
}


//
// -- Main Diode Test Program for Controller --
//

Programs_status_t Programs_TEMPLATEProgram(void)
{
	static uint8_t FirstEntry = 0;
	/*First entry, code which will be performed only at the first entry to this program after launching it */
	if(0 == FirstEntry)
	{
		/* Clearing display */
		OLED_ClearBuffer(BLACK);
		OLED_MoveCursor(0, 0);
		OLED_WriteString("Launching TEMPLATE ...", WHITE);
		OLED_SendBuffer();
		FirstEntry = 1;
	}

	/* Program exit process */
	if(1 == TEMPLATEDatabase.ProgramExitFlag)
	{

		/* If there was an exit ACK, CurrentRobotProgramID was cleared by parser */
		if(NO_PROGRAM_SET == Programs_GetCurrentRobotProgramID() )
		{
			TEMPLATEDatabase.ProgramExitFlag = 0;
			FirstEntry = 0;
			return PROGRAM_COMPLETED;
		}
		/* If ACK have not came before timeout, exit program with error */
		else if(HAL_GetTick() - TEMPLATEDatabase.TimeoutStamp > PROGRAM_EXIT_TIMEOUT_MS)
		{
			TEMPLATEDatabase.ProgramExitFlag = 0;
			FirstEntry = 0;
			Programs_ClearCurrentRobotProgramID();
			return PROGRAM_EXIT_ERROR;
		}
	}

	/* Program launch process */
	/* Check if we had response from robot that program has properly started
	 * (parser is writing CurrentRobotProgramID if robot sends start ACK*/
	if(TEMPLATE_PROG != Programs_GetCurrentRobotProgramID() )
	{
		if(HAL_GetTick() - TEMPLATEDatabase.TimeoutStamp > PROGRAM_START_TIMEOUT_MS)
		{
			FirstEntry = 0;
			return PROGRAM_LAUNCH_ERROR;
		}
		else
		{
			return PROGRAM_IN_PROGRESS;
		}
	}

	/* Main program "loop" */
	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_WriteString("TEMPLATE", WHITE);

	OLED_SendBuffer();

	return PROGRAM_IN_PROGRESS;
}

//
// -- Program start/exit --
//

void Programs_TEMPLATESet(void)
{
	/* Send start command to robot */
	Programs_SendProgramStartCommand(TEMPLATE_PROG);
	/* Set this program in this device */
	Programs_SetProgram(Programs_TEMPLATEProgram);
	/* Setting proper buttons funcionality for this program */
	Inputs_ClearButtonsCallbacks();
	Inputs_ButtonsRegisterCallback(UP_BUTTON, &Programs_TEMPLATE_CommandSend, &Programs_TEMPLATEExitProgram);
	Inputs_ButtonsRegisterCallback(DOWN_BUTTON, &Programs_TEMPLATE_CommandSend, NULL);
	/* Timestamp for counting timeout for program launch on Klebot */
	TEMPLATEDatabase.TimeoutStamp = HAL_GetTick();
}

void Programs_TEMPLATEExitProgram(void)
{
	TEMPLATEDatabase.ProgramExitFlag = 1;
	Programs_SendProgramExitCommand(TEMPLATE_PROG);
	/* Timestamp for counting timeout for program exit on Klebot */
	TEMPLATEDatabase.TimeoutStamp = HAL_GetTick();
}

//
// -- Program Parser --
//

void Programs_TEMPLATEParser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	//uint8_t Length = length;

	switch(*CurrentByte)
	{
	case START_PROGRAM:
		CurrentByte++;
		if(ACK == *CurrentByte)
		{
			Programs_SetCurrentRobotProgramID(TEMPLATE_PROG);				//ack that program has started
		}
		else
		{
			//ERROR
		}

		break;

	case EXIT_PROGRAM:
		CurrentByte++;
		if(ACK == *CurrentByte)
		{
			Programs_ClearCurrentRobotProgramID();
		}

	default:

		break;
	}
}





