
main()
{
	new x
	
	while (true)
	{
		sleep(500)
		qcm_display_clear()
		qcm_display_write_text(0,0,random(0x10),random(0x10),random(0x10),"Hello World!")
		qcm_display_write_framebuffer()
		sleep(500)
		
		x = 56;
		
		while (x > 0)
		{
			qcm_display_scroll_horizontal(false)
			qcm_display_write_framebuffer()
			sleep(25)
			x--
		}

		sleep(500)
		qcm_display_clear()
		qcm_display_write_text(0,0,random(0x10),random(0x10),random(0x10),"Hello World!")
		qcm_display_write_framebuffer()
		sleep(500)
		
		x = 56;
		
		while (x > 0)
		{
			qcm_display_scroll_horizontal(true)
			qcm_display_write_framebuffer()
			sleep(25)
			x--
		}
		
		sleep(500)
		qcm_display_clear()
		qcm_display_write_text(0,0,random(0x10),random(0x10),random(0x10),"Hello World!")
		qcm_display_write_framebuffer()
		sleep(500)
		
		x = 8;
		
		while (x > 0)
		{
			qcm_display_scroll_vertical(true)
			qcm_display_write_framebuffer()
			sleep(50)
			x--
		}
		
		sleep(500)
		qcm_display_clear()
		qcm_display_write_text(0,0,random(0x10),random(0x10),random(0x10),"Hello World!")
		qcm_display_write_framebuffer()
		sleep(500)
		
		x = 8;
		
		while (x > 0)
		{
			qcm_display_scroll_vertical(false)
			qcm_display_write_framebuffer()
			sleep(50)
			x--
		}
	}

}
