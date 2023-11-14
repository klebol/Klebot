/*
 * klebot_commands.h
 *
 *  Created on: 23 maj 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_KLEBOT_COMMANDS_H_
#define INC_KLEBOT_COMMANDS_H_

//
//Connection related commands
//
#define COMM_END 0x04
#define CONNECTION_HOLD 0x05

//
//Status identifiers
//

#define OK 0x06
#define ERROR 0x07

//
//Commands
//
#define GET_TICK 0x08

#endif /* INC_KLEBOT_COMMANDS_H_ */
