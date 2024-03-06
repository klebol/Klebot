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
Klebot_Radio_Status ConnectionStatus;
Klebot_Radio_Status TxStatus;
Klebot_Radio_Status RxStatus;

/* Counter for stating connection loss */
uint32_t ConnectionTimeoutCounter;

/* Radio task handler for task notification */
TaskHandle_t xTaskRadioHandle;

/* Queue for transmiting radio data */
QueueHandle_t QueueRadioTX;
/* Buffer for sending via NRF */
uint8_t FrameToSend[MAX_COMMAND_LENGTH];

/* Simple ring buffer for data to transmit */
RBuffer_t RxBuff;




void Radio_TaskInit(void)
{
	xTaskCreate(vTaskRadio, "NRF24 Task", 512, NULL, 1, &xTaskRadioHandle);
}

void vTaskRadio(void *pvParameters)
{
	/* Create queue for transmission (TX) */
	QueueRadioTX = xQueueCreate(64, sizeof(uint8_t));
	/* Transceiver init */
	nRF24_Init(&hspi3);
	/* Set communication addresses */
	nRF24_SetRXAddress(0, (uint8_t*) "Bot");
	nRF24_SetTXAddress( (uint8_t*) "Con");
	/* Enable RX mode */
	nRF24_RX_Mode();


	for(;;)
	{
		/* Wait for notification from NRF IRQ */
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		/* Check kind of IRQ */
		nRF24_Event();

		if( xQueueReceive(QueueRadioTX, FrameToSend, 0 ) == pdPASS ) /* TODO: COLLECT WHOLE FRAME !! */
		{
			nRF24_WriteAckPayload(0, FrameToSend, Length);
		}




	}
}



/* Whole interrupt mechanism should be more optimised for RTOS usage but now I want to just get it just work... */
void Radio_HandlerIRQ(void)	//TODO: Check priorities later
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	/* Set Interrupt Flag to 1 */
	nRF24_IRQ_Handler();
	/* Notify the radio Task */
	vTaskNotifyGiveFromISR(xTaskRadioHandle, &xHigherPriorityTaskWoken);
	/* yield if unblocked task (radio) has higher priority than current task */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}




Klebot_Radio_Status Radio_TxBufferPut(uint8_t *Command, uint8_t Length)
{
	Klebot_Radio_Status Status = RADIO_OK;
	uint8_t CommandEnd = COMM_END;
	for(uint8_t i = 0; i < Length; i++)
	{
		if(xQueueSendToBack( QueueRadioTX, Command, (TickType_t)10 ) != pdTRUE )
		{
			/* If put to queue failed */
			Status = RADIO_ERROR;
		}
		Command++;
	}
	if (xQueueSendToBack( QueueRadioTX, &CommandEnd, (TickType_t)10 ) != pdTRUE )
	{
		/* If put to queue failed */
		/* TODO: FLUSH ! */
		Status = RADIO_ERROR;
	}
	return Status;
}




//
// -- NRF24 Event Callbacks --
//
void nRF24_EventTxCallback(void)
{
	TxStatus = RADIO_OK;
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

	/* Write received frame to parses queue */
	//Radio_RxBufferPut(ReceivedCommand, ReceivedLength); 	//TODO: QUEUE TO PARSER
	RxStatus = RADIO_NEW_RX;
}

/* This callback means connection lost */
void nRF24_EventMrCallback(void)
{
	ConnectionStatus = RADIO_ERROR;
}

