#include "1602alib.h"

#include <string.h>

#define word_delay_ms 10

static int timestamps[];
static char *characters;

void Play_Celebration_Lyrics();

int Get_Next_Word_Length(char *chars, int start);