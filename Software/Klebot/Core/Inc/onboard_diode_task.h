/*
 * onboard_diode_task.h
 *
 *  Created on: Mar 4, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_ONBOARD_DIODE_TASK_H_
#define INC_ONBOARD_DIODE_TASK_H_

#include "stdint.h"

typedef enum
{
	DIODE_ON,
	DIODE_OFF,
	DIODE_NORMAL_BLINK,
	DIODE_SHORT_BLINK
}OnboardDiode_state_t;

/* Task */
void vTaskOnboardDiode(void *pvParameters);
/* Set normal blink */
void OnboardDiode_SetNormalBlink(uint32_t blink_delay);
/* Set short blink */
void OnboardDiode_SetShortBlink(uint32_t on_time, uint32_t off_time);
/* Set ON or OFF */
void OnboardDiode_SetStaticState(uint8_t onoff);
/* Get actual state */
OnboardDiode_state_t OnboardDiode_GetState(void);


#endif /* INC_ONBOARD_DIODE_TASK_H_ */
