/*
 * debounce.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_DEBOUNCE_H_
#define INC_DEBOUNCE_H_

#include "gpio.h"
#include "tim.h"

//

typedef enum
{
	IDLE = 0,
	DEBOUNCE,
	PRESSED
}DB_State_t;


typedef struct
{
	uint16_t Button_Pin;
	GPIO_TypeDef* Button_Port;
	uint16_t DebounceTime_ms;
	void(*ButtonPressAction)(void);
	DB_State_t ButtonState;
	uint16_t TimTick;

}DB_Button_t;


void DB_ButtonInit(DB_Button_t *Button, GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin, uint16_t Debounce_ms);

void DB_ButtonPressCallbackRegister(DB_Button_t *Button, void(*ActionFun)(void));

void DB_ButtonProcess(DB_Button_t *Button, TIM_HandleTypeDef *htim);


#endif /* INC_DEBOUNCE_H_ */