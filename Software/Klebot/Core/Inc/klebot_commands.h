/*
 * klebot_commands.h
 *
 *  Created on: Dec 1, 2023
 *      Author: miqix
 */

#ifndef INC_KLEBOT_COMMANDS_H_
#define INC_KLEBOT_COMMANDS_H_

#define MAX_COMMAND_LENGTH 32		// [Bytes]
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

//
// --- Type Of Commands ---
//

#define PROGRAM_CMD 0x12



#define HARDWARE_CMD 0x13
#define HW_READ 0x14
#define HW_SET 0x15

// --- TEMPLATE ---

#define TEMPLATE_PROG 0xFF

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

#define MOTORS_DEBUG 0xD1
	#define MOTOR_SET_PWM 0x20
	#define MOTOR_SET_DIRECTION 0x21
	#define MOTOR_SET_TARGET	0x22

#define PID_CALIBRATION 		0xD2
	#define PID_SET_GAIN		0x20
		#define KP				0x30
		#define KI				0x31
		#define KD				0x32
	#define PID_SET_TARGET		0x25
	#define PID_START_IMPULSE	0x26
	#define PID_STOP_MOTOR		0x27
	#define PID_RESET_TEMPS		0x28
#endif /* INC_KLEBOT_COMMANDS_H_ */
