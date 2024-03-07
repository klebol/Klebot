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

#define DEAD_PWM_OFFSET 150
#define MAX_VELOCITY_VALUE 70
#define PID_ON 1
#define PID_OFF 0

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

Motors_Error_t Motors_SetPIDTarget(DRV8836_Output_t motorAB, int16_t Target);
Motors_Error_t Motors_SetKP(DRV8836_Output_t motorAB, float p);
float Motors_GetKP(DRV8836_Output_t motorAB);
Motors_Error_t Motors_SetKI(DRV8836_Output_t motorAB, float i);
float Motors_GetKI(DRV8836_Output_t motorAB);
Motors_Error_t Motors_SetKD(DRV8836_Output_t motorAB, float d);
float Motors_GetKD(DRV8836_Output_t motorAB);
Motors_Error_t Motors_ResetPIDGains(DRV8836_Output_t motorAB);
Motors_Error_t Motors_ResetTemps(DRV8836_Output_t motorAB);
Motors_Error_t Motors_SetControllPID(uint8_t ONOFF);

#endif /* INC_MOTORS_MOTORS_H_ */
