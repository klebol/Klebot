/*
 * motors.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_MOTORS_MOTORS_H_
#define INC_MOTORS_MOTORS_H_

#include "drv8836.h"
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

//
// Init
//
void Motors_Init(void);


//
// Encoder routine
//

/* Encoder sampling routine, made to be used in timer interrupt with encoder sampling frequency */
void Motors_EncoderSample(void);

//
// Motors setters
//

/* Setting all motor parameters at once */
void Motors_SetMotor(DRV8836_Output_t motorAB, DRV8836_Direction_t direction, uint16_t speed);
/* Setting PWM only, direction remain the same */
Motors_Error_t Motors_SetMotorPWM(DRV8836_Output_t motorAB, uint16_t speed);
/* Setting direction only, PWM remain the same */
Motors_Error_t Motors_SetMotorDirection(DRV8836_Output_t motorAB, DRV8836_Direction_t direction);
/* Turn all motors OFF */
Motors_Error_t Motors_SetMotorsOff(void);

//
// Motors getters
//

/* Get current motor PWM */
uint16_t Motors_GetMotorPWM(DRV8836_Output_t motorAB);
/* Get current motor direction */
DRV8836_Direction_t Motors_GetMotorDirection(DRV8836_Output_t motorAB);
/* Get real motor velocity */
float Motors_GetMotorVelocity(DRV8836_Output_t motorAB);

//
// Basic PID Related functions
//

/* Enable or disable PID controll */
Motors_Error_t Motors_SetControllPID(uint8_t ONOFF);
/* Set target speed for motor */
Motors_Error_t Motors_SetPIDTarget(DRV8836_Output_t motorAB, int16_t Target);
/* Get motors target speed */
int16_t Motors_GetPIDTarget(DRV8836_Output_t motorAB);

//
// PID Tuning functions
//

/* Set KP */
Motors_Error_t Motors_SetKP(DRV8836_Output_t motorAB, float p);
/* Get KP */
float Motors_GetKP(DRV8836_Output_t motorAB);
/* Set KI */
Motors_Error_t Motors_SetKI(DRV8836_Output_t motorAB, float i);
/* Get KI */
float Motors_GetKI(DRV8836_Output_t motorAB);
/* Set KD */
Motors_Error_t Motors_SetKD(DRV8836_Output_t motorAB, float d);
/* Get KD */
float Motors_GetKD(DRV8836_Output_t motorAB);
/* Reset all gains */
Motors_Error_t Motors_ResetPIDGains(DRV8836_Output_t motorAB);
/* Reset temporary PID's variables */
Motors_Error_t Motors_ResetTemps(DRV8836_Output_t motorAB);

#endif /* INC_MOTORS_MOTORS_H_ */
