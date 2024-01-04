/*
 * DiodeTest_Prog.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Michal Klebokowski
 */

#include "Programs/DiodeTest_Prog.h"
#include "Programs/controller_programs.h"

#include "klebot_radio.h"
#include "klebot_commands.h"
#include "ssd1106.h"
#include "controller_inputs.h"

//
// -- Program struct variable --
//
Programs_Program_t DiodeTestProgram = {&Prog_DiodeTest_Init, &Prog_DiodeTest_Deinit, &Prog_DiodeTest_Program, DIODE_TEST};

//
// -- Specific program (data) variables --
//

uint8_t DiodeState;

//
// -- Setting LED on/off --
//
static void Prog_DiodeTest_SendOnCmd(void)
{
	uint8_t Buffer[2];
	Buffer[0] = DIODE_TEST;
	Buffer[1] = DIODE_SET_ON;
	Radio_TxBufferPut(Buffer, 2);
}

static void Prog_DiodeTest_SendOffCmd(void)
{
	uint8_t Buffer[2];
	Buffer[0] = DIODE_TEST;
	Buffer[1] = DIODE_SET_OFF;
	Radio_TxBufferPut(Buffer, 2);
}

//
// -- Init & Deinit functions for Diode Test Program --
//
Programs_error_t Prog_DiodeTest_Init(void)
{
	Inputs_ClearButtonsCallbacks();
	Inputs_ButtonsRegisterCallback(UP_BUTTON, &Prog_DiodeTest_SendOnCmd, NULL);
	Inputs_ButtonsRegisterCallback(DOWN_BUTTON, &Prog_DiodeTest_SendOffCmd, NULL);
	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_SendBuffer();
	return PROGRAMS_OK;
}

Programs_error_t Prog_DiodeTest_Deinit(void)
{
	DiodeState = 0;
	return PROGRAMS_OK;
}

//
// -- Main Diode Test Program for Controller --
//

Programs_error_t Prog_DiodeTest_Program(void)
{
	/* Main program "loop" */
	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_WriteString("LED STATE:", WHITE);
	OLED_MoveCursor(0, 16);
	OLED_WriteInt(DiodeState, WHITE);
	OLED_SendBuffer();

	return PROGRAMS_OK;
}

//
// -- Set / Launch function --
//

void Prog_DiodeTest_Launch(void)
{
	Programs_SetProgram(&DiodeTestProgram);
}

//
// -- Program Parser --
//

void Prog_DiodeTest_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;

	switch(*CurrentByte)
	{
	case DIODE_REAL_STATE:
		CurrentByte++;
		DiodeState = *CurrentByte;
		break;

	default:
		break;
	}
}



