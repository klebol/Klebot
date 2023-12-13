  /*
 * simple_scheduler.c
 *
 *  Created on: 7 maj 2023
 *      Author: miqix
 */
#include "simple_scheduler.h"





//
//=====
//



void ToggleLed(void)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

static void MenuTaskInit(void)
{
	Inputs_ButtonsRegisterCallback(ENC_BUTTON, Menu_Select, Menu_Back);
	Inputs_ButtonsRegisterCallback(UP_BUTTON, Menu_Select, NULL);
	Inputs_ButtonsRegisterCallback(DOWN_BUTTON, Menu_Back, NULL);
	Menu_RefreshScreen();
}

static void MenuTask(void)
{
	int8_t EncoderRotation = 0;

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
	static uint8_t StartupInitFlag = 0;
	Programs_status_t SubProgramStatus;

	Radio_Process();

	if(0 == StartupInitFlag)
	{
		MenuTaskInit();								//Init for menu
		StartupInitFlag = 1;
	}

	Inputs_ButtonsRoutine();
	SubProgramStatus = Programs_PerformProgram();

	if(SubProgramStatus == PROGRAM_COMPLETED)
	{
		Programs_ClearProgram();					//clear program pointer to go to menu next time
		Inputs_ClearButtonsCallbacks();				//clear callbacks for buttons after last subprogram
		MenuTaskInit(); 							//Init for menu again
	}
	else if(SubProgramStatus == NO_PROGRAM_SET)		//if there is no pointer to program, perform menu task
	{
		MenuTask();
	}
	else if(SubProgramStatus == PROGRAM_LAUNCH_ERROR)
	{
		Programs_ClearProgram();					//clear program pointer to go to menu next time
		Inputs_ClearButtonsCallbacks();				//clear callbacks for buttons after last subprogram
		MenuTaskInit(); 							//Init for menu again
	}
	else if(SubProgramStatus == PROGRAM_EXIT_ERROR)
	{
		Programs_ClearProgram();					//clear program pointer to go to menu next time
		Inputs_ClearButtonsCallbacks();				//clear callbacks for buttons after last subprogram
		MenuTaskInit(); 							//Init for menu again
	}
}

//
//
//

void Radio_NewCommandReceivedCallback(uint8_t *command, uint8_t length)
{
	Parser_Controller(command, length);
}
