/*
 * MotorsDebug_Prog.c
 *
 *  Created on: Jan 4, 2024
 *      Author: Michal Klebokowski
 */

#include "Programs/MotorsDebug_Prog.h"
#include "Programs/controller_programs.h"

#include "klebot_radio.h"
#include "klebot_commands.h"
#include "ssd1106.h"
#include "controller_inputs.h"

//
// -- Program struct variable --
//
Programs_Program_t MotorsDebugProgram = {&Prog_MotorsDebug_Init, &Prog_MotorsDebug_Deinit, &Prog_MotorsDebug_Program, MOTORS_DEBUG};

//
// -- Specific program (data) variables --
//



//
// -- Specific program functions --
//


//
// -- Init & Deinit functions for Motors Debug Program --
//
Programs_error_t Prog_MotorsDebug_Init(void)
{
	Inputs_ClearButtonsCallbacks();
	Inputs_ButtonsRegisterCallback(ENC_BUTTON, NULL, &Programs_ExitProgram);


	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_SendBuffer();
	return PROGRAMS_OK;
}

Programs_error_t Prog_MotorsDebug_Deinit(void)
{

	return PROGRAMS_OK;
}

//
// -- Main Diode Test Program for Controller --
//

Programs_error_t Prog_MotorsDebug_Program(void)
{
	/* Main program "loop" */
	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);

	OLED_SendBuffer();

	return PROGRAMS_OK;
}

//
// -- Set / Launch function --
//

void Prog_MotorsDebug_Launch(void)
{
	Programs_SetProgram(&MotorsDebugProgram);
}

//
// -- Program Parser --
//

void Prog_MotorsDebug_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;

	switch(*CurrentByte)
	{


	default:
		break;
	}
}

