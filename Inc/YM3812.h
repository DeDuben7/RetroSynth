/*
* Filename      : YM3812.c
* Version       : V1.00
* Programmer(s) : van Renswoude
*/

#ifndef YM3812_H_
#define YM3812_H_

#include <stdint.h>



#define NO_CHIP_SELECT 0x01

/**< structure for storing the effect settings of each chip channel */
typedef struct {
	uint8_t Waveform;
	uint8_t AM;
	uint8_t Vibrato;
	uint8_t Pedal_Sustain;
	uint8_t ModFreqMult;
	uint8_t Volume;
	uint8_t Attack;
	uint8_t Decay;
	uint8_t Sustain;
	uint8_t Release;
	uint8_t KSR;
	uint8_t ScalingLevel;
} Operator;

/**< Structure for storing the data of each voice channel */
typedef struct {
	uint8_t Enable;
	uint8_t KEY_Numb;
	uint16_t F_Numb;
	uint8_t Octave;
	uint8_t Velocity;
	uint8_t i_tel;
} pVCH;

/**< structure for storing the effect settings of each operator */
typedef struct {
	uint8_t AM_Depth;
	uint8_t Vib_Depth;
	uint8_t Feedback;
	uint8_t ModulatieMode;

	Operator OP1;
	Operator OP2;
} *pCCH;


extern pCCH CCH[4];		/**< four variables for the effects settings structs of each chip channel */

//Function declarations for the YM3812
uint8_t YM_WRITE_Databus(uint8_t chips, uint8_t adress, uint8_t data);
uint8_t YM_WriteBits(uint8_t data);
uint8_t YM_NOTE_ON(uint8_t VCH_Num);
uint8_t YM_NOTE_OFF(uint8_t KEY_NUMBER, uint8_t VELOCITY);
uint8_t YM_PITCH(uint8_t KeyNumber, uint8_t Velocity, uint8_t YM_PitchValue);
void YM_SET_Def();
void YM_RESET();
void YM_AM(uint8_t channel,uint8_t op,uint8_t value);
void YM_VIB(uint8_t channel,uint8_t op,uint8_t value);
void YM_EG(uint8_t channel,uint8_t op,uint8_t value);
void YM_KSR(uint8_t channel,uint8_t op,uint8_t value);
void YM_MFM(uint8_t channel,uint8_t op,uint8_t value);
void YM_LKS(uint8_t channel,uint8_t op,uint8_t value);
void YM_VOL(uint8_t channel,uint8_t op,uint8_t value);
void YM_ATTACK(uint8_t channel,uint8_t op,uint8_t value);
void YM_DECAY(uint8_t channel,uint8_t op,uint8_t value);
void YM_SUSTAIN(uint8_t channel,uint8_t op,uint8_t value);
void YM_RELEASE(uint8_t channel,uint8_t op,uint8_t value);
void YM_WAV(uint8_t channel,uint8_t op,uint8_t value);
void YM_FEEDBACK(uint8_t channel,uint8_t op,uint8_t value);
void YM_DECAYALG(uint8_t channel,uint8_t op,uint8_t value);
#endif /* YM3812_H_ */
