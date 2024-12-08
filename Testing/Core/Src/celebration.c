#include "celebration.h"

// 13944
static int time_stamps[] = {0, 0, 0, 0, 14168, 0, 0, 0, 0, 14316, 0, 0, 0, 0, 14553, 0, 0, 0, 0, 14889, 0, 0, 15895, 0, 0, 0, 16628, 0, 16817, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 17573, 0, 0, 0, 0, 0, 0, 0, 18814, 0, 0, 0, 0, 19525, 0, 19709, 0, 0, 0, 0, 0, 20021, 0, 0, 0, 0, 20285, 0, 20469, 0, 0, 0, 0, 0, 21695, 0, 0, 0, 0, 0, 22673, 0, 0, 0, 0, 22869,
0, 23029, 0, 0, 0, 0, 23245, 0, 0, 0, 0, 23485, 0, 0, 0, 23809, 0, 0, 0};
static char *characters = "You know what this is Its a celebration bitches grab a drink grab a glass after that I grab your ass why"; // Longest possible array

void Play_Celebration_Lyrics() {
    uint32_t previous_time_stamp = 0;
    int word_length = 0;
    for (int i = 0; i < 4; i++){
        char *chars = "abcde";
        LCD_Send_Word(chars + i, i + 1, word_delay_ms);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
        HAL_Delay(500);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
        HAL_Delay(500);
    }
    HAL_Delay(5000);
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);

    LCD_Send_Word(characters, 1, word_delay_ms);

    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
    for (int i = 0; characters[i] != '\0'; i += word_length) {
        word_length = Get_Next_Word_Length(characters, i);

        LCD_Send_Word(characters + i, word_length, word_delay_ms);

        HAL_Delay(1000);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
    }

    int index = 0;
    // The final character is 00000000, which is a false boolean
    while (characters[index] != '\0') {
        int word_len = Get_Next_Word_Length(characters, index);

        LCD_Send_Word(characters + index, word_len, word_delay_ms);

        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
        HAL_Delay(time_stamps[index] - previous_time_stamp - word_len * word_delay_ms);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
        previous_time_stamp = time_stamps[index];
        index += word_len;
    }
}

// Get the length of the next word after start index, including the space
int Get_Next_Word_Length(char *chars, int start) {
    int length = start;

    while (chars[length] && chars[length] != ' ') {
        length++;
    }

    // Add the final space
    if (chars[length] == ' ') length++;

    return length - start;
}