/*
 * controller_inputs.c
 *
 *  Created on: 5 maj 2023
 *      Author: miqix
 */

#include "controller_inputs.h"


//JoyStick Variables
uint16_t AdcSamples[40];
uint16_t AdcSamplesMean[4];
Joystick_t LeftJoystick;
Joystick_t RightJoystick;
uint8_t JoysitckCalibrationFlag;

//Buttons Variables
void(*EncoderButtonAction)(void);
void(*UpButtonAction)(void);
void(*DownButtonAction)(void);
void(*RightButtonAction)(void);
void(*LeftButtonAction)(void);
void(*JoyLeftButtonAction)(void);
void(*JoyRightButtonAction)(void);


void Inputs_Init(void)
{
	/*Start ADC for Joysticks and init Joystick api library */
	HAL_TIM_Base_Start(&htim3);								//Update event for ADC
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)AdcSamples, 40);	//External trigger conversion source, Scan mode, DMA continuous requests, DMA circular mode
	HAL_Delay(50);
	JoyS_Init(&LeftJoystick, &AdcSamplesMean[0], &AdcSamplesMean[1]);
	JoyS_Init(&RightJoystick, &AdcSamplesMean[2], &AdcSamplesMean[3]);
	JoyS_SetIdleValues(&LeftJoystick);
	JoyS_SetIdleValues(&RightJoystick);

	/*Start Encoder timer */
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

//
// J O Y S T I C K
//
int8_t Inputs_GetLeftJoystickDev(uint8_t axis)
{
	if(JoysitckCalibrationFlag > 0)
	{
		return Joy_GetDeviationPercentCal(&LeftJoystick, axis);
	}
	else
	{
		return Joy_GetDeviationPercent(&LeftJoystick, axis);
	}
}

int8_t Inputs_GetRightJoystickDev(uint8_t axis)
{
	if(JoysitckCalibrationFlag > 0)
	{
		return Joy_GetDeviationPercentCal(&RightJoystick, axis);
	}
	else
	{
		return Joy_GetDeviationPercent(&RightJoystick, axis);
	}
}

void Inputs_CalibrateLeftJoystickMax(uint8_t axis)
{
	Joy_SetMaxValue(&LeftJoystick, axis);
}

void Inputs_CalibrateRightJoystickMax(uint8_t axis)
{
	Joy_SetMaxValue(&RightJoystick, axis);
}

void Inputs_CalibrateLeftJoystickMin(uint8_t axis)
{
	Joy_SetMinValue(&LeftJoystick, axis);
}

void Inputs_CalibrateRightJoystickMin(uint8_t axis)
{
	Joy_SetMinValue(&RightJoystick, axis);
}

void Inputs_CalibrateRightJoystickIdle(void)
{
	JoyS_SetIdleValues(&RightJoystick);
}

void Inputs_CalibrateLeftJoystickIdle(void)
{
	JoyS_SetIdleValues(&LeftJoystick);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)		//getting 10 samples of ADC, each
{
	uint32_t ValuesBuffer[4];

	ValuesBuffer[0] = 0;
	ValuesBuffer[1] = 0;
	ValuesBuffer[2] = 0;
	ValuesBuffer[3] = 0;

	for(uint8_t i = 0; i < 37; i+=4)
	{
		ValuesBuffer[0] += AdcSamples[i];
		ValuesBuffer[1] += AdcSamples[i+1];
		ValuesBuffer[2] += AdcSamples[i+2];
		ValuesBuffer[3] += AdcSamples[i+3];
	}

	AdcSamplesMean[0] = ValuesBuffer[0]/10;
	AdcSamplesMean[1] = ValuesBuffer[1]/10;
	AdcSamplesMean[2] = ValuesBuffer[2]/10;
	AdcSamplesMean[3] = ValuesBuffer[3]/10;
}

//
// E N C O D E R
//
int8_t Inputs_GetEncoderCount(void)
{
	static uint16_t LastTimerCounter = 0;
	int CounterDif = htim3.Instance->CNT - LastTimerCounter;
	if(CounterDif >= 4 || CounterDif <= -4)
	{
		LastTimerCounter = htim3.Instance->CNT;
		return (int8_t)(CounterDif / 4);
	}
	else
	{
		return 0;
	}
}



//
// B U T T O N S
//


//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	static uint32_t LastTick;
//
//	if(HAL_GetTick() - LastTick > 200)
//	{
//
//		switch(GPIO_Pin)
//		{
//		case ENC_BTN_Pin:
//			if(NULL != EncoderButtonAction)
//			{
//				EncoderButtonAction();
//			}
//
//			HAL_GPIO_TogglePin(LED_USER_GPIO_Port, LED_USER_Pin);
//			break;
//
//		case UP_BTN_Pin:
//			if(NULL != UpButtonAction)
//			{
//				UpButtonAction();
//			}
//			break;
//
//		case DOWN_BTN_Pin:
//			if(NULL != DownButtonAction)
//			{
//				DownButtonAction();
//			}
//			break;
//
//		case RIGHT_BTN_Pin:
//			if(NULL != RightButtonAction)
//			{
//				RightButtonAction();
//			}
//			break;
//
//		case LEFT_BTN_Pin:
//			if(NULL != LeftButtonAction)
//			{
//				LeftButtonAction();
//			}
//			break;
//
//		default:
//			break;
//		}
//		LastTick = HAL_GetTick();
//	}
//}

