/*
 * hw_manager.c
 *
 *  Created on: Mar 25, 2024
 *      Author: Michal Klebokowski
 */
#include "hw_manager.h"
/* HAL */

/* Hardware modules */
#include "motors.h"
#include "onboard_diode_task.h"
/* Other */
#include "klebot_commands.h"
#include "radio_task.h"

/* Very simple flag mechanism, to identify if currently running program is using specific hardware module or not */
uint8_t MotorsControllFlag;
uint8_t DiodeControllFlag;

//
// -- Controll over hardware units --
//

/* Get or give back controll over hardware */
HW_Error_t HW_Manager_SetControll(uint8_t hw_id, uint8_t controll_state)
{
	uint8_t *FlagToSet;

	if(controll_state != 0 && controll_state != 1)
	{
		return HW_ERROR;
	}

	switch(hw_id)
	{
	case HW_MOTORS:
		FlagToSet = &MotorsControllFlag;
		break;
	case HW_DIODE:
		FlagToSet = &DiodeControllFlag;
		break;
	default:
		return HW_ERROR;
	}
	if(*FlagToSet != controll_state)
	{
		*FlagToSet = controll_state;
		return HW_OK;
	}
	else return HW_ERROR;
}

/* Check if hardware is controlled */
uint8_t HW_Manager_CheckControll(uint8_t hw_id)
{
	uint8_t *FlagToCheck;
	switch(hw_id)
	{
	case HW_MOTORS:
		FlagToCheck = &MotorsControllFlag;
		break;
	case HW_DIODE:
		FlagToCheck = &DiodeControllFlag;
		break;
	default:
		return 0;
	}

	return *FlagToCheck;
}

//
// -- Hardware parsers --
//

//
// -- SPECIFIC HARDWARE PARSERS --
//

/* Onboard Diode Parser */
HW_Error_t HW_Manager_OnboardDiode_Parser(uint8_t* cmd)
{
	uint8_t *CurrentByte = cmd;
	switch(*CurrentByte)
	{
	case DIODE_STATE_ON:
		OnboardDiode_SetStaticState(1);
		break;
	case DIODE_STATE_OFF:
		OnboardDiode_SetStaticState(0);
		break;

	case DIODE_STATE_BLINK:
		uint16_t BlinkDelay = ((*CurrentByte) << 8 ) | *(CurrentByte + 1);
		OnboardDiode_SetNormalBlink(BlinkDelay);
		break;

	case DIODE_STATE_SHORT_BLINK:
		uint16_t TimeOn = ((*CurrentByte) << 8 ) | *(CurrentByte + 1);
		uint16_t TimeOff = ((*CurrentByte + 2) << 8 ) | *(CurrentByte + 3);
		OnboardDiode_SetShortBlink(TimeOn, TimeOff);
		break;

	case DIODE_GET_STATE:
		uint8_t DiodeState = OnboardDiode_GetState();
		Radio_Frame_t Buffer;
		Buffer.data[0] = HARDWARE_FRAME;
		Buffer.data[1] = HW_GET;
		Buffer.data[2] = HW_DIODE;
		Buffer.data[3] = DIODE_GET_STATE;
		Buffer.data[4] = DiodeState;
		Buffer.length = 5;
		Radio_TxPutFrame(&Buffer);
		break;
	}

	return HW_OK;
}

//TODO: SIMPLIFY TO ONE SWITCH (IF STATEMENT CHECKING IF HARWARE BUSY IF COMMAND IS SET)
/* Main parser */
HW_Error_t HW_Manager_Parser(uint8_t* cmd, uint8_t length)
{
	uint8_t *CurrentByte = cmd;

	uint8_t HW_ID;


	switch(*CurrentByte)
	{
	/* Frame: [HARDWARE_CMD, HW_SET, HW_ID, Specific hardware commands...] */
	case HW_SET:
		CurrentByte++;
		HW_ID = *CurrentByte;
		CurrentByte++;
		/* Check if hardware is busy */
		if(HW_Manager_CheckControll(HW_ID) == 0)
		{
			switch(HW_ID)
			{
			case HW_MOTORS:
				//MOTORS SPECIFIED FUN
				break;
			case HW_DIODE:
				HW_Manager_OnboardDiode_Parser(CurrentByte);
				break;
			}
			return HW_OK;

		}
		else
		{
			return HW_BUSY;
		}
		break;
	case HW_GET:
		/* Frame: [HARDWARE_CMD, HW_GET, HW_ID, Specific hardware commands...] */
		CurrentByte++;
		HW_ID = *CurrentByte;
		CurrentByte++;

		switch(HW_ID)
		{
		case HW_MOTORS:
			//MOTORS SPECIFIED FUN
			break;
		case HW_DIODE:
			HW_Manager_OnboardDiode_Parser(CurrentByte);
			break;
		}
		return HW_OK;

	default:
		return HW_ERROR;
	}
}


