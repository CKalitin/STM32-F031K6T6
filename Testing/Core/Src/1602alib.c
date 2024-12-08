#include "1602alib.h"

void LCD_Init() {
	HAL_GPIO_WritePin(POWER_GPIO_Port, POWER_Pin, 1);
	HAL_Delay(100);

	// Start up functions:
	// 1. 4-bit mode 0x02, 2. TODO FINISH THIS

	LCD_Send(0, 0b00000010); // Set to 4-bit operation
	HAL_Delay(20);

	LCD_Send(0, 0b00101100); // Set display to 2 rows and font to 0
	LCD_Send(0, 0b00001110); // Turn on display and cursor appears
	LCD_Send(0, 0b00000110); // Increase address by one, shift cursor to right when writing, display has no shift

	LCD_Send(1, 0b01010111); // W
	LCD_Send(1, 0b01001111); // O
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01001011); // K

	LCD_Send(1, 0b00100000); // Space

	LCD_Send(1, 0b01001000); // H
	LCD_Send(1, 0b01000001); // A
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01000100); // D
	LCD_Send(1, 0b01000101); // E
	LCD_Send(1, 0b01010010); // R

	LCD_Send(1, 0b00100000); // Space

	LCD_Send(1, 0b01010111); // W
	LCD_Send(1, 0b01001111); // O
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01001011); // K

	LCD_Send(0, 0b11000000); // Switch to second line - is this a register select?

	LCD_Send(1, 0b00100000); // Space

	LCD_Send(1, 0b01001000); // H
	LCD_Send(1, 0b01000001); // A
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01000100); // D
	LCD_Send(1, 0b01000101); // E
	LCD_Send(1, 0b01010010); // R
}

void LCD_Send(uint8_t RS_Pin_value, uint8_t data){
	// Register select pin. RS=0: Command, RS=1: Data
	// Read the documentation: https://www.technologicalarts.ca/support/docs/Components/OLED1602A/SOC1602A.pdf
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, RS_Pin_value);

	// We send the higher order bits (left most) first, then the lower order bits. So we get 4+4=8 bits total
	// Look at the top of page 11 in the 1602A documentation for more info
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, data & 0b00010000);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, data & 0b00100000);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, data & 0b01000000);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, data & 0b10000000);

	// Pulse the E pin high then low so the microcontroller reads in the data
	LCD_E_Pulse();

	// 4 Lower order bits (right most in the byte)
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, data & 0b00000001);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, data & 0b00000010);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, data & 0b00000100);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, data & 0b00001000);

	LCD_E_Pulse();

	//HAL_UART_Transmit(&huart1, "Test", 1, 0xFFFF);
}

// We need to pulse the "Enable" pin to read the data pins
// Operation enable signal. Falling edge triggers reading data.
void LCD_E_Pulse() {
	// The display reads in the values from the data pins when it detects the falling edge of the E signal
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);

  // After testing various delays, this one was found to be necessary
  // This makes sense because the display should only need a delay to process after the falling edge of the E signal, as this is what triggers the read
	HAL_Delay(1);
}
