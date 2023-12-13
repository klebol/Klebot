/*
 * controller_parser.h
 *
 *  Created on: Dec 1, 2023
 *      Author: miqix
 */

#ifndef INC_CONTROLLER_PARSER_H_
#define INC_CONTROLLER_PARSER_H_

#include "stdio.h"
#include "klebot_radio.h"
#include "Programs/controller_programs.h"
#include "klebot_commands.h"









void Parser_Controller(uint8_t *command, uint8_t length);

#endif /* INC_CONTROLLER_PARSER_H_ */
