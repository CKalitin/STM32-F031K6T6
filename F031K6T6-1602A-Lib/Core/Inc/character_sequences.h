// To prevent recurrsive inclusion
#pragma once

#include "1602alib.h"

#include <string.h>

#define word_delay_ms 10

void Play_Debug_Sequence(UART_HandleTypeDef *huart);
void Play_Celebration_Lyrics(UART_HandleTypeDef *huart);

int Get_Next_Word_Length(char *chars, int start);