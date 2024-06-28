/**
******************************************************************************
* @file           : ym3812_hal.h
* @brief          : Functions for writing data to the ym3812 chip over the 8 bit databus. Later on
* 									Functions for reading data will be added as well #TODO
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
* All rights reserved.</center></h2>
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __YM3812_HAL_H
#define __YM3812_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/

#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

#define NO_CHIP_SELECT 0x00
#define YM_CS_1 0x01
#define YM_CS_2 0x02
#define YM_CS_3 0x04
#define YM_CS_4 0x08

/* Typedefs -------------------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

void ym_hard_reset(void);
uint8_t ym_write_databus(uint16_t chips, uint8_t adress, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* __YM3812_HAL_H */