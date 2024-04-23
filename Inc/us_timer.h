/**
******************************************************************************
* @file           : us_timer.h
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
#ifndef __US_TIMER_H
#define __US_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include <stdint.h>
/* Defines -------------------------------------------------------------------*/

/* Typedefs -------------------------------------------------------------------*/

/* Functions -------------------------------------------------------------------*/
void us_timer_init(void);
void us_delay(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __US_TIMER_H */