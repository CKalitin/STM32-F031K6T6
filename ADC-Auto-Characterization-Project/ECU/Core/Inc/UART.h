#include "main.h"

void Continue_On_UART_Receive(UART_HandleTypeDef);
void Send_ADC_Values_Over_UART(UART_HandleTypeDef, int, int);

char tx_buff[100];
char rx_buff[100];
