  /*
 * simple_scheduler.c
 *
 *  Created on: 7 maj 2023
 *      Author: miqix
 */
#include "simple_scheduler.h"



uint8_t (*ProgramToPerform)(void);

//
//=====
//

void Scheduler_SetProgramPointer(uint8_t (*Program)(void))
{
	ProgramToPerform = Program;
}

void ToggleLed(void)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

static void MenuTaskInit(void)
{
	Inputs_ButtonsRegisterCallback(ENC_BUTTON, Menu_Select, Menu_Back);
	Inputs_ButtonsRegisterCallback(UP_BUTTON, Menu_Select, NULL);
	Inputs_ButtonsRegisterCallback(UP_BUTTON, Menu_Back, NULL);
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
	uint8_t IsSubProgramCompleted;

	if(0 == StartupInitFlag)
	{
		MenuTaskInit();								//Init for menu
	}

	Inputs_ButtonsRoutine();

	if(ProgramToPerform != NULL)					//if there is a pointer to program
	{
		IsSubProgramCompleted = ProgramToPerform();	//keep executing it till it's completed
		if(IsSubProgramCompleted)
		{
			ProgramToPerform = NULL;				//when it's completed NULL the pointer in order to go to the menu in next loop
			Inputs_ClearButtonsCallbacks();			//clear callbacks for buttons after last subprogram
			MenuTaskInit(); 						//Init for menu again
		}
	}
	else											//if there is no pointer to program, perform menu task
	{
		MenuTask();
	}
}


