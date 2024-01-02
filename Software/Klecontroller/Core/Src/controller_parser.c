/*
 * controller_parser.c
 *
 *  Created on: Dec 1, 2023
 *      Author: miqix
 */
#include "controller_parser.h"
#include "klebot_commands.h"
#include "Programs/controller_programs.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebugControll_Prog.h"


void Parser_Controller(uint8_t *command, uint8_t length)							//main parser funciton
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;

	switch(*CurrentByte)
	{
	case START_PROGRAM:
		CurrentByte++;
		Programs_ProgramLaunchedACK(*CurrentByte);
		break;

	case EXIT_PROGRAM:
		Programs_ProgramExitACK();
		break;

	case DIODE_TEST:
		CurrentByte++;
		Length--;
		Prog_DiodeTestParser(CurrentByte, Length);

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



