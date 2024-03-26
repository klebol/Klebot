/*
 * onboard_diode_task.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Michal Klebokowski
 */

#include "onboard_diode_task.h"
/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
/* HAL */
#include "gpio.h"


OnboardDiode_state_t DiodeActualState = DIODE_NORMAL_BLINK;
uint32_t NormalBlinkDelay = 500;
uint32_t ShortBlinkOnTime;
uint32_t ShortBlinkOffTime;

//
// -- Diode Task --
//
void vTaskOnboardDiode(void *pvParameters)
{

	for(;;)
	{
		switch(DiodeActualState)
		{
		case DIODE_NORMAL_BLINK:
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			vTaskDelay(NormalBlinkDelay);
			break;

		case DIODE_SHORT_BLINK:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			vTaskDelay(ShortBlinkOnTime);
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			vTaskDelay(ShortBlinkOffTime);
			break;
		default:
			break;
		}
	}
}

/* Set normal blink */
void OnboardDiode_SetNormalBlink(uint32_t blink_delay)
{
	NormalBlinkDelay = blink_delay;
	DiodeActualState = DIODE_NORMAL_BLINK;
}

/* Set short blink */
void OnboardDiode_SetShortBlink(uint32_t on_time, uint32_t off_time)
{
	ShortBlinkOnTime = on_time;
	ShortBlinkOffTime = off_time;
	DiodeActualState = DIODE_SHORT_BLINK;
}

/* Set ON or OFF */
void OnboardDiode_SetStaticState(uint8_t onoff)
{
	if(onoff == 0)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		DiodeActualState = DIODE_OFF;
	}
	else
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		DiodeActualState = DIODE_ON;
	}
}

/* Get actual state */
OnboardDiode_state_t OnboardDiode_GetState(void)
{
	return DiodeActualState;
}





