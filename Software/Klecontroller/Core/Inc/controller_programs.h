/*
 * controller_programs.h
 *
 *  Created on: Nov 16, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_CONTROLLER_PROGRAMS_H_
#define INC_CONTROLLER_PROGRAMS_H_

typedef enum
{
	NO_PROGRAM_SET,
	PROGRAM_COMPLETED,
	PROGRAM_IN_PROGESS
}Programs_status_t;


void Programs_ClearProgram(void);

Programs_status_t Programs_PerformProgram(void);

void SetTestBlink(void);

#endif /* INC_CONTROLLER_PROGRAMS_H_ */
