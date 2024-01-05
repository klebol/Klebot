/*
 * MotorsDebug_Prog.h
 *
 *  Created on: Jan 5, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_PROGRAMS_MOTORSDEBUG_PROG_H_
#define INC_PROGRAMS_MOTORSDEBUG_PROG_H_

#include "Programs/klebot_programs.h"

Programs_error_t Prog_MotorsDebug_Launch(void);

Programs_error_t Prog_MotorsDebug_Init(void);

Programs_error_t Prog_MotorsDebug_Deinit(void);

Programs_error_t Prog_MotorsDebug_Program(void);

void Prog_MotorsDebug_Parser(uint8_t *command, uint8_t length);

#endif /* INC_PROGRAMS_MOTORSDEBUG_PROG_H_ */
