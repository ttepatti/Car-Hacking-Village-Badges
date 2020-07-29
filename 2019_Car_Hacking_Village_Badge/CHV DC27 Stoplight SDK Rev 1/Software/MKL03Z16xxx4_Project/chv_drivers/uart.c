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
 * @brief UART driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "fsl_common.h"
#include "fsl_lpuart.h"
#include "fsl_clock.h"

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
void uart_init(void)
{
	lpuart_config_t config;

	/* set to 1MHz MCGIRCLK */
	CLOCK_SetLpuart0Clock(3U);

	/*
	 * config.baudRate_Bps = 115200;
	 * config.parityMode = kLPUART_ParityDisabled;
	 * config.stopBitCount = kLPUART_OneStopBit;
	 * config.txFifoWatermark = 0;
	 * config.rxFifoWatermark = 0;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	LPUART_GetDefaultConfig(&config);
	config.baudRate_Bps = 56000;
	config.enableTx = true;
	config.enableRx = false;

	LPUART_Init(LPUART0, &config, 1000000U);
}

void uart_tx(uint8_t const * const buffer, uint32_t const buffer_size)
{
	LPUART_WriteBlocking(LPUART0, buffer, buffer_size);
}
