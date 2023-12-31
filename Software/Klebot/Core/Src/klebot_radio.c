/*
 * klebot_radio.c
 *
 *  Created on: 23 maj 2023
 *      Author: Michal Klebkowski
 */

#include "klebot_radio.h"
#include "nRF24.h"
#include "nRF24_Defs.h"
#include "RingBuffer.h"
#include "klebot_commands.h"

Klebot_Radio_Status ConnectionStatus;
Klebot_Radio_Status TxStatus;
Klebot_Radio_Status RxStatus;

RBuffer_t TxBuffer;
RBuffer_t RxBuffer;

uint32_t ConnectionTimeoutCounter;

//
// -- INIT --
//
void Radio_Init(SPI_HandleTypeDef *hspi)
{
	nRF24_Init(hspi);

#ifdef ROBOT
	nRF24_SetRXAddress(0, (uint8_t*) "Bot");
	nRF24_SetTXAddress( (uint8_t*) "Con");
	nRF24_RX_Mode();
#endif

#ifdef CONTROLLER
	nRF24_SetRXAddress(0, (uint8_t*) "Con");
	nRF24_SetTXAddress( (uint8_t*) "Bot");
	nRF24_TX_Mode();
#endif
}


//
// -- RX --
//
Klebot_Radio_Status Radio_RxBufferPut(uint8_t *ReceivedCommand, uint8_t ReceivedLength)
{
	Klebot_Radio_Status Status = RADIO_OK;
	for(uint8_t i = 0; i < ReceivedLength; i++)						//Put Command to a buffer
	{
		Status |= RBuffer_Write(&RxBuffer, *ReceivedCommand);
		ReceivedCommand++;
	}
	return Status;
}

Klebot_Radio_Status Radio_RxBufferGet(uint8_t *CommandDestination, uint8_t *LengthDestination)		//get one command from buffer (FIFO)
{
	uint8_t Length = 0;
	Klebot_Radio_Status Status = RADIO_OK;
	uint8_t Data;

	Status |= RBuffer_Read(&RxBuffer,&Data);				//Get first byte
	while( (Data != COMM_END) && (Status == RADIO_OK) )		//Check if this is end-of-command or if there is nothing in buffer(status)
	{
		*(CommandDestination+Length) = Data;				//write received byte to destination
		Length++;											//increment length info
		Status |= RBuffer_Read(&RxBuffer,&Data);			//read next byte
	}
	*LengthDestination = Length;							//after end of the frame write length to destination
	return Status;
}

//
// -- TX --
//
Klebot_Radio_Status Radio_TxBufferPut(uint8_t *Command, uint8_t Length)
{
	Klebot_Radio_Status Status = RADIO_OK;
	for(uint8_t i = 0; i < Length; i++)						//Put Command to a buffer
	{
		Status |= RBuffer_Write(&TxBuffer, *Command);
		Command++;
	}
	Status |= RBuffer_Write(&TxBuffer, COMM_END);			//Add end-of-command identifier
	return Status;
}

Klebot_Radio_Status Radio_TxBufferSend(void)		//Send one command from buffer (FIFO)
{
	Klebot_Radio_Status Status = RADIO_OK;
	uint8_t Length = 0;
	uint8_t DataToSend[MAX_COMMAND_LENGTH];

	do
	{
		Status |= RBuffer_Read(&TxBuffer,&DataToSend[Length]);
	}while((DataToSend[Length++] != COMM_END) && Status == RADIO_OK);

#ifdef CONTROLLER
	if(Status == RADIO_OK)
	{
		Status |= nRF24_SendPacket(DataToSend, Length);
		TxStatus = RADIO_BUSY;
	}
#endif

#ifdef ROBOT
	if(Status == RADIO_OK)
	{
		nRF24_WriteAckPayload(0, DataToSend, Length);
		TxStatus = RADIO_BUSY;
	}
#endif

	return Status;
}

Klebot_Radio_Status Radio_SendConnectionCheck(void)
{
#ifdef CONTROLLER
	uint8_t Command [2] = {CONNECTION_HOLD, COMM_END};
	TxStatus = RADIO_BUSY;
	return nRF24_SendPacket(Command, 2);
#endif


#ifdef ROBOT
	uint8_t Command [3] = {CONNECTION_HOLD, _OK, COMM_END};
	TxStatus = RADIO_BUSY;
	return nRF24_WriteAckPayload(0, Command, 3);
#endif
}




void Radio_SetResponseACK(uint8_t *ResponseCommand, uint8_t Length)		//are ack payloads stored in nRF's TX fifo?
{
	uint8_t i;
	uint8_t Buffer[MAX_COMMAND_LENGTH];

	for(i = 0; i < Length; i++)
	{
		Buffer[i] = *(ResponseCommand+i);
	}
	Buffer[i] = COMM_END;

	nRF24_WriteAckPayload(0, Buffer, Length+1);
}

void Radio_Process(void)			//Process to put in main loop
{
	nRF24_Event();											//check for irq's

#ifdef CONTROLLER

	static uint32_t LastTick;
	if((HAL_GetTick() - LastTick) > PACKET_SEND_DELAY)		//connection freqency
	{
		if(TxStatus == RADIO_OK)							//If Tx is free, send message
		{
			if(Radio_TxBufferSend() == RADIO_ERROR)			//send message or send connection hold if buffer is empty
			{
				Radio_SendConnectionCheck();
			}
		}
		else if(TxStatus != RADIO_OK && ConnectionStatus == RADIO_ERROR)	//if no connection (max retransmitt IRQ),
		{
			Radio_NoConnectionCallback();									//callback for no connection
			Radio_SendConnectionCheck();									//try to reconnect
		}
		LastTick = HAL_GetTick();
	}
#endif

#ifdef ROBOT

	if(TxStatus == RADIO_OK)	//If Tx is free, send response
	{
		Radio_TxBufferSend();	//send ack payload
	}

	if((HAL_GetTick() - ConnectionTimeoutCounter) > (3 * PACKET_SEND_DELAY) )	//check when last message came to know if connection isnt dead
	{
		ConnectionStatus = RADIO_ERROR;
		Radio_NoConnectionCallback();
	}
#endif

	if(RxStatus == RADIO_NEW_RX)				//If there is new message, get it and pass it to parser
	{
		uint8_t ReceivedCommand[MAX_COMMAND_LENGTH];		//TODO: add check here if there is more than one new command in rbuffer
		uint8_t ReceivedLength;

		Radio_RxBufferGet(ReceivedCommand, &ReceivedLength);
		Radio_NewCommandReceivedCallback(ReceivedCommand, ReceivedLength);

		RxStatus = RADIO_OK;
	}
}

//
//Get connection status
//

Klebot_Radio_Status Radio_GetConnectionStatus(void)
{
	return ConnectionStatus;
}

//
//Klebot radio callbacks to use
//
void Radio_HandlerIRQ(void)
{
	nRF24_IRQ_Handler();
}

__weak void Radio_NoConnectionCallback(void)
{

}

__weak void Radio_NewCommandReceivedCallback(uint8_t *command, uint8_t length)
{

}
//
// -- NRF24 Callbacks --
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

#ifdef ROBOT
	ConnectionStatus = RADIO_OK;
	ConnectionTimeoutCounter = HAL_GetTick();			//Connection timeout counter is a tool for robot to check if there is still a connection with controller, on controller side we have MrCallback to check this
	if(CONNECTION_HOLD == ReceivedCommand[0]) return;	//just ignore if this is a connection hold
#endif

	Radio_RxBufferPut(ReceivedCommand, ReceivedLength);
	RxStatus = RADIO_NEW_RX;
}

void nRF24_EventMrCallback(void)
{
	ConnectionStatus = RADIO_ERROR;		//Max retransmitt - no connection
}



