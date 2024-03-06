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
