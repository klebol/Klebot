/*
 * PROGRAM_TEMPLATE.h
 *
 *  Created on: Dec 14, 2023
 *      Author: miqix
 */

#ifndef INC_PROGRAMS_PROGRAM_TEMPLATE_H_
#define INC_PROGRAMS_PROGRAM_TEMPLATE_H_

#include "Programs/controller_programs.h"


typedef struct
{
	uint8_t ProgramExitFlag;
	uint32_t TimeoutStamp;
}TEMPLATEProgramData_t;


void Programs_TEMPLATEParser(uint8_t *command, uint8_t length);
void Programs_TEMPLATESet(void);
void Programs_TEMPLATEExitProgram(void);


#endif /* INC_PROGRAMS_PROGRAM_TEMPLATE_H_ */
