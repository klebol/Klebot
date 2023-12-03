/*
 * controller_programs.c
 *
 *  Created on: Nov 16, 2023
 *      Author: Michal Klebokowski
 */

#include "controller_programs.h"

Programs_status_t (*ProgramToPerform)(void);	//pointer to program to execute, in this project
static uint8_t CurrentRobotProgramID;

DiodeTestProgramData_t DiodeTestDatabase;


void Programs_SetProgram(uint8_t (*Program)(void))
{
	ProgramToPerform = Program;
}

void Programs_ClearProgram(void)
{
	ProgramToPerform = NULL;
}

Programs_status_t Programs_PerformProgram(void)
{
	Programs_status_t status;
	if(NULL != ProgramToPerform)		//if there is a program to perform
	{
		status = ProgramToPerform();	//perform it and return it's status
	}
	else
	{
		status = NO_PROGRAM_SET;
	}
	return status;
}

static Programs_error_t Programs_SendProgramStartCommand(uint8_t ProgramID)
{
	uint8_t Buffer[2];
	Buffer[0] = ProgramID;
	Buffer[1] = START_PROGRAM;
	return Radio_TxBufferPut(Buffer, 2);
}

static Programs_error_t Programs_SendProgramExitCommand(uint8_t ProgramID)
{
	uint8_t Buffer[2];
	Buffer[0] = ProgramID;
	Buffer[1] = EXIT_PROGRAM;
	return Radio_TxBufferPut(Buffer, 2);
}

//
// --- DIODE TEST PROGRAM ---
//



void Programs_DiodeTestSendOnCmd(void)
{
	uint8_t Buffer[2];
	Buffer[0] = DIODE_TEST;
	Buffer[1] = DIODE_SET_ON;
	Radio_TxBufferPut(Buffer, 2);
}

void Programs_DiodeTestSendOffCmd(void)
{
	uint8_t Buffer[2];
	Buffer[0] = DIODE_TEST;
	Buffer[1] = DIODE_SET_OFF;
	Radio_TxBufferPut(Buffer, 2);
}

void Programs_DiodeTestExitProgram(void)
{
	DiodeTestDatabase.ProgramExitFlag = 1;
	Programs_SendProgramExitCommand(DIODE_TEST);
}

Programs_status_t Programs_DiodeTestProgram(void)
{
	static uint8_t FirstEntry = 0;
	static uint32_t LaunchTimeoutStamp = 0;
	if(0 == FirstEntry)
	{
		Inputs_ClearButtonsCallbacks();
		Inputs_ButtonsRegisterCallback(UP_BUTTON, &Programs_DiodeTestSendOnCmd, &Programs_DiodeTestExitProgram);
		Inputs_ButtonsRegisterCallback(DOWN_BUTTON, &Programs_DiodeTestSendOffCmd, NULL);
		Programs_SendProgramStartCommand(DIODE_TEST);
		FirstEntry = 1;
		LaunchTimeoutStamp = HAL_GetTick();				//timestamp in first entry for counting program lauch on klebot timeout
		OLED_ClearBuffer(BLACK);
		OLED_SendBuffer();
	}

	if(DIODE_TEST != CurrentRobotProgramID)				//check if we had response from robot that program has properly started
	{
		if(HAL_GetTick() - LaunchTimeoutStamp > PROGRAM_START_TIMEOUT_MS)
		{
			FirstEntry = 0;
			return PROGRAM_LAUNCH_ERROR;
		}
	}

	if(1 == DiodeTestDatabase.ProgramExitFlag)
	{
		DiodeTestDatabase.ProgramExitFlag = 0;
		DiodeTestDatabase.DiodeState = 0;
		FirstEntry = 0;
		return PROGRAM_COMPLETED;
	}

	OLED_MoveCursor(0, 0);
	OLED_WriteString("LED STATE:", WHITE);
	OLED_MoveCursor(0, 16);
	OLED_WriteInt(DiodeTestDatabase.DiodeState, WHITE);

	return PROGRAM_IN_PROGRESS;
}


void Programs_DiodeTestParser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	//uint8_t Length = length;

	switch(*CurrentByte)
	{
	case START_PROGRAM:
		CurrentByte++;
		if(ACK == *CurrentByte)
		{
			CurrentRobotProgramID = DIODE_TEST;				//ack that program has started
		}
		else
		{
			//ERROR
		}

		break;
	case DIODE_REAL_STATE:
		CurrentByte++;
		DiodeTestDatabase.DiodeState = *CurrentByte;
		break;

	default:

		break;
	}
}

void Programs_DiodeTestSet(void)
{
	ProgramToPerform = &Programs_DiodeTestProgram;
}































Programs_status_t TestBlinkProgram(void)
{
	static uint8_t FirstEntry = 0;
	static uint32_t LastTick;
	static uint8_t state = 0;
	static uint8_t blinks = 0;


	if(0 == FirstEntry)
	{
		OLED_ClearBuffer(BLACK);
		OLED_MoveCursor(0, 0);
		OLED_WriteString("Blinks:",WHITE);
		LastTick = HAL_GetTick();
		OLED_SendBuffer();
		FirstEntry = 1;
	}





	if(HAL_GetTick() - LastTick > 1000)
	{
		switch(state)
		{
		case 0:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			LastTick = HAL_GetTick();
			state = 1;
			break;

		case 1:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			LastTick = HAL_GetTick();
			blinks++;
			state = 0;

			OLED_MoveCursor(64, 0);
			OLED_WriteInt(blinks, WHITE);
			OLED_SendBuffer();
			break;
		}
	}




	if(blinks >= 10)
	{
		return PROGRAM_COMPLETED;
	}
	else
	{
		return PROGRAM_IN_PROGRESS;
	}

}

void SetTestBlink(void)
{
	ProgramToPerform = &TestBlinkProgram;
}


void SetFreeRideControll(void)
{
	ProgramToPerform = &FreeRideControll;
}

Programs_status_t FreeRideControll(void)
{
	static uint8_t FirstEntry = 0;
	uint8_t Cmd[4];

	int8_t DevL;
	int8_t DevR, LastDevR = 0;

	if(0 == FirstEntry)
	{
		Cmd[0] = 0xA1;
		Cmd[1] = 0x10;
		Radio_TxBufferPut(Cmd, 2);
		Inputs_ClearButtonsCallbacks();
		OLED_ClearBuffer(BLACK);
		OLED_MoveCursor(0, 0);
		OLED_SendBuffer();
		FirstEntry = 1;
	}
	OLED_ClearBuffer(BLACK);

	DevR =  Inputs_GetRightJoystickDev(X_AXIS);
	if(DevR > 2 && DevR != LastDevR)
	{

		Cmd[0] = 0xA1;
		Cmd[1] = 0x22;
		Cmd[2] = 1;
		Radio_TxBufferPut(Cmd, 3);
		Cmd[0] = 0xA1;
		Cmd[1] = 0x20;
		Cmd[2] = (DevR * 255) / 100;
		Radio_TxBufferPut(Cmd, 3);
		LastDevR = DevR;

	}
	else
	{

	}

	OLED_MoveCursor(0, 0);
	OLED_WriteString("Right Motor: ", WHITE);
	OLED_MoveCursor(90, 0);
	OLED_WriteInt(DevR, WHITE);

//	OLED_MoveCursor(0, 8);
//	OLED_WriteInt(Inputs_GetRightJoystickDev(Y_AXIS), WHITE);

	DevL = Inputs_GetLeftJoystickDev(X_AXIS);

	OLED_MoveCursor(0, 16);
	OLED_WriteString("LEFT Motor: ", WHITE);
	OLED_MoveCursor(90, 16);
	OLED_WriteInt(DevL, WHITE);

//	OLED_MoveCursor(0, 32);
//	OLED_WriteInt(Inputs_GetLeftJoystickDev(Y_AXIS), WHITE);

	OLED_SendBuffer();

	return PROGRAM_IN_PROGRESS;


}

