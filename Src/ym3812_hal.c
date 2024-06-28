/**
 ******************************************************************************
 * @file     	ym3812_hal.c
 * @brief    	HAL functions for ym3812
 * @version		v1
 * @author		R. van Renswoude
 * @date		  2024
 ******************************************************************************
 * @details	In this code data will be written to the YM3812's registers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 Ruben van Renswoude.
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 */
/**
 * @addtogroup	YM
 * @{
 */


/* Includes -------------------------------------------------------------------*/

#include "ym3812_hal.h"
#include "gpio.h"
#include "global.h"
#include "us_timer.h"

/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Variables -------------------------------------------------------------------*/

/* Function prototypes ---------------------------------------------------------*/

static void ym_write_byte(uint8_t data);

/* Functions -------------------------------------------------------------------*/

/**
 * @fn		void YM_RESET()
 * @brief 	Function for resetting the YM's.
 * @details The YM's need to get an reset trigger before uploading any code. This function resets and set the reset pin to trigger the YM's.
 */
void ym_hard_reset(void) {
	HAL_GPIO_WritePin(GPIOB, YM_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, YM_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
}

/**
 * @fn		uint8_t YM_WRITE_Databus(uint8_t chip, uint8_t address, uint8_t data)
 * @brief 	Function to time the writing of the addresses and data to the YM3812 chip 1,2,3 and 4.
 * @details In this function data can be send to the 4 different YM3812's. With the parameter 'chip' can be selected
 * 			which chip can be programmed. If the chip is selected, first the address from parameter 'address' will be send to
 * 			the YM3812 using the function YM_WriteBits. Following will the data from the parameter 'data' be send to the YM3812.
 * 			If the parameter chip is out of bound. the error 'NO_CHIP_SELECT' will be returned.
 * @param  	chip_select	Selected chip
 * @param 	address	Chip adress to write to
 * @param 	data	Data to write
 * @return 	iError
 *
 */

uint8_t ym_write_databus(uint16_t chip_select, uint8_t address, uint8_t data) {
	uint8_t iError = 0;
	
	uint16_t chip_select_pins = 0;
	
	if(chip_select & YM_CS_1)
		chip_select_pins |= YM_CS_1_Pin;
	if(chip_select & YM_CS_2)
		chip_select_pins |= YM_CS_2_Pin;
	if(chip_select & YM_CS_3)
		chip_select_pins |= YM_CS_3_Pin;
	if(chip_select & YM_CS_4)
		chip_select_pins |= YM_CS_4_Pin;

	if (chip_select_pins != 0) {
		HAL_GPIO_WritePin(GPIOB,YM_A0_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,YM_WR_Pin|chip_select_pins,GPIO_PIN_RESET);
		ym_write_byte(address);
		HAL_GPIO_WritePin(GPIOB,YM_WR_Pin|chip_select_pins,GPIO_PIN_SET);
		us_delay(4);

		HAL_GPIO_WritePin(GPIOB,YM_A0_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,YM_WR_Pin|chip_select_pins,GPIO_PIN_RESET);
		ym_write_byte(data);
		HAL_GPIO_WritePin(GPIOB,YM_WR_Pin|chip_select_pins,GPIO_PIN_SET);
		us_delay(23);
	} else {
		iError = NO_CHIP_SELECT;
	}
	
	return iError;
}

/**
 * @fn		uint8_t YM_WriteBits(uint8_t data)
 * @brief 	Function for writing bits to the YM3812 chip.
 * @details This program writes data to the YM3812. First the parameter 'data' is compared with 8 bits. If this
 * 			comparison gives a high output then the Data pins D0-D7 are added to the variable 'wridata'. Then the
 * 			variable 'wridata' will be send to the register GPIOB->BSRR.
 * @param 	data	data to be written
 * @var		uint32_t wridata
 * 			XOR the data with the data pin, setting the pin using BSSR
 * @return 	void
 */
static void ym_write_byte(uint8_t data) {
	uint32_t wridata = 0;

	// Determine the pin states based on the data
	wridata |= (data & 0x01) ? YM_D0_Pin : (YM_D0_Pin << 16);
	wridata |= (data & 0x02) ? YM_D1_Pin : (YM_D1_Pin << 16);
	wridata |= (data & 0x04) ? YM_D2_Pin : (YM_D2_Pin << 16);
	wridata |= (data & 0x08) ? YM_D3_Pin : (YM_D3_Pin << 16);
	wridata |= (data & 0x10) ? YM_D4_Pin : (YM_D4_Pin << 16);
	wridata |= (data & 0x20) ? YM_D5_Pin : (YM_D5_Pin << 16);
	wridata |= (data & 0x40) ? YM_D6_Pin : (YM_D6_Pin << 16);
	wridata |= (data & 0x80) ? YM_D7_Pin : (YM_D7_Pin << 16);

	// Write the byte to the databus
	GPIOB->BSRR = wridata;
}