#include "UART.h"

/**
  * @brief Wait for 's' character to be received over UART to continue the program
  * @param uart: UART_HandleTypeDef object
  * @retval None
  */
void Continue_On_UART_Receive(UART_HandleTypeDef uart){
  // The 's' character here is arbitrary
  // We just pause the program until we see 's\n' received over uart
  memset(rx_buff_me, 0, sizeof(rx_buff_me));
  while (rx_buff_me[0] != 's'){
    memset(rx_buff_me, 0, sizeof(rx_buff_me));
    HAL_UART_Receive(&uart, (uint8_t*)rx_buff_me, sizeof(rx_buff_me), 1000); // HAL_UART_Receive waits until '\n' to continue the program
    HAL_Delay(1); // Wait a ms because why not
  }
}

/**
  * @brief Send ADC values over UART to the Python script
  * @param uart: UART_HandleTypeDef object
  * @retval None
  */
void Send_ADC_Values_Over_UART(UART_HandleTypeDef uart, int adcValuesAveraged, int adcValuesADCAdjusted, int adcValuesCurrentAdjusted){
  memset(tx_buff_me, 0, sizeof(tx_buff_me));
  sprintf(tx_buff_me, "%d, %d, %d\n\r", adcValuesAveraged, adcValuesADCAdjusted, adcValuesCurrentAdjusted);
  HAL_UART_Transmit(&uart, (uint8_t*)tx_buff_me, sizeof(tx_buff_me), 1000);
}
