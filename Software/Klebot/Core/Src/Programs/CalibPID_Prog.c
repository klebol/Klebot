/*
 * CalibPID_Prog.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Michal Klebokowski
 */
#include "Programs/klebot_programs.h"
#include "Programs/CalibPID_Prog.h"
#include "klebot_commands.h"
#include "motors.h"
/* HAL Components */
#include "gpio.h"
/* Standard libraries */
#include "string.h"
#include "stdlib.h"

//
// -- Program struct variable --
//

Programs_Program_t CalibPIDProgram = {&Prog_CalibPID_Init, &Prog_CalibPID_Deinit, &Prog_CalibPID_Program, &Prog_CalibPID_Parser, PID_CALIBRATION};

//
// -- Init & Deinit functions for Diode Test Program --
//

Programs_error_t Prog_CalibPID_Init(void)
{

	return PROGRAMS_OK;

}

Programs_error_t Prog_CalibPID_Deinit(void)
{
	return PROGRAMS_OK;
}

//
// -- Main Diode Test Program for Robot --
//

Programs_error_t Prog_CalibPID_Program(void)
{
	/* Main program "loop" */




	return PROGRAMS_OK;
}

//
// -- Set / Launch function --
//

Programs_error_t Prog_CalibPID_Launch(void)
{
	return Programs_SetProgram(&CalibPIDProgram);
}

//
// -- Diode Test Program Parser --
//

void Prog_CalibPID_Parser(uint8_t *command, uint8_t length)
{
	uint8_t *CurrentByte = command;
	uint8_t Buffer[3];
	uint8_t ExeResult = _OK;

	uint8_t GainType;
	char GainBuffer[7];
	float Gain;
	DRV8836_Output_t MotorID;
	int16_t Target;

	switch(*CurrentByte)
	{
	case PID_SET_GAIN:
		/* Frame: [... , PID_SET_GAIN, Motor ID, (ASCII, 7 bytes), Gain type  */
		/* Get motor ID */
		CurrentByte++;
		MotorID = *CurrentByte;
		if(MotorID > MOTOR_ALL)
		{
			ExeResult = _ERROR;
		}
		/* Get Gain in ASCII */
		CurrentByte++;
		memcpy(GainBuffer, CurrentByte, 7);	//TODO: AWARE HERE
		/* Convert ASCII to float */
		Gain = atof(GainBuffer);
		/* Get gain type */
		CurrentByte += 7;
		GainType = *CurrentByte;
		/* Set proper gain */
		if(ExeResult == _OK)
		{
			switch(GainType)
			{
			case KP:
				Motors_SetKP(MotorID, Gain);
				break;
			case KI:
				Motors_SetKI(MotorID, Gain);
				break;

			case KD:
				Motors_SetKD(MotorID, Gain);
				break;
			default:
				ExeResult = _ERROR;
				break;
			}
		}
		/* Send response */
		Buffer[0] = PID_CALIBRATION;
		Buffer[1] = PID_SET_GAIN;
		Buffer[2] = ExeResult;
		//Radio_TxBufferPut(Buffer, 3);
		break;

	case PID_SET_TARGET:
		/* Frame: [... , PID_SET_TARGET, Motor ID, Target */
		/* Get Motor ID */
		CurrentByte++;
		MotorID = *CurrentByte;
		if(MotorID > MOTOR_ALL)
		{
			ExeResult = _ERROR;
		}
		/* Get target value */
		CurrentByte++;
		Target = *CurrentByte;
		if(Target > MAX_VELOCITY_VALUE && Target < -MAX_VELOCITY_VALUE)
		{
			ExeResult = _ERROR;
		}

		if(ExeResult == _OK)
		{
			Motors_SetPIDTarget(MotorID, Target);
		}
		/* Send response */
		Buffer[0] = PID_CALIBRATION;
		Buffer[1] = PID_SET_TARGET;
		Buffer[2] = ExeResult;
		//Radio_TxBufferPut(Buffer, 3);
		break;

	case PID_RESET_TEMPS:
		/* Frame: [... , PID_RESET_TEMPS ] */
		Motors_ResetTemps(MOTOR_ALL);
		/* Send response */
		Buffer[0] = PID_CALIBRATION;
		Buffer[1] = PID_RESET_TEMPS;
		Buffer[2] = _OK;
		//Radio_TxBufferPut(Buffer, 3);
		break;

	case PID_START_IMPULSE:
		/* Frame: [..., PID_START_IMPULSE ] */
		/* Turn on PID */
		Motors_SetControllPID(1);
		/* Send response */
		Buffer[0] = PID_CALIBRATION;
		Buffer[1] = PID_START_IMPULSE;
		Buffer[2] = _OK;
		//Radio_TxBufferPut(Buffer, 3);
		break;

	case PID_STOP_MOTOR:
		/* Frame: [..., PID_STOP_MOTOR ] */
		/* Turn off PID */
		Motors_SetControllPID(0);
		/* Stop motors */
		Motors_SetMotor(MOTOR_A, Coast, 0);
		Motors_SetMotor(MOTOR_B, Coast, 0);
		/* Reset PID temps */
		Motors_ResetTemps(MOTOR_ALL);
		/* Send response */
		Buffer[0] = PID_CALIBRATION;
		Buffer[1] = PID_STOP_MOTOR;
		Buffer[2] = _OK;
		//Radio_TxBufferPut(Buffer, 3);
	default:
		break;
	}

}


