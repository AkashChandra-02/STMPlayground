/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define T_NRST_Pin GPIO_PIN_2
#define T_NRST_GPIO_Port GPIOF
#define T_VCP_TX_Pin GPIO_PIN_2
#define T_VCP_TX_GPIO_Port GPIOA
#define T_VCP_RX_Pin GPIO_PIN_3
#define T_VCP_RX_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_6
#define LD3_GPIO_Port GPIOC
#define T_JTMS_Pin GPIO_PIN_13
#define T_JTMS_GPIO_Port GPIOA
#define T_JTCK_Pin GPIO_PIN_14
#define T_JTCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
extern uint32_t systime;
#define __JOIN_UINT8_INTO_UINT16__(__MSB__, __LSB__) ((__MSB__ << 8) | __LSB__)
#define TS_CAL_30_LSB_ADDR (uint8_t *) 0x1FFF75A8
#define TS_CAL_30_MSB_ADDR (uint8_t *) 0x1FFF75A9

#define TS_CAL_130_LSB_ADDR (uint8_t *) 0x1FFF75CA
#define TS_CAL_130_MSB_ADDR (uint8_t *) 0x1FFF75CB

#define VREF_30_LSB_ADDR (uint8_t *) 0x1FFF75AA
#define VREF_30_MSB_ADDR (uint8_t *) 0x1FFF75AB

#define TS_CAL_30_VAL __JOIN_UINT8_INTO_UINT16__((uint8_t) *(TS_CAL_30_MSB_ADDR), (uint8_t) *(TS_CAL_30_LSB_ADDR))
#define TS_CAL_130_VAL __JOIN_UINT8_INTO_UINT16__((uint8_t) *(TS_CAL_130_MSB_ADDR), (uint8_t) *(TS_CAL_130_LSB_ADDR))
#define VREF_CAL_30_VAL __JOIN_UINT8_INTO_UINT16__((uint8_t) *(VREF_30_MSB_ADDR), (uint8_t) *(VREF_30_LSB_ADDR))

#define VREF_VALUE 1.212f
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
