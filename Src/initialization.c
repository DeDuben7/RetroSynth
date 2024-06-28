/**
******************************************************************************
* @file           : initialization.c
* @brief          : all functions for initializing the syntmodule
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
#include "uart.h"
#include "system_clock.h"
#include "ym3812_control.h"
#include "us_timer.h"
#include "stm32f1xx.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

void initialize_synth() {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
	
  /* Configure the system clock */
  system_clock_config();
	
	//__HAL_AFIO_REMAP_SWJ_DISABLE(); // necessary to enable PB3 and PB4, respectively YM_D2 and YM_D3
	__HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* Initialize all configured peripherals */
  init_gpio();
	
	us_timer_init();
	
  midi_uart_init();
  display_uart_init();
  midi_uart_enable(); //enable receive under interrupt
  display_uart_enable(); //enable receive under interrupt

	ym_init();

	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

