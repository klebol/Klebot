/*
 * drv8836.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Michal Klebokowski
 */
#include "drv8836.h"

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

void DRV8836_SetDirection(DRV8836_t *ic, DRV8836_Output_t output, DRV8836_Direction_t direction)		//maybe this set of 2 function can be raplaced by: set speed, set direction, apply changes
{																										//also consider switch to gpio when coast and brake because of spikes
	DRV8836_Direction_t *TargetDirection;
	uint16_t TargetForwardChannel;
	uint16_t TargetReverseChannel;
	uint16_t TargetSpeed;

	if(Output_A == output)
	{
		TargetForwardChannel = ic->a_forward_channel;
		TargetReverseChannel = ic->a_reverse_channel;
		TargetSpeed = ic->a_speed;
		TargetDirection = &(ic->a_direction);			//TODO: test here
	}
	else if(Output_B == output)
	{
		TargetForwardChannel = ic->b_forward_channel;
		TargetReverseChannel = ic->b_reverse_channel;
		TargetSpeed = ic->b_speed;
		TargetDirection = &(ic->b_direction);
	}
	else
	{
		//error
	}

	switch(direction)
	{
	case Coast:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, 0);
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, 0);
		break;

	case Reverse:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, 0);
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, TargetSpeed);
		break;

	case Forward:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, TargetSpeed);
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, 0);
		break;

	case Brake:
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetForwardChannel, ic->drv_htim->Init.Period);	//TODO: CHECK IF IT WORKS CORRECTLY!
		__HAL_TIM_SET_COMPARE(ic->drv_htim, TargetReverseChannel, ic->drv_htim->Init.Period);
		break;

	default:
		break;
	}

	*TargetDirection = direction;	//save set direction
}

void DRV8836_SetSpeed(DRV8836_t *ic, DRV8836_Output_t output, uint16_t speed)
{
	if(speed > ic->drv_htim->Init.Period)
	{
		//error
		ic->a_speed = speed;
				DRV8836_SetDirection(ic, output, ic->a_direction);
	}

	if(Output_A == output)
	{
		ic->a_speed = speed;
		DRV8836_SetDirection(ic, output, ic->a_direction);
	}
	else if(Output_B == output)
	{
		ic->b_speed = speed;
		DRV8836_SetDirection(ic, output, ic->b_direction);
	}
	else
	{

	}

}
