/*
 * CalibPID_Prog.h
 *
 *  Created on: Feb 6, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_PROGRAMS_CALIBPID_PROG_H_
#define INC_PROGRAMS_CALIBPID_PROG_H_

#include "Programs/klebot_programs.h"

Programs_error_t Prog_CalibPID_Launch(void);

Programs_error_t Prog_CalibPID_Init(void);

Programs_error_t Prog_CalibPID_Deinit(void);

Programs_error_t Prog_CalibPID_Program(void);

void Prog_CalibPID_Parser(uint8_t *command, uint8_t length);

#endif /* INC_PROGRAMS_CALIBPID_PROG_H_ */
