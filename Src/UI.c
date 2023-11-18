/**
 ******************************************************************************
 * @file		UI.c
 * @brief       Program using YM3812
 * @version		V 3.0
 * @author		van Renswoude
 * @date		6-1-2020
 ******************************************************************************
 * @details		In this code the data from the touchscreen display is processed and the correct registers
 * 				of the YM3812 are written.
 ******************************************************************************
 */
/**
 * @addtogroup	YM
 * @{
 */

#include "includes.h"

uint8_t buf[2];
uint8_t wait = 0;

void UI_Proc(uint8_t data)
{
    if(wait == 0)
    {
        if(data&128)
        {
            wait = 1;
            buf[0] = data;
        }
    }

    else if(wait == 1)
    {
        if(data&128)
        {
            buf[0] = 0;
            return;
        }

        else
        {
            buf[1] = data;
            wait = 0;
            uint8_t effect  = (buf[0] & 120)>>3;
            uint8_t channel = (buf[0] & 6)>>1;
            uint8_t op      =  buf[0] & 1;
            uint8_t value   =  buf[1];
            switch(effect)
            {
                case 0: //AM
                	YM_AM(channel,op,value);
                    break;
                case 1: //VIB
                    YM_VIB(channel,op,value);
                    break;
                case 2: //EG
                    YM_EG(channel,op,value);
                    break;
                case 3: //KSR
                    YM_KSR(channel,op,value);
                    break;
                case 4: //MFM
                    YM_MFM(channel,op,value);
                    break;
                case 5: //LKS
                    YM_LKS(channel,op,value);
                    break;
                case 6: //VOL
                    YM_VOL(channel,op,value);
                    break;
                case 7: //Attack
                    YM_ATTACK(channel,op,value);
                    break;
                case 8: //Decay
                    YM_DECAY(channel,op,value);
                    break;
                case 9: //Sustain
                    YM_SUSTAIN(channel,op,value);
                    break;
                case 10: //Release
                    YM_RELEASE(channel,op,value);
                    break;
                case 11: //WAV
                    YM_WAV(channel,op,value);
                    break;
                case 12: //Feedback
                    YM_FEEDBACK(channel,op,value);
                    break;
                case 13: //Decay alg
                    YM_DECAYALG(channel,op,value);
                    break;
                case 14: //nd
                    break;
                case 15: //nd
                    break;
                default: //default
                    break;
            }
        }
    }
}


