/*
 * controller_programs.c
 *
 *  Created on: Nov 16, 2023
 *      Author: Michal Klebokowski
 */

#include "main.h"
#include "controller_programs.h"
#include "simple_scheduler.h"

void Programs_StartJoystickCalib(void) 		//this fun go for menu
{
	Scheduler_SetProgramPointer(NULL);
}

