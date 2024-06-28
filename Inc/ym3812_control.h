/**
******************************************************************************
* @file           : ym3812_control.h
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
#ifndef __YM3812_CONTROL_H
#define __YM3812_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/* Defines -------------------------------------------------------------------*/

// Generic OPL2 definitions.
#define OPL2_NUM_CHANNELS 9
#define CHANNELS_PER_BANK 9

// Operator definitions.
#define OPERATOR1 0
#define OPERATOR2 1
#define MODULATOR 0
#define CARRIER   1

// Synthesis type definitions.
#define SYNTH_MODE_FM 0
#define SYNTH_MODE_AM 1

// Drum sounds.
#define DRUM_BASS   0
#define DRUM_SNARE  1
#define DRUM_TOM    2
#define DRUM_CYMBAL 3
#define DRUM_HI_HAT 4

// Drum sound bit masks.
#define DRUM_BITS_BASS   0x10
#define DRUM_BITS_SNARE  0x08
#define DRUM_BITS_TOM    0x04
#define DRUM_BITS_CYMBAL 0x02
#define DRUM_BITS_HI_HAT 0x01

// Note to frequency mapping.
#define NOTE_C   0
#define NOTE_CS  1
#define NOTE_D   2
#define NOTE_DS  3
#define NOTE_E   4
#define NOTE_F   5
#define NOTE_FS  6
#define NOTE_G   7
#define NOTE_GS  8
#define NOTE_A   9
#define NOTE_AS 10
#define NOTE_B  11

// Tune specific declarations.
#define NUM_OCTAVES      7
#define NUM_NOTES       12
#define NUM_DRUM_SOUNDS  5

#define INSTRUMENT_DATA_PROGMEM true
#define INSTRUMENT_DATA_SRAM false

/* Typedefs -------------------------------------------------------------------*/

typedef struct {
	bool hasTremolo;
	bool hasVibrato;
	bool hasSustain;
	bool hasEnvelopeScaling;
	uint8_t frequencyMultiplier;
	uint8_t keyScaleLevel;
	uint8_t outputLevel;
	uint8_t attack;
	uint8_t decay;
	uint8_t sustain;
	uint8_t release;
	uint8_t waveForm;
} operator_t;


typedef struct {
	operator_t operators[2];
	uint8_t feedback;
	bool isAdditiveSynth;
	uint8_t transpose;
} instrument_t;

/* Functions -------------------------------------------------------------------*/

void ym_init();
void ym_reset();
void createShadowRegisters();

uint8_t getChipRegister(uint16_t reg);
uint8_t getChannelRegister(uint8_t baseRegister, uint8_t channel);
uint8_t getOperatorRegister(uint8_t baseRegister, uint8_t channel, uint8_t op);
uint8_t getRegisterOffset(uint8_t channel, uint8_t operatorNum);
void setChipRegister(uint16_t reg, uint8_t value);
void setChannelRegister(uint8_t baseRegister, uint8_t channel, uint8_t value);
void setOperatorRegister(uint8_t baseRegister, uint8_t channel, uint8_t op, uint8_t value);
uint8_t getChipRegisterOffset(uint16_t reg);
uint8_t getChannelRegisterOffset(uint8_t baseRegister, uint8_t channel);
uint16_t getOperatorRegisterOffset(uint8_t baseRegister, uint8_t channel, uint8_t operatorNum);
void write(uint8_t reg, uint8_t data);


float getFrequency(uint8_t channel);
void setFrequency(uint8_t channel, float frequency);
uint8_t getFrequencyBlock(float frequency);
uint16_t getFrequencyFNumber(uint8_t channel, float frequency);
uint16_t getNoteFNumber(uint8_t note);
float getFrequencyStep(uint8_t channel);
void playNote(uint8_t channel, uint8_t octave, uint8_t note);
void playDrum(uint8_t drum, uint8_t octave, uint8_t note);

instrument_t createInstrument();
instrument_t loadInstrument(const unsigned char *instrument, bool fromProgmem);
instrument_t getInstrument(uint8_t channel);
void setInstrument(uint8_t channel, instrument_t instrument, float volume);
void setDrumInstrument(instrument_t instrument, uint8_t drumType, float volume);

bool getWaveFormSelect();
bool getTremolo(uint8_t channel, uint8_t operatorNum);
bool getVibrato(uint8_t channel, uint8_t operatorNum);
bool getMaintainSustain(uint8_t channel, uint8_t operatorNum);
bool getEnvelopeScaling(uint8_t channel, uint8_t operatorNum);
uint8_t getMultiplier(uint8_t channel, uint8_t operatorNum);
uint8_t getScalingLevel(uint8_t channel, uint8_t operatorNum);
uint8_t getVolume(uint8_t channel, uint8_t operatorNum);
uint8_t getChannelVolume(uint8_t channel);
uint8_t getAttack(uint8_t channel, uint8_t operatorNum);
uint8_t getDecay(uint8_t channel, uint8_t operatorNum);
uint8_t getSustain(uint8_t channel, uint8_t operatorNum);
uint8_t getRelease(uint8_t channel, uint8_t operatorNum);
uint16_t getFNumber(uint8_t channel);
uint8_t getBlock(uint8_t channel);
bool getNoteSelect();
bool getKeyOn(uint8_t channel);
uint8_t getFeedback(uint8_t channel);
uint8_t getSynthMode(uint8_t channel);
bool getDeepTremolo();
bool getDeepVibrato();
bool getPercussion();
uint8_t getDrums();
uint8_t getWaveForm(uint8_t channel, uint8_t operatorNum);

void setWaveFormSelect(bool enable);
void setTremolo(uint8_t channel, uint8_t operatorNum, bool enable);
void setVibrato(uint8_t channel, uint8_t operatorNum, bool enable);
void setMaintainSustain(uint8_t channel, uint8_t operatorNum, bool enable);
void setEnvelopeScaling(uint8_t channel, uint8_t operatorNum, bool enable);
void setMultiplier(uint8_t channel, uint8_t operatorNum, uint8_t multiplier);
void setScalingLevel(uint8_t channel, uint8_t operatorNum, uint8_t scaling);
void setVolume(uint8_t channel, uint8_t operatorNum, uint8_t volume);
void setChannelVolume(uint8_t channel, uint8_t volume);
void setAttack(uint8_t channel, uint8_t operatorNum, uint8_t attack);
void setDecay(uint8_t channel, uint8_t operatorNum, uint8_t decay);
void setSustain(uint8_t channel, uint8_t operatorNum, uint8_t sustain);
void setRelease(uint8_t channel, uint8_t operatorNum, uint8_t release);
void setFNumber(uint8_t channel, uint16_t fNumber);
void setBlock(uint8_t channel, uint8_t block);
void setNoteSelect(bool enable);
void setKeyOn(uint8_t channel, bool keyOn);
void setFeedback(uint8_t channel, uint8_t feedback);
void setSynthMode(uint8_t channel, uint8_t synthMode);
void setDeepTremolo(bool enable);
void setDeepVibrato(bool enable);
void setPercussion(bool enable);
void setDrumsByte(uint8_t drums);
void setDrumsBool(bool bass, bool snare, bool tom, bool cymbal, bool hihat);
void setWaveForm(uint8_t channel, uint8_t operatorNum, uint8_t waveForm);

float clamp_float_value(float value, float min, float max);
uint8_t clamp_uint8_value(uint8_t value, uint8_t min, uint8_t max);
uint16_t clamp_uint16_value(uint16_t value, uint16_t min, uint16_t max);

// create shadow registers
extern uint8_t chipRegisters[3];
extern uint8_t channelRegisters[3 * OPL2_NUM_CHANNELS];	// 27
extern uint8_t operatorRegisters[10 * OPL2_NUM_CHANNELS];	// 90

extern const float fIntervals[8];
extern const unsigned int noteFNumbers[12];
extern const float blockFrequencies[8];
extern const uint8_t registerOffsets[2][9];
extern const uint8_t drumRegisterOffsets[2][5];
extern const uint8_t drumChannels[5];
extern const uint8_t drumBits[5];

#ifdef __cplusplus
}
#endif

#endif /* __YM3812_CONTROL_H */