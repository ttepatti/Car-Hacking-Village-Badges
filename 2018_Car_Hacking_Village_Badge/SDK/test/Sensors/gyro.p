
@sensorgyroupdate(x, y, z)
{
	new x0 = x / 350
	new y0 = y / 350
	new z0 = z / 350
	
	qcm_display_clear()
	
	if (x0 < 0)
	{
		qcm_display_bar(19+x0, 2, 19, 4, 0xF, 0, 0)
	}
	else
	{
		qcm_display_bar(19, 2, 19+x0, 4, 0xF, 0, 0)
	}
	
	if (y0 < 0)
	{
		qcm_display_bar(19+y0, 5, 19, 7, 0, 0xF, 0)
	}
	else
	{
		qcm_display_bar(19, 5, 19+y0, 7, 0, 0xF, 0)
	}
	
	if (z0 < 0)
	{
		qcm_display_bar(19+z0, 8, 19, 9, 0, 0, 0xF)
	}
	else
	{
		qcm_display_bar(19, 8, 19+z0, 9, 0, 0, 0xF)
	}
	
	
	qcm_display_write_framebuffer()
	
}

main()
{
	qcm_display_clear();
	qcm_sensor_gyro_init();
    
}