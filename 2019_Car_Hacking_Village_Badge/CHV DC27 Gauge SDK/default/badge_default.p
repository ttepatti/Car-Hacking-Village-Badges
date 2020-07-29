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
 * Default Badge Script for the speedometer badge
 *
 * This demo shows off many features of the PAWN language and the QCM
 * subsystem.
 *
 *****************************************************************************/

new selected_item = 0
 
/******************************************************************************
 * Menu handling code 
 *****************************************************************************/
new const menu_items[6]{} = [ "RAND", "GAME", "SUN", "WAVE", "BOX","BLOX"]

show_menu()
{
	state menu
    
	qcm_display_clear()
	qcm_display_write_text(0, 0, 0xF, 0xF, 0xF, menu_items[selected_item])
	qcm_display_write_framebuffer()
}

input_switch_right_debouncce() <menu>
{
	selected_item++;
	
	if (selected_item > 5)
	{
		selected_item = 0;
	}
	
	show_menu()
	
}

input_switch_left_debouncce() <menu>
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
		sun_demo()
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
	else if (selected_item == 5)
	{
		selected_item = 0
		blox_demo()
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
	
	for (x = 0; x < 56; x++)
	{
		for (y = 0; y < 8; y++)
		{
			qcm_display_set_pixel(x, y, random(0x10), random(0x10), random(0x10))
		}
	}
	
	qcm_display_write_framebuffer()
}

input_switch_right_debouncce() <random_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_left_debouncce() <random_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Game of life demo code 
 *****************************************************************************/
new univ[56][8]

game_demo()
{
	qcm_timer_start(TIMER_4,2000,true)
	state game_demo
	
	new x, y
	
	for (x = 0; x < 56; x++)
	{
		for (y = 0; y < 8; y++)
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
			if (univ[(x1 + 56) % 56][(y1 + 8) % 8])
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
	new new_univ[56][8]
	new n, x, y, counter
	
	/* display universe */
	qcm_display_clear()
	
	counter = 0
	
	for (x = 0; x < 56; x++)
	{
		for (y = 0; y < 8; y++)
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
		for (x = 0; x < 56; x++)
		{
			for (y = 0; y < 8; y++)
			{
				n = count_live_neighbors(x, y)
				
				if ((n == 3) || ((n == 2) && (univ[x][y] == 1)))
				{
					new_univ[x][y] = 1;
				}
			}
		}
		
		for (x = 0; x < 56; x++)
		{
			for (y = 0; y < 8; y++)
			{
				univ[x][y] = new_univ[x][y]
			}
		}
	}
	else
	{
		/* new universe */
		for (x = 0; x < 56; x++)
		{
			for (y = 0; y < 8; y++)
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

input_switch_right_debouncce() <game_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_left_debouncce() <game_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * sun mode
 *****************************************************************************/
new head_pos[56]

sun_demo()
{
	qcm_timer_start(TIMER_4,150,true)
	state sun_demo
	
	new x
	
	for (x = 0; x < 56; x++)
	{
		head_pos[x] = random(8)
	}
	
}

@timer4() <sun_demo>
{
	new x, y, r, g, b
	
	for (x = 0; x < 56; x++)
	{
		r = random(0x10)
		g = random(0x10)
		b = random(0x10)
		
		for (y = head_pos[x] + 1; y >= 0; y--)
		{
			qcm_display_set_pixel(x, y, r, g, b)
			
			r /= 2
			g /= 2
			b /= 2
			
		}
		
		head_pos[x]--
		
		if (head_pos[x] < 0)
		{
			head_pos[x] = 7
		}
	}
	
	
	qcm_display_write_framebuffer()
	
	
}

input_switch_right_debouncce() <sun_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_left_debouncce() <sun_demo>
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

new Float:temp
new Float:temp2
new Float:temp3
new Float:delta
	
@timer4() <wave_demo>
{
	new x, y

	qcm_display_clear()
	
	for (x = wave_pos; x >= 0 ; x--)
	{
		temp = floatsin(90.0 - delta, degrees) * 16.0
		temp2 = floatsin(76.0 - delta, degrees) * 16.0
		temp3 = floatsin(13.0 - delta, degrees) * 16.0
		
		if (temp < 0.0)
		{
			temp = 0.0;
		}
		
		if (temp2 < 0.0)
		{
			temp2 = 0.0;
		}
		
		if (temp3 < 0.0)
		{
			temp3 = 0.0;
		}
		
		for (y = 0; y < 8; y++)
		{
			qcm_display_set_pixel(x % 56, y, floatround(temp, floatround_floor), floatround(temp2, floatround_floor), floatround(temp3, floatround_floor))
		}
		
		delta += 90.0 / 15.0;
	}
	
	qcm_display_write_framebuffer()
	
	wave_pos++
	
}

input_switch_right_debouncce() <wave_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_left_debouncce() <wave_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Box mode
 *****************************************************************************/

#define BOX[.r,.g,.b]

new boxes[28][BOX] = [
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
	[0, 0xF, 0xF],
	[0xF, 0, 0xF],
	[0xF, 0xF, 0xF],
	[0xF, 0, 0],
	[0, 0xF, 0],
	[0, 0, 0xF],
	[0xF, 0xF, 0],
	[0, 0xF, 0xF],
	[0xF, 0, 0xF],
	[0xF, 0xF, 0xF]]


	
new locations[14][2]

box_demo()
{
	new x
	new y
	new i
	
	x = 0
	y = 0
	
	i = 0;
	for (x = 0; x < 14; x++)
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
	
	for (x = 0; x < 14; x++)
	{
		for (y = 0; y < 2; y++)
		{
			if (locations[x][y] != 0xFF)
			{
				temp = locations[x][y]
				qcm_display_bar(x*4, y*4, ((x+1) * 4) - 1, ((y+1) * 4) - 1, boxes[temp].r, boxes[temp].g, boxes[temp].b)
			}
		}
	}
	
	qcm_display_write_framebuffer()
}
	
@timer4() <box_demo>
{
	new x, y, random_move, temp
	
	
	/* find blank */
	for (x = 0; x < 14; x++)
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
					if (x < 13)
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

input_switch_right_debouncce() <box_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

input_switch_left_debouncce() <box_demo>
{
	qcm_timer_stop(TIMER_4)
	selected_item = 0;
	show_menu()
}

/******************************************************************************
 * Blox Demo
 *****************************************************************************/
new speed
new bool:board[28][4]
#define COORDINATE [.x, .y]
new new_blox[COORDINATE]

blox_demo()
{
	new x, y
	
	speed = 50
	state blox_demo
	
	qcm_timer_start(TIMER_4,speed,true)
	qcm_display_clear()
	qcm_display_write_framebuffer()
	
	for (x = 0; x < 28; x++)
	{
		for (y = 0; y < 4; y++)
		{
			board[x][y] = false
		}
	}
	
	new_blox.x = 0
	new_blox.y = 1	
	
	render_board()
}

render_board()
{
	new x, y
	
	qcm_display_clear()
	
	/* render existing stack */
	for (x = 0; x < 28; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (board[x][y])
			{
				qcm_display_bar(x*2, y*2, ((x+1) * 2) - 1, ((y+1) * 2) - 1, 0, 0xF, 0xF)
			}
		}
	}
	
	/* render new_blox */
	qcm_display_bar(new_blox.x*2, new_blox.y*2, ((new_blox.x+1) * 2) - 1, ((new_blox.y+1) * 2) - 1, 0xF, 0, 0xF)
	
	qcm_display_write_framebuffer()
		
}

@timer4() <blox_demo>
{
	new x, y
	new bool:line_full
	
	new_blox.x++
	
	if (new_blox.x == 27)
	{
		/* new_blox has hit the bottom */
		board[27][new_blox.y] = true
		
		/* check to see if the line is full */
		line_full = true
		for (y = 0; y < 4; y++)
		{
			if (board[27][y] != true)
			{
				line_full = false
			}
		}
		
		if (line_full)
		{
			/* shift board down */
			for (x = 26; x >= 0; x--)
			{
				for (y = 0; y < 4; y++)
				{
					board[x + 1][y] = board[x][y]
				}
			}
		}
		
		new_blox.x = 0
		new_blox.y = 1
		
	}
	else if (board[new_blox.x + 1][new_blox.y])
	{
		/* blox has landed above existing blox */
		board[new_blox.x][new_blox.y] = true
		
		/* check to see if the line is full */
		line_full = true
		for (y = 0; y < 4; y++)
		{
			if (board[new_blox.x][y] != true)
			{
				line_full = false
			}
		}
		
		if (line_full)
		{
			/* shift board down */
			for (x = 26; x >= 0; x--)
			{
				for (y = 0; y < 4; y++)
				{
					board[x + 1][y] = board[x][y]
				}
			}
		}
		
		new_blox.x = 0
		new_blox.y = 1
		
	}
	
	if (board[1][1] == true)
	{		
		qcm_display_clear()
		qcm_display_write_text(0, 0, 0xF, 0xF, 0xF, "Game over")
		qcm_display_write_framebuffer()
		sleep 2000
		selected_item = 0;
		show_menu()
	}
	else
	{
		render_board()
	}
	
}

input_switch_right_debouncce() <blox_demo>
{
	new_blox.y++
	
	if (new_blox.y > 3)
	{
		new_blox.y = 3
	}
	
	render_board()
	
}

input_switch_left_debouncce() <blox_demo>
{
	new_blox.y--
	
	if (new_blox.y < 0)
	{
		new_blox.y = 0
	}
	
	render_board()
}


/******************************************************************************
 * Default state handlers
 *****************************************************************************/

input_switch_left_debouncce() <>
{

}

input_switch_right_debouncce() <>
{

}

@timer4() <>
{

}

/******************************************************************************
 * Switch debounce routines
 *****************************************************************************/
@gpio_input_switch_left()
{
    /* start debounce timer */
	printf("Left\n")
    qcm_timer_start(TIMER_2,50,false)
}

@gpio_input_switch_right()
{
    /* start debounce timer */
	printf("Right\n")
    qcm_timer_start(TIMER_3,50,false)
}

@timer2()
{
    if (qcm_gpio_get_input(GPIO_INPUT_SWITCH_LEFT))
    {
        /* button has been released - call new function to handle debounced input */
        printf("Left\n")
		input_switch_left_debouncce()
    }
}

@timer3()
{
    if (qcm_gpio_get_input(GPIO_INPUT_SWITCH_RIGHT))
    {
        /* button has been released - call new function to handle debounced input */
       
		input_switch_right_debouncce()
    }
}

/******************************************************************************
 * Main routine (initilization)
 *****************************************************************************/
main()
{
	sleep 1000

	state menu
	
	qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_LEFT, GPIO_EVENT_HIGH)
	qcm_gpio_configure_handler(GPIO_INPUT_SWITCH_RIGHT, GPIO_EVENT_HIGH)
	
	show_menu()
	
}
