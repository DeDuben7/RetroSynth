/**
******************************************************************************
* @file           : gpio.h
* @brief          : functions and defines for initializing gpio's
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
* All rights reserved.</center></h2>
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Defines -------------------------------------------------------------------*/
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

/* Functions -------------------------------------------------------------------*/
extern void init_gpio(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */