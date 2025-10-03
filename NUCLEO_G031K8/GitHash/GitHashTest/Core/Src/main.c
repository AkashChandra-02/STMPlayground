/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "adc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "git_hash.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_SYSTIME_STR_LEN 250
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t systime = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void send_uart_new_line(UART_HandleTypeDef *, uint32_t);

void send_systime(UART_HandleTypeDef *, uint32_t);
void send_int(UART_HandleTypeDef *, char*, uint32_t);
void send_float(UART_HandleTypeDef *, char*, float);
uint16_t poll_adc_channel(uint32_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const char git_hash[GIT_HASH_LEN] = GIT_COMMIT_HASH;
const char git_branch[GIT_BRANCH_LEN] = GIT_BRANCH;
const char cat[] =  "meow";
uint16_t ts_30_val = 0;//TS_CAL_30_VAL;
uint16_t ts_130_val = 0;//TS_CAL_130_VAL;
uint16_t vref_val = 0;//VREF_CAL_30_VAL;
uint16_t temp_sensor = 0, vref_int = 0;
char temp_label[] = "temp raw";
char vref_label[] = "vref raw";
char nice_vref[] = "Vref value";
char nice_temp[] = "Temp value";
float curr_temp, curr_vref;
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
  ts_30_val = TS_CAL_30_VAL;
  ts_130_val = TS_CAL_130_VAL;
  vref_val = VREF_CAL_30_VAL;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_UART_Transmit(&huart2, (const uint8_t*) cat, sizeof(cat), 100);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    HAL_UART_Transmit(&huart2, (const uint8_t*) git_hash, sizeof(git_hash), 100);
    send_uart_new_line(&huart2, 1);
    HAL_UART_Transmit(&huart2, (const uint8_t*) git_branch, sizeof(git_branch), 100);
    send_uart_new_line(&huart2, 1);

    send_systime(&huart2, systime);
    // HAL_UART_Transmit(&huart2, (const uint8_t*) systime, sizeof(systime), 100);
    send_uart_new_line(&huart2, 1);

    vref_int = poll_adc_channel(ADC_CHANNEL_VREFINT);
    temp_sensor = poll_adc_channel(ADC_CHANNEL_TEMPSENSOR);

    send_int(&huart2, vref_label, (uint32_t) vref_int);
    send_uart_new_line(&huart2, 1);
    send_int(&huart2, temp_label, (uint32_t) temp_sensor);
    send_uart_new_line(&huart2, 1);
    curr_vref = 3.3 * vref_int/4095;
    curr_temp = 30 + (((ts_130_val-ts_30_val)/100) * (temp_sensor/4095.0)); 

    send_float(&huart2, nice_temp, curr_temp);
    send_uart_new_line(&huart2, 1);
    send_float(&huart2, nice_vref, curr_vref);
    send_uart_new_line(&huart2, 1);
       
    // HAL_Delay(500);
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
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
}

/* USER CODE BEGIN 4 */
void send_uart_new_line(UART_HandleTypeDef * huart, uint32_t timeout){
  const char new_line_char = '\n';
  HAL_UART_Transmit(huart, (const uint8_t*) &new_line_char, sizeof(new_line_char), timeout);
}
void send_systime(UART_HandleTypeDef * huart, uint32_t systime){
  char str[MAX_SYSTIME_STR_LEN];
  uint8_t str_len = MAX_SYSTIME_STR_LEN;
  for(int i = 0; i < MAX_SYSTIME_STR_LEN; i++){
    str[i] = 0;
  }
  sprintf(str, "Systime: %u", (int) systime);
  // find last non null char
  for(int i = 0; i < MAX_SYSTIME_STR_LEN; i++){
    if(str[i] == 0){
      str_len = i;
      i = MAX_SYSTIME_STR_LEN+100;
    }
  }
  HAL_UART_Transmit(huart, (const uint8_t*) &str, str_len, 100);
}

void send_int(UART_HandleTypeDef * huart, char* label, uint32_t value){
  char str[MAX_SYSTIME_STR_LEN];
  uint8_t str_len = MAX_SYSTIME_STR_LEN;
  for(int i = 0; i < MAX_SYSTIME_STR_LEN; i++){
    str[i] = 0;
  }
  sprintf(str, "%s: %u", label, (int) value);
  // find last non null char
  for(int i = 0; i < MAX_SYSTIME_STR_LEN; i++){
    if(str[i] == 0){
      str_len = i;
      i = MAX_SYSTIME_STR_LEN+100;
    }
  }
  HAL_UART_Transmit(huart, (const uint8_t*) &str, str_len, 100);
}

void send_float(UART_HandleTypeDef * huart, char* label, float value){
  char str[MAX_SYSTIME_STR_LEN];
  uint8_t str_len = MAX_SYSTIME_STR_LEN;
  for(int i = 0; i < MAX_SYSTIME_STR_LEN; i++){
    str[i] = 0;
  }
  sprintf(str, "%s: %f", label, value);
  // find last non null char
  for(int i = 0; i < MAX_SYSTIME_STR_LEN; i++){
    if(str[i] == 0){
      str_len = i;
      i = MAX_SYSTIME_STR_LEN+100;
    }
  }
  HAL_UART_Transmit(huart, (const uint8_t*) &str, str_len, 100);
}

uint16_t poll_adc_channel(uint32_t channel){
  
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = channel;//ADC_CHANNEL_TEMPSENSOR;//ADC_CHANNEL_VREFINT
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 10);
  uint16_t return_val = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  return return_val;
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
#ifdef USE_FULL_ASSERT
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
