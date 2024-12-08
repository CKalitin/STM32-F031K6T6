#include "1602alib.h"
#include "char_to_uint8.h"

void LCD_Init() {
	HAL_GPIO_WritePin(POWER_GPIO_Port, POWER_Pin, 1); // Power up display
	HAL_Delay(40); // Appendix C Page 11 of the datasheet for delay length

	LCD_Send(0, 0b00000010); // Set to 4-bit operation
	HAL_Delay(5);

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
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);

  // After testing various delays, this one was found to be necessary
  // This makes sense because the display should only need a delay to process after the falling edge of the E signal, as this is what triggers the read
	HAL_Delay(E_Pin_Pulse_Delay);
}

void LCD_Send_Test_Words() {

	LCD_Send(1, 0b00110000); // 0
    LCD_Send(1, 0b00110001); // 1
    LCD_Send(1, 0b00110010); // 2
    LCD_Send(1, 0b00110011); // 3
    LCD_Send(1, 0b00110100); // 4
    LCD_Send(1, 0b00110101); // 5
    LCD_Send(1, 0b00110110); // 6
    LCD_Send(1, 0b00110111); // 7
    LCD_Send(1, 0b00111000); // 8
    LCD_Send(1, 0b00111001); // 9
	LCD_Send(1, 0b00110000); // 0
    LCD_Send(1, 0b00110001); // 1
    LCD_Send(1, 0b00110010); // 2
    LCD_Send(1, 0b00110011); // 3
    LCD_Send(1, 0b00110100); // 4
    LCD_Send(1, 0b00110101); // 5
    LCD_Send(1, 0b00110110); // 6
    LCD_Send(1, 0b00110111); // 7
    LCD_Send(1, 0b00111000); // 8
    LCD_Send(1, 0b00111001); // 9

    // Set Display Data RAM Address (aaaaaaa) to the Address Counter
    // 0b10000000 = first line, 0b11000000 = second line
	LCD_Send(0, 0b11000100);

	LCD_Send(1, 0b00110000); // 0
    LCD_Send(1, 0b00110001); // 1
    LCD_Send(1, 0b00110010); // 2
    LCD_Send(1, 0b00110011); // 3
    LCD_Send(1, 0b00110100); // 4
    LCD_Send(1, 0b00110101); // 5
    LCD_Send(1, 0b00110110); // 6
    LCD_Send(1, 0b00110111); // 7
    LCD_Send(1, 0b00111000); // 8
    LCD_Send(1, 0b00111001); // 9

	LCD_Send(0, 0b10000000);

    // Test the LCD_Char_To_Uint8 function with 'A'
    char c = 'A';
    uint8_t u;
    char_to_uint8(c, &u);
    LCD_Send(1, u);

    // Test the LCD_Char_To_Uint8 function with an array of chars
    char *str = "Hello World";
    uint8_t u_arr[11];
    LCD_Char_To_Uint8(str, u_arr);
    for (int i = 0; i < 11; i++) {
        LCD_Send(1, u_arr[i]);
    }

	//LCD_Send(1, 0b00100000); // Space
}

// Convert char array to uint8_t array
void LCD_Char_To_Uint8(char *c, uint8_t *u) {
    while (*c) {
        char_to_uint8(*c, u);
        c++;
        u++;
    }
}