/*
 * DiodeTest_Prog.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_PROGRAMS_DIODETEST_PROG_H_
#define INC_PROGRAMS_DIODETEST_PROG_H_

#include "Programs/controller_programs.h"
#include "klebot_radio.h"

typedef struct
{
	uint8_t DiodeState;
	uint8_t ProgramExitFlag;
}DiodeTestProgramData_t;


void Programs_DiodeTestParser(uint8_t *command, uint8_t length);
void Programs_DiodeTestSet(void);
void Programs_DiodeTestExitProgram(void);

#endif /* INC_PROGRAMS_DIODETEST_PROG_H_ */
