/**
******************************************************************************
* @file           : main.c
* @brief          : main function
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
* All rights reserved.</center></h2>
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#include "main.h"
#include "uart.h"
#include "initialization.h"
#include "gpio.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/

/* Function prototypes ---------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	initialize_synth();
	
  /* Infinite loop */
	while (1)
	{
		// if(midi_cnt != midi_buffer_index)
		// {
		// 	MIDI_PROC(midi_buffer[midi_cnt++]);

		// 	if(midi_cnt > (MIDI_BUFFER_SIZE - 1))
		// 	{
		// 		midi_cnt = 0;
		// 	}

		// 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
		// }

		// else
		// {
		// 	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
		// }

			//ReceiveFlag = 0;
			//UI_Proc(data2);
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
