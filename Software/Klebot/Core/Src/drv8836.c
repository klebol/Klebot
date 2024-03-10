/*
 * drv8836.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Michal Klebokowski
 */
#include "drv8836.h"
#include "tim.h"

void DRV8836_Init(DRV8836_t *ic, TIM_HandleTypeDef *htim, uint16_t a_forward_channel, uint16_t a_reverse_channel, uint16_t b_forward_channel, uint16_t b_reverse_channel)
{
	ic->drv_htim = htim;
	ic->a_forward_channel = a_forward_channel;
	ic->a_reverse_channel = a_reverse_channel;
	ic->b_forward_channel = b_forward_channel;
	ic->b_reverse_channel = b_reverse_channel;
	HAL_TIM_PWM_Start(ic->drv_htim, ic->a_forward_channel);
	HAL_TIM_PWM_Start(ic->drv_htim, ic->a_reverse_channel);
	HAL_TIM_PWM_Start(ic->drv_htim, ic->b_forward_channel);
	HAL_TIM_PWM_Start(ic->drv_htim, ic->b_reverse_channel);
	__HAL_TIM_SET_COMPARE(ic->drv_htim, a_forward_channel, 0);
	__HAL_TIM_SET_COMPARE(ic->drv_htim, a_reverse_channel, 0);
	__HAL_TIM_SET_COMPARE(ic->drv_htim, b_forward_channel, 0);
	__HAL_TIM_SET_COMPARE(ic->drv_htim, b_reverse_channel, 0);
}

DRV8836_Error_t DRV8836_SetMotor(DRV8836_t *ic, DRV8836_Output_t output, DRV8836_Direction_t direction, uint16_t speed)
{
	DRV8836_Direction_t *TargetDirection;
	uint16_t *TargetSpeed;
	uint16_t TargetForwardChannel;
	uint16_t TargetReverseChannel;

	if(speed > ic->drv_htim->Instance->ARR) //check if pwm value fit the counter period range
	{
		return DRV8836_ERROR;
	}

	if(MOTOR_A == output)
	{
		TargetForwardChannel = ic->a_forward_channel;
		TargetReverseChannel = ic->a_reverse_channel;
		TargetSpeed = &(ic->a_speed);
		TargetDirection = &(ic->a_direction);			//TODO: test here
	}
	else if(MOTOR_B == output)
	{
		TargetForwardChannel = ic->b_forward_channel;
		TargetReverseChannel = ic->b_reverse_channel;
		TargetSpeed = &(ic->b_speed);
		TargetDirection = &(ic->b_direction);
	}
	else
	{
		return DRV8836_ERROR;
	}

	switch(direction)
	{
	case Coast:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, 0);
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, 0);
		break;

	case Reverse:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, 0);
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, speed);
		break;

	case Forward:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, speed);
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, 0);
		break;

	case Brake:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, ic->drv_htim->Init.Period);	//TODO: CHECK IF IT WORKS CORRECTLY!
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, ic->drv_htim->Init.Period);
		break;

	default:
		return DRV8836_ERROR;
		break;
	}

	*TargetDirection = direction;	//save set direction and speed to struct
	*TargetSpeed = speed;

	return DRV8836_OK;
}


