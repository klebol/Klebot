/*
 * klebot_commands.h
 *
 *  Created on: Dec 1, 2023
 *      Author: miqix
 */

#ifndef INC_KLEBOT_COMMANDS_H_
#define INC_KLEBOT_COMMANDS_H_

//
//--- Connection related commands ---
//
#define COMM_END 0x04
#define CONNECTION_HOLD 0x05
#define SOURCE_BLOCKED 0x06

//
// --- Status identifiers ---
//

#define _OK 0x00
#define _ERROR 0x01

#define ACK 0xF0
#define NACK 0xF1

//
// --- Program Identifiers for commands ---
//

#define START_PROGRAM 0x10
#define EXIT_PROGRAM 0x11

// --- Free Ride ---
#define FREERIDE_PROG 0xA1
	#define LEFT_MOTOR_SPEED 0x20
	#define RIGHT_MOTOR_SPEED 0x21
	#define LEFT_MOTOR_DIRECTION 0x22
	#define RIGHT_MOTOR_DIRECTION 0x23



// --- Diode debug ---
#define DIODE_TEST 0xD0
	#define DIODE_SET_ON 0x20
	#define DIODE_SET_OFF 0x21
	#define DIODE_REAL_STATE 0x22

#endif /* INC_KLEBOT_COMMANDS_H_ */
