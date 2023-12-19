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

typedef struct{
	TIM_HandleTypeDef *htimEnc;
	int16_t Velocity;
	float RPM;
	int16_t Position;
	uint32_t LastCounter;
}MotorEncoder_t;

void MotorEnc_Init(MotorEncoder_t *encoder, TIM_HandleTypeDef *htim);
void MotorEnc_Uptade(MotorEncoder_t *encoder);



#endif /* INC_MOTORS_MOTOR_ENCODER_H_ */
