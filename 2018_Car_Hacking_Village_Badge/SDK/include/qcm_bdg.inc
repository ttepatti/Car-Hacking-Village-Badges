/******************************************************************************
 * Copyright 2014-2018 Specialized Solutions LLC
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

/* 
 * Used to specify/receive CAN messages.
 * 
 * Members:
 * .id : CAN message ID
 * .is_extended : if true, message ID is 29-bit.  IF false, message id is 11-bit
 * .is_fd : if true, message is sent in CANFD format
 * .use_brs : if true, message payload is sent using faster baudrate for CANFD (ignored
 *            if .is_fd is false)
 * .dlc : length of CAN message (0 through 8 for CAN, 0 through 64 for CANFD inclusive)
 * .data : payload of CAN message (use .dlc to determine the valid data bytes)
 */ 
#define QCM_CAN_MSG[.id, bool:.is_extended, bool:.is_fd, bool:.use_brs, .dlc, .data[64]]

/*****************************************************************************
 * Tags (types) for use in calling the handlers 
 *****************************************************************************/

 /* Input tags */
const GPIO_IN:GPIO_INPUT_SWITCH_TOP = 0
const GPIO_IN:GPIO_INPUT_SWITCH_BOTTOM = 1
const GPIO_IN:GPIO_INPUT_EXTERNAL_POWER = 2

/* Input event tags */
const GPIO_EVENT:GPIO_EVENT_NONE = 0
const GPIO_EVENT:GPIO_EVENT_LOW = 1
const GPIO_EVENT:GPIO_EVENT_HIGH = 2
const GPIO_EVENT:GPIO_EVENT_ALL = 3

/* timer tags */
const TIMER:TIMER_0 = 0
const TIMER:TIMER_1 = 1
const TIMER:TIMER_2 = 2
const TIMER:TIMER_3 = 3
const TIMER:TIMER_4 = 4
const TIMER:TIMER_5 = 5
const TIMER:TIMER_6 = 6
const TIMER:TIMER_7 = 7

/* CAN channel tags 
 * CAN 0, 1, and 2 are CANFD capable 
 */
const CAN_CHANNEL:CAN0 = 0 
const CAN_CHANNEL:CAN1 = 1
const CAN_CHANNEL:CAN2 = 2
const CAN_CHANNEL:CAN3 = 3

/* CAN receive handler tags */
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
 * use_fd : use CAN-FD if true
 * fd_brs_speed : Bit rate of CANFD transactions, defaults to same as speed
 */
native qcm_can_init(CAN_CHANNEL:channel, speed, bool:use_fd, brs_speed) = -51

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
 * channel_a : specifies the source CAN channel
 * channel_b : specifies the destination can channel
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
 * Display is organized as a 40x12 matrix.  
 * 
 * 0,0 is located at the top left corner of the matrix.  The first two rows are
 * discrete LED's (only one color, but 4bits of intensity), 
 * the middle 8 rows are RGB (12-bit color), and the bottom two rows are 
 * discrete LED's.
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
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * x : x location between 0 and 39, inclusive, to set pixel
 * y : y location between 0 and 11, inclusive, to set pixel
 * r : red intensity or discrete LED duty cycle (0 - 0xF)
 * g : green intensity (does not apply to discrete LEDs)
 * b : blue intensity  (does not apply to discrete LEDs)
 */
native qcm_display_set_pixel(x, y, r, g, b) = -58

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
 * x : x location between 0 and 39, inclusive, left corner of text
 * y : y location between 0 and 11, inclusive, top corner of text
 * r : red intensity or discrete LED duty cycle (0 - 0xF)
 * g : green intensity (does not apply to discrete LEDs)
 * b : blue intensity  (does not apply to discrete LEDs)
 * text : string to write, can be either packed or unpacked
 */
native qcm_display_write_text(x, y, r, g, b, const text[]) = -59

/* 
 * Draw a line on the LED matrix
 *
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * x1 : x1 location between 0 and 39
 * y1 : y1 location between 0 and 11
 * x2 : x1 location between 0 and 39
 * y2 : y1 location between 0 and 11
 * r : red intensity or discrete LED duty cycle (0 - 0xF)
 * g : green intensity (does not apply to discrete LEDs)
 * b : blue intensity  (does not apply to discrete LEDs)
 * text : string to write, can be either packed or unpacked
 */
native qcm_display_line(x1, y1, x2, y2, r, g, b) = -60

/* 
 * Draw a filled box on the LED matrix
 *
 * Note: only modifies frame buffer - call qcm_display_write_framebuffer() to apply
 * changes to LED matrix (allows for many operations to take place with one call to
 * update the LED matrix).
 *
 * Arguments:
 * x1 : x1 location between 0 and 39
 * y1 : y1 location between 0 and 11
 * x2 : x1 location between 0 and 39
 * y2 : y1 location between 0 and 11
 * r : red intensity or discrete LED duty cycle (0 - 0xF)
 * g : green intensity (does not apply to discrete LEDs)
 * b : blue intensity  (does not apply to discrete LEDs)
 * text : string to write, can be either packed or unpacked
 */
native qcm_display_bar(xtop, yleft, xbottom, yright, r, g, b) = -61

/* 
 * Write frame buffer to LED matrix display.
 *
 * Arguments:
 * None.
 */
native qcm_display_write_framebuffer() = -62

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
native qcm_host_send(data[], data_width, data_length = sizeof data) = -63

/********************************************************************************
 * SD Card Routines
 *
 * Note that only one file can be opened at once.  Test the result of fopen to see 
 * if open was successful.
 *
 *******************************************************************************/
native qcm_fopen(const name[], FileMode:mode) = -64
native qcm_fseek(position) = -65
native qcm_fwrite(const data[], data_length = sizeof data) = -66
native qcm_fread(data[], bytes_to_read) = -67
native qcm_fclose() = -68

/********************************************************************************
 * Ethernet Routines
 *
 * Note that up to 4 ports can be listened to simultaneously.
 *
 *******************************************************************************/
native qcm_eth_init(ipv4_addr, ipv4_gw, ipv4_subnet) = -69
native qcm_eth_listenport(port) = -70
native qcm_eth_closeport(port) = -71
native qcm_eth_sendudp(ipv4_addr, port, packet[], packet_size = sizeof packet) = -72
native qcm_eth_make_ip_addr(a, b, c, d) = -73

/********************************************************************************
 * K-Line Routines
 *******************************************************************************/
native kwp_init(KWP_CHANNEL:channel, baud = 10400) = -74
native kwp_send(KWP_CHANNEL:channel, data[], data_size = sizeof data) = -75

/********************************************************************************
 * Power Management Controller Routines
 *******************************************************************************/
native qcm_reset() = -76

/********************************************************************************
 * Sensor Routines
 *******************************************************************************/
native qcm_sensor_gyro_init() = -77
native qcm_sensor_accel_init() = -78
 
/******************************************************************************
 * Forward declarations for event handlers 
 *****************************************************************************/

 /* timer event handlers */
forward @timer0()
forward @timer1()
forward @timer2()
forward @timer3()
forward @timer4()
forward @timer5()
forward @timer6()
forward @timer7()

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

/* CAN message ID event handlers for channel CAN2 */
forward @can2_rx0(rx_msg[QCM_CAN_MSG])
forward @can2_rx1(rx_msg[QCM_CAN_MSG])
forward @can2_rx2(rx_msg[QCM_CAN_MSG])
forward @can2_rx3(rx_msg[QCM_CAN_MSG])
forward @can2_rx4(rx_msg[QCM_CAN_MSG])
forward @can2_rx5(rx_msg[QCM_CAN_MSG])
forward @can2_rx6(rx_msg[QCM_CAN_MSG])
forward @can2_rx7(rx_msg[QCM_CAN_MSG])

/* CAN message ID event handlers for channel CAN3 */
forward @can3_rx0(rx_msg[QCM_CAN_MSG])
forward @can3_rx1(rx_msg[QCM_CAN_MSG])
forward @can3_rx2(rx_msg[QCM_CAN_MSG])
forward @can3_rx3(rx_msg[QCM_CAN_MSG])
forward @can3_rx4(rx_msg[QCM_CAN_MSG])
forward @can3_rx5(rx_msg[QCM_CAN_MSG])
forward @can3_rx6(rx_msg[QCM_CAN_MSG])
forward @can3_rx7(rx_msg[QCM_CAN_MSG])

/* input change handlers */
forward @gpio_input_switch_top()
forward @gpio_input_switch_bottom()
forward @gpio_input_obd2()

/* 
 * This event handler is invoked with the data received on the host 
 * USB endpoint.  Passed data is one byte per cell and not packed.
 * Note that the USB command ID of 0x01 is not passed (see document 
 * titled "USB Protocol.txt" in doc subfolder of SDK).
 *
 */
forward @host_rx(data[], data_size)

forward @portrecv(ipv4_addr, remote_port, local_port, data[], data_size)

forward @kwprecv0(data[], data_size)
forward @kwprecv1(data[], data_size)

forward @sensorgyroupdate(x, y, z)
forward @sensoraccelupdate(x, y, z)


