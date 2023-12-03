/*
 * controller_programs.h
 *
 *  Created on: Nov 16, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_CONTROLLER_PROGRAMS_H_
#define INC_CONTROLLER_PROGRAMS_H_

#include "main.h"
#include "ssd1106.h"
#include "controller_inputs.h"
#include "klebot_radio.h"

#define PROGRAM_START_TIMEOUT_MS 1000

typedef enum
{
	NO_PROGRAM_SET,
	PROGRAM_COMPLETED,
	PROGRAM_IN_PROGRESS,
	PROGRAM_LAUNCH_ERROR
}Programs_status_t;

typedef enum
{
	PROGRAMS_OK,
	PROGRAMS_ERROR
}Programs_error_t;

//
// PROGRAMS TYPES
//

typedef struct
{
	uint8_t DiodeState;
	uint8_t ProgramExitFlag;
}DiodeTestProgramData_t;


void Programs_ClearProgram(void);

Programs_status_t Programs_PerformProgram(void);

void SetTestBlink(void);

Programs_status_t FreeRideControll(void);

void SetFreeRideControll(void);

void Programs_DiodeTestParser(uint8_t *command, uint8_t length);

void Programs_DiodeTestSet(void);

#endif /* INC_CONTROLLER_PROGRAMS_H_ */
