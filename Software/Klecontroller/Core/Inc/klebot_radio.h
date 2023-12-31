/*
 * klebot_radio.h
 *
 *  Created on: 23 maj 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_KLEBOT_RADIO_H_
#define INC_KLEBOT_RADIO_H_

#include "spi.h"

//
//TODO: Select device
//

#define CONTROLLER
//#define ROBOT

//
//Options
//

#define MAX_COMMAND_LENGTH 32		// [Bytes]
#define PACKET_SEND_DELAY 50 		// [ms]



//
//Typedefs
//

typedef enum
{
	RADIO_OK,		// 0
	RADIO_ERROR,	// 1
	RADIO_BUSY,		// 2
	RADIO_NEW_RX
} Klebot_Radio_Status;

//
//Functions
//

void Radio_Init(SPI_HandleTypeDef *hspi);	//Init

void Radio_Process(void); //Process for main loop, pass function for parsing received data

Klebot_Radio_Status Radio_TxBufferPut(uint8_t *Command, uint8_t Length);	//Put data in TX ring buffer

void Radio_NoConnectionCallback(void);										//Callback for no connection

void Radio_HandlerIRQ(void);

void Radio_NewCommandReceivedCallback(uint8_t *command, uint8_t length);


#endif /* INC_KLEBOT_RADIO_H_ */
