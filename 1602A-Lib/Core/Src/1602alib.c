#include "1602alib.h"

void LCD_Init() {
	//HAL_GPIO_WritePin(POWER_GPIO_Port, POWER_Pin, 1); // Power up display
	HAL_Delay(40); // Appendix C Page 11 of the datasheet for delay length

	LCD_Send(0, 0b00000010); // Set to 4-bit operation
	HAL_Delay(5);

	// Note that we're using the font sheet on Page 29 of Appendix C on the datasheet and that I have no clue how to change this
	LCD_Send(0, 0b00101000); // 001D NF00: D=Date Length (4 bits is low, 8 bits high), N=Number of lines, F=Font Size
	LCD_Send(0, 0b00001100); // 0000 1DCB: D=Display, C=Cursor, B=Blink
	LCD_Send(0, 0b00000110); // 0000 01IS: I=Increment (1) / Decrement (0), S=Shift
}

void LCD_Send(uint8_t RS_Pin_value, uint8_t data){
	// Register select pin. RS=0: Command, RS=1: Data
	// Read the documentation: https://www.crystalfontz.com/products/document/964/CFAH1602XYYHJP_v2.0.pdf
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, RS_Pin_value);

	// We send the higher order bits (left most) first, then the lower order bits. So we get 4+4=8 bits total
	// Look at the top of page 11 in the 1602A documentation for more info
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, data & 0b00010000);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, data & 0b00100000);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, data & 0b01000000);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, data & 0b10000000);

	// Pulse the E pin high then low so the microcontroller reads in the data
	LCD_Pulse_E_Pin();

	// 4 Lower order bits (right most in the byte)
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, data & 0b00000001);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, data & 0b00000010);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, data & 0b00000100);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, data & 0b00001000);

	LCD_Pulse_E_Pin();
}

// We need to pulse the "Enable" pin to read the data pins
// Operation enable signal. Falling edge triggers reading data.
void LCD_Pulse_E_Pin() {
	// The display reads in the values from the data pins when it detects the falling edge of the E signal
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
	HAL_Delay(E_Pin_Pulse_Delay); // you could get by without this line
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);

  // After testing various delays, this one was found to be necessary
  // This makes sense because the display should only need a delay to process after the falling edge of the E signal, as this is what triggers the read
	HAL_Delay(E_Pin_Pulse_Delay);
}

void LCD_Clear_Display() {
    LCD_Send(0, 0b00000001);
}

// str: The string to print, char_delay_ms: The delay between each character
void LCD_Send_Word(char *str, uint8_t size, uint32_t char_delay_ms){
	uint8_t u_arr[size];
	LCD_Char_Array_To_Uint8(str, u_arr, size);
	
	// If the size is larger than a single line, clear the display and print from position zero
	// You get an ugly seam in the middle of the word, but this is better than the alternative
	if (size > 16) {
		current_position = 0;
		LCD_Set_Cursor_Pos(0);
		LCD_Clear_Display();
		LCD_Send_Char_Array_At_Cursor(u_arr, 16, char_delay_ms);
		LCD_Set_Cursor_Pos(16);
		LCD_Send_Char_Array_At_Cursor(u_arr + 16, size - 16, char_delay_ms);
		return;
	}

	// If size is greater than the remaining space on line 2, clear the display and print from position zero
	if (current_position + size > 32) {
		current_position = 0;
		LCD_Set_Cursor_Pos(0);
		LCD_Clear_Display();
		LCD_Send_Char_Array_At_Cursor(u_arr, size, char_delay_ms);
		return;
	}

	// If size is greater than the remaining space on line 1, go to line 2
	if (current_position + size >= 16 && current_position < 16) {
		current_position = 16;
		LCD_Set_Cursor_Pos(16);
		LCD_Send_Char_Array_At_Cursor(u_arr, size, char_delay_ms);
		return;
	}

	// Otherwise, print the string
	LCD_Send_Char_Array_At_Cursor(u_arr, size, char_delay_ms);
}

// This prints a char array to the display starting at the current cursor position
// str: The string to print, char_delay_ms: The delay between each character
void LCD_Send_Char_Array_At_Cursor(uint8_t *arr, uint8_t size, uint32_t char_delay_ms) {
	for (int i = 0; i < size; i++) {
		LCD_Send(1, arr[i]);
		HAL_Delay(char_delay_ms);
	}
	current_position += size;
}

void LCD_Set_Cursor_Pos(uint8_t pos) {
	// I'm using this command from Appendix C page 6 of the datasheet (5.2.8)
    // Set Display Data RAM Address (1xxxxxxx) to the Address Counter
    // 0b10000000 = first line, 0b11000000 = second line

	if (pos < 16) {
		LCD_Send(0, 0b10000000 + pos);
	} else {
		LCD_Send(0, 0b11000000 + pos - 16);
	}
}

// Convert char array to uint8_t array
void LCD_Char_Array_To_Uint8(char *c, uint8_t *u, uint8_t size) {
    while (*c && size > 0) {
        char_to_uint8(*c, u);
        c++;
        u++;
		size--;
    }
}