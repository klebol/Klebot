/*
 * DiodeTest_Prog.c
 *
 *  Created on: Dec 4, 2023
 *      Author: miqix
 */
#include "Programs/DiodeTest_Prog.h"

uint8_t ProgramExitFlag;

//
// -- Main Diode Test Program for Robot --
//
Programs_status_t Programs_DiodeTestProgram(void)
{
	static uint8_t StartupInitFlag = 0;
	if(0 == StartupInitFlag)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		StartupInitFlag = 1;
	}

	if(1 == ProgramExitFlag)
	{
		ProgramExitFlag = 0;
		StartupInitFlag = 0;
		return PROGRAM_COMPLETED;
	}
	return PROGRAM_IN_PROGRESS;
}

//
// -- Diode Test Program Parser --
//

void Programs_DiodeTestParser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	uint8_t Buffer[3];

	switch(*CurrentByte)
	{
	case START_PROGRAM:
		if(PROGRAMS_OK == Programs_SetProgram(Programs_DiodeTestProgram) )
		{
			Programs_SendProgramStartedACK(DIODE_TEST);
		}
		break;

	case DIODE_SET_ON:
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		Buffer[0] = DIODE_TEST;
		Buffer[1] = DIODE_REAL_STATE;
		Buffer[2] = 1;
		Radio_TxBufferPut(Buffer, 3);
		break;

	case DIODE_SET_OFF:
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		Buffer[0] = DIODE_TEST;
		Buffer[1] = DIODE_REAL_STATE;
		Buffer[2] = 0;
		Radio_TxBufferPut(Buffer, 3);
		break;

	case EXIT_PROGRAM:
		ProgramExitFlag = 1;
		Programs_SendProgramExitACK(DIODE_TEST);
		break;

	default:
		break;
	}

}
