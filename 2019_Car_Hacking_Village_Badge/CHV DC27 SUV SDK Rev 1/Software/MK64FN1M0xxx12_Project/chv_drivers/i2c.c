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
 * @brief I2C Interface driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/*  SDK Included Files */
#include "board.h"
#include "peripherals.h"
#include "fsl_common.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"

#include "pin_mux.h"
#include "clock_config.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/


/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void i2c_init(void)
{
	NVIC_SetPriority(I2C1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
}

BOOL i2c_read(uint8_t const address, uint32_t const addr, uint8_t const addr_size, uint8_t * const read_buffer, uint32_t const read_size)
{

    i2c_master_transfer_t masterXfer;

    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress   = address;
	masterXfer.direction      = kI2C_Read;
	masterXfer.subaddress     = addr;
	masterXfer.subaddressSize = addr_size;
	masterXfer.data           = read_buffer;
	masterXfer.dataSize       = read_size;
	masterXfer.flags          = kI2C_TransferDefaultFlag;

	return (kStatus_Success == I2C_RTOS_Transfer(&I2C_1_rtosHandle, &masterXfer));
}

BOOL i2c_write(uint8_t const address, uint32_t const addr, uint8_t const addr_size, uint8_t const * const write_buffer, uint32_t const write_size)
{
	i2c_master_transfer_t masterXfer;

	memset(&masterXfer, 0, sizeof(masterXfer));

	masterXfer.slaveAddress   = address;
	masterXfer.direction      = kI2C_Write;
	masterXfer.subaddress     = addr;
	masterXfer.subaddressSize = addr_size;
	masterXfer.data           = write_buffer;
	masterXfer.dataSize       = write_size;
	masterXfer.flags          = kI2C_TransferDefaultFlag;

	return (kStatus_Success == I2C_RTOS_Transfer(&I2C_1_rtosHandle, &masterXfer));

}
