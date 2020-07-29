/******************************************************************************
 * @file
 *
 * Copyright 2019, Specialized Solutions LLC

 * @brief LED Driver declarations
 *
 *****************************************************************************/

#ifndef LED_H
#define LED_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "datatypes.h"
#include <stdio.h>
#include "fsl_common.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/

/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void led_init( void );
uint8_t *led_get_framebuffer_address(void);
void led_set_driver_headlight(BOOL const state);
void led_set_passenger_headlight(BOOL const state);
void led_set_reverse_lights(BOOL const state);
void led_all_off(void);
void led_set_led(uint8_t const x, uint8_t const y, uint8_t const red, uint8_t const blue, uint8_t const green);

#endif


