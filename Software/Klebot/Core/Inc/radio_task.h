/*
 * radio_task.h
 *
 *  Created on: Mar 4, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_RADIO_TASK_H_
#define INC_RADIO_TASK_H_

#include "stdint.h"
#include "klebot_commands.h"

#define RADIO_TIMEOUT_TICKS 2000
#define PACKET_SEND_DELAY 50 		// [ms]


/* Type for communication frames */
typedef struct{
	uint8_t data[MAX_COMMAND_LENGTH];
	uint8_t length;
}Radio_Frame_t;

/* Error type */
typedef enum
{
	RADIO_OK,		// 0
	RADIO_ERROR,	// 1
	RADIO_BUSY,		// 2
	RADIO_NEW_RX
}Radio_Status_t;



/* Init */
void Radio_TaskInit(void);
/* Interrupt routine */
void Radio_HandlerIRQ(void);
/* Put frame for sending to controller */
Radio_Status_t Radio_TxPutFrame(Radio_Frame_t* FrameToPut);
/* Get connection status */
Radio_Status_t Radio_GetConnectionStatus(void);

#endif /* INC_RADIO_TASK_H_ */
