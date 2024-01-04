/*
 * klebot_parser.c
 *
 *  Created on: 29 maj 2023
 *      Author: Michal Klebokowski
 */

#include "klebot_parser.h"
#include "klebot_commands.h"
#include "Programs/klebot_programs.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebug_Prog.h"





void Parser_Klebot(uint8_t *command, uint8_t length)							//main parser funciton
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;



	switch(*CurrentByte)
	{
	case START_PROGRAM:


		break;

	case EXIT_PROGRAM:


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


