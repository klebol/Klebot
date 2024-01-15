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
Programs_Program_t MotorsDebugProgram = {&Prog_MotorsDebug_Init, &Prog_MotorsDebug_Deinit, &Prog_MotorsDebug_Program, &Prog_MotorsDebug_Parser,MOTORS_DEBUG};

//
// -- Specific program (data) variables --
//

//TODO: Create motor info separate files, universal for every program which uses motors


MotorsDebug_Motor_t Motor_0 = {0, 0, "Motor_0", Output_A};
MotorsDebug_Motor_t Motor_1 = {0, 0, "Motor_1", Output_B};
MotorsDebug_Motor_t *ManipulatedMotor;

DRV8836_Direction_t DirectionToSet;
uint8_t PWMToSet;


//
// -- Specific program functions --
//

void Prog_MotorsDebug_ChangeMotor(void)
{
	if(ManipulatedMotor == &Motor_0)
	{
		ManipulatedMotor = &Motor_1;

	}
	else if(ManipulatedMotor == &Motor_1)
	{
		ManipulatedMotor = &Motor_0;
	}

	PWMToSet = ManipulatedMotor->PWM;
	DirectionToSet = ManipulatedMotor->MotorDirection;
}

void Prog_MotorsDebug_ChangeDirection(void)
{

	DirectionToSet = ManipulatedMotor->MotorDirection + 1;
	if(DirectionToSet > 3)
	{
		DirectionToSet = 0;
	}

	uint8_t Buffer[4];
	Buffer[0] = MOTORS_DEBUG;
	Buffer[1] = MOTOR_SET_DIRECTION;
	Buffer[2] = ManipulatedMotor->ID;
	Buffer[3] = DirectionToSet;
	Radio_TxBufferPut(Buffer, 4);

	ManipulatedMotor->MotorDirection = DirectionToSet;
}

void ProgMotorsDebug_ChangeSpeedRoutine(void)
{
	uint8_t Buffer[4];

	PWMToSet += Inputs_GetEncoderCount();

	if(PWMToSet != ManipulatedMotor->PWM)
	{
		Buffer[0] = MOTORS_DEBUG;
		Buffer[1] = MOTOR_SET_PWM;
		Buffer[2] = ManipulatedMotor->ID;
		Buffer[3] = PWMToSet;
		Radio_TxBufferPut(Buffer, 4);
		ManipulatedMotor->PWM = PWMToSet;

	}


}

//
// -- Init & Deinit functions for Motors Debug Program --
//
Programs_error_t Prog_MotorsDebug_Init(void)
{
	Inputs_ClearButtonsCallbacks();
	Inputs_ButtonsRegisterCallback(ENC_BUTTON, &Prog_MotorsDebug_ChangeMotor, NULL);
	Inputs_ButtonsRegisterCallback(UP_BUTTON, &Prog_MotorsDebug_ChangeDirection, NULL);
	Inputs_ButtonsRegisterCallback(DOWN_BUTTON, NULL, &Programs_ExitProgram);
	ManipulatedMotor = &Motor_0;

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

	ProgMotorsDebug_ChangeSpeedRoutine();

	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_WriteString("Motor: ", WHITE);
	OLED_WriteString(ManipulatedMotor->Name, WHITE);
	OLED_MoveCursor(0, 8);
	OLED_WriteString("Direction: :", WHITE);
	OLED_WriteInt(ManipulatedMotor->MotorDirection, WHITE);
	OLED_MoveCursor(0, 16);
	OLED_WriteString("PWM: :", WHITE);
	OLED_WriteInt(ManipulatedMotor->PWM, WHITE);

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

