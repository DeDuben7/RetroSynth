/**
******************************************************************************
* @file           : gpio.c
* @brief          : functions for initializing gpio's
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
* All rights reserved.</center></h2>
*
******************************************************************************
*/

/* Includes -------------------------------------------------------------------*/
#include "gpio.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void init_gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
	
		/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, 	GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|
														GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|
														GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, 	YM_D0_Pin|YM_D1_Pin|YM_WR_Pin|
														YM_CS_1_Pin|YM_CS_2_Pin|YM_CS_3_Pin|
														YM_CS_4_Pin|YM_D2_Pin|YM_D3_Pin|
														YM_D4_Pin|YM_D5_Pin|YM_D6_Pin|
														YM_D7_Pin|YM_A0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, YM_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : DEBUG_LED_Pin */
  GPIO_InitStruct.Pin = DEBUG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DEBUG_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA4 PA5
                           PA6 PA7 PA11 PA12
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : YM_D0_Pin YM_D1_Pin YM_RST_Pin YM_WR_Pin
                           YM_CS_1_Pin YM_CS_2_Pin YM_CS_3_Pin YM_CS_4_Pin
                           YM_D2_Pin YM_D3_Pin YM_D4_Pin YM_D5_Pin
                           YM_D6_Pin YM_D7_Pin YM_A0_Pin */
  GPIO_InitStruct.Pin = YM_D0_Pin|YM_D1_Pin|YM_RST_Pin|YM_WR_Pin
                          |YM_CS_1_Pin|YM_CS_2_Pin|YM_CS_3_Pin|YM_CS_4_Pin
                          |YM_D2_Pin|YM_D3_Pin|YM_D4_Pin|YM_D5_Pin
                          |YM_D6_Pin|YM_D7_Pin|YM_A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}