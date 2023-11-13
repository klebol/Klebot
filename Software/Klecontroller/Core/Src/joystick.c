/*
 * joystick.c
 *
 *  Created on: 24 lut 2023
 *      Author: Michal Klebokowski
 */

#include "main.h"
#include "joystick.h"

//Use after starting ADC
JOYS_StatusTypeDef JoyS_Init(Joystick_t *Joystick, uint16_t *AdcValueSourceX, uint16_t *AdcValueSourceY)
{
	if(AdcValueSourceX || AdcValueSourceX)
	{
		Joystick->ValX = AdcValueSourceX;
		Joystick->ValY = AdcValueSourceY;
		return JOYS_OK;
	}
	return JOYS_ERROR;
}

//When this function is called, joystick must be in idle position
JOYS_StatusTypeDef JoyS_SetIdleValues(Joystick_t *Joystick)
{
	uint32_t tick = HAL_GetTick();
	while( (HAL_GetTick() - tick) < 100)
	{
		if( ( *(Joystick->ValX) != 0) || ( *(Joystick->ValY) ) != 0 )
		{
			Joystick->IdleX = *(Joystick->ValX);
			Joystick->IdleY = *(Joystick->ValY);
			return JOYS_OK;
		}
	}
	return JOYS_TIMEOUT;
}
JOYS_StatusTypeDef Joy_SetMaxValue(Joystick_t *Joystick, uint8_t axis)
{
	if(Joystick == NULL)
	{
		return JOYS_ERROR;
	}

	if(axis == X_AXIS)
	{
		Joystick->MaxX = *(Joystick->ValX);
	}
	else if(axis == Y_AXIS)
	{
		Joystick->MaxY = *(Joystick->ValY);
	}
	return JOYS_OK;
}

JOYS_StatusTypeDef Joy_SetMinValue(Joystick_t *Joystick, uint8_t axis)
{
	if(Joystick == NULL)
	{
		return JOYS_ERROR;
	}

	if(axis == X_AXIS)
	{
		Joystick->MinX = *(Joystick->ValX);
	}
	else if(axis == Y_AXIS)
	{
		Joystick->MinY = *(Joystick->ValY);
	}
	return JOYS_OK;
}

int8_t Joy_GetDeviationPercent(Joystick_t *Joystick, uint8_t axis)
{
	uint32_t CurrentValue;
	uint32_t IdleValue;

	if(axis == X_AXIS)
	{
		CurrentValue = *(Joystick->ValX);
		IdleValue = Joystick->IdleX;
	}
	else if(axis == Y_AXIS)
	{
		CurrentValue = *(Joystick->ValY);
		IdleValue = Joystick->IdleY;
	}
	else return 0;


	if(CurrentValue >= IdleValue)
	{
		return ( (CurrentValue - IdleValue) * 100) / (4095 - IdleValue);		//formula for positive deviation percentage
	}
	else
	{
		return -100 + ((CurrentValue * 100) / IdleValue);	//formula for negative deviation percentage
	}

}


int8_t Joy_GetDeviationPercentCal(Joystick_t *Joystick, uint8_t axis)
{
	uint32_t CurrentValue;
	uint32_t IdleValue;
	uint32_t MaxValue;
	uint32_t MinValue;

	if(axis == X_AXIS)
	{
		CurrentValue = *(Joystick->ValX);
		IdleValue = Joystick->IdleX;
		MaxValue = Joystick->MaxX;
		MinValue = Joystick->MinX;
	}
	else if(axis == Y_AXIS)
	{
		CurrentValue = *(Joystick->ValY);
		IdleValue = Joystick->IdleY;
		MaxValue = Joystick->MaxY;
		MinValue = Joystick->MinY;
	}
	else return 0;

	if(MaxValue == 0) return 0;

	if(CurrentValue < MinValue)
	{
		CurrentValue = MinValue;
	}
	if(CurrentValue >= IdleValue)
	{
		return ( (CurrentValue - IdleValue) * 100) / (MaxValue - IdleValue);		//formula for positive deviation percentage
	}
	else
	{
		return -100 + ((CurrentValue - MinValue) * 100) / (IdleValue - MinValue);	//formula for negative deviation percentage
	}
}


