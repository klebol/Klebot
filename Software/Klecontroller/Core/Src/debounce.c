/*
 * debounce.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Michal Klebokowski
 */


#include "debounce.h"

void DB_ButtonInit(DB_Button_t *Button, GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin, uint32_t DebounceTime_ms, uint32_t HoldTime_ms)
{
	Button->Button_Port = GPIOx;
	Button->Button_Pin = Gpio_Pin;
	Button->DebounceTime_ms = DebounceTime_ms;
	Button->HoldTime_ms = HoldTime_ms;
	Button->ButtonState = IDLE;
	Button->ButtonPressAction = NULL;
	Button->ButtonHoldAction = NULL;
}

void DB_ButtonPressCallbackRegister(DB_Button_t *Button, void(*PressActionFun)(void), void(*HoldActionFun)(void))
{
	Button->ButtonPressAction = PressActionFun;
	Button->ButtonHoldAction = HoldActionFun;
}

static uint8_t DB_IsButtonPressed(DB_Button_t *Button)
{
	if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Button->Button_Port, Button->Button_Pin) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void DB_ButtonProcess(DB_Button_t *Button)	//pass a handle to timer with 1ms tick! Don't forget to start a timer in main loop
{
	switch(Button->ButtonState)
	{
	case IDLE:
		if(DB_IsButtonPressed(Button))
		{
			Button->ButtonState = DEBOUNCE;
			Button->LastTick = HAL_GetTick();
		}
		break;
	case DEBOUNCE:
		if(HAL_GetTick() - (Button->LastTick) > (Button->DebounceTime_ms) )
		{
			if(DB_IsButtonPressed(Button))
			{
				Button->ButtonState = PRESSED;
				Button->LastTick = HAL_GetTick();
			}
			else
			{
				Button->ButtonState = IDLE;
			}
		}
		break;
	case PRESSED:
		if(HAL_GetTick() - (Button->LastTick) > 50 )
		{
			if(DB_IsButtonPressed(Button))
			{
				Button->ButtonState = HOLD;
				Button->LastTick = HAL_GetTick();
			}
			else
			{
				if(NULL != Button->ButtonPressAction)
				{
					Button->ButtonPressAction();
				}
				Button->ButtonState = IDLE;
				printf("Debounce: Button pressed! \n");
			}
		}
		break;
	case HOLD:
		if(HAL_GetTick() - (Button->LastTick) > (Button->HoldTime_ms) )
		{
			if(DB_IsButtonPressed(Button) && NULL != Button->ButtonHoldAction)
			{
				Button->ButtonHoldAction();
			}

			Button->ButtonState = IDLE;
			printf("Debounce: Button held! \r\n");
		}
	}
}
