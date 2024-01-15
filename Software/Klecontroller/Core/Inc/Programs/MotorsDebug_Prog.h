/*
 * MotorsDebug_Prog.h
 *
 *  Created on: Jan 4, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_PROGRAMS_MOTORSDEBUG_PROG_H_
#define INC_PROGRAMS_MOTORSDEBUG_PROG_H_

#include "Programs/controller_programs.h"

typedef enum
{
	Coast = 0,
	Reverse = 1,
	Forward = 2,
	Brake = 3
}DRV8836_Direction_t;

typedef enum
{
	Output_A = 0,
	Output_B = 1
}DRV8836_Output_t;

typedef enum
{
	DRV8836_OK,
	DRV8836_ERROR
}DRV8836_Error_t;



typedef struct
{
	DRV8836_Direction_t MotorDirection;
	uint8_t PWM;
	char Name[10];
	DRV8836_Output_t ID;
}MotorsDebug_Motor_t;



void Prog_MotorsDebug_Launch(void);

Programs_error_t Prog_MotorsDebug_Init(void);

Programs_error_t Prog_MotorsDebug_Deinit(void);

Programs_error_t Prog_MotorsDebug_Program(void);

void Prog_MotorsDebug_Parser(uint8_t *command, uint8_t length);

#endif /* INC_PROGRAMS_MOTORSDEBUG_PROG_H_ */
