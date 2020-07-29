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
 * @brief BLE UART driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>
#include "fsl_common.h"

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "FreeRTOS.h"

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
uint8_t background_buffer[32];

static uart_rtos_handle_t handle;
struct _uart_handle t_handle;

static uart_rtos_config_t uart_config = {
    .baudrate    = 115200,
    .parity      = kUART_ParityDisabled,
    .stopbits    = kUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void ble_uart_init(void)
{
	uart_config.srcclk = CLOCK_GetFreq(UART0_CLK_SRC);
	uart_config.base   = UART0;

	NVIC_SetPriority(UART0_RX_TX_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
	UART_RTOS_Init(&handle, &t_handle, &uart_config);

}

BOOL ble_uart_rx_message(uint8_t * const message_id, uint8_t * const message_data, uint8_t * const message_data_size)
{
	size_t n = 0;

	UART_RTOS_Receive(&handle, message_data, 2, &n);
	*message_data_size = n;
}

void ble_uart_tx(uint8_t const message_id, uint8_t const * const message_data, uint8_t const message_data_size)
{
	UART_RTOS_Send(&handle, message_data, message_data_size);
}

