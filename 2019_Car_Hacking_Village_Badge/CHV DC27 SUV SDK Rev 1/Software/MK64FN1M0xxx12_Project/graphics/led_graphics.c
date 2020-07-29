/******************************************************************************
 * @file
 *
 * Copyright 2019 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * @brief CHV LED routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>
#include "led.h"
#include "led_graphics.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/


/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
static led_graphics_pattern_t selected_pattern = LED_GRAPHICS_PATTERN_EOL;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
static void color_fade_next(uint8_t * const red, uint8_t * const blue, uint8_t * const green)
{
	static int8_t _red = 14;
	static int8_t _blue = 7;
	static int8_t _green = 1;
	static int8_t _red_dir = -1;
	static int8_t _blue_dir = -1;
	static int8_t _green_dir = 1;

	_red += _red_dir;
	_green += _green_dir;
	_blue += _blue_dir;

	if ((_red >= 15) || (_red <= 0))
	{
		_red_dir = -_red_dir;
	}

	if ((_blue >= 15) || (_blue <= 0))
	{
		_blue_dir = -_blue_dir;
	}

	if ((_green >= 15) || (_green <= 0))
	{
		_green_dir = -_green_dir;
	}

	*red = _red;
	*blue = _blue;
	*green = _green;
}


static void run_racer(void)
{
	static uint32_t index = 0;
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	int y;

	led_all_off();
	color_fade_next(&red, &blue, &green);

	index++;

	if (index >= 8)
	{
		index = 0;
	}

	for (y = 0; y < 5; y++)
	{
		led_set_led(index, y, red, green, blue);
	}

	vTaskDelay(OS_MS_TO_TICKS(50));

}

static void run_bling(void)
{
	/* choose randoms that blink white */
	int i;
	int x, y;


	/* turn on some randoms */
	for (i = 0; i < 20; i++)
	{
		x = rand() % 5;
		y = rand() % 8;

		led_set_led(x, y, 15, 15, 15);

	}

	if (rand() % 2)
	{
		led_set_driver_headlight(TRUE);
	}


	if (rand() % 2)
	{
		led_set_passenger_headlight(TRUE);
	}

	if (rand() % 2)
	{
		led_set_reverse_lights(TRUE);
	}

	vTaskDelay(OS_MS_TO_TICKS(5));

	/* turn off all */
	led_all_off();

	vTaskDelay(OS_MS_TO_TICKS(100));


}

static void run_fade(void)
{
	uint8_t red, green, blue;
	int x, y;

	color_fade_next(&red, &blue, &green);

	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 5; y++)
		{
			led_set_led(x, y, red, green, blue);
		}
	}

	vTaskDelay(OS_MS_TO_TICKS(100));
}

static void run_police(void)
{
	/* alternate red and blue flashing of all 8 on top, the front/rear sides, and the tail light rgbs */
	int x, y;

	/* tops on pattern A */
	for (x = 0; x < 8; x++)
	{
		led_set_led(x,0, 15, 0, 0);
		led_set_led(x,2, 15, 0, 0);
		led_set_led(x,1, 0, 15, 0);
		led_set_led(x,3, 0, 15, 0);
		led_set_led(x,4, 0, 15, 0);
	}

	led_set_reverse_lights(FALSE);
	led_set_driver_headlight(TRUE);
	led_set_passenger_headlight(FALSE);

	vTaskDelay(OS_MS_TO_TICKS(5));

		led_set_reverse_lights(FALSE);
		led_set_driver_headlight(FALSE);
		led_set_passenger_headlight(FALSE);

	vTaskDelay(OS_MS_TO_TICKS(45));

	led_set_reverse_lights(FALSE);
		led_set_driver_headlight(TRUE);
		led_set_passenger_headlight(FALSE);

		vTaskDelay(OS_MS_TO_TICKS(5));

			led_set_reverse_lights(FALSE);
			led_set_driver_headlight(FALSE);
			led_set_passenger_headlight(FALSE);

		vTaskDelay(OS_MS_TO_TICKS(45));

	/* all off */
	led_all_off();



	/* tops on pattern B */
	for (x = 0; x < 8; x++)
	{
		led_set_led(x,1, 15, 0, 0);
		led_set_led(x,3, 15, 0, 0);
		led_set_led(x,0, 0, 15, 0);
		led_set_led(x,2, 0, 15, 0);
		led_set_led(x,4, 15, 0, 0);
	}

	led_set_reverse_lights(TRUE);
	led_set_driver_headlight(FALSE);
	led_set_passenger_headlight(TRUE);

	vTaskDelay(OS_MS_TO_TICKS(5));

		led_set_reverse_lights(FALSE);
		led_set_driver_headlight(FALSE);
		led_set_passenger_headlight(FALSE);

	vTaskDelay(OS_MS_TO_TICKS(45));

	led_set_reverse_lights(TRUE);
		led_set_driver_headlight(FALSE);
		led_set_passenger_headlight(TRUE);

		vTaskDelay(OS_MS_TO_TICKS(5));

			led_set_reverse_lights(FALSE);
			led_set_driver_headlight(FALSE);
			led_set_passenger_headlight(FALSE);


			vTaskDelay(OS_MS_TO_TICKS(45));

	/* all off */
	led_all_off();
}

static void run_fire(void)
{
	/* alternate red and white flashing of all 8 on top, the front/rear sides, and the tail light rgbs */
	int x, y;

	/* tops on pattern A */
	for (x = 0; x < 8; x++)
	{
		led_set_led(x,0, 15, 0, 0);
		led_set_led(x,2, 15, 0, 0);
		led_set_led(x,1, 15, 15, 15);
		led_set_led(x,3, 15, 15, 15);
		led_set_led(x,4, 15, 15, 15);
	}


	led_set_reverse_lights(FALSE);
	led_set_driver_headlight(TRUE);
	led_set_passenger_headlight(FALSE);

	vTaskDelay(OS_MS_TO_TICKS(5));

		led_set_reverse_lights(FALSE);
		led_set_driver_headlight(FALSE);
		led_set_passenger_headlight(FALSE);

	vTaskDelay(OS_MS_TO_TICKS(100));

	/* tops on pattern B */
	for (x = 0; x < 8; x++)
	{
		led_set_led(x,3, 15, 0, 0);
		led_set_led(x,2, 15, 15, 15);

		led_set_led(x,0, 15, 15, 15);
		led_set_led(x,2, 15, 15, 15);
		led_set_led(x,1, 15, 0,0);
		led_set_led(x,3, 15, 0,0);
		led_set_led(x,4, 15, 0,0);

	}

	led_set_reverse_lights(TRUE);
	led_set_driver_headlight(FALSE);
	led_set_passenger_headlight(TRUE);

	vTaskDelay(OS_MS_TO_TICKS(5));

		led_set_reverse_lights(FALSE);
		led_set_driver_headlight(FALSE);
		led_set_passenger_headlight(FALSE);

	vTaskDelay(OS_MS_TO_TICKS(100));

}


static void run_eol(void)
{
	/* cycle red green blue white each row */
	int x, y;

	led_all_off();

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 8; x++)
		{
			led_set_led(x, y, 15, 0, 0);
		}
	}

	vTaskDelay(OS_MS_TO_TICKS(100));

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 8; x++)
		{
			led_set_led(x, y, 0, 15, 0);
		}
	}

	vTaskDelay(OS_MS_TO_TICKS(100));

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 8; x++)
		{
			led_set_led(x, y, 0, 0, 15);
		}
	}

	vTaskDelay(OS_MS_TO_TICKS(100));

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 8; x++)
		{
			led_set_led(x, y, 15, 15, 15);
		}
	}

	led_set_reverse_lights(TRUE);
	led_set_driver_headlight(TRUE);
	led_set_passenger_headlight(TRUE);
	vTaskDelay(OS_MS_TO_TICKS(100));
}

static void vLEDTask(void *pvParams)
{
	led_graphics_pattern_t current_pattern = LED_GRAPHICS_PATTERN_BLING;

	srand(0);

	while(1)
	{
		if (current_pattern != selected_pattern)
		{
			/* pattern changed */
			current_pattern = selected_pattern;
			led_all_off();
		}

		switch (current_pattern)
		{
		case LED_GRAPHICS_PATTERN_RACER:
			run_racer();
			break;
		case LED_GRAPHICS_PATTERN_BLING:
			run_bling();
			break;
		case LED_GRAPHICS_PATTERN_FADE:
			run_fade();
			break;
		case LED_GRAPHICS_PATTERN_POLICE:
			run_police();
			break;
		case LED_GRAPHICS_PATTERN_FIRE:
			run_fire();
			break;
		case LED_GRAPHICS_PATTERN_EOL:
			run_eol();
			break;

		}
	}
}

void led_graphics_init(void)
{
	/* start task */
	xTaskCreate(vLEDTask , ( signed portCHAR * ) TASK_LED_NAME, TASK_LED_STACK_SIZE, NULL, TASK_LED_PRIORITY, NULL);
}

void led_graphics_set_pattern(led_graphics_pattern_t const pattern)
{
	selected_pattern = pattern;
}
