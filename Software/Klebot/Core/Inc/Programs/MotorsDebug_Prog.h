/*
 * MotorsDebug_Prog.h
 *
 *  Created on: Dec 30, 2023
 *      Author: miqix
 */

#ifndef INC_PROGRAMS_MOTORSDEBUG_PROG_H_
#define INC_PROGRAMS_MOTORSDEBUG_PROG_H_

#include "Programs/klebot_programs.h"
#include "Motors/motors.h"

Programs_status_t Programs_MotorsDebugProgram(void);
void Programs_MotorsDebugParser(uint8_t *command, uint8_t length);


#endif /* INC_PROGRAMS_MOTORSDEBUG_PROG_H_ */
