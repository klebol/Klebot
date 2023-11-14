/*
 * controller_inputs.h
 *
 *  Created on: 5 maj 2023
 *      Author: miqix
 */

#ifndef INC_CONTROLLER_INPUTS_H_
#define INC_CONTROLLER_INPUTS_H_

#include "main.h"
#include "joystick.h"
#include "debounce.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include "menu.h"




#define LEFT_JOYSTICK 0
#define RIGHT_JOYSTICK 1

void Inputs_Init(void);

int8_t Inputs_GetEncoderCount(void);

void Inputs_ButtonsRoutine(void);

#endif /* INC_CONTROLLER_INPUTS_H_ */
