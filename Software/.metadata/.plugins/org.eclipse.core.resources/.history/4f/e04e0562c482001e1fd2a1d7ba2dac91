/*
 * simple_scheduler.c
 *
 *  Created on: 7 maj 2023
 *      Author: miqix
 */
#include "simple_scheduler.h"





//
//Programs
//

void MenuTask(void)
{
	static uint8_t FirstEnterFlag = 0;
	int8_t EncoderRotation = 0;

	if(0 == FirstEnterFlag)
	{
		Menu_RefreshScreen();
		FirstEnterFlag = 1;
	}

	EncoderRotation = Inputs_GetEncoderCount();

	if(EncoderRotation > 0)
	{
		Menu_Next();
	}
	else if(EncoderRotation < 0)
	{
		Menu_Prev();
	}

}

void SimpleScheduler(void)
{
	MenuTask();
}
