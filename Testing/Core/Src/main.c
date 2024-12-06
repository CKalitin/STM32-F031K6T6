/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

static void LCD_Init();
static void LCD_Send(uint8_t RS_Pin_Value, uint8_t data);
static void LCD_E_Pulse();

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  const char *msg = "Hello, STM32 UART!\r\n";
	  HAL_UART_Transmit_IT(&huart1, (uint8_t*)msg, 1);

	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	  HAL_Delay(500);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RS_Pin|E_Pin|D4_Pin|D5_Pin
                          |D6_Pin|D7_Pin|POWER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RS_Pin E_Pin D4_Pin D5_Pin
                           D6_Pin D7_Pin POWER_Pin */
  GPIO_InitStruct.Pin = RS_Pin|E_Pin|D4_Pin|D5_Pin
                          |D6_Pin|D7_Pin|POWER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

static void LCD_Init(){
	HAL_GPIO_WritePin(POWER_GPIO_Port, POWER_Pin, 1);
	HAL_Delay(100);

	// Set to 4-bit mode
	// Because this command is only 4 bits (and not two pulses of 4 bits to get 8 in total), it is done manually
	/*HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 0);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
	LCD_E_Pulse();

	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 0);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
	LCD_E_Pulse();
	*/

	// Start up functions:
	// 1. 4-bit mode 0x02, 2. TODO FINISH THIS

	LCD_Send(0, 0b00000010); // Set to 4-bit operation
	HAL_Delay(100);

	LCD_Send(0, 0b00100001); // Set font to 0,0
	LCD_Send(0, 0b00001110); // Turn on display and cursor appears
	LCD_Send(0, 0b00000110); // Increase address by one, shift cursor to right when writing, display has no shift

	LCD_Send(1, 0b01010111); // W
	LCD_Send(1, 0b01001111); // O
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01001011); // K

	LCD_Send(1, 0b00100000); // Space

	LCD_Send(1, 0b01001000); // H
	LCD_Send(1, 0b01000001); // A
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01000100); // D
	LCD_Send(1, 0b01000101); // E
	LCD_Send(1, 0b01010010); // R

	LCD_Send(1, 0b01010111); // W
	LCD_Send(1, 0b01001111); // O
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01001011); // K

	LCD_Send(1, 0b00100000); // Space

	LCD_Send(1, 0b01001000); // H
	LCD_Send(1, 0b01000001); // A
	LCD_Send(1, 0b01010010); // R
	LCD_Send(1, 0b01000100); // D
	LCD_Send(1, 0b01000101); // E
	LCD_Send(1, 0b01010010); // R
}

static void LCD_Send(uint8_t RS_Pin_value, uint8_t data){
	// Register select pin. RS=0: Command, RS=1: Data
	// Read the documentation: https://www.technologicalarts.ca/support/docs/Components/OLED1602A/SOC1602A.pdf
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, RS_Pin_value);

	// We send the higher order bits (left most) first, then the lower order bits. So we get 4+4=8 bits total
	// Look at the top of page 11 in the 1602A documentation for more info
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, data & 0b00010000);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, data & 0b00100000);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, data & 0b01000000);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, data & 0b10000000);

	// Pulse the E pin high then low so the microcontroller reads in the data
	LCD_E_Pulse();

	// 4 Lower order bits (right most in the byte)
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, data & 0b00000001);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, data & 0b00000010);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, data & 0b00000100);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, data & 0b00001000);

	LCD_E_Pulse();

	//HAL_UART_Transmit(&huart1, "Test", 1, 0xFFFF);
}

// We need to pulse the "Enable" pin to read the data pins
static void LCD_E_Pulse() {
	// Operation enable signal. Falling edge triggered.
	// The display reads in the values from the data pins when it detects the falling edge of the E signal
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
	HAL_Delay(1); // Slight delay for the sake of the display, probably needed idk I haven't learned this from first principles
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
	HAL_Delay(1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
