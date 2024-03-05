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


/* Queue for transmiting radio data */
QueueHandle_t QueueRadioTX;
/* Simple ring buffer for received data (*/
RBuffer_t RxBuff;



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
		//xQueueReceive(QueueRadioRX, &ReceivedADC, portMAX_DELAY);



		/* Check for IRQ's */
		nRF24_Event();
	}
}



