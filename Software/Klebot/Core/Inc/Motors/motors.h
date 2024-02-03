/*
 * motors.h
 *
 *  Created on: Dec 30, 2023
 *      Author: miqix
 */

#ifndef INC_MOTORS_MOTORS_H_
#define INC_MOTORS_MOTORS_H_

#include "Motors/drv8836.h"
#include "tim.h"

typedef enum
{
	MOTORS_OK,
	MOTORS_ERROR
}Motors_Error_t;

void Motors_Init(void);
void Motors_SetMotor(DRV8836_Output_t motorAB, DRV8836_Direction_t direction, uint16_t speed);
Motors_Error_t Motors_SetMotorPWM(DRV8836_Output_t motorAB, uint16_t speed);
Motors_Error_t Motors_SetMotorDirection(DRV8836_Output_t motorAB, DRV8836_Direction_t direction);
void Motors_EncoderSample(void);
Motors_Error_t Motors_SetMotorsOff(void);
uint16_t Motors_GetMotorPWM(DRV8836_Output_t motorAB);
DRV8836_Direction_t Motors_GetMotorDirection(DRV8836_Output_t motorAB);

void Motors_RoutinePID(void);

void Motors_SetPIDTarget(int8_t target);

#endif /* INC_MOTORS_MOTORS_H_ */
