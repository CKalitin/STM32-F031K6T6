#include "main.h"

#define ADC_BUFFER_LENGTH 128

uint32_t adcBuffer[ADC_BUFFER_LENGTH];

// Note that UART_HandleTypeDef and ADC_HandleTypeDef are parameters so that we can change if we use UART1, UART2, etc. or ADC1, ADCx, etc.
void Get_Averaged_ADC_Values(int*, int*, int*);
