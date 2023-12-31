/*
 * MotorsDebug_Prog.c
 *
 *  Created on: Jan 5, 2024
 *      Author: Michal Klebokowski
 */

#include "Programs/klebot_programs.h"
#include "Programs/MotorsDebug_Prog.h"
#include "Motors/motors.h"
#include "klebot_commands.h"
#include "klebot_radio.h"
#include "gpio.h"

//
// -- Program struct variable --
//

Programs_Program_t MotorsDebugProgram = {&Prog_MotorsDebug_Init, &Prog_MotorsDebug_Deinit, &Prog_MotorsDebug_Program, &Prog_MotorsDebug_Parser, MOTORS_DEBUG};

//
// -- Init & Deinit functions for Diode Test Program --
//

Programs_error_t Prog_MotorsDebug_Init(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	Motors_SetMotorsOff();
	return PROGRAMS_OK;

}

Programs_error_t Prog_MotorsDebug_Deinit(void)
{
	Motors_SetMotorsOff();
	return PROGRAMS_OK;
}

//
// -- Main Diode Test Program for Robot --
//

Programs_error_t Prog_MotorsDebug_Program(void)
{
	/* Main program "loop" */
	return PROGRAMS_OK;
}

//
// -- Set / Launch function --
//

Programs_error_t Prog_MotorsDebug_Launch(void)
{
	return Programs_SetProgram(&MotorsDebugProgram);
}

//
// -- Diode Test Program Parser --
//

void Prog_MotorsDebug_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;

	DRV8836_Output_t Motor;
	DRV8836_Direction_t ReceivedDir;
	uint8_t ReceivedPWM;

	switch(*CurrentByte)
	{
	case MOTOR_SET_PWM:
		/* Frame: [... , MOTORS_SET_PWM, Motor ID, PWM Value] */ 	//TODO: Check pwm wideness thing
		Motor = *(CurrentByte + 1);									//TODO: The same value writing safety
		ReceivedPWM = *(CurrentByte + 2);
		Motors_SetMotorSpeed(Motor, ReceivedPWM);
		break;

	case MOTOR_SET_DIRECTION:
		/* Frame: [... , MOTORS_SET_DIRECTION, Motor ID, Direction] */
		Motor = *(CurrentByte + 1);
		ReceivedDir = *(CurrentByte + 2);
		Motors_SetMotorDirection(Motor, ReceivedDir);
		break;
		break;

	default:
		/* Unknown command! */
		break;
	}

}

