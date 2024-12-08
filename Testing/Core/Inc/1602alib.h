#include "main.h"

#define E_Pin_Pulse_Delay 1 // ms

void LCD_Init();
void LCD_Send(uint8_t RS_Pin_Value, uint8_t data);
void LCD_E_Pulse();

void LCD_Send_Test_Words();