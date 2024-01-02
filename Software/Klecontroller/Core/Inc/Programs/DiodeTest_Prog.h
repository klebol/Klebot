/*
 * DiodeTest_Prog.h
 *
 *  Created on: Dec 9, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_PROGRAMS_DIODETEST_PROG_H_
#define INC_PROGRAMS_DIODETEST_PROG_H_

#include "Programs/controller_programs.h"


void Prog_DiodeTestLaunch(void);
Programs_error_t Prog_DiodeTestProgram(void);
void Prog_DiodeTestParser(uint8_t *command, uint8_t length);
Programs_error_t Prog_DiodeTestInit(void);
Programs_error_t Prog_DiodeTestDeinit(void);

#endif /* INC_PROGRAMS_DIODETEST_PROG_H_ */
