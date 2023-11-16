/*
 * controller_programs.c
 *
 *  Created on: Nov 16, 2023
 *      Author: Michal Klebokowski
 */

#include "main.h"
#include "controller_programs.h"
#include "ssd1106.h"

Programs_status_t (*ProgramToPerform)(void);	//pointer to program to execute, in this project



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
		return PROGRAM_IN_PROGESS;
	}

}

void SetTestBlink(void)
{
	ProgramToPerform = &TestBlinkProgram;
}
