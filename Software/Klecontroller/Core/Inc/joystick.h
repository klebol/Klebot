/*
 * joystick.h
 *
 *  Created on: 24 lut 2023
 *      Author: Michal Klebokowski
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

//	!NOTE!
//	To init the joystick you have to set your ADC separately
//	and pass pointers to measured values to joystick via init function

#include "stdint.h"

#define X_AXIS 0
#define Y_AXIS 1

//
//Joystick struct
//
typedef struct{
	uint16_t* ValX;		//Pointers to tab where DMA is writing our values from ADC
	uint16_t* ValY;

	uint16_t IdleX;
	uint16_t IdleY;
	uint16_t MaxY;
	uint16_t MaxX;
	uint16_t MinY;
	uint16_t MinX;

	int8_t DeviationX;
	int8_t DeviationY;
}Joystick_t;

//
//Error type enum
//

typedef enum
{
  JOYS_OK       = 0x00,
  JOYS_ERROR    = 0x01,
  JOYS_BUSY     = 0x02,
  JOYS_TIMEOUT  = 0x03
} JOYS_StatusTypeDef;


//
//Functions
//

JOYS_StatusTypeDef JoyS_Init(Joystick_t *Joystick, uint16_t *AdcValueSourceX, uint16_t *AdcValueSourceY);	//Init
JOYS_StatusTypeDef JoyS_SetIdleValues(Joystick_t *Joystick);												//Calibration
JOYS_StatusTypeDef Joy_SetMaxValue(Joystick_t *Joystick, uint8_t axis);										//
JOYS_StatusTypeDef Joy_SetMinValue(Joystick_t *Joystick, uint8_t axis);										//
int8_t Joy_GetDeviationPercent(Joystick_t *Joystick, uint8_t axis);											//Getting deviation in %
int8_t Joy_GetDeviationPercentCal(Joystick_t *Joystick, uint8_t axis);										//


#endif /* INC_JOYSTICK_H_ */
