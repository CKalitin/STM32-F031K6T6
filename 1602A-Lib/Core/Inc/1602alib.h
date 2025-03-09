#include "main.h"
#include "char_to_uint8.h"

#include <string.h>

#define E_Pin_Pulse_Delay 500 // ms

// Init & Sending Bits
void LCD_Init();
void LCD_Send(uint8_t RS_Pin_Value, uint8_t data);
void LCD_Pulse_E_Pin();

// Display Functions
void LCD_Clear_Display();
void LCD_Set_Cursor_Pos(uint8_t pos);

// Sending Strings
void LCD_Send_Word(char *str, uint8_t size, uint32_t char_delay_ms);
void LCD_Send_Char_Array_At_Cursor(uint8_t *arr, uint8_t size, uint32_t char_delay_ms);
void LCD_Char_Array_To_Uint8(char *c, uint8_t *u, uint8_t size);

// 0-31, where 0 is char 1 on line 1 and 16 char 1 on line 2
uint8_t current_position;
