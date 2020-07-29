/******************************************************************************
 * Copyright 2016-2018 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * Default Badge Script for the DC2018 QCM badge
 *
 * This demo shows off many features of the PAWN language and the QCM
 * subsystem.
 *
 *****************************************************************************/

new selected_item = 0
 
/******************************************************************************
 * Menu handling code 
 *****************************************************************************/
new const menu_items[5]{} = [ "RAND", "GAME", "NEO", "WAVE", "BOX"]

show_menu()
{
	state menu
    
	qcm_display_clear()
	qcm_display_write_text(0, 2, 0xF, 0xF, 0xF, menu_items[selected_item])
	qcm_display_write_framebuffer()
}

input_switch_bottom_debounce() <menu>
{
	selected_item++;
	
	if (selected_item > 4)
	{
		selected_item = 0;
	}
	
	show_menu()
	
}

input_switch_top_debounce() <menu>
{
	if (selected_item == 0)
	{
		random_demo()
	}
    else if (selected_item == 1)
	{
		selected_item = 0
		game_demo()
	}
	else if (selected_item == 2)
	{
		selected_item = 0
		matrix_demo()
	}
	else if (selected_item == 3)
	{
		selected_item = 0
		wave_demo()
	}
	else if (selected_item == 4)
	{
		selected_item = 0
		box_demo()
	}
	else
	{
		selected_item = 0
		show_menu()
	}
}


/******************************************************************************
 * Random demo code 
 *****************************************************************************/

random_demo()
{
	qcm_timer_start(TIMER_4,150,true)
	state random_demo
	
}

@timer4() <random_demo>
{
	new x, y;
	
	qcm_display_clear()
	
	for (x = 0; x < 40; x++)
	{
		for (y = 0; y < 12; y++)
		{
			qcm_display_set_pixel(x, y, random(10), random(10), random(10))
		}
	}
	
	qcm_display_write_framebuffer()
}

input_switch_bottom_debounce() <random_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_top_debounce() <random_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Game of life demo code 
 *****************************************************************************/
new univ[40][12]

game_demo()
{
	qcm_timer_start(TIMER_4,2000,true)
	state game_demo
	
	new x, y
	
	for (x = 0; x < 40; x++)
	{
		for (y = 0; y < 12; y++)
		{
			if (random(10) < 5)
			{
				univ[x][y] = 1
			}
			else
			{
				univ[x][y] = 0;
			}
		}
	}
	
}

count_live_neighbors(x, y)
{
	new x1, y1, n
	
	n = 0
			
	for (y1 = y - 1; y1 <= y + 1; y1++)
	{
		for (x1 = x - 1; x1 < x + 1; x1++)
		{
			if (univ[(x1 + 40) % 40][(y1 + 12) % 12])
			{
				n++
			}
		}
	}
	
	if (univ[x][y])
	{
		n--
	}
	
	return n
}


@timer4() <game_demo>
{
	new new_univ[40][12]
	new n, x, y, counter
	
	/* display universe */
	qcm_display_clear()
	
	counter = 0
	
	for (x = 0; x < 40; x++)
	{
		for (y = 0; y < 12; y++)
		{
			if (univ[x][y])
			{
				n = count_live_neighbors(x, y)
				
				qcm_display_set_pixel(x, y, n, n, n)
				counter++
			}
		}
	}
	
	qcm_display_write_framebuffer()
	
	if (counter > 0)
	{
		/* evolve the universe */
		for (x = 0; x < 40; x++)
		{
			for (y = 0; y < 12; y++)
			{
				n = count_live_neighbors(x, y)
				
				if ((n == 3) || ((n == 2) && (univ[x][y] == 1)))
				{
					new_univ[x][y] = 1;
				}
			}
		}
		
		for (x = 0; x < 40; x++)
		{
			for (y = 0; y < 12; y++)
			{
				univ[x][y] = new_univ[x][y]
			}
		}
	}
	else
	{
		/* new universe */
		for (x = 0; x < 40; x++)
		{
			for (y = 0; y < 12; y++)
			{
				if (random(10) < 5)
				{
					univ[x][y] = 1
				}
				else
				{
					univ[x][y] = 0;
				}
			}
		}
	}
	
}

input_switch_bottom_debounce() <game_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_top_debounce() <game_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Matrix mode
 *****************************************************************************/
new columns[40]
new intensityx[40]
new intensityy[40]
new intensityz[40]

matrix_demo()
{
	qcm_timer_start(TIMER_4,100,true)
	state matrix_demo
	
	new x
	
	for (x = 0; x < 40; x++)
	{
		columns[x] = random(10)
		intensityx[x] = random(0x10)
		intensityy[x] = random(0x10)
		intensityz[x] = random(0x10)
	}
	
}

@timer4() <matrix_demo>
{
	new x, y, r, g, b
	
	for (x = 0; x < 40; x++)
	{
		if (random(100) < 2)
		{
			columns[x]++
	
			if (columns[x] > 15)
			{
				columns[x] = 0;
				intensityx[x] = random(0x10)
				intensityy[x] = random(0x10)
				intensityz[x] = random(0x10)
			}
		}
		
		r = intensityx[x]
		g = intensityy[x]
		b = intensityz[x]
		
		for (y = columns[x]; y >= 0; y--)
		{
			qcm_display_set_pixel(x, y, r, g, b)
			r = r / 2			
			g = g / 2			
			b = b / 2			
		}
		
		for (y = columns[x] + 1; y < 12; y++)
		{
			qcm_display_set_pixel(x, y, 0, 0, 0)
		}
		
		
		columns[x]++
	
		if (columns[x] > 15)
		{
			columns[x] = 0
			intensityx[x] = random(0x10)
			intensityy[x] = random(0x10)
			intensityz[x] = random(0x10)
		}
	}
	
	qcm_display_write_framebuffer()
	
	
}

input_switch_bottom_debounce() <matrix_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_top_debounce() <matrix_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Wave mode
 *****************************************************************************/

new wave_pos

wave_demo()
{
	wave_pos = 0
	
	qcm_timer_start(TIMER_4,100,true)
	
	state wave_demo
}

@timer4() <wave_demo>
{
	new Float:temp
	new x, y
	new Float:delta
	
	qcm_display_clear()
	
	delta = 0.0;
	
	for (x = wave_pos; x >= 0 ; x--)
	{
		temp = floatsin(90.0 - delta, degrees) * 255.0
		
		if (temp < 0.0)
		{
			temp = 0.0;
		}
		
		for (y = 0; y < 10; y++)
		{
			qcm_display_set_pixel(x, y, floatround(temp, floatround_floor), floatround(temp, floatround_floor), floatround(temp, floatround_floor))
		}
		
		delta += 90.0 / 28.0;
	}
	
	qcm_display_write_framebuffer()
	
	wave_pos++
	
	if (wave_pos > 27 * 2)
	{
		wave_pos = 0
	}
}

input_switch_bottom_debounce() <wave_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_top_debounce() <wave_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Box mode
 *****************************************************************************/

#define BOX[.r,.g,.b]

new boxes[19][BOX] = [
	[0xF, 0, 0],
	[0, 0xF, 0],
	[0, 0, 0xF],
	[0xF, 0xF, 0],
	[0, 0xF, 0xF],
	[0xF, 0, 0xF],
	[0xF, 0xF, 0xF],
	[0xF, 0, 0],
	[0, 0xF, 0],
	[0, 0, 0xF],
	[0xF, 0xF, 0],
	[0, 0xF, 0xF],
	[0xF, 0, 0xF],
	[0xF, 0xF, 0xF],
	[0xF, 0, 0],
	[0, 0xF, 0],
	[0, 0, 0xF],
	[0xF, 0xF, 0],
	[0, 0xF, 0xF]]
	
new locations[10][2]

box_demo()
{
	new x
	new y
	new i
	
	x = 0
	y = 0
	
	i = 0;
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 2; y++)
		{
			locations[x][y] = i++
		}
	}
	
	/* blank location */
	locations[9][1] = 0xFF
	
	qcm_timer_start(TIMER_4,500,true)
	
	state box_demo
}

box_render()
{
	new x, y, temp
	
	qcm_display_clear()
	
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 2; y++)
		{
			if (locations[x][y] != 0xFF)
			{
				temp = locations[x][y]
				qcm_display_bar(x*4, y*4 + 2, ((x+1) * 4) - 1, ((y+1) * 4) - 1 + 2, boxes[temp].r, boxes[temp].g, boxes[temp].b)
			}
		}
	}
	
	qcm_display_write_framebuffer()
}
	
@timer4() <box_demo>
{
	new x, y, random_move, temp
	
	
	/* find blank */
	for (x = 0; x < 10; x++)
	{
		for (y = 0; y < 2; y++)
		{
			if (locations[x][y] == 0xFF)
			{
				/* found blank, figure out which adjacent box to move */
				random_move = random(3)
				
				if (random_move == 0)
				{
					if (x > 0)
					{
						/* left to blank */
						temp = locations[x-1][y]
						locations[x-1][y] = 0xFF
						locations[x][y] = temp
						box_render()
						return
					}
					else
					{
						if (y == 0)
						{
							/* x is on left already, go to next possible move below */
							temp = locations[x][y+1]
							locations[x][y+1] = 0xFF
							locations[x][y] = temp
							box_render()
							return
						}
						else
						{
							/* x is on left already, go to next possible move above */
							temp = locations[x][y-1]
							locations[x][y-1] = 0xFF
							locations[x][y] = temp
							box_render()
							return
						}
					}
				}
				else if (random_move == 1)
				{
					if (y == 0)
					{
						/* move from the bottom */
						temp = locations[x][y+1]
						locations[x][y+1] = 0xFF
						locations[x][y] = temp
						box_render()
						return
					}
					else
					{
						/* move from the top */
						temp = locations[x][y-1]
						locations[x][y-1] = 0xFF
						locations[x][y] = temp
						box_render()
						return
					}
				}
				else
				{
					if (x < 9)
					{
						/* move from the right */
						temp = locations[x+1][y]
						locations[x+1][y] = 0xFF
						locations[x][y] = temp
						box_render()
						return
					}
					else
					{
						/* move from the left as an alternate move */
						temp = locations[x-1][y]
						locations[x-1][y] = 0xFF
						locations[x][y] = temp
						box_render()
						return
					}
				}
			}
		}
	}
}

input_switch_bottom_debounce() <box_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_top_debounce() <box_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}



/******************************************************************************
 * Default state handlers
 *****************************************************************************/

input_switch_top_debounce() <>
{

}

input_switch_bottom_debounce() <>
{

}

@timer4() <>
{

}

/******************************************************************************
 * Switch debounce routines
 *****************************************************************************/
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

/******************************************************************************
 * Main routine (initilization)
 *****************************************************************************/
main()
{
	sleep 1000

	state menu
	
	qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_TOP, GPIO_EVENT_HIGH)
	qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_BOTTOM, GPIO_EVENT_HIGH)
	
	show_menu()
	
}
