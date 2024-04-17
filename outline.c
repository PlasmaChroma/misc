
#include "main.h"
#include <string.h>
#include <stdio.h>

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);

int main(void)
{
  uint16_t raw;
  char msg[10];

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Test: Set GPIO pin high
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);

    // Get ADC value
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    raw = HAL_ADC_GetValue(&hadc1);

    // Test: Set GPIO pin low
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

    // Convert to string and print
    sprintf(msg, "%hu\r\n", raw);
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    // Pretend we have to do something else for a while
    HAL_Delay(1);
  }
}