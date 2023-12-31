/*
 * ssd1106.h
 *
 *  Created on: 7 mar 2023
 *      Author: Michal Klebokowski
 */

#ifndef OLED_SSD1106_SSD1106_H_
#define OLED_SSD1106_SSD1106_H_

#define DISPLAY_WIDTH        128
#define DISPLAY_HEIGHT        64

#include "i2c.h"

#if DISPLAY_WIDTH == 128
#define COLLUMN_CENTER_OFFSET 2 //For displays with 128p width (SSD1106 is 132x64 driver, when display has 128p, pixels are centered in RAM)
#elif DISPLAY_WIDTH == 132
#define COLLUMN_CENTER_OFFSET 0
#endif

//
//CONTROL BYTES
//
#define SEND_COMMAND            0x00
#define SEND_DATA               0x40
#define NOT_LAST_CONTROL_BYTE   (1<<7)

//
//OLED COMMANDS
//
#define OLED_ADDR           (0x3C << 1) //Without bit - shift 0x1E addres was being sent (idk why)


#define DISPLAY_ON          0xAF		//--Display state--
#define DISPLAY_OFF         0xAE		//0xAF - ON, 0xAE - OFF(Sleep mode)

#define SET_PAGE            0xB0		//--Set page address--
										//Use with OR 0-7

#define SET_COLLUMN_ADDR_L  0x00		//--Set collumn address--
#define SET_COLLUMN_ADDR_H  0x10		//Use with OR (Lower part of address 0x00-0x0F, Higher part 0x10-0x1F)

#define SET_VOLTAGE         0x30		//--Set voltage of internal charger pump--
										//Use with OR (0x30 - 0x33)

#define SET_START_LINE      0x40		//--Set Display start line--
										//Specifies line address for the initial display line (0x40 - 0x7F) (Add 0-63 to the command)

#define SET_CONTRAST        0x81		//--Set Display contrast--
										//Double bytes command! After command, send contrast value (0x00 - 0xFF)

#define NO_SEGMENT_REMAP    0xA0		//--Segment remap--
#define SET_SEGMENT_REMAP   0xA1		//Collumn (x) addressing start from the bottom or the top of display) (0xA0 or 0xA1)

#define SET_INVERSE_MODE    0xA7		//--Display mode--
#define NO_INVERSE_MODE     0xA6		//Non-inverse display mode(0xA6) or Inverse display mode (0xA7)


#define SET_MULTIPLEX_RATIO 0xA8		//--Set multiplex ratio--
										//Double bytes command! Set display height (0 - 63)

#define SET_DCDC            0xAD		//--DC DC Voltage Converter--
										//Double bytes command! (0x8A - disable, 0x8B - enable)

#define SET_COMM_SCAN_FTOP  0xC0		//--Common pins scan direction--
#define SET_COMM_SCAN_FBOT  0xC8		//Page (y) addressing starting from bottom (0xC8) or from top (0xC0)

#define SET_OFFSET          0xD3		//--Display offset--
										//Double bytes command! Lines offset (y) , mapping of display start line (0x00 - 0x3F)

#define SET_CLOCK_RATIO     0xD5		//--Oscillator frequency--
										//Double bytes command! Set display clock divide ratio / oscillator freq. (0x00 - 0xFF)

#define SET_CHARGE_PERIOD   0xD9		//--Dis/Pre Charge Period--
										//Double bytes command! (datasheet for more info)

#define SET_COMMON_CONFIG   0xDA		//--Set Common pins configuration--
										//Double bytes command! Sequential - 0x02, Alternative - 0x12

#define SET_VCOM            0xDB		//--VCOM Deselect level data--
										//Double bytes command!  (0x00 - 0xFF)

#define READ_MODIFY_WRITE	0xE0		//--Read-modify-write--
#define	END_RMW				0xEE		//Read modify write operation. Always has to be ended by 0xEE

//
//COLORS
//
#define WHITE 0x01
#define BLACK 0x00

//
//Typedefs
//
typedef struct{
	uint8_t x;			//collumn
	uint8_t y; 			//line
	uint8_t page;		//Y/8
}CursorPosition;

typedef struct{
	const uint8_t *FontPointer;
	uint8_t FirstChar;
	uint8_t FontWidth;
	uint8_t FontHeight;
}FontInfo;

typedef enum{
	OLED_OK,
	OLED_ERROR
}OLED_Status;

//
//Functions
//

OLED_Status OLED_Init(I2C_HandleTypeDef *hi2c);															//Initialization
OLED_Status OLED_ClearDisp(void);																		//Clear screen (but not Vram buffer)

OLED_Status OLED_MoveCursor(uint8_t x, uint8_t y);														//Move cursor to x y
void OLED_GetCursorPosition(CursorPosition *OutputPosition);											//Get cursor position
//Buffer related
void OLED_ClearBuffer(uint8_t color);																	//Clear VRAM buffer
OLED_Status OLED_WriteToBuffer(uint8_t *data, uint8_t length, uint8_t color);							//Write to VRAM buffer
OLED_Status OLED_SendBuffer(void);																		//Display VRAM buffer on the screen
//Drawing & Writing
OLED_Status OLED_ChangeFont(const uint8_t *Font);														//Chagne current font for writing
OLED_Status OLED_WriteChar(char character, uint8_t color);												//Write character
OLED_Status OLED_WriteString(char *String, uint8_t color);												//Write whole string
OLED_Status OLED_WriteInt(int Value, uint8_t color);													//Write integer
OLED_Status OLED_DrawBitmapFlash(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t color);			//Draw bitmap from Flash


#endif /* OLED_SSD1106_SSD1106_H_ */
