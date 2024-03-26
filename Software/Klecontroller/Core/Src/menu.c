/*
 * menu.c
 *
 *  Created on: 15 mar 2023
 *      Author: Michal Klebokowski
 */
#include "menu.h"
#include "string.h"
#include "ssd1106.h"
#include "Programs/DiodeTest_Prog.h"
#include "Programs/MotorsDebug_Prog.h"
#include "Programs/CalibPID_CProg.h"

//
//TODO: 1. Define here your menu members, remember to add extern declarations in menu.h file!
//
/*--------------Name, *Next, *Prev, *Child, *Parent, *Function---
 *
 * WARNING: First member's *Prev pointer have to be NULL,
 * & Last member's *Next pointer have to be NULL!  */

Menu_t RobotModes = {"Robot's modes", &HardwareControll, NULL, NULL, NULL, NULL};
	//Menu_t FreeRide = {"Free Ride", NULL, NULL, NULL, &RobotModes, &SetFreeRideControll};

Menu_t HardwareControll = {"Hardware controll", &Settings, &RobotModes, &DiodeTest, NULL, NULL};
	Menu_t DiodeTest = {"Onboard diode", &MotorsTest, NULL, NULL, &HardwareControll, &Prog_DiodeTest_Launch};
	Menu_t MotorsTest = {"Motors test", NULL, &DiodeTest, NULL, &HardwareControll, &Prog_MotorsDebug_Launch};


Menu_t Settings = {"Settings", NULL, &HardwareControll, &JoyCalib, NULL, NULL};
	Menu_t JoyCalib = {"Joystick Calib", &PIDCalib, NULL, &JoyCalib1, &Settings, NULL};
	Menu_t PIDCalib = {"PID Calib", NULL, &JoyCalib, NULL, &Settings, &Prog_CalibPID_Launch};
		Menu_t JoyCalib1 = {"Left X", &JoyCalib2, NULL, NULL, &JoyCalib, NULL};
		Menu_t JoyCalib2 = {"Left Y", &JoyCalib3, &JoyCalib1, NULL, &JoyCalib, NULL};
		Menu_t JoyCalib3 = {"Right X", &JoyCalib4, &JoyCalib2, NULL, &JoyCalib, NULL};
		Menu_t JoyCalib4 = {"Right Y", NULL, &JoyCalib3, NULL, &JoyCalib, NULL};










//
//End of member list
//


//
//Global variables
//
static Menu_t *MenuCurrentMember = MENU_FIRST_MEMBER;
static Menu_t *FirstMemberToDisplayPtr = MENU_FIRST_MEMBER;

static uint8_t LevelsIndexes[MENU_MAX_LEVELS_NUMBER];
static uint8_t LevelsFirstMembersToDisplay[MENU_MAX_LEVELS_NUMBER];
static uint8_t MenuLevel;

//
//Functions
//

void Menu_RefreshScreen(void)
{
	//static Menu_t *LastMenuPtr = NULL;
	Menu_t *Tmp;
	uint8_t i = 0;
	uint8_t CenterCalculate;

	//if(LastMenuPtr == MenuCurrentMember) return;  TODO: IS THIS NEEDED?

	while(LevelsIndexes[MenuLevel] > (LevelsFirstMembersToDisplay[MenuLevel] + MENU_ROWS_TO_DISPLAY - 1) )		//while our menu member is in out of screen range...
	{
		LevelsFirstMembersToDisplay[MenuLevel]++;																//"scroll down" by increasing first to display member
		FirstMemberToDisplayPtr = FirstMemberToDisplayPtr->Next;
	}
	while(LevelsIndexes[MenuLevel] < LevelsFirstMembersToDisplay[MenuLevel] )
	{
		LevelsFirstMembersToDisplay[MenuLevel]--;																//or "scroll up"
		FirstMemberToDisplayPtr = FirstMemberToDisplayPtr->Prev;
	}

	OLED_ClearBuffer(BLACK);
	OLED_MoveCursor(0, 0);
	OLED_WriteString("-------M E N U-------",WHITE);

	Tmp = FirstMemberToDisplayPtr;															//temporary pointer for displaying
	while((i != MENU_ROWS_TO_DISPLAY) && Tmp != NULL)										//print all menu rows
	{
		if(MenuCurrentMember == Tmp)														//if actually printed member is current member, add >> <<
		{
			CenterCalculate = ((DISPLAY_WIDTH - ((strlen(Tmp->Name) + 6) * 6) ) / 2);
			OLED_MoveCursor(CenterCalculate, (i+1)*8);
			OLED_WriteString(">> ", WHITE);
			OLED_WriteString((char*)Tmp->Name, WHITE);
			OLED_WriteString(" <<", WHITE);
		}
		else																				//if not, just print it
		{
			CenterCalculate = ((DISPLAY_WIDTH - (strlen(Tmp->Name) * 6) ) / 2);
			OLED_MoveCursor(CenterCalculate, (i+1)*8);
			OLED_WriteString((char*)Tmp->Name, WHITE);
		}
		i++;																				//increment for printing next member
		Tmp = Tmp->Next;
	}
	OLED_SendBuffer();
	//LastMenuPtr = MenuCurrentMember;

}

void Menu_Next(void)
{
	if(MenuCurrentMember->Next != NULL)
	{
		MenuCurrentMember = MenuCurrentMember->Next;	//change current member pointer to next member
		LevelsIndexes[MenuLevel]++;						//increase current level index
	}
#ifdef MENU_LOOPING
	else												//if there is no next member, go to first member (looping)
	{
		while(MenuCurrentMember->Prev != NULL)
		{
			MenuCurrentMember = MenuCurrentMember->Prev;
		}
		LevelsIndexes[MenuLevel] = 0;
	}
#endif

	Menu_RefreshScreen();
}

void Menu_Prev(void)
{
	if(MenuCurrentMember->Prev != NULL)
	{
		MenuCurrentMember = MenuCurrentMember->Prev;
		LevelsIndexes[MenuLevel]--;
	}
#ifdef MENU_LOOPING
	else
	{
		while(MenuCurrentMember->Next != NULL)
		{
			MenuCurrentMember = MenuCurrentMember->Next;
			LevelsIndexes[MenuLevel]++;
		}
	}
#endif

	Menu_RefreshScreen();
}



void Menu_Select(void)
{
	if(MenuCurrentMember->FunctionPtr != NULL)			//if there is a function pointer...
	{
		MenuCurrentMember->FunctionPtr();
	}

	if(MenuCurrentMember->Child != NULL)				//if there is a child...
	{
		MenuCurrentMember = MenuCurrentMember->Child;
		FirstMemberToDisplayPtr = MenuCurrentMember;
		MenuLevel++;
	}

	Menu_RefreshScreen();
}

void Menu_Back(void)
{
	uint8_t i;

	if(MenuCurrentMember->Parent != NULL)
	{
		LevelsIndexes[MenuLevel] = 0;
		MenuCurrentMember = MenuCurrentMember->Parent;
		FirstMemberToDisplayPtr = MenuCurrentMember;
		MenuLevel--;

		for(i = 0; i < (LevelsIndexes[MenuLevel] - LevelsFirstMembersToDisplay[MenuLevel]) ; i++)
		{
			FirstMemberToDisplayPtr = FirstMemberToDisplayPtr->Prev;
		}
	}

	Menu_RefreshScreen();
}

uint8_t Menu_CountMembers(void)
{
	Menu_t *Tmp = MenuCurrentMember;
	uint8_t Counter = 1;

	while(Tmp->Next != NULL)
	{
		Counter++;
		Tmp = Tmp->Next;
	}
	Tmp = MenuCurrentMember;
	while(Tmp->Prev != NULL)
	{
		Counter++;
		Tmp = Tmp->Prev;
	}

	return Counter;
}


