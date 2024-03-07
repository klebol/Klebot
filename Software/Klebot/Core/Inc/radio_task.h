/*
 * radio_task.h
 *
 *  Created on: Mar 4, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_RADIO_TASK_H_
#define INC_RADIO_TASK_H_

#include "stdint.h"

#define MAX_COMMAND_LENGTH 32		// [Bytes]
#define PACKET_SEND_DELAY 50 		// [ms]



typedef struct{
	uint8_t data[MAX_COMMAND_LENGTH];
	uint8_t length;
}RadioFrame_t;

typedef enum
{
	RADIO_OK,		// 0
	RADIO_ERROR,	// 1
	RADIO_BUSY,		// 2
	RADIO_NEW_RX
} Klebot_Radio_Status;



void vTaskRadio(void *pvParameters);

#endif /* INC_RADIO_TASK_H_ */
