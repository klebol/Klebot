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
#include "Programs/MotorsDebug_Prog.h"


void Parser_Controller(uint8_t *command, uint8_t length)							//main parser funciton
{
	uint8_t *CurrentByte = command;
	uint8_t Length = length;

	switch(*CurrentByte)
	{
	case START_PROGRAM:
		/* Frame: [START_PROGRAM, ProgramID, Ack or Nack] */
		CurrentByte++;
		Programs_ProgramLaunchedACK(*CurrentByte, *(CurrentByte + 1) );
		break;

	case EXIT_PROGRAM:
		/* Frame: [EXIT_PROGRAM, Ack or Nack] */
		CurrentByte++;
		Programs_ProgramExitACK(*CurrentByte);
		break;

	case DIODE_TEST:
		/* Frame: [DIODE_TEST, Specific program commands ...] */
		CurrentByte++;
		Length--;
		Prog_DiodeTest_Parser(CurrentByte, Length);

		break;

	case MOTORS_DEBUG:
		/* Frame: [MOTORS_DEBUG, Specific program commands ...] */
		CurrentByte++;
		Length--;
		Prog_MotorsDebug_Parser(CurrentByte, Length);;
		break;

	default:

		break;
	}


}



