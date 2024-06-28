/**
******************************************************************************
* @file           : name.h
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
#ifndef __GLOBAL_H
#define __GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#define FALSE 0
#define TRUE 1

#define ON 	1

#define OFF 0
/* Typedefs -------------------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/

#include <stdint.h>

// Function to find the maximum of two uint8_t numbers
static uint8_t max(uint8_t a, uint8_t b) {
    return (a > b) ? a : b;
}

// Function to find the minimum of two uint8_t numbers
static uint8_t min(uint8_t a, uint8_t b) {
    return (a < b) ? a : b;
}

#ifdef __cplusplus
}
#endif

#endif /* __GLOBAL_H */