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
 * Example showing simulated speed and rpm.
 *
 *****************************************************************************/

new rpm = 0
new speed = 0

@timer0() 
{
	new rpm_columns, speed_columns, i, y, green, red
	
	rpm = rpm + 25
	speed = speed + 2
	
	if (rpm > 7000)
	{
		rpm = 0
	}
	
	if (speed > 110)
	{
		speed = 0
	}
	
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

main()
{
	qcm_timer_start(TIMER_0, 50, true)
    
}

