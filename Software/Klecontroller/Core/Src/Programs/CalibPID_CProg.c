/*
 * CalibPID_CProg.c
 *
 *  Created on: Feb 9, 2024
 *      Author: Michal Klebokowski
 */
#include "Programs/CalibPID_CProg.h"
#include "Programs/controller_programs.h"

#include "klebot_radio.h"
#include "klebot_commands.h"
#include "ssd1106.h"
#include "controller_inputs.h"

//
// -- Program struct variable --
//
Programs_Program_t CalibPIDProgram = {&Prog_CalibPID_Init, &Prog_CalibPID_Deinit, &Prog_CalibPID_Program, &Prog_CalibPID_Parser, PID_CALIBRATION};
//
// -- Specific program (data) variables --
//
float Kp_A, Ki_A, Kd_A;
float Kp_B, Ki_B, Kd_B;


//
// -- Specific program functions --
//



//
// -- Init & Deinit functions for Motors Debug Program --
//
Programs_error_t Prog_CalibPID_Init(void)
{
	Inputs_ClearButtonsCallbacks();
//	Inputs_ButtonsRegisterCallback(ENC_BUTTON, &Prog_MotorsDebug_ChangeMotor, NULL);
//	Inputs_ButtonsRegisterCallback(UP_BUTTON, &Prog_MotorsDebug_ChangeDirection, NULL);
//	Inputs_ButtonsRegisterCallback(DOWN_BUTTON, NULL, &Programs_ExitProgram);


	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_SendBuffer();
	return PROGRAMS_OK;
}

Programs_error_t Prog_CalibPID_Deinit(void)
{

	return PROGRAMS_OK;
}

//
// -- Main Diode Test Program for Controller --
//

Programs_error_t Prog_CalibPID_Program(void)
{
	/* Main program "loop" */



	return PROGRAMS_OK;
}

//
// -- Set / Launch function --
//

void Prog_CalibPID_Launch(void)
{
	Programs_SetProgram(&CalibPIDProgram);
}

//
// -- Program Parser --
//

void Prog_CalibPID_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;

	switch(*CurrentByte)
	{


	default:
		break;
	}
}


