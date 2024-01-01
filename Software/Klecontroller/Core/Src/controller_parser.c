/*
 * controller_parser.c
 *
 *  Created on: Dec 1, 2023
 *      Author: miqix
 */
#include "controller_parser.h"


void Parser_Controller(uint8_t *command, uint8_t length)							//main parser funciton
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;



	switch(*CurrentByte)
	{
	case DIODE_TEST:
		CurrentByte++;
		Length--;
		Programs_DiodeTestParser(CurrentByte, Length);

		break;

	case MOTORS_DEBUG:
		CurrentByte++;
		Length--;
		Programs_MotorsDebugControllParser(CurrentByte, Length);;
		break;

	default:

		break;
	}


}



