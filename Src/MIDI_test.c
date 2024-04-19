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

#include <stdint.h>

#include "gpio.h"

uint8_t KEYS[9] = {0,0,0,0,0,0,0,0,0};

int pins[9] = {
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_11,
	GPIO_PIN_12
};

void control_leds(uint8_t key, uint8_t vel) {
  if(vel != 0) { // note on
		for(uint8_t t = 0;t<9;++t) {
			if(KEYS[t] == key) {
				return;
			} else if(KEYS[t] == 0) {
				KEYS[t] = key;
				break;
			}
		}
  } else { // note off
	  for(uint8_t t = 0;t<9;++t) {
			if(KEYS[t] == key) {
	      KEYS[t] = 0;
			}
    }
  }

	int key_count = 0;
	for(uint8_t t = 0;t<9;++t) {
		if(KEYS[t] != 0) {
			key_count += 1;
		}
	}

	for(uint8_t t = 0; t < key_count; ++t) {
    HAL_GPIO_WritePin(GPIOA, pins[t], GPIO_PIN_SET);
	}

	for(uint8_t t = key_count; t < 9; ++t) {
			HAL_GPIO_WritePin(GPIOA, pins[t], GPIO_PIN_RESET);
	}

	return;
}
