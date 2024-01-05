/*
 * DiodeTest_Prog.h
 *
 *  Created on: Dec 4, 2023
 *      Author: miqix
 */

#ifndef INC_PROGRAMS_DIODETEST_PROG_H_
#define INC_PROGRAMS_DIODETEST_PROG_H_

#include "Programs/klebot_programs.h"

Programs_error_t Prog_DiodeTest_Launch(void);

Programs_error_t Prog_DiodeTest_Init(void);

Programs_error_t Prog_DiodeTest_Deinit(void);

Programs_error_t Prog_DiodeTest_Program(void);

void Prog_DiodeTest_Parser(uint8_t *command, uint8_t length);

#endif /* INC_PROGRAMS_DIODETEST_PROG_H_ */
