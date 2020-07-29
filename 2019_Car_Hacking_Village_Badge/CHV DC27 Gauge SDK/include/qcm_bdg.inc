/******************************************************************************
 * Copyright 2014-2015 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * @brief QCM Native Functions for Badge
 *
 *****************************************************************************/
#pragma library QCM_BDG

/*****************************************************************************
 * Data structure definitions 
 ****************************************************************************/
#define QCM_CAN_MSG[.id, bool:.is_extended, .dlc, .data[8]]

/*****************************************************************************
 * Tags (types) for use in calling the handlers 
 *****************************************************************************/
const GPIO_IN:GPIO_INPUT_SWITCH_RIGHT = 0
const GPIO_IN:GPIO_INPUT_SWITCH_LEFT = 1
const GPIO_IN:GPIO_INPUT_USB_POWER = 2

const GPIO_OUT:GPIO_OUTPUT_0 = 0
const GPIO_OUT:GPIO_OUTPUT_1 = 1
const GPIO_OUT:GPIO_OUTPUT_2 = 2
const GPIO_OUT:GPIO_OUTPUT_3 = 3

const GPIO_EVENT:GPIO_EVENT_NONE = 0
const GPIO_EVENT:GPIO_EVENT_LOW = 1
const GPIO_EVENT:GPIO_EVENT_HIGH = 2
const GPIO_EVENT:GPIO_EVENT_ALL = 3

const TIMER:TIMER_0 = 0
const TIMER:TIMER_1 = 1
const TIMER:TIMER_2 = 2
const TIMER:TIMER_3 = 3
const TIMER:TIMER_4 = 4
const TIMER:TIMER_5 = 5
const TIMER:TIMER_6 = 6
const TIMER:TIMER_7 = 7
const TIMER:TIMER_8 = 8
const TIMER:TIMER_9 = 9

/* CAN channel tags  */
const CAN_CHANNEL:CAN0 = 0 
const CAN_CHANNEL:CAN1 = 1

const CAN_RX_HANDLER:CAN_RX_HANDLER_0 = 0
const CAN_RX_HANDLER:CAN_RX_HANDLER_1 = 1
const CAN_RX_HANDLER:CAN_RX_HANDLER_2 = 2
const CAN_RX_HANDLER:CAN_RX_HANDLER_3 = 3
const CAN_RX_HANDLER:CAN_RX_HANDLER_4 = 4
const CAN_RX_HANDLER:CAN_RX_HANDLER_5 = 5
const CAN_RX_HANDLER:CAN_RX_HANDLER_6 = 6
const CAN_RX_HANDLER:CAN_RX_HANDLER_7 = 7

/* CAN gateway mode tags */
const CAN_GWY_MODE:CAN_GWY_MODE_PASS = 0
const CAN_GWY_MODE:CAN_GWY_MODE_NO_PASS = 1

/********************************************************************************
 * System Native Routines 
 *******************************************************************************/

 /* returns number of milliseconds since system start */ 
native qcm_get_system_time() = -47

/********************************************************************************
 * Timer Routines
 *******************************************************************************/

/* 
 * Start a timer that will invoke associated event handler at expiration.  
 *
 * Arguments: 
 * timer_number : timer to start, must be of type TIMER (see above, for example TIMER_0)
 * timeout_ms : duration/period of timer, in milliseconds 
 * auto_reload : if true, then restart timer immediately on expiration, if false, do not restart timer on expiration
 *
 * Returns true if timer was started, false otherwise
 */
native bool:qcm_timer_start(TIMER:timer_number, timeout_ms, bool:auto_reload) = -48

/* 
 * Stop a previously started timer.
 *
 * Arguments: 
 * timer_number : timer to stop, must be of type TIMER (see above, for example TIMER_0)
 *
 * Returns true if timer was stopped, false otherwise
 */
native bool:qcm_timer_stop(TIMER:timer_number) = -49

/* 
 * Check to see if a timer is expired.
 *
 * Arguments: 
 * timer_number : timer to check, must be of type TIMER (see above, for example TIMER_0)
 *
 * Returns true if timer is expired, false if timer not expired, not started, or is set to auto_reload
 */
native bool:qcm_timer_expired(TIMER:timer_number) = -50

/********************************************************************************
 * CAN Routines
 *******************************************************************************/

/* 
 * Initialize CAN to the desired baud rate. 
 *
 * Arguments:
 * channel : specifies the CAN channel to initialize, must be of type CAN_CHANNEL (see above, for example CAN0)
 * speed : Bit rate of CAN - can be 33333, 125000, 250000, 500000, or 1000000
 */
native qcm_can_init(CAN_CHANNEL:channel, speed) = -51

/*
 * Configures RX handler for specified ID
 *
 * Arguments:
 * channel : specifies the CAN channel to initialize, must be of type CAN_CHANNEL (see above, for example CAN0)
 * handler : specifies handler number for id, must be of type CAN_RX_HANDLER (see above, for example CAN_RX_HANDLER_0)
 * can_id : specifies ID of CAN message to invoke specified event handler upon reception. For example 0x7E8
 * is_extended : if true, can_id is a 29-bit identifier, if false it is an 11-bit identifier
 *
 * When specified message is received, then the associated event handler of the form @can_rx<n> will be invoked
 */
native qcm_can_configure_rx_handler(CAN_CHANNEL:channel, CAN_RX_HANDLER:handler, can_id, bool:is_extended) = -52

/* 
 * Transmit a CAN message
 *
 * Arguments:
 * channel : specifies the CAN channel to initialize, must be of type CAN_CHANNEL (see above, for example CAN0)
 * tx_msg : structure containing message to send.  See QCM_CAN_MSG above.
 */
native qcm_can_tx(CAN_CHANNEL:channel, tx_msg[QCM_CAN_MSG]) = -53

/* 
 * Sets the CAN channel gateway mode
 *
 * Arguments:
 * channel : specifies the CAN channel to initialize, must be of type CAN_CHANNEL (see above, for example CAN0)
 * mode : specifies the mode of the CAN gateway, must be of type CAN_GWY_MODE (see above, for example CAN_GWY_MODE_PASS)
 */
native qcm_can_gw_mode(CAN_CHANNEL:channel_a, CAN_CHANNEL:channel_b, CAN_GWY_MODE:mode) = -54

/********************************************************************************
 * GPIO Routines
 *******************************************************************************/

/*
 * Get the state of an input.
 *
 * Arguments:
 * channel : channel to get, must be of type GPIO_IN.  For example, GPIO_INPUT_0
 *
 * Returns true if input level is logic high, false otherwise
 */
native bool:qcm_gpio_get_input(GPIO_IN:channel) = -55

/* 
 * Registers event handler on an input
 *
 * Arguments:
 * channel : channel to monitor, must be of type GPIO_IN.  For example, GPIO_INPUT_0
 * event : input change condition to monitor.  Must be of type GPIO_EVENT.
 *
 * When specified event on specified channel occurs, event handler of the form @gpio_input<n> will be invoked.
 */
native qcm_gpio_configure_handler(GPIO_IN:channel, GPIO_EVENT:event) = -56

/********************************************************************************
 * Display Routines
 *
 * Display is organized as a 56x8 matrix.  
 * 
 * 0,0 of matrix array is located at bottom left side (by button).  (55,7) of array
 * is located on bottom right side, furthest away from button.
 *
 *******************************************************************************/

/* 
 * Clears LED matrix display's frame buffer.
 *
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * None.
 */
native qcm_display_clear() = -57

/* 
 * Sets a single pixel on the LED matrix
 *
 * 0,0 of matrix array is located at bottom left size (by button).  (55,7) of array
 * is located on bottom right side, furthest aray from button.
 *
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * x : x location between 0 and 55, inclusive, to set pixel
 * y : y location between 0 and 7, inclusive, to set pixel
 * color : 12 bit color in rrrrggggbbbb format.  For discrete
 *         LED's, only bbbb is used.
 */
native qcm_display_set_pixel(x, y, r, g, b) = -58

/* 
 * Gets a single pixel on the LED matrix
 *
 * 0,0 of matrix array is located at bottom left size (by button).  (55,7) of array
 * is located on bottom right side, furthest aray from button.
 *
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * x : x location between 0 and 55, inclusive, to set pixel
 * y : y location between 0 and 7, inclusive, to set pixel
 * color : 12 bit color in rrrrggggbbbb format.  For discrete
 *         LED's, only bbbb is used.
 */
native qcm_display_get_pixel(x, y, &r, &g, &b) = -59


/* 
 * Write a text string to the LED matrix
 *
 * x and y specify the top left corner of the text to write.
 *
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * x : x location between 0 and 55, inclusive, left corner of text
 * y : y location between 0 and 7, inclusive, top corner of text
 * color : 12 bit color in rrrrggggbbbb format.  For discrete
 *         LED's, only bbbb is used.
 * text : string to write, can be either packed or unpacked
 */
native qcm_display_write_text(x, y, r, g, b, const text[]) = -60

native qcm_display_line(x1, y1, x2, y2, r, g, b) = -61
native qcm_display_bar(xtop, yleft, xbottom, yright, r, g, b) = -62

/* 
 * Write frame buffer to LED matrix display.
 *
 * Arguments:
 * None.
 */
native qcm_display_write_framebuffer() = -63

native qcm_display_scroll_horizontal(bool:scroll_right) = -64
native qcm_display_scroll_vertical(bool:scroll_up) = -65

/********************************************************************************
 * Host USB routines 
 *******************************************************************************/
/* 
 * Write binary data to the host USB endpoint.  
 *
 * All data will be sent using the debug command ID 0x01.  See the USB interface
 * specification for more information.  Maximum send size is 128 bytes.  Multiple
 * USB frames will be generated for any size over 63 bytes.
 *
 * Arguments:
 * data : array of data to be written
 * data_width: specifies number of bits used for data in each cell of data array,
 * can be 8, 16, 24, or 32.  Data will be written most significant byte first for
 * sizes greater than 8.
 * data_length: number of elements to write from data array (note - not number of 
 * bytes).
 */
native qcm_host_send(data[], data_width, data_length = sizeof data) = -66


/********************************************************************************
 * Power Management Controller Routines
 *******************************************************************************/
native qcm_reset() = -67

/******************************************************************************
 * Forward declarations for event handlers 
 *****************************************************************************/

forward @timer0()
forward @timer1()
forward @timer2()
forward @timer3()
forward @timer4()
forward @timer5()
forward @timer6()
forward @timer7()
forward @timer8()
forward @timer9()

/* 
 * If present in the script, then all messages not matched by any handlers registered with 
 * qcm_can_configure_rx_handler() are passed to this event handler.  Registered event handlers
 * will continue to get the ID's that they are registered for.  This can be thought of as a handler
 * to catch "whatever ID's are left over" after the individual handlers are registered.
 */
forward @can0_rx_all(rx_msg[QCM_CAN_MSG])
forward @can1_rx_all(rx_msg[QCM_CAN_MSG])

/* CAN message ID event handlers for channel CAN0 */
forward @can0_rx0(rx_msg[QCM_CAN_MSG])
forward @can0_rx1(rx_msg[QCM_CAN_MSG])
forward @can0_rx2(rx_msg[QCM_CAN_MSG])
forward @can0_rx3(rx_msg[QCM_CAN_MSG])
forward @can0_rx4(rx_msg[QCM_CAN_MSG])
forward @can0_rx5(rx_msg[QCM_CAN_MSG])
forward @can0_rx6(rx_msg[QCM_CAN_MSG])
forward @can0_rx7(rx_msg[QCM_CAN_MSG])

/* CAN message ID event handlers for channel CAN1 */
forward @can1_rx0(rx_msg[QCM_CAN_MSG])
forward @can1_rx1(rx_msg[QCM_CAN_MSG])
forward @can1_rx2(rx_msg[QCM_CAN_MSG])
forward @can1_rx3(rx_msg[QCM_CAN_MSG])
forward @can1_rx4(rx_msg[QCM_CAN_MSG])
forward @can1_rx5(rx_msg[QCM_CAN_MSG])
forward @can1_rx6(rx_msg[QCM_CAN_MSG])
forward @can1_rx7(rx_msg[QCM_CAN_MSG])

forward @gpio_input_switch_left()
forward @gpio_input_switch_right()
forward @gpio_input_usb_power()

/* 
 * This event handler is invoked with the data received on the host 
 * USB endpoint.  Passed data is one byte per cell and not packed.
 * Note that the USB command ID of 0x01 is not passed (see document 
 * titled "USB Protocol.txt" in doc subfolder of SDK).
 *
 */
forward @host_rx(data[], data_size);

