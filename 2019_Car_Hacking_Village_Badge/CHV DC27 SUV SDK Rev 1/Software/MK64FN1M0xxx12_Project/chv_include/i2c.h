/******************************************************************************
 * @file
 *
 * Copyright 2019, Specialized Solutions LLC

 * @brief I2C declarations
 *
 *****************************************************************************/

#ifndef I2C_H
#define I2C_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
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
void i2c_init(void);

BOOL i2c_read(uint8_t const address, uint32_t const addr, uint8_t const addr_size, uint8_t * const read_buffer, uint32_t const read_size);
BOOL i2c_write(uint8_t const address, uint32_t const addr, uint8_t const addr_size, uint8_t const * const write_buffer, uint32_t const write_size);

#endif


