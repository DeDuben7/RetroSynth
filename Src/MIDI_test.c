/**
  ******************************************************************************
  *
  * @file			MIDI.c
  * @brief			Filters incoming MIDI messages.
  * @version		V2.0
  * @authors  		van Renswoude
  * @date			25-10-19
  ******************************************************************************
  * @details			This file filters incoming MIDI messages in MIDI functions.
  * 					When filterd it will send the messages to the corresponding function.
  ******************************************************************************
*/

#include "includes.h"

uint8_t i1 = 0;
uint8_t KEYS[9] = {0,0,0,0,0,0,0,0,0};

void control_leds(int data, int stat)
{
  if(stat == 1)
  {
	for(int t = 0;t<9;t++)
	{

	  if(KEYS[t] == data)
	  {
		return;
	  }

	  else if(KEYS[t] == 0)
	  {
		KEYS[t] = data;

		switch(t)
		{
		  case 0:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			break;
		  case 1:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
			break;
		  case 2:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			break;
		  case 3:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
			break;
		  case 4:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
			break;
		  case 5:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
			break;
		  case 6:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
			break;
		  case 7:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
			break;
		  case 8:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
			break;
		  default:
			break;
		}
		return;
	  }
	}
  }

  else if(stat == 0)
  {
	 for(uint8_t t = 0;t<9;t++)
	 {
		if(KEYS[t] == data)
		{
	      KEYS[t] = 0;

	      switch(t)
		  {
			case 0:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			  break;
			case 1:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			  break;
			case 2:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			  break;
			case 3:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
			  break;
			case 4:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
			  break;
			case 5:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
			  break;
			case 6:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
			  break;
			case 7:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
			  break;
			case 8:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
			  break;
			default:
			  break;
		  }

	      return;
		}
      }
  }
}
