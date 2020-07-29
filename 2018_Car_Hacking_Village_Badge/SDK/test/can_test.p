/******************************************************************************
 * Copyright 2016-2017 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * Default Badge Script for the small QCM badge
 *
 * This demo shows off many features of the PAWN language and the QCM
 * subsystem.
 *
 *****************************************************************************/

@timer4()
{
    qcm_display_clear()
	qcm_display_write_framebuffer()
}

@can0_rx0(rx_msg[QCM_CAN_MSG])
{
	rx_msg.id = 0x001
	
	qcm_can_tx(CAN0, rx_msg)
	
	qcm_display_write_text(0, 2, 0xF, 0xF, 0xF, "RX0")
	qcm_display_write_framebuffer()
	qcm_timer_start(TIMER_4, 500, false)
		
}

@can1_rx0(rx_msg[QCM_CAN_MSG])
{
	rx_msg.id = 0x002
	
	qcm_can_tx(CAN0, rx_msg)
	
	qcm_display_write_text(0, 2, 0xF, 0xF, 0xF, "RX1")
	qcm_display_write_framebuffer()
	qcm_timer_start(TIMER_4, 500, false)
		
}

@can2_rx0(rx_msg[QCM_CAN_MSG])
{
	rx_msg.id = 0x003
	
	qcm_can_tx(CAN0, rx_msg)
	
	qcm_display_write_text(0, 2, 0xF, 0xF, 0xF, "RX2")
	qcm_display_write_framebuffer()
	qcm_timer_start(TIMER_4, 500, false)
		
}

input_switch_bottom_debounce()
{
	/* send normal CAN frame */
	new msg[QCM_CAN_MSG]
	
	msg.id = 0x555
	msg.is_extended = false
	msg.is_fd = false
	msg.use_brs = false
	msg.dlc = 8
	
	qcm_can_tx(CAN0, msg)
}

input_switch_top_debounce()
{
	qcm_timer_stop(TIMER_4)
	
	/* send FD CAN frame */
	new msg[QCM_CAN_MSG]
	
	msg.id = 0x555
	msg.is_extended = false
	msg.is_fd = true
	msg.use_brs = true
	msg.dlc = 10
	
	qcm_can_tx(CAN1, msg)
	
}

@gpio_input_switch_top()
{
    /* start debounce timer */
    qcm_timer_start(TIMER_2,50,false)
}	


@gpio_input_switch_bottom()
{
    /* start debounce timer */
    qcm_timer_start(TIMER_3,50,false)
}

@timer2()
{
    if (qcm_gpio_get_input(GPIO_INPUT_SWITCH_TOP))
    {
        /* button has been released - call new function to handle debounced input */
        input_switch_top_debounce()
    }
}

@timer3()
{
    if (qcm_gpio_get_input(GPIO_INPUT_SWITCH_BOTTOM))
    {
        /* button has been released - call new function to handle debounced input */
        input_switch_bottom_debounce()
    }
}

main()
{
	sleep 1000
	
	qcm_can_init(CAN0, 500000, true, 1000000)
	qcm_can_init(CAN1, 500000, true, 1000000)
	qcm_can_init(CAN2, 500000, true, 1000000)
	
	qcm_can_configure_rx_handler(CAN0, CAN_RX_HANDLER_0, 0x555, false)
	qcm_can_configure_rx_handler(CAN1, CAN_RX_HANDLER_0, 0x555, false)
	qcm_can_configure_rx_handler(CAN2, CAN_RX_HANDLER_0, 0x555, false)
	
	qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_TOP, GPIO_EVENT_HIGH)
	qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_BOTTOM, GPIO_EVENT_HIGH)
	
	
}
