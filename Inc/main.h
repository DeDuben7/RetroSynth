/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define DEBUG_LED_Pin GPIO_PIN_13
#define DEBUG_LED_GPIO_Port GPIOC
#define YM_D0_Pin GPIO_PIN_0
#define YM_D0_GPIO_Port GPIOB
#define YM_D1_Pin GPIO_PIN_1
#define YM_D1_GPIO_Port GPIOB
#define YM_RST_Pin GPIO_PIN_10
#define YM_RST_GPIO_Port GPIOB
#define YM_WR_Pin GPIO_PIN_11
#define YM_WR_GPIO_Port GPIOB
#define YM_CS_1_Pin GPIO_PIN_12
#define YM_CS_1_GPIO_Port GPIOB
#define YM_CS_2_Pin GPIO_PIN_13
#define YM_CS_2_GPIO_Port GPIOB
#define YM_CS_3_Pin GPIO_PIN_14
#define YM_CS_3_GPIO_Port GPIOB
#define YM_CS_4_Pin GPIO_PIN_15
#define YM_CS_4_GPIO_Port GPIOB
#define YM_D2_Pin GPIO_PIN_3
#define YM_D2_GPIO_Port GPIOB
#define YM_D3_Pin GPIO_PIN_4
#define YM_D3_GPIO_Port GPIOB
#define YM_D4_Pin GPIO_PIN_5
#define YM_D4_GPIO_Port GPIOB
#define YM_D5_Pin GPIO_PIN_6
#define YM_D5_GPIO_Port GPIOB
#define YM_D6_Pin GPIO_PIN_7
#define YM_D6_GPIO_Port GPIOB
#define YM_D7_Pin GPIO_PIN_8
#define YM_D7_GPIO_Port GPIOB
#define YM_A0_Pin GPIO_PIN_9
#define YM_A0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

typedef struct /**< structure for storing the effect settings of each chip channel */
{
	uint8_t Waveform;
	uint8_t AM;
	uint8_t Vibrato;
	uint8_t Pedal_Sustain;
	uint8_t ModFreqMult;
	uint8_t Volume;
	uint8_t Attack;
	uint8_t Decay;
	uint8_t Sustain;
	uint8_t Release;
	uint8_t KSR;
	uint8_t ScalingLevel;
}Operator;

typedef struct /**< Structure for storing the data of each voice channel */
{
	uint8_t Enable;
	uint8_t KEY_Numb;
	uint16_t F_Numb;
	uint8_t Octave;
	uint8_t Velocity;
	uint8_t i_tel;

}pVCH;

typedef struct /**< structure for storing the effect settings of each operator */
{
	uint8_t AM_Depth;
	uint8_t Vib_Depth;
	uint8_t Feedback;
	uint8_t ModulatieMode;

	Operator OP1;
	Operator OP2;
}*pCCH;


extern pCCH CCH[4];		/**< four variables for the effects settings structs of each chip channel */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
