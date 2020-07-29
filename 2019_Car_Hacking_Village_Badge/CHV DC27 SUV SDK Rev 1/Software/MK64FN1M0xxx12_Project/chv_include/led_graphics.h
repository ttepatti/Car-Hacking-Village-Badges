/******************************************************************************
 * @file
 *
 * Copyright 2019, Specialized Solutions LLC

 * @brief LED Graphics declarations
 *
 *****************************************************************************/

#ifndef LED_GRAPHICS_H
#define LED_GRAPHICS_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "datatypes.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/

/******************************************************************************
 * Typedefs
 *****************************************************************************/
typedef enum
{
	LED_GRAPHICS_PATTERN_RACER = 0,
	LED_GRAPHICS_PATTERN_BLING,
	LED_GRAPHICS_PATTERN_FADE,
	LED_GRAPHICS_PATTERN_POLICE,
	LED_GRAPHICS_PATTERN_FIRE,
	LED_GRAPHICS_PATTERN_EOL,
	LED_GRAPHICS_PATTERN_COUNT
} led_graphics_pattern_t;

/******************************************************************************
 * Functions
 *****************************************************************************/
void led_graphics_init(void);
void led_graphics_set_pattern(led_graphics_pattern_t const pattern);

#endif


