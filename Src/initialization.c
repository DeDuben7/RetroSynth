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
#include "YM3812.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/
uint8_t pageinit[9] = {112,97,103,101,32,49,255,255,255};

/* Functions -------------------------------------------------------------------*/

void initialize_synth() {
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  system_clock_config();

  /* Initialize all configured peripherals */
  init_gpio();
	
  midi_uart_init();
  display_uart_init();

  for(int i = 0;i<9;i++)
  {
    display_uart_transmit(pageinit, sizeof(pageinit), HAL_MAX_DELAY);
  }

  midi_uart_enable(); //enable receive under interrupt
  display_uart_enable(); //enable receive under interrupt

	// Setting YM_CS pins+ WR, AO and RST
	HAL_GPIO_WritePin(GPIOB,YM_CS_1_Pin|YM_CS_2_Pin|YM_CS_3_Pin|YM_CS_4_Pin|YM_WR_Pin|YM_RST_Pin|YM_A0_Pin,GPIO_PIN_SET);

	YM_RESET();  // reset the YM3812 chips

	YM_SET_Def(); // set the default settings for the YM3812 chips


	int pitch = 0;
	for(pitch=70;pitch<74;pitch++) {
		YM_PITCH(pitch, 127,0);
		HAL_Delay(500);
		YM_NOTE_OFF(pitch,127);
	}

  YM_NOTE_OFF(pitch,255);

	HAL_Delay(1000);

	YM_NOTE_OFF(50, 255);
	YM_NOTE_OFF(51, 255);
	YM_NOTE_OFF(52, 255);

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
}

