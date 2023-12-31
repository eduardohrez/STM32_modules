/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/*
#include "I2C_base.h"

#include "I2C_ATH10.h"
#include "font_lcd.h"
#include "I2C_LCD.h"

#include "../../User_modules/run_time/Roun_time.h"
#include "SPI_BASE.h"
#include "LCD_ST7.h"

#include "crc7_soft.h"
#include "SD_Base_SPI.h"
*/
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
void Set_flag_interrupt(uint8_t Value);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Interrupt_Pin GPIO_PIN_0
#define Interrupt_GPIO_Port GPIOA
#define Interrupt_EXTI_IRQn EXTI0_IRQn
#define CS_SD_Pin GPIO_PIN_2
#define CS_SD_GPIO_Port GPIOA
#define CS_ST7_Pin GPIO_PIN_9
#define CS_ST7_GPIO_Port GPIOA
#define RES_Pin GPIO_PIN_10
#define RES_GPIO_Port GPIOA
#define DC_Pin GPIO_PIN_11
#define DC_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
