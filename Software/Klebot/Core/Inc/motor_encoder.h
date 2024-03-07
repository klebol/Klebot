/*
 * motor_encoder.h
 *
 *  Created on: Dec 14, 2023
 *      Author: miqix
 */

#ifndef INC_MOTORS_MOTOR_ENCODER_H_
#define INC_MOTORS_MOTOR_ENCODER_H_

#include "tim.h"

#define PULSES_PER_ROTATION 1400
#define ENCODER_SAMPLING_TIME_MS 10

typedef struct{
	TIM_HandleTypeDef *htimEnc;
	int8_t Velocity;
	float VelocityFiltered;
	int16_t Position;
	uint32_t LastCounter;
	float RPM;



}MotorEncoder_t;

void MotorEnc_Init(MotorEncoder_t *encoder, TIM_HandleTypeDef *htim);
void MotorEnc_Uptade(MotorEncoder_t *encoder);
void MotorEnc_Update(MotorEncoder_t *encoder);
void MotorEnc_FilterVelocity(MotorEncoder_t *encoder);



#endif /* INC_MOTORS_MOTOR_ENCODER_H_ */
