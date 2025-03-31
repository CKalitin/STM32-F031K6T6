#include "character_sequences.h"

static int celebration_character_delays[] = {13500, 0, 0, 0, 0, 444, 0, 0, 0, 224, 0, 0, 0, 0, 148, 0, 0, 0, 0, 237, 0, 0, 0, 0, 336, 0, 0, 1006, 0, 0, 0, 0, 733, 0, 189, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 756, 0, 0, 0, 0, 0, 0, 0, 1241, 0, 0, 0, 0, 711, 0, 184, 0, 0, 0, 0, 0, 312, 0, 0, 0, 0, 264, 0, 184, 0, 0, 0, 0, 0, 1226, 0, 0, 0, 0, 0, 978, 0, 0, 0, 0, 196, 0, 160, 0, 0, 0, 0, 216, 0, 0, 0, 0, 240, 0, 0, 0, 324, 0, 0, 0, 220, 0, 0, 0, 160, 0, 0, 0, 0, 0, 0, 456, 0, 0, 0, 772, 0, 0, 0, 283, 0, 0, 0, 416, 0, 0, 0, 821, 0, 0, 0, 263, 0, 0, 437, 0, 0, 0, 0, 0, 816, 0, 0, 0, 0, 0, 556, 0, 0, 0, 500, 0, 280, 0, 0, 0, 0, 0, 272, 0, 0, 0, 235, 0, 0, 0, 0, 257, 0, 0, 0, 0, 0, 0, 992, 0, 0, 0, 0, 760, 0, 0, 0, 0, 351, 0, 0, 0, 0, 261, 0, 0, 0, 172, 0, 0, 0, 0, 160, 0, 0, 0, 0, 244, 0, 0, 0, 0, 0, 0, 1116, 0, 428, 0, 0,
    0, 199, 0, 0, 0, 0, 341, 0, 204, 0, 0, 0, 0, 176, 0, 200, 0, 0, 0, 0, 0, 0, 0, 320, 0, 0, 0, 0, 0, 712, 0, 0, 0, 424, 0, 0, 0, 0, 276, 0, 0, 0, 216, 0, 0, 0, 520, 0, 0, 0, 275, 0, 0, 0, 0, 261, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 423, 0, 0, 0, 325, 0, 0, 0, 0, 0, 380, 0, 0, 0, 520, 0, 0, 0, 280, 0, 0, 0, 272, 0, 0, 0, 320, 0, 0, 0, 0, 348, 0, 0, 0, 1166, 0, 0, 854, 0, 0, 0, 272, 0, 0, 0, 348, 0, 0, 0, 0, 332, 0, 0, 0, 1214, 0, 0, 0, 0, 0, 942, 0, 0, 0, 256, 0, 196, 0, 0, 0, 0, 244, 0, 0, 0, 419, 0, 0, 285, 0, 0, 0, 0, 448, 0, 0, 0, 300, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1012, 0, 0, 0, 249, 0, 0, 0, 0, 299, 0, 0, 0, 0, 0, 0, 0, 372, 0, 0, 200, 0, 0, 0, 296, 0, 0, 0, 0, 196, 0, 0, 160, 0, 187, 0, 0, 0, 0, 0, 0, 0, 925, 0, 0, 0, 356, 0, 0, 0, 228, 0, 156, 0, 0, 0, 0, 0, 323, 0, 0, 213, 0, 0, 0, 0,
     0, 488, 0, 0, 0, 284, 0, 0, 0, 0, 0, 188, 0, 0, 199, 0, 0, 0, 0, 0, 437, 0, 0, 0, 0, 0, 256, 0, 0, 0, 188, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 348, 0, 0, 0, 0, 0, 0, 0, 552, 0, 0, 0, 0, 396, 0, 0, 251, 0, 0, 0, 0, 0, 0, 0, 441, 0, 0, 0, 548, 0, 0, 0, 540, 0, 256, 0, 0, 0, 0, 188, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 199, 0, 0, 0, 0, 0, 0, 229, 0, 0, 0, 0, 408, 0, 0, 284, 0, 0, 0, 200, 0, 0, 0, 172, 0, 0, 0, 0, 0, 0, 364, 0, 0, 0, 0, 0, 524, 0, 0, 0, 203, 0, 0, 0, 0, 149, 0, 0, 0, 0, 0, 0, 0, 0, 0, 915, 0, 0, 0, 504, 0, 0, 217, 0, 0, 0, 0, 0, 296, 0, 0, 208, 0, 0, 0, 188, 0, 0, 172, 0, 0, 0, 0, 826, 0, 0, 1242, 0, 0, 1080, 0, 0, 1092, 0, 0, 844, 0, 0, 872, 0, 0, 0, 364, 0, 0, 0, 0, 188, 0, 0, 0, 0, 0, 0, 0, 0, 416, 0, 0, 0, 0, 0, 0, 532, 0, 0, 0, 304, 0, 0, 0, 215, 0, 0, 241, 0, 0, 0, 211, 0, 0, 0, 0,
     201, 0, 0, 424, 0, 0, 0, 296, 0, 0, 172, 0, 0, 0, 0, 0, 228, 0, 0, 144, 0, 0, 0, 0, 176, 0, 0, 0, 0, 528, 0, 0, 0, 244, 0, 0, 216, 0, 0, 0, 0, 0, 296, 0, 0, 236, 0, 0, 0, 172, 0, 0, 188, 0, 0, 0, 0, 628, 0, 0, 0, 0, 6899, 0, 0, 0, 301, 0, 0, 0, 0, 184, 0, 0, 0, 0, 244, 0, 0, 0, 0, 307, 0, 0, 1015, 0, 0, 0, 0, };
static char *celebration_characters = "Yeah You know what this is It's a celebration bitches grab a drink grab a glass after that I grab your ass why you acting all shy and all why is y'all lying for I never did this before stop that What you want some patron I got that I mean I promise y'all you fine and all and your girlfriend she kinda raw but she not like you No she not like you Right now I need you to mute all the monologue All that talking is gon give me a Tylenol You put a nigga to sleep I'm tired of y'all Right now that Louis Vuitton dine is signing off But I just thought you should know We hit the liquor store got some Christmas and we about to let it flow oh oh oh oh oh Had some problems before but see we let them go Got an ounce of that draw and we about to let it flow Yeah you know what this is It's";

static int debug_character_delays[] = {1000, 0, 1000, 0, 1000, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000, 0, 0, 1000, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 1000, 0, 0, 0, 0};
static char *debug_characters = "1 2 3 reallylongword 4 5 6 7 8 9 10 more really long words";

void Play_Celebration_Lyrics() {
   int index = 0;
   // The final character is 00000000, which is a false boolean
   while (celebration_characters[index] != '\0') {
       int word_len = Get_Next_Word_Length(celebration_characters, index);

       // Set LED high when we're in a delay
       HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

       // Before showing the letter, delay, because that's how the time stamps work
       HAL_Delay(celebration_character_delays[index] - word_len * word_delay_ms);

       HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);

       LCD_Send_Word(celebration_characters + index, word_len, word_delay_ms);

       index += word_len;
   }
}

void Play_Debug_Sequence() {
    int index = 0;
    // The final character is 00000000, which is a false boolean
    while (debug_characters[index] != '\0') {
        int word_len = Get_Next_Word_Length(debug_characters, index);

        // Set LED high when we're in a delay
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

        // Before showing the letter, delay, because that's how the time stamps work
        HAL_Delay(debug_character_delays[index] - word_len * word_delay_ms);

        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);

        LCD_Send_Word(debug_characters + index, word_len, word_delay_ms);

        index += word_len;
    }
}

int Get_Next_Word_Length(char *chars, int start) {
    int length = start;
    while (chars[length] && chars[length] != ' ') {
        length++;
    }
    if (chars[length] == ' ') length++;
    return length - start;
}