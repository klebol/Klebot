/*
 * klebot_scheduler.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Michal Klebokowski
 */

#include "klebot_scheduler.h"
#include "Programs/klebot_programs.h"
#include "klebot_radio.h"
#include "klebot_parser.h"


uint8_t CommandSource = RADIO_DATA_SOURCE;

/* Blink LED when controller is connected */
static void ConnectionBlinkLED(void)
{
	static uint32_t LastTick = 0;
	/* Get the connection status */
	if(RADIO_ERROR == Radio_GetConnectionStatus())
	{
		/* If there is no connection, set the LED off and return */
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		return;
	}
	/* Blink the diode if there is connection with controller */
	if(HAL_GetTick() - LastTick > 500)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		LastTick = HAL_GetTick();
	}
}

/* Main scheduler function */
void KlebotScheduler(void)
{
	static uint8_t StartupInitFlag = 0;
	Programs_status_t SubProgramStatus;

	/* Radio process - always active in the background */
	Radio_Process();

	/* Startup sequence */
	if(0 == StartupInitFlag)
	{
		StartupInitFlag = 1;
	}

	/* Perform current program, returns proper status */
	SubProgramStatus = Programs_PerformProgram();

	if(SubProgramStatus == PROGRAM_COMPLETED)
	{
		Programs_ClearProgram();

	}
	else if(SubProgramStatus == NO_PROGRAM_SET)
	{
		ConnectionBlinkLED();
	}
}


/* Callback from klebot_radio, forwards data if currently selected commands source is radio */
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
