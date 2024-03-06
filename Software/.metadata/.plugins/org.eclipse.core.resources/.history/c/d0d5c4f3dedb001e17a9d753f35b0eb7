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

/* Status variables */
Klebot_Radio_Status ConnectionStatus;
Klebot_Radio_Status TxStatus;
Klebot_Radio_Status RxStatus;




/* Radio task handler for task notification */
TaskHandle_t xTaskRadioHandle;

/* Queue for transmiting radio data */
QueueHandle_t QueueRadioTX;
/* Simple ring buffer for received data */
RBuffer_t RxBuff;



void Radio_TaskInit(void)
{
	xTaskCreate(vTaskRadio, "NRF24 Task", 512, NULL, 1, &xTaskRadioHandle);
}

void vTaskRadio(void *pvParameters)
{

	QueueRadioTX = xQueueCreate(32, 1);
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



	}
}



/* Whole interrupt mechanism should be more optimised for RTOS usage but now I want to just get it work... */
void Radio_HandlerIRQ(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	/* Set Interrupt Flag to 1 */
	nRF24_IRQ_Handler();
	/* Notify the radio Task */
	vTaskNotifyGiveFromISR(xTaskRadioHandle, &xHigherPriorityTaskWoken);
	/* yield if unblocked task (radio) has higher priority than current task */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
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

	ConnectionStatus = RADIO_OK;
	ConnectionTimeoutCounter = HAL_GetTick();			//Connection timeout counter is a tool for robot to check if there is still a connection with controller, on controller side we have MrCallback to check this
	if(CONNECTION_HOLD == ReceivedCommand[0]) return;	//just ignore if this is a connection hold

	//Radio_RxBufferPut(ReceivedCommand, ReceivedLength); 	//TODO: QUEUE TO PARSER
	RxStatus = RADIO_NEW_RX;
}

void nRF24_EventMrCallback(void)
{
	ConnectionStatus = RADIO_ERROR;		//Max retransmitt - no connection
}

