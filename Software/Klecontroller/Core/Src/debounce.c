/*
 * debounce.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Michal Klebokowski
 */


#include "debounce.h"


void DB_ButtonInit(DB_Button_t *Button, GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin, uint16_t Debounce_ms)
{
	Button->Button_Port = GPIOx;
	Button->Button_Pin = Gpio_Pin;
	Button->DebounceTime_ms = Debounce_ms;
	Button->ButtonState = IDLE;
	Button->ButtonPressAction = NULL;
}


void DB_ButtonPressCallbackRegister(DB_Button_t *Button, void(*ActionFun)(void))
{
	Button->ButtonPressAction = ActionFun;
}

void DB_ButtonProcess(DB_Button_t *Button, TIM_HandleTypeDef *htim)	//pass a handle to timer with 1ms tick! Don't forget to start a timer in main loop
{
	switch(Button->ButtonState)
	{
	case IDLE:
		if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Button->Button_Port, Button->Button_Pin) )
		{
			Button->ButtonState = DEBOUNCE;
			Button->TimTick = htim->Instance->CNT;
		}
		break;
	case DEBOUNCE:
		if( (htim->Instance->CNT) - (Button->TimTick) >= (Button->DebounceTime_ms) )
		{
			if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Button->Button_Port, Button->Button_Pin) )
			{
				Button->ButtonState = PRESSED;
			}
			else
			{
				Button->ButtonState = IDLE;
			}
		}
		break;
	case PRESSED:
		if(NULL != Button->ButtonPressAction)
		{
			Button->ButtonPressAction();
		}
		Button->ButtonState = IDLE;
		break;
	}
}