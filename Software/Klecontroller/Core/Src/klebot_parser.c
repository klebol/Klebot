/*
 * klebot_parser.c
 *
 *  Created on: 29 maj 2023
 *      Author: Michal Klebokowski
 */

#include "klebot_parser.h"
#include "stdio.h"
#include "klebot_commands.h"

void Parser_Klebot(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	uint8_t ResponseCommand[MAX_COMMAND_LENGTH];
	uint32_t tick = 0;
	uint8_t len = 0;

	switch(*CurrentByte)
	{
	case CONNECTION_HOLD:
		ResponseCommand[0] = CONNECTION_HOLD;
		ResponseCommand[1] = OK;
		Radio_TxBufferPut(ResponseCommand, 2);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		break;

	case GET_TICK:

		tick = HAL_GetTick();

		len = sprintf((char*)&ResponseCommand[1], "%ld", tick);
		ResponseCommand[0] = GET_TICK;
		ResponseCommand[1] = HAL_GetTick();
		Radio_TxBufferPut(ResponseCommand, len + 1);

	default:
		Radio_TxBufferPut(command, length);
		//GFX_DrawString(0, 8, (char*)command, 1, 0);
		//SSD1306_Display();
		break;
	}
}
