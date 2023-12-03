/*
 * klebot_programs.h
 *
 *  Created on: Nov 29, 2023
 *      Author: miqix
 */

#ifndef INC_KLEBOT_PROGRAMS_H_
#define INC_KLEBOT_PROGRAMS_H_

#include "klebot_commands.h"
#include "drv8836.h"
#include "tim.h"



//
// --- Status typedef ---
//

typedef enum
{
	NO_PROGRAM_SET,
	PROGRAM_COMPLETED,
	PROGRAM_IN_PROGESS,
	PROGRAM_LAUNCH_ERROR
}Programs_status_t;


//
// --- Functions ---
//

Programs_status_t (*Programs_GetProgram(void))(void);
void Programs_ClearProgram(void);

Programs_status_t Programs_PerformProgram(void);

Programs_status_t FreeRide (void);

void FreeRide_Parser(uint8_t *command, uint8_t length);

#endif /* INC_KLEBOT_PROGRAMS_H_ */
