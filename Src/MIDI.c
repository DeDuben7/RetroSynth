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
#include "includes.h"

uint8_t i = 0;  			/**< integer for counting incoming bytes.*/
uint8_t DATA[2]; 		/**< Data array for saving incoming data bytes from MIDI messages.*/
char MIDI_FUNC; 		/**< Nibble for storing the function of the MIDI message*/
char MIDI_CHANNEL; 		/**< Nibble for storing the channel of the MIDI message*/

// Some flags for receiving different messages
uint8_t NOTE_ON_FLAG;			/**< value made for flagging note on*/
uint8_t NOTE_OFF_FLAG;			/**< value made for flagging note off*/
uint8_t NOTE_PROG_CHANGE_FLAG;	/**< value made for flagging program change*/
uint8_t NOTE_CONT_CHANGE_FLAG;	/**< value made for flagging control change*/
uint8_t NOTE_PITCH_CHANGE_FLAG;	/**< value made for flagging pitch change */

/**
  * @fn				uint8_t MIDI_PROC(uint8_t MIDI_MSG)
  * @brief 			Function for processing MIDI messages
  * @details 		Checks if incoming message is first or second byte. If first byte, it will check wich function and post a corresponding flag.
  * 		 		If second byte, checks wich flag is posted and sends the data array to corresponding function.
  * @param 			MIDI_MSG is an eight bit integer wich is a byte of the incoming MIDI message
  * @return			iError
  */
uint8_t MIDI_PROC(uint8_t MIDI_MSG)
{
	uint8_t iError = 0;

	if(MIDI_MSG & 128) // Check if this is the first byte of a message
	{
		// Check the function of the message
		if((MIDI_MSG & 0xF0) == 144)
		{
			NOTE_ON_FLAG = 1;
			NOTE_OFF_FLAG = 0;
			NOTE_PROG_CHANGE_FLAG = 0;
			NOTE_CONT_CHANGE_FLAG = 0;
			NOTE_PITCH_CHANGE_FLAG = 0;
		}

		else if((MIDI_MSG & 0xF0) == 128)
		{
			NOTE_ON_FLAG = 0;
			NOTE_OFF_FLAG = 1;
			NOTE_PROG_CHANGE_FLAG = 0;
			NOTE_CONT_CHANGE_FLAG = 0;
			NOTE_PITCH_CHANGE_FLAG = 0;
		}

		else if((MIDI_MSG & 0xF0) == 192)
		{
			NOTE_ON_FLAG = 0;
			NOTE_OFF_FLAG = 0;
			NOTE_PROG_CHANGE_FLAG = 1;
			NOTE_CONT_CHANGE_FLAG = 0;
			NOTE_PITCH_CHANGE_FLAG = 0;
		}

		else if((MIDI_MSG & 0xF0) == 176)
		{
			NOTE_ON_FLAG = 0;
			NOTE_OFF_FLAG = 0;
			NOTE_PROG_CHANGE_FLAG = 0;
			NOTE_CONT_CHANGE_FLAG = 1;
			NOTE_PITCH_CHANGE_FLAG = 0;
		}

		else if((MIDI_MSG & 0xF0) == 224)
		{
			NOTE_ON_FLAG = 0;
			NOTE_OFF_FLAG = 0;
			NOTE_PROG_CHANGE_FLAG = 0;
			NOTE_CONT_CHANGE_FLAG = 0;
			NOTE_PITCH_CHANGE_FLAG = 1;
		}
	}

	else // If the received byte isn't the first byte of a message, process the byte
	{
		if(NOTE_ON_FLAG == 1) 		// If the message was Note On
		{

			iError = 0;
			DATA[i++] = MIDI_MSG; 	// Store the data

			if(i==2)				// If the last byte is received
			{
				if(DATA[1] == 0) // note off
				{
					control_leds(DATA[0], 0);
					YM_NOTE_OFF(DATA[0],DATA[1]); // Call the Note Off function
				}


				else // note on
				{
					control_leds(DATA[0], 1); //For debugging purposes, should be removed.
					YM_PITCH(DATA[0],DATA[1],0); // Call the Note on function
				}


				// Reset the variables
				i = 0;
				DATA[0] = 0;
				DATA[1] = 0;
			}
			return iError;
		}

		else if(NOTE_OFF_FLAG == 1)	// If the message was Note Off
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;	// Store the data

			if(i==2)				// If the last byte is received
			{
				YM_NOTE_OFF(DATA[0],DATA[1]); // Call the Note Off function

				// Reset the variables
				i = 0;
				DATA[0] = 0;
				DATA[1] = 0;
			}
			return iError;
		}

		else if(NOTE_PROG_CHANGE_FLAG == 1) // If the message was Program change
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;			// Store the data

			if(i==2)						// If the last byte is received
			{
//				NOTE_PROG_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],0); // Call the PROG_CHANGE function
				// Reset the variables
				i = 0;
				DATA[0] = 0;
				DATA[1] = 0;
			}
			return iError;
		}

		else if(NOTE_CONT_CHANGE_FLAG == 1) // If the message was Control change
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;			// Store the data

			if(i==2)						// If the last byte is received
			{
//				NOTE_CONT_CHANGE(MIDI_CHANNEL,FUNC_VAR[0],0); // Call the CONT_CHANGE function
				// Reset the variables
				i = 0;
				DATA[0] = 0;
				DATA[1] = 0;
			}
			return iError;
		}

		else if(NOTE_PITCH_CHANGE_FLAG == 1) // If the message was Control change
		{
			iError = 0;
			DATA[i++] = MIDI_MSG;			// Store the data

			if(i==2)						// If the last byte is received
			{
				YM_PITCH(0,0, DATA[1]); // Call the PICTH function

				// Reset the variables
				i = 0;
				DATA[0] = 0;
				DATA[1] = 0;
			}
			return iError;
		}
	}
	return iError;
}
/**
 * @}
 */
