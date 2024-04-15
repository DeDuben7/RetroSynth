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
/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/
UART_HandleTypeDef midi_uart_handle;
UART_HandleTypeDef display_uart_handle;

volatile uint8_t ReceiveFlag = 0;	/**< flag to indicate whether a uart message is received */
uint8_t data1;					/**< byte for storing the received uart data */
uint8_t data2;


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
  * @details	This function is called by the UART interrupt handler and 
  * 			sets the receive flag. 
  */ 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) { 
	if (huart->Instance == USART1) { 
		if(data1 <= 144) { 
			midi_buffer[midi_buffer_index++] = data1; 
 
			if(midi_buffer_index > (MIDI_BUFFER_SIZE - 1)) { 
				midi_buffer_index = 0; 
			} 
		} 
 
		HAL_UART_Receive_IT(&huart1, &data1, 1); // enable receive under interrupt mode again 
	} 
 
	if (huart->Instance == USART2) { 
		ReceiveFlag = 2;						// set the receiveflag 
		HAL_UART_Receive_IT(&huart2, &data2, 1); // enable receive under interrupt mode again 
	} 
} 

void midi_uart_enable() {
  HAL_UART_Receive_IT(&midi_uart_handle, &data1, 1); // enable the receive under interrupt mode for UART1
}

void midi_uart_disable() {
	HAL_NVIC_DisableIRQ(USART1_IRQn); // USART1 interrupt disable
}

void display_uart_enable() {
  HAL_UART_Receive_IT(&display_uart_handle, &data2, 1); // enable the receive under interrupt mode for UART2
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

//void USART1_IRQHandler(void)
//{
//  HAL_UART_IRQHandler(&midi_uart_handle);
//}


//void USART2_IRQHandler(void)
//{
//  HAL_UART_IRQHandler(&display_uart_handle);
//}

//uint8_t data;
///* This callback is called by the HAL_UART_IRQHandler when the given number of bytes are received */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == USART1) {
//		
//		/* Receive one byte in interrupt mode */ 
//		if(data & 144) {
//			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//		}
//    HAL_UART_Receive_IT(&midi_uart_handle, &data, 1);
//  } else if (huart->Instance == USART2) {
//    /* Transmit one byte with 100 ms timeout */
//    //HAL_UART_Transmit(&huart2, &byte, 1, 100);

//    /* Receive one byte in interrupt mode */ 
//    HAL_UART_Receive_IT(&display_uart_handle, &data, 1);
//  }
//}



static void midi_uart_gpio_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**USART1 GPIO Configuration
	PA9     ------> USART1_TX
	PA10     ------> USART1_RX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


static void display_uart_gpio_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**USART2 GPIO Configuration
	PA2     ------> USART2_TX
	PA3     ------> USART2_RX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void midi_uart_deinit(void) {
	__HAL_RCC_USART1_CLK_DISABLE(); // Peripheral clock disable
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);  // PA9 = USART1_TX, PA10 = USART1_RX
	HAL_NVIC_DisableIRQ(USART1_IRQn); // USART1 interrupt DeInit
}

static void display_uart_deinit(void) {
	__HAL_RCC_USART2_CLK_DISABLE(); // Peripheral clock disable
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3); // PA2 = USART2_TX, PA3 = USART2_RX
	HAL_NVIC_DisableIRQ(USART2_IRQn); // USART2 interrupt DeInit
}