/*
 * hw_manager.h
 *
 *  Created on: Mar 25, 2024
 *      Author: Michal Klebokowski
 */

#ifndef INC_HW_MANAGER_H_
#define INC_HW_MANAGER_H_

#include "stdint.h"

typedef enum
{
	HW_OK,
	HW_BUSY,
	HW_ERROR
}HW_Error_t;

/* Get or give back controll over hardware */
HW_Error_t HW_Manager_SetControll(uint8_t hw_id, uint8_t controll_state);
/* Check if hardware is controlled */
uint8_t HW_Manager_CheckControll(uint8_t hw_id);
/* Hardware parser */
HW_Error_t HW_Manager_Parser(uint8_t* cmd, uint8_t length);

#endif /* INC_HW_MANAGER_H_ */
