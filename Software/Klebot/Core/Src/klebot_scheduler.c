/*
 * klebot_scheduler.c
 *
 *  Created on: Nov 28, 2023
 *      Author: miqix
 */

#include "klebot_scheduler.h"

uint8_t CommandSource = RADIO_DATA_SOURCE;


static void ConnectionBlinkLED(void)
{
	static uint32_t LastTick = 0;

	if(RADIO_ERROR == Radio_GetConnectionStatus())
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		return;
	}

	if(HAL_GetTick() - LastTick > 500)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		LastTick = HAL_GetTick();
	}
}



void KlebotScheduler(void)
{
	static uint8_t StartupInitFlag = 0;
	Programs_status_t SubProgramStatus;

	Radio_Process();


	if(0 == StartupInitFlag)
	{
		//startup things
		StartupInitFlag = 1;
	}

	SubProgramStatus = Programs_PerformProgram();

	if(SubProgramStatus == PROGRAM_COMPLETED)
	{
		Programs_ClearProgram();

	}
	else if(SubProgramStatus == NO_PROGRAM_SET)
	{
		ConnectionBlinkLED();
	}
	else if(SubProgramStatus == PROGRAM_LAUNCH_ERROR)
	{

	}

	//app pointer



}



//
//Callback from klebot_radio, forwards data if currently selected commands source is radio
//

void Radio_NewCommandReceivedCallback(uint8_t *command, uint8_t length)
{
	if(RADIO_DATA_SOURCE == CommandSource)
	{
		Parser_Klebot(command, length);
	}
	else
	{

	}
}
