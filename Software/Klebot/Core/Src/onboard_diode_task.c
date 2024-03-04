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




void vTaskOnboardDiode(void *pvParameters)
{

	for(;;)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		vTaskDelay(500);
	}
}
