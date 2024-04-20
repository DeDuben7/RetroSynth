/**
******************************************************************************
* @file           : uart.c
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
#include "uart.h"
#include "main.h"
#include "midi_in.h"
/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/
UART_HandleTypeDef midi_uart_handle;
UART_HandleTypeDef display_uart_handle;

uint8_t midi_uart_receive_byte;					/**< byte for storing the received uart data */
uint8_t display_uart_receive_byte;


/* Function prototypes ---------------------------------------------------------*/
static void midi_uart_gpio_init(void);
static void display_uart_gpio_init(void);
static void midi_uart_deinit(void);
static void display_uart_deinit(void);

/* Functions -------------------------------------------------------------------*/

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void midi_uart_init()
{
	__USART1_CLK_ENABLE();
	
  midi_uart_handle.Instance = USART1;
  midi_uart_handle.Init.BaudRate = 31250;
  midi_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
  midi_uart_handle.Init.StopBits = UART_STOPBITS_1;
  midi_uart_handle.Init.Parity = UART_PARITY_NONE;
  midi_uart_handle.Init.Mode = UART_MODE_RX;
  midi_uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  midi_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&midi_uart_handle) != HAL_OK)
  {
    //Error_Handler();
  }
	
	/* USART1 interrupt Init */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void display_uart_init()
{
	__USART2_CLK_ENABLE();
	
  display_uart_handle.Instance = USART2;
  display_uart_handle.Init.BaudRate = 9600;
  display_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
  display_uart_handle.Init.StopBits = UART_STOPBITS_1;
  display_uart_handle.Init.Parity = UART_PARITY_NONE;
  display_uart_handle.Init.Mode = UART_MODE_TX_RX;
  display_uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  display_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&display_uart_handle) != HAL_OK)
  {
    //Error_Handler();
  }
	
	/* USART2 interrupt Init */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

/** 
  * @fn			void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
  * @brief		UART callback function. 
  * @details	This function is called by the UART interrupt handler and buffers the received data
  */ 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) { 
	if (huart->Instance == USART1) { 
		midi_buffer_add_data(midi_uart_receive_byte);
		HAL_UART_Receive_IT(&midi_uart_handle, &midi_uart_receive_byte, 1); // enable receive under interrupt mode again 
	} 
 
	if (huart->Instance == USART2) { 
		// buffer ui data
		HAL_UART_Receive_IT(&display_uart_handle, &display_uart_receive_byte, 1); // enable receive under interrupt mode again 
	} 
} 

void midi_uart_enable() {
  HAL_UART_Receive_IT(&midi_uart_handle, &midi_uart_receive_byte, 1); // enable the receive under interrupt mode for UART1
}

void midi_uart_disable() {
	HAL_NVIC_DisableIRQ(USART1_IRQn); // USART1 interrupt disable
}

void display_uart_enable() {
  HAL_UART_Receive_IT(&display_uart_handle, &display_uart_receive_byte, 1); // enable the receive under interrupt mode for UART2
}

void display_uart_disable() {
	HAL_NVIC_DisableIRQ(USART2_IRQn); // USART2 interrupt disable
}

void display_uart_transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout) {
  HAL_UART_Transmit(&display_uart_handle, pData, Size, Timeout);
}

UART_HandleTypeDef* get_midi_uart_handle(void) {
	return &midi_uart_handle;
}	

// static void midi_uart_gpio_init(void) {
// 	GPIO_InitTypeDef GPIO_InitStruct = {0};

// 	__HAL_RCC_GPIOA_CLK_ENABLE();

// 	GPIO_InitStruct.Pin = GPIO_PIN_9; // PA9 ------> USART1_TX
// 	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
// 	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// 	GPIO_InitStruct.Pin = GPIO_PIN_10; // PA10 ------> USART1_RX
// 	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
// }


// static void display_uart_gpio_init(void) {
// 	GPIO_InitTypeDef GPIO_InitStruct = {0};

// 	__HAL_RCC_GPIOA_CLK_ENABLE();

// 	GPIO_InitStruct.Pin = GPIO_PIN_2; // PA2 ------> USART2_TX
// 	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
// 	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// 	GPIO_InitStruct.Pin = GPIO_PIN_3; // PA3 ------> USART2_RX
// 	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
// }

// static void midi_uart_deinit(void) {
// 	__HAL_RCC_USART1_CLK_DISABLE(); // Peripheral clock disable
// 	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);  // PA9 = USART1_TX, PA10 = USART1_RX
// 	HAL_NVIC_DisableIRQ(USART1_IRQn); // USART1 interrupt DeInit
// }

// static void display_uart_deinit(void) {
// 	__HAL_RCC_USART2_CLK_DISABLE(); // Peripheral clock disable
// 	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3); // PA2 = USART2_TX, PA3 = USART2_RX
// 	HAL_NVIC_DisableIRQ(USART2_IRQn); // USART2 interrupt DeInit
// }