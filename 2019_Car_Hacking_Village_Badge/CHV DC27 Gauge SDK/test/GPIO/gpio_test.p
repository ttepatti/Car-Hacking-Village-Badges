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
 * QCM GPIO tests - this test is designed to be run with jumpers between 
 * inputs 0-5 and outputs 0-5 (out 0 -> in 0, out1 -> in 1, etc.)
 *
 *****************************************************************************/

print_gpio_notice(gpio, bool:io_state)
{
    printf("GPIO %d event - state %d\n", gpio, io_state)
}

@gpio_input_switch_left()
{
    print_gpio_notice(0, qcm_gpio_get_input(GPIO_INPUT_SWITCH_LEFT))
	qcm_display_bar(0,0,5,7,0xF,0xF,0)
	qcm_timer_start(TIMER_0, 500, false)
	qcm_display_write_framebuffer()
}

@gpio_input_switch_right()
{
    print_gpio_notice(1, qcm_gpio_get_input(GPIO_INPUT_SWITCH_RIGHT))
	qcm_display_bar(50,0,55,7,0,0xF,0xF)
	qcm_timer_start(TIMER_1, 500, false)
	qcm_display_write_framebuffer()
}

@timer0()
{
	qcm_display_bar(0,0,5,7,0,0,0)
	qcm_display_write_framebuffer()
}

@timer1()
{
	qcm_display_bar(50,0,55,7,0,0,0)
	qcm_display_write_framebuffer()
}

@gpio_input_usb_power()
{
    print_gpio_notice(2, qcm_gpio_get_input(GPIO_INPUT_USB_POWER))
	
	if (qcm_gpio_get_input(GPIO_INPUT_USB_POWER))
	{
		qcm_display_bar(24,0,34,7,0,0xF,0)
	}
	else
	{	
		qcm_display_bar(24,0,34,7,0xF,0,0)
	}
	
	qcm_display_write_framebuffer()
	
}

main()
{
	sleep 1000
	
    printf "Starting GPIO Tests\n"
    qcm_display_clear()
	qcm_display_write_framebuffer()
	
    qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_LEFT, GPIO_EVENT_LOW)
    qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_RIGHT, GPIO_EVENT_HIGH)
    qcm_gpio_configure_handler(GPIO_INPUT_USB_POWER, GPIO_EVENT_ALL)
    
}