/*
 * klebot_parser.h
 *
 *  Created on: 29 maj 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_KLEBOT_PARSER_H_
#define INC_KLEBOT_PARSER_H_

#include "stdio.h"
#include "klebot_radio.h"
#include "Programs/klebot_programs.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebug_Prog.h"










void Parser_Klebot(uint8_t *command, uint8_t length);




#endif /* INC_KLEBOT_PARSER_H_ */
