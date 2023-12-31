/*
 * debounce.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_DEBOUNCE_H_
#define INC_DEBOUNCE_H_

#include "gpio.h"

typedef enum
{
	IDLE,
	DEBOUNCE,
	PRESSED,
	HOLD
}DB_State_t;


typedef struct
{
	uint16_t Button_Pin;
	GPIO_TypeDef* Button_Port;

	uint32_t HoldTime_ms;
	uint32_t DebounceTime_ms;

	void(*ButtonPressAction)(void);
	void(*ButtonHoldAction)(void);

	DB_State_t ButtonState;
	uint32_t LastTick;
}DB_Button_t;


void DB_ButtonInit(DB_Button_t *Button, GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin, uint32_t DebounceTime_ms, uint32_t HoldTime_ms);

void DB_ButtonPressCallbackRegister(DB_Button_t *Button, void(*PressActionFun)(void), void(*HoldActionFun)(void));

void DB_ButtonProcess(DB_Button_t *Button);


#endif /* INC_DEBOUNCE_H_ */
