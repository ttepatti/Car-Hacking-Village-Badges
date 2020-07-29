/******************************************************************************
 * @file
 *
 * Copyright 2012-2019 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * @brief Accelerometer module declarations
 *
 *****************************************************************************/

#ifndef ACCEL_H
#define ACCEL_H

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
typedef struct
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t magn_x;
    int16_t magn_y;
    int16_t magn_z;
} accel_data_t;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
BOOL accel_process(accel_data_t * const accel_data, BOOL * const tap_event);
void accel_init(void);

#endif

