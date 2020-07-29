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
 * Example showing speed and rpm using standard OBD2 messaging
 * THis should work on most vehicles (especially vehicles with an OBD2 gateway)
 * If your vehicle is publishing speed and rpm to the OBD2 port, this example 
 * can be modified to simply receive and parse those messages (as opposed to what
 * this script does by sending requests and parsing the responses).  This would
 * allow for a faster refresh rate as well.  The maximum refresh rate on the 
 * display is around 50ms (20 fps).  This limitation is mostly based on the 
 * display breaking up due to the S9 having to service the incoming SPI data 
 * while it is rendering the display.  If only the S9 had a DMA so that SPI
 * data could be handled without the core having to do anything...
 *
 *****************************************************************************/

new rpm = 0
new speed = 0

@timer0() 
{
	new rpm_columns, speed_columns, i, y, green, red
	
	/* RPM max is 7k, so 1 column per 125rpm (56 columns) */
	rpm_columns = rpm / 125
	speed_columns = speed / 2
    
	qcm_display_clear()
	
	for (i = 0; (i < rpm_columns) || (i < speed_columns); i++)
	{
		/* start turning to yellow at 2000 rpm */
		if (i > 16)
		{
			red = (i - 16) / 2
		}
		
		/* at 6k, make all red */
		if (i > 48)
		{
			green = 0
			red = 0xF
		}
		else
		{
			green = 0xF
		}
		
		if (i < rpm_columns)
        {
            for (y = 4; y < 8; y++)
            {
                qcm_display_set_pixel(i, y, red, green, 0)
            }
        }
        
        if (i < speed_columns)
        {
            for (y = 0; y < 4; y++)
            {
                qcm_display_set_pixel(i, y, red, 0, green)
            }
        
        }
	}
	
	qcm_display_write_framebuffer()
}

@timer1() <rpm_request>
{
    new tx_msg[QCM_CAN_MSG]
    
    /* make the requests */
    tx_msg.dlc = 8
    tx_msg.id = 0x7E0
    tx_msg.is_extended = false
    
    tx_msg.data[0] = 0x02
    tx_msg.data[1] = 0x01
    tx_msg.data[2] = 0x0C
    
    qcm_can_tx(CAN0, tx_msg)
	
	printf("Send RPM\n")
}

@timer1() <speed_request>
{
    new tx_msg[QCM_CAN_MSG]
    
    /* make the requests */
    tx_msg.dlc = 8
    tx_msg.id = 0x7E0
    tx_msg.is_extended = false
    
    tx_msg.data[0] = 0x02
    tx_msg.data[1] = 0x01
    tx_msg.data[2] = 0x0D
    
    qcm_can_tx(CAN0, tx_msg)
	printf("Send Speed\n")
}

@timer1()<>
{

}

@can0_rx0(rx_msg[QCM_CAN_MSG]) <rpm_request>
{
	new temp
    
    if ((rx_msg.data[1] == 0x41) && (rx_msg.data[2] == 0x0C))
    {
        temp = rx_msg.data[3]
        temp <<= 8
        temp += rx_msg.data[4]
        rpm = temp >> 2
        state speed_request
    }
}

@can0_rx0(rx_msg[QCM_CAN_MSG]) <speed_request>
{
	new Float:temp
    
    if ((rx_msg.data[1] == 0x41) && (rx_msg.data[2] == 0x0D))
    {
        temp = float(rx_msg.data[3])        
        temp *= 0.621371
        speed = floatround(temp)
        state rpm_request
    }
}

@can0_rx0(rx_msg[QCM_CAN_MSG]) <>
{

}

main()
{
	qcm_can_init(CAN0, 500000)
	qcm_can_configure_rx_handler(CAN0, CAN_RX_HANDLER_0, 0x7E8, false)
	
	qcm_timer_start(TIMER_0, 100, true)
    qcm_timer_start(TIMER_1, 100, true)
	
	state rpm_request
	
}

