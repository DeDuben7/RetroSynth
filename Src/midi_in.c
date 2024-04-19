/**
  ******************************************************************************
  *
  * @file			MIDI.c
  * @brief			Filters incoming MIDI messages.
  * @version		V2.0
  * @author  		van Renswoude
  * @date			25-10-19
  ******************************************************************************
  * @details			This file filters incoming MIDI messages in MIDI functions.
  * 					When filterd it will send the messages to the corresponding function.
  ******************************************************************************
*/


/**
 * @addtogroup MIDI
 * @{
 */

#include <stdint.h>

#include "midi_in.h"
#include "midi_test.h"
#include "gpio.h"
#include <stdbool.h>

#define MIDI_BUFFER_SIZE 256
// why volatile can be used here: https://www.embedded.com/introduction-to-the-volatile-keyword/
uint8_t midi_buffer[MIDI_BUFFER_SIZE];
uint16_t midi_buffer_head = 0;
uint16_t midi_buffer_tail = 0;


void midi_buffer_add_data(uint8_t data) {
	midi_buffer[midi_buffer_head++] = data; 

	if(midi_buffer_head >= MIDI_BUFFER_SIZE) { 
		midi_buffer_head = 0; 
	}
}

static bool is_command_byte(uint8_t byte) {
    return (0xF0 & byte) >> 7;
}

void parse_midi_messages_task(void) {
  static uint8_t command_type = 0;
  static uint8_t expected_length = 0;
  static uint8_t current_lenght = 0;
  static uint8_t data[2];

  while(midi_buffer_tail != midi_buffer_head) {
		uint8_t byte = midi_buffer[midi_buffer_tail++];;
		
    if(midi_buffer_tail >= MIDI_BUFFER_SIZE) {
      midi_buffer_tail = 0;
    }
		
		if (is_command_byte(byte) && byte != MIDI_CMD_SYSEX_END) {
			command_type = byte & 0xf0;

      switch (command_type) {
        case MIDI_CMD_NOTE_OFF:
        case MIDI_CMD_NOTE_ON:
        case MIDI_CMD_KEY_PRESSURE:
        case MIDI_CMD_CONTROL_CHANGE:
        case MIDI_CMD_PITCH_BEND:
        case MIDI_CMD_MTC_QUARTER:
          expected_length = 2;
          break;
          
        case MIDI_CMD_PROGRAM_CHANGE:
        case MIDI_CMD_CHANNEL_PRESSURE:
        case MIDI_CMD_SONG_POSITION:
          expected_length = 1;
          break;
          
        default:
          expected_length = 0;
          break;
      }
		} else if (expected_length > 0) {
			if(current_lenght != expected_length) {
        data[current_lenght++] = byte;
      }

      if(current_lenght == expected_length) {
        switch(command_type) {
          case MIDI_CMD_NOTE_OFF:
          case MIDI_CMD_NOTE_ON:
            //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            control_leds(data[0], data[1]);
            break;
          case MIDI_CMD_PITCH_BEND:
            break;
          case MIDI_CMD_CONTROL_CHANGE:
            break;
          default:
            break;
        }

        current_lenght = 0;
        expected_length = 0;
        // do not reset command type here, so this can be used if messages are received in a sequence
      }
    }
  }
}
