/*
 * klebot_scheduler.c
 *
 *  Created on: Nov 28, 2023
 *      Author: miqix
 */

#include "klebot_scheduler.h"

uint8_t CommandSource = RADIO_DATA_SOURCE;

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

	}
	else if(SubProgramStatus == PROGRAM_LAUNCH_ERROR)
	{

	}

	//app pointer



}





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
