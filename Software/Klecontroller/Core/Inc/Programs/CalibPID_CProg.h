/*
 * CalibPID_CProg.h
 *
 *  Created on: Feb 9, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_PROGRAMS_CALIBPID_CPROG_H_
#define INC_PROGRAMS_CALIBPID_CPROG_H_

#include "Programs/controller_programs.h"

void Prog_CalibPID_Launch(void);

Programs_error_t Prog_CalibPID_Init(void);

Programs_error_t Prog_CalibPID_Deinit(void);

Programs_error_t Prog_CalibPID_Program(void);

void Prog_CalibPID_Parser(uint8_t *command, uint8_t length);

#endif /* INC_PROGRAMS_CALIBPID_CPROG_H_ */