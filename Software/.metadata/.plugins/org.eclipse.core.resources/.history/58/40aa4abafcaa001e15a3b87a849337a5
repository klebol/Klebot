/*
 * MotorsDebugControll_Prog.h
 *
 *  Created on: Dec 31, 2023
 *      Author: miqix
 */

#ifndef INC_PROGRAMS_MOTORSDEBUGCONTROLL_PROG_H_
#define INC_PROGRAMS_MOTORSDEBUGCONTROLL_PROG_H_

#include "Programs/controller_programs.h"


typedef struct
{
	uint8_t ProgramExitFlag;
	uint32_t TimeoutStamp;
	uint8_t MotorSpeedA;
	uint8_t MotorSpeedB;
	uint8_t MotorDirA;
	uint8_t MotorDirB;
}MotorsProgramData_t;


void Programs_MotorsDebugControllParser(uint8_t *command, uint8_t length);
void Programs_MotorsDebugControllSet(void);
void Programs_MotorsDebugControllExitProgram(void);


#endif /* INC_PROGRAMS_MOTORSDEBUGCONTROLL_PROG_H_ */
