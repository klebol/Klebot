/*
 * radio_task.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Michal Klebokowski
 */
#include "radio_task.h"
/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* HAL */
#include "spi.h"
/* Other */
#include "nRF24.h"
#include "nRF24_Defs.h"
#include "RingBuffer.h"
#include "klebot_commands.h"

/* Status variables */
Radio_Status_t ConnectionStatus;
Radio_Status_t TxStatus;
Radio_Status_t RxStatus;

/* Counter for stating connection loss */
uint32_t ConnectionTimeoutCounter;

/* Radio task handler for task notification */
TaskHandle_t xTaskRadioHandle;

/* Queue for transmiting radio data */
QueueHandle_t QueueRadioTX;

/* Buffer for sending via NRF */
Radio_Frame_t FrameToSend;

//
// -- The task --
//

void vTaskRadio(void *pvParameters)
{
	/* Create queue for transmission (TX) */
	QueueRadioTX = xQueueCreate(3, sizeof(Radio_Frame_t));

	for(;;)
	{
		/* Block the task untill notification from NRF IRQ arrives */
		if(xTaskNotifyWait(0, 0, NULL, RADIO_TIMEOUT_TICKS) == pdTRUE)
		{
			/* Check kind of IRQ and take related actions (callbacks) */
			nRF24_Event();
			/* Take massage from TX Queue and send it via next ACK Payload */
			if(TxStatus == RADIO_OK && ConnectionStatus == RADIO_OK)
			{
				if( xQueueReceive(QueueRadioTX, &FrameToSend, 0 ) == pdPASS )
				{
					nRF24_WriteAckPayload(0, FrameToSend.data, FrameToSend.length);
					/* Radio busy to prevent overwriting ack payload with next frame untill TX Callback arrives */
					TxStatus = RADIO_BUSY;
				}
			}
		}
		else
		/* If any interrupt haven't came during RADIO_TIMEOUT_TICKS period, communication is lost */
		{
			ConnectionStatus = RADIO_ERROR;
		}

	}
}


//
// -- API Functions to use in main.c --
//

/* Init, to use before scheduler start */
void Radio_TaskInit(void)
{
	/* Transceiver init */
	nRF24_Init(&hspi3);
	/* Set communication addresses */
	nRF24_SetRXAddress(0, (uint8_t*) "Bot");
	nRF24_SetTXAddress( (uint8_t*) "Con");
	/* Enable RX mode */
	nRF24_RX_Mode();
	/* Task creation */
	xTaskCreate(vTaskRadio, "NRF24 Task", 512, NULL, 1, &xTaskRadioHandle);
}

/* Interrupt handler to put in EXTI routine */
/* Whole interrupt mechanism should be more optimised for RTOS usage but now I want to just get it just work... */
void Radio_HandlerIRQ(void)	//TODO: Check priorities later
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	/* Set Interrupt Flag to 1 */
	nRF24_IRQ_Handler();

	Radio_Frame_t TestFrame;
	TestFrame.data[0] = 0xFF;
	TestFrame.length = 1;

	xQueueSendToBackFromISR( QueueRadioTX, &TestFrame, NULL );


	/* Notify the radio Task */
	vTaskNotifyGiveFromISR(xTaskRadioHandle, &xHigherPriorityTaskWoken);
	/* yield if unblocked task (radio) has higher priority than current task */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

//
// -- API Functions for other tasks --
//

/* Function to put the frame into the queue, frame will be sent in ACK Payload after receiving next message from controller */
Radio_Status_t Radio_TxPutFrame(Radio_Frame_t* FrameToPut)
{
	/* Return error if there is no connection */
	if(ConnectionStatus == RADIO_ERROR)
	{
		return RADIO_ERROR;
	}

	Radio_Status_t Status = RADIO_OK;

	/* Add end of command identifier to frame */
	FrameToPut->data[FrameToPut->length] = COMM_END;
	FrameToPut->length++;

	/* Put the frame into TX queue */
	if(xQueueSendToBack( QueueRadioTX, FrameToPut, (TickType_t)10 ) != pdTRUE )
	{
		/* If put to queue failed */
		Status = RADIO_ERROR;
	}

	return Status;
}

/* Connection status getter */
Radio_Status_t Radio_GetConnectionStatus(void)
{
	return ConnectionStatus;
}


//
// -- NRF24 Event Callbacks --
//

void nRF24_EventTxCallback(void)
{
	/* Unlock sending next TX ACK Payload */
	TxStatus = RADIO_OK;
	/* Radio OK - connection is live */
	ConnectionStatus = RADIO_OK;
}


void nRF24_EventRxCallback(void)					// Received Packet or received ACK Payload
{
	uint8_t ReceivedCommand[MAX_COMMAND_LENGTH];
	uint8_t ReceivedLength;
	nRF24_ReadRXPaylaod((uint8_t*)ReceivedCommand,&ReceivedLength);

	/* If new RX is available, that means the connection is OK */
	ConnectionStatus = RADIO_OK;
	/* Save tick for connection lost timeot */
	ConnectionTimeoutCounter = xTaskGetTickCount();

	/* Note: ACK Payload !propably! is cleared from nRF buffer after send, so there is no need to prevent
	 *  sending the same frame in ACK payload again and again when no new frame was written to send */

	/* Ingore if it is connection hold (it's only important for controller side */
	if(CONNECTION_HOLD == ReceivedCommand[0]) return;

	/* Write received frame to parser queue */
	//Radio_RxBufferPut(ReceivedCommand, ReceivedLength); 	//TODO: QUEUE TO PARSER
	RxStatus = RADIO_NEW_RX;
}

/* This callback means connection lost */
void nRF24_EventMrCallback(void)
{
	ConnectionStatus = RADIO_ERROR;
	//TODO: Check if this has any sense on robot
}

