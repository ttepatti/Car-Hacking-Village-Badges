new r
new g
new b

main()
{
	new x, y
	
    while(1)
    {
        r = random(0x10)
        g = random(0x10)
        b = random(0x10)
        qcm_display_clear()
        qcm_display_write_text(0,2,r,g,b,"Hello")
		for (x = 0; x < 40; x++)
		{
			for (y = 0; y < 2; y++)
			{
				qcm_display_set_pixel(x, y, random(0x10), 0, 0)
			}
			
			for (y = 10; y < 12; y++)
			{
				qcm_display_set_pixel(x, y, random(0x10), 0, 0)
			}
		}
		
        qcm_display_write_framebuffer()
        sleep(50)
    }
    
}
