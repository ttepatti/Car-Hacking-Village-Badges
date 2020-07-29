/******************************************************************************
 * @file
 *
 * Copyright 2019, Specialized Solutions LLC

 * @brief Encoder Driver declarations
 *
 *****************************************************************************/

#ifndef ENCODER_H
#define ENCODER_H

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
typedef enum
{
	ENCODER_UI_DIRECTION_NONE,
	ENCODER_UI_DIRECTION_CW,
	ENCODER_UI_DIRECTION_CCW
} encoder_ui_direction_t;

/******************************************************************************
 * Functions
 *****************************************************************************/
void encoder_init(void);
void encoder_ui_reset(void);
void encoder_motor_reset(void);
encoder_ui_direction_t encoder_ui_get(void);
uint32_t encoder_motor_get(void);

#endif


