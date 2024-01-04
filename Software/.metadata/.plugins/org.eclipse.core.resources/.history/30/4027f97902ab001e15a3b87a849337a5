/*
 * klebot_parser.c
 *
 *  Created on: 29 maj 2023
 *      Author: Michal Klebokowski
 */

#include "klebot_parser.h"


void Parser_Klebot(uint8_t *command, uint8_t length)							//main parser funciton
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;



	switch(*CurrentByte)
	{
	case FREERIDE_PROG:
		CurrentByte++;
		Length--;
		//FreeRide_Parser(CurrentByte, Length);
		break;

	case DIODE_TEST:
		CurrentByte++;
		Length--;
		Programs_DiodeTestParser(CurrentByte, Length);
		break;

	case MOTORS_DEBUG:
		CurrentByte++;
		Length--;
		Programs_MotorsDebugParser(CurrentByte, Length);
	default:

		break;
	}


}


