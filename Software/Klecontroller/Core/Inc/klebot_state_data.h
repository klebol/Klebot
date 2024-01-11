/*
 * klebot_state_data.h
 *
 *  Created on: Jan 11, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_KLEBOT_STATE_DATA_H_
#define INC_KLEBOT_STATE_DATA_H_

#include "stdint.h"

//
// -- Motors Data --
//

#define MOTOR_A 0
#define MOTOR_B 1

typedef enum
{
	Coast = 0,
	Reverse = 1,
	Forward = 2,
	Brake = 3
}Motor_Direction_t;

typedef struct
{
	Motor_Direction_t Direction;
	uint16_t PWM;
}Motor_Data_t;



#endif /* INC_KLEBOT_STATE_DATA_H_ */
