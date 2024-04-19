/**
  ******************************************************************************
  *
  * @file			MIDI.h
  * @brief			Defines voor MIDI.C
  * @version		V1.0
  * @author  		van Renswoude
  * @date			25-10-19
  ******************************************************************************
  * @details		This file contains the defines for MIDI.C
  ******************************************************************************
*/

/*
*********************************************************************************************************
 * Libraries
*********************************************************************************************************
*/

#include <stdint.h>

/*
*********************************************************************************************************
 * Defines
*********************************************************************************************************
*/

typedef enum {
  MIDI_CMD_NOTE_OFF               = 0x80,
  MIDI_CMD_NOTE_ON                = 0x90,
  MIDI_CMD_KEY_PRESSURE          	= 0xa0,
  MIDI_CMD_CONTROL_CHANGE         = 0xb0,
  MIDI_CMD_PROGRAM_CHANGE         = 0xc0,
  MIDI_CMD_CHANNEL_PRESSURE       = 0xd0,
  MIDI_CMD_PITCH_BEND             = 0xe0,

  MIDI_CMD_SYSEX           				= 0xf0,
  MIDI_CMD_MTC_QUARTER     				= 0xf1,
  MIDI_CMD_SONG_POSITION   				= 0xf2,
  MIDI_CMD_SONG_SELECT     				= 0xf3,
  MIDI_CMD_TUNE_REQUEST    				= 0xf6,
  MIDI_CMD_SYSEX_END       				= 0xf7,
  MIDI_CMD_CLOCK_TICK      				= 0xf8,
  MIDI_CMD_START_SONG      				= 0xfa,
  MIDI_CMD_CONTINUE_SONG   				= 0xfb,
  MIDI_CMD_STOP_SONG       				= 0xfc,
  MIDI_CMD_ACTIVE_SENSING  				= 0xfe,
  MIDI_CMD_SYSTEM_RESET    				= 0xff,
} command_type_t;

/*
*********************************************************************************************************
 * Functions
*********************************************************************************************************
*/

void midi_buffer_add_data(uint8_t data);

void parse_midi_messages_task(void);
