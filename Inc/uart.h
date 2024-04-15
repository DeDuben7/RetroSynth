/**
******************************************************************************
* @file           : uart.h
* @brief          : description
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
* All rights reserved.</center></h2>
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

/* Includes -------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

extern void midi_uart_init();
extern void display_uart_init();
extern void midi_uart_enable();
extern void midi_uart_disable();
extern void display_uart_enable();
extern void display_uart_disable();
void display_uart_transmit(const uint8_t *pData, uint16_t Size, uint32_t Timeout);
//void USART1_IRQHandler(void);
//void USART2_IRQHandler(void);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
UART_HandleTypeDef* get_midi_uart_handle(void);
//void USART1_IRQHandler(void);
//void USART2_IRQHandler(void);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */