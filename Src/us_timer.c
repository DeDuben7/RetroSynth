/**
******************************************************************************
* @file           : us_timer.c
* @brief          : description
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
* All rights reserved.</center></h2>
*
******************************************************************************
*/


/* Includes -------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#include "us_timer.h"
#include "gpio.h"
#include "main.h"
/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/

/* Function prototypes ---------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

TIM_HandleTypeDef us_timer_handle;
 
void us_timer_init(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  us_timer_handle.Instance = TIM2;
  us_timer_handle.Init.Prescaler = 72-1;
  us_timer_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  us_timer_handle.Init.Period = 0xFFFF;
  us_timer_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&us_timer_handle) != HAL_OK)
  {
    Error_Handler();
  }
	
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&us_timer_handle, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&us_timer_handle, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
	// Start the timer
  if (HAL_TIM_Base_Start(&us_timer_handle) != HAL_OK)
  {
    Error_Handler();
  }
}

void us_delay(uint32_t us) {
	// Calculate the number of timer ticks required for the given microseconds
	uint32_t ticks = us;

	// Calculate the number of complete timer overflows
	uint32_t overflows = ticks / 0xFFFF;
	// Calculate the remaining ticks after complete overflows
	uint32_t remainder = (ticks % 0xFFFF) - 1; // the -1 is as compensation for the time code execution takes
	// Reset the counter
	__HAL_TIM_SET_COUNTER(&us_timer_handle, 0);

	// Wait for the complete overflows
	for (uint32_t i = 0; i < overflows; ++i) {
		while (__HAL_TIM_GET_COUNTER(&us_timer_handle) < 0xFFFE) {
				// Empty loop
		}
		__HAL_TIM_SET_COUNTER(&us_timer_handle, 0);
	}

	// Wait for the remaining ticks
	while (__HAL_TIM_GET_COUNTER(&us_timer_handle) < remainder) {
		// Empty loop
	}
}