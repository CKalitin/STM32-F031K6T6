#include "main.h"
#include "char_to_uint8.h"

#include <string.h>

#define E_Pin_Pulse_Delay 1 // ms

void LCD_Init();
void LCD_Send(uint8_t RS_Pin_Value, uint8_t data);
void LCD_Pulse_E_Pin();

void LCD_Clear_Display();

void LCD_Send_Test_Words();

void LCD_Send_Word(char *str);
void LCD_Char_Array_To_Uint8(char *c, uint8_t *u);

