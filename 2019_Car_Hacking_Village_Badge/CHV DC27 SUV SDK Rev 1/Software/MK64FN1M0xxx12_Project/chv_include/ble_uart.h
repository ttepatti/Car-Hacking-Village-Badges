/******************************************************************************
 * @file
 *
 * Copyright 2019, Specialized Solutions LLC

 * @brief BLE UART Driver declarations
 *
 *****************************************************************************/

#ifndef BLE_UART_H
#define BLE_UART_H

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
void ble_uart_init(void);
BOOL ble_uart_rx_message(uint8_t * const message_id, uint8_t * const message_data, uint8_t * const message_data_size);
void ble_uart_tx(uint8_t const message_id, uint8_t const * const message_data, uint8_t const message_data_size);

#endif


