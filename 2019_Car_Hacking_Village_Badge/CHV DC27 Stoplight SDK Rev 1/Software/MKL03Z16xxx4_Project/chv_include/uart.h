/******************************************************************************
 * @file
 *
 * Copyright 2019 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * @brief UART module declarations
 *
 *****************************************************************************/

#ifndef UART_H
#define UART_H

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

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void uart_init(void);
void uart_tx(uint8_t const * const buffer, uint32_t const buffer_size);

#endif

