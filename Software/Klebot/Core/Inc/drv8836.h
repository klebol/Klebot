/*
 * drv8836.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_DRV8836_H_
#define INC_DRV8836_H_

#include "tim.h"

/*	THIS LIBRARY SUPPORTS DRV8836 MODE 0 ONLY
 * 	This library was written to use with HAL and one 4-channel timer
 * 	Max PWM Frequency according to datasheet : 250kHz
 *
 */

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

typedef struct
{
	uint8_t sleep;
	TIM_HandleTypeDef *drv_htim;
	uint16_t a_forward_channel;
	uint16_t a_reverse_channel;
	uint16_t b_forward_channel;
	uint16_t b_reverse_channel;
	uint16_t a_speed;
	uint16_t b_speed;
	DRV8836_Direction_t a_direction;
	DRV8836_Direction_t b_direction;
}DRV8836_t;


void DRV8836_Init(DRV8836_t *ic, TIM_HandleTypeDef *htim, uint16_t a_forward_channel, uint16_t a_reverse_channel, uint16_t b_forward_channel, uint16_t b_reverse_channel);
void DRV8836_SetDirection(DRV8836_t *ic, DRV8836_Output_t output, DRV8836_Direction_t direction);
void DRV8836_SetSpeed(DRV8836_t *ic, DRV8836_Output_t output, uint16_t speed);


#endif /* INC_DRV8836_H_ */
