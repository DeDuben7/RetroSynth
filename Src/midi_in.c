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
#include <stdbool.h>

#include "midi_in.h"
#include "midi_test.h"
#include "gpio.h"
#include "ym3812_control.h"
#include "global.h"


#define MIDI_BUFFER_SIZE 256
// why volatile can be used here: https://www.embedded.com/introduction-to-the-volatile-keyword/
uint8_t midi_buffer[MIDI_BUFFER_SIZE];
uint16_t midi_buffer_head = 0;
uint16_t midi_buffer_tail = 0;

static void play_note(uint8_t note, uint8_t velocity);
static void stop_note(uint8_t note, uint8_t velocity);
static void change_control(uint8_t midi_channel, uint8_t value);
static void stop_all_notes();

void midi_buffer_add_data(uint8_t data) {
	midi_buffer[midi_buffer_head++] = data; 
	
	if(midi_buffer_head >= MIDI_BUFFER_SIZE) { 
		midi_buffer_head = 0; 
	}
}

static bool is_command_byte(uint8_t byte) {
    return (0xF0 & byte) >> 7;
}

static bool is_common_command_byte(uint8_t byte) {
	return (byte & 0xf0) == 0xf0;
}

void parse_midi_messages_task(void) {
  static uint8_t command_type = 0;
  static uint8_t expected_length = 0;
  static uint8_t current_lenght = 0;
  static uint8_t data[2];

  while(midi_buffer_tail != midi_buffer_head) {
		uint8_t byte = midi_buffer[midi_buffer_tail];
		
		if (is_command_byte(byte) && byte != MIDI_CMD_COMMON_SYSEX_END) { // sysex end is not a start of a message
			if(is_common_command_byte(byte)) {
				
			} else {
				command_type = byte & 0xf0;
				current_lenght = 0;

				switch (command_type) {
					case MIDI_CMD_NOTE_OFF:
					case MIDI_CMD_NOTE_ON:
					case MIDI_CMD_KEY_PRESSURE:
					case MIDI_CMD_CONTROL_CHANGE:
					case MIDI_CMD_PITCH_BEND:
						expected_length = 2;
						break;
						
					case MIDI_CMD_PROGRAM_CHANGE:
					case MIDI_CMD_CHANNEL_PRESSURE:
						expected_length = 1;
						break;
						
					default:
						//don't write the expected lenght
						break;
				}
			}
		} else if (expected_length > 0) {

			data[current_lenght++] = byte;

      if(current_lenght == expected_length) {
        switch(command_type) {
          case MIDI_CMD_NOTE_OFF:
          case MIDI_CMD_NOTE_ON:
            control_leds(data[0], data[1]);
						if(data[1] == 0) {
							stop_note(data[0],data[1]);
						} else {
							play_note(data[0],data[1]);
						}
            break;
          case MIDI_CMD_PITCH_BEND:
            break;
          case MIDI_CMD_CONTROL_CHANGE:
						change_control(data[0],data[1]);
            break;
          default:
            break;
        }

        current_lenght = 0;
				data[0] = 0;
				data[1] = 0;
        // do not reset command type here, so this can be used if messages are received in a sequence
      }
    }
		
		midi_buffer_tail += 1;
		if(midi_buffer_tail >= MIDI_BUFFER_SIZE) {
      midi_buffer_tail = 0;
    }
  }
}

#define NO_NOTE 255
#define MIN_NOTE 24
#define MAX_NOTE 119

uint8_t oplChannel = 0;
uint8_t oplNotes[OPL2_NUM_CHANNELS] = {
	NO_NOTE, NO_NOTE, NO_NOTE,
	NO_NOTE, NO_NOTE, NO_NOTE,
	NO_NOTE, NO_NOTE, NO_NOTE
};

/**
 * Play a note on the next available OPL2 channel.
 */
static void play_note(uint8_t note, uint8_t velocity) {

	// Register which note is playing on which channel.
	oplNotes[oplChannel] = note;

	// Adjust note to valid range and extract octave.
	note = max(MIN_NOTE, min(note, MAX_NOTE));
	uint8_t octave = 1 + (note - 24) / 12;
	note = note % 12;
	playNote(oplChannel, octave, note);

	// Set OPL2 channel for the next note.
	oplChannel = (oplChannel + 1) % OPL2_NUM_CHANNELS;
}


/**
 * Stop playing a note by looking up its OPL2 channel and releasing the key.
 */
static void stop_note(uint8_t note, uint8_t velocity) {
	for (uint8_t i = 0; i < OPL2_NUM_CHANNELS; i ++) {
		if (oplNotes[i] == note) {
			oplNotes[i] = NO_NOTE;
			setKeyOn(i, false);
		}
	}
}


/**
 * Change some of the carrier properties on control changes. Here the control's channel is used to pick the property to
 * change. If it's more convenient to use the actual control numbers from your MIDI controller then use midiData[0] to
 * get the control number.
 */
static void change_control(uint8_t midi_channel, uint8_t value) {
	stop_all_notes();

	for (uint8_t i = 0; i < OPL2_NUM_CHANNELS; i ++) {
		switch (midi_channel) {
			case 0:
				setAttack(i, CARRIER, value);
				break;
			case 1:
				setDecay(i, CARRIER, value);
				break;
			case 2:
				setSustain(i, CARRIER, value);
				break;
			case 3:
				setRelease(i, CARRIER, value);
				break;
			case 4:
				setWaveForm(i, CARRIER, value);
				break;
			case 5:
				setMultiplier(i, CARRIER, value);
				break;
			default:
				break;
		}
	}
}

/**
 * Immediately stop playing notes on all OPL2 channels when a control is changed.
 */
static void stop_all_notes() {
	for (uint8_t i = 0; i < OPL2_NUM_CHANNELS; i ++) {
		setFNumber(i, 0);
		setKeyOn(i, false);
		oplNotes[i] = NO_NOTE;
	}
}