#include "celebration.h"

static int timestamps[] = {13500, 0, 0, 0, 0, 13944, 0, 0, 0, 14168, 0, 0, 0, 0, 14316, 0, 0, 0, 0, 14553, 0, 0, 0, 0, 14889, 0, 0, 15895, 0, 0, 0, 0, 16628, 0, 16817, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17573, 0, 0, 0, 0, 0, 0, 0, 18814, 0, 0, 0, 0, 19525, 0, 19709, 0, 0, 0, 0, 0, 20021, 0, 0, 0, 0, 20285, 0, 20469, 0, 0, 0, 0, 0, 21695, 0, 0, 0, 0, 0, 22673, 0, 0, 0, 0, 22869, 0, 23029, 0, 0, 0, 0, 23245, 0, 0, 0, 0, 23485, 0, 0, 0, 23809, 0, 0, 0, 24029, 0, 0, 0, 24189, 0, 0, 0, 0, 0, 0, 24645, 0, 0, 0, 25417, 0, 0, 0, 25700, 0, 0, 0, 26116, 0, 0, 0, 26937, 0, 0, 0, 27200, 0, 0, 27637, 0, 0, 0, 0, 0, 28453, 0, 0, 0, 0, 0, 29009, 0, 0, 0, 29509, 0, 29789, 0, 0, 0, 0, 0, 30061, 0, 0, 0, 30296, 0, 0, 0, 0, 30553, 0, 0, 0, 0, 0, 0, 31545, 0, 0, 0, 0, 32305, 0, 0, 0, 0, 32656, 0, 0, 0, 0, 32917, 0, 0, 0, 33089, 0, 0, 0, 0, 33249, 0, 0, 0, 0, 33493, 0, 0, 0, 0, 0, 0, 34609, 0, 35037, 0, 0, 0, 35236, 0, 0, 0, 0, 35577, 0, 35781, 0, 0, 0, 0, 35957, 0, 36157, 0, 0, 0, 0, 0, 0, 0, 36477, 0, 0, 0, 0, 0, 37189, 0, 0, 0, 37613, 0, 0, 0, 0, 37889, 0, 0, 0, 38105, 0, 0, 0, 38625, 0, 0, 0, 38900, 0, 0, 0, 0, 39161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39584, 0, 0, 
0, 39909, 0, 0, 0, 0, 0, 40289, 0, 0, 0, 40809, 0, 0, 0, 41089, 0, 0, 0, 41361, 0, 0, 0, 41681, 0, 0, 0, 0, 42029, 0, 0, 0, 43195, 0, 0, 44049, 0, 0, 0, 44321, 0, 0, 0, 44669, 0, 0, 0, 0, 45001, 0, 0, 0, 46215, 0, 0, 0, 0, 0, 
47157, 0, 0, 0, 47413, 0, 47609, 0, 0, 0, 0, 47853, 0, 0, 0, 48272, 0, 0, 48557, 0, 0, 0, 0, 49005, 0, 0, 0, 49305, 0, 0, 0, 49545, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50557, 0, 0, 0, 50806, 0, 0, 0, 0, 51105, 0, 0, 0, 0, 0, 0, 0, 51477, 0, 0, 51677, 0, 0, 0, 51973, 0, 0, 0, 0, 52169, 0, 0, 52329, 0, 52516, 0, 0, 0, 0, 0, 0, 0, 53441, 0, 0, 0, 53797, 0, 0, 0, 54025, 0, 54181, 0, 0, 0, 0, 0, 54504, 0, 0, 54717, 0, 0, 0, 0, 0, 55205, 0, 0, 0, 55489, 0, 0, 0, 
0, 0, 55677, 0, 0, 55876, 0, 0, 0, 0, 0, 56313, 0, 0, 0, 0, 0, 56569, 0, 0, 0, 56757, 0, 0, 0, 0, 56957, 0, 0, 0, 0, 0, 57305, 0, 0, 0, 0, 0, 0, 0, 57857, 0, 0, 0, 0, 58253, 0, 0, 58504, 0, 0, 0, 0, 0, 0, 0, 58945, 0, 0, 0, 59493, 0, 0, 0, 60033, 0, 60289, 0, 0, 0, 0, 60477, 0, 0, 0, 0, 0, 0, 0, 60677, 0, 0, 0, 60876, 0, 0, 0, 0, 0, 0, 61105, 0, 0, 0, 0, 61513, 0, 0, 61797, 0, 0, 0, 61997, 0, 0, 0, 62169, 0, 0, 0, 0, 0, 0, 62533, 0, 0, 0, 0, 0, 63057, 0, 0, 0, 63260, 0, 0, 0, 0, 63409, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64324, 0, 0, 0, 64828, 0, 0, 65045, 0, 0, 0, 0, 0, 65341, 0, 0, 65549, 0, 0, 0, 65737, 0, 0, 65909, 0, 0, 0, 0, 66735, 0, 0, 67977, 0, 0, 69057, 0, 0, 70149, 0, 0, 70993, 0, 0, 71865, 0, 0, 0, 72229, 0, 0, 0, 0, 72417, 0, 0, 0, 0, 0, 0, 0, 0, 72833, 0, 0, 0, 0, 0, 0, 73365, 0, 0, 0, 73669, 0, 0, 0, 73884, 0, 0, 74125, 0, 0, 0, 74336, 0, 0, 0, 0, 74537, 0, 0, 74961, 0, 0, 0, 75257, 0, 0, 75429, 0, 0, 0, 0, 0, 75657, 0, 0, 75801, 0, 0, 0, 0, 75977, 0, 0, 0, 0, 76505, 0, 0, 0, 76749, 0, 0, 76965, 0, 0, 0, 0, 0, 77261, 0, 0, 77497, 0, 0, 0, 77669, 0, 0, 77857, 0, 0, 0, 0, 78485, 0, 0, 0, 0, 85384, 0, 0, 0, 85685, 0, 0, 0, 0, 85869, 0, 0, 0, 0, 86113, 0, 0, 0, 0, 86420, 0, 0, 87435, 0, 0, 0, 0};
static char *characters = "Yeah You know what this is It's a celebration bitches grab a drink grab a glass after that I grab your ass why you acting all shy and all why is y'all lying for I never did this before stop that What you want some patron I got that I mean I promise y'all you fine and all and your girlfriend she kinda raw but she not like you No she not like you Right now I need you to mute all the monologue All that talking is gon give me a Tylenol You put a nigga to sleep I'm tired of y'all Right now that Louis Vuitton dine is signing off But I just thought you should know We hit the liquor store got some Christmas and we about to let it flow oh oh oh oh oh Had some problems before but see we let them go Got an ounce of that draw and we about to let it flow Yeah you know what this is It's";

void Play_Celebration_Lyrics() {
    uint32_t previous_time_stamp = 0;

    int index = 0;
    // The final character is 00000000, which is a false boolean
    while (characters[index] != '\0') {
        int word_len = Get_Next_Word_Length(characters, index);

        // Set LED high when we're in a delay
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

        // Before showing the letter, delay, because that's how the time stamps work
        HAL_Delay(timestamps[index] - previous_time_stamp - word_len * word_delay_ms);
        previous_time_stamp = timestamps[index];

        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);

        LCD_Send_Word(characters + index, word_len, word_delay_ms);

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