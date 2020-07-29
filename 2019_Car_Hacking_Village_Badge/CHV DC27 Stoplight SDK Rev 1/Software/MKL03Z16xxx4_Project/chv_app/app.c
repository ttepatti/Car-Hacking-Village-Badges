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
 * @brief Main application routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "accel.h"
#include "adc.h"
#include "timer.h"
#include "led.h"
#include "uart.h"
#include <math.h>
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
static uint8_t _mode = 0;
static uint32_t _timeout = 0;
static uint8_t _sub_mode = 0;
/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void stoplight_mode(void)
{
	switch(_sub_mode)
	{
		case 0:
			if (_timeout > 0)
			{
				_timeout--;
			}
			else
			{
				led_set_state(LED_GREEN, FALSE);
				led_set_state(LED_YELLOW, TRUE);
				_sub_mode = 1;
				_timeout = 400;
			}
			break;

		case 1:
			if (_timeout > 0)
			{
				_timeout--;
			}
			else
			{
				led_set_state(LED_YELLOW, FALSE);
				led_set_state(LED_RED, TRUE);
				_sub_mode = 2;
				_timeout = 1000;
			}
			break;

		case 2:
			if (_timeout > 0)
			{
				_timeout--;
			}
			else
			{
				led_set_state(LED_RED, FALSE);
				led_set_state(LED_GREEN, TRUE);
				_sub_mode = 0;
				_timeout = 1000;
			}
			break;

		default:
			_sub_mode = 0;
			led_all_off();
			break;
	}
}

static void blinky_mode(void)
{
	if (_timeout > 0)
		{
			_timeout--;
		}
		else
		{
			led_set_state(LED_RED, rand() % 2);
			led_set_state(LED_YELLOW, rand() % 2);
			led_set_state(LED_GREEN, rand() % 2);
			_timeout = 100;
		}
}



static void accel_mode(accel_data_t const * const accel_data)
{
	uint16_t abs_accel;

	if (accel_data->accel_x < 0)
	{
		abs_accel = -accel_data->accel_x;
	}
	else
	{
		abs_accel = 0;
	}

	/* three thresholds for magnitude */

	if (abs_accel < 6000)
	{
		led_all_off();
	}
	else if (abs_accel < (6000 + 50))
	{
		led_set_state(LED_GREEN, TRUE);
		led_set_state(LED_YELLOW, FALSE);
		led_set_state(LED_RED, FALSE);
	}
	else if (abs_accel < (6000 + 75))
	{
		led_set_state(LED_GREEN, TRUE);
		led_set_state(LED_YELLOW, TRUE);
		led_set_state(LED_RED, FALSE);
	}
	else
	{
		led_set_state(LED_GREEN, TRUE);
		led_set_state(LED_YELLOW, TRUE);
		led_set_state(LED_RED, TRUE);
	}
}

static void compass_mode(accel_data_t const * const accel_data)
{
	/* three thresholds as approaching north */
	double result;

	result = atan((double)(accel_data->magn_y)/(double)(accel_data->magn_x)) * 180.0 * 3.1416;

	if (result > 360.0)
	{
		result -= 360.0;
	}
	else if (result < 0.0)
	{
		result += 360.0;
	}

	if (result > 337.25)
	{
		if (result < 352.41)
		{
			/* yellow and red */
			led_set_state(LED_GREEN, FALSE);
			led_set_state(LED_YELLOW, TRUE);
			led_set_state(LED_RED, TRUE);
		}
		else
		{
			/* green, yellow, and red  */
			led_set_state(LED_GREEN, TRUE);
			led_set_state(LED_YELLOW, TRUE);
			led_set_state(LED_RED, TRUE);
		}
	}
	else if (result < 22.5)
	{
		if (result < 7.5)
		{
			/* green, yellow and red */
			led_set_state(LED_GREEN, TRUE);
			led_set_state(LED_YELLOW, TRUE);
			led_set_state(LED_RED, TRUE);
		}
		else
		{
			/* yellow and red */
			led_set_state(LED_GREEN, FALSE);
			led_set_state(LED_YELLOW, TRUE);
			led_set_state(LED_RED, TRUE);
		}
	}
	else
	{
		/* red */
		led_set_state(LED_GREEN, FALSE);
		led_set_state(LED_YELLOW, FALSE);
		led_set_state(LED_RED, TRUE);
	}


}

static void night_on_mode(void)
{
	/* turn all uv leds on */
	led_set_state(LED_RED_UV, TRUE);
	led_set_state(LED_YELLOW_UV, TRUE);
	led_set_state(LED_GREEN_UV, TRUE);
	led_set_state(LED_CENTER_UV, TRUE);
}

static void night_blinky_mode(void)
{
	if (_timeout > 0)
		{
			_timeout--;
		}
		else
		{
			led_set_state(LED_RED_UV, rand() % 2);
			led_set_state(LED_YELLOW_UV, rand() % 2);
			led_set_state(LED_GREEN_UV, rand() % 2);
			led_set_state(LED_CENTER_UV, rand() % 2);
			_timeout = 100;
		}
}

static void night_accel_mode(accel_data_t const * const accel_data)
{
	/* three thresholds for magnitude */

	uint16_t abs_accel;

		if (accel_data->accel_x < 0)
		{
			abs_accel = -accel_data->accel_x;
		}
		else
		{
			abs_accel = 0;
		}


		if (abs_accel <= 6000)
		{
			led_all_off();
		}
		else if (abs_accel < (6000 + 50))
		{
			led_set_state(LED_RED_UV, FALSE);
			led_set_state(LED_YELLOW_UV, TRUE);
			led_set_state(LED_GREEN_UV, FALSE);
			led_set_state(LED_CENTER_UV, FALSE);
		}
		else if (abs_accel < (6000 + 75))
		{
			led_set_state(LED_RED_UV, FALSE);
			led_set_state(LED_YELLOW_UV, TRUE);
			led_set_state(LED_GREEN_UV, FALSE);
			led_set_state(LED_CENTER_UV, TRUE);
		}
		else
		{
			led_set_state(LED_RED_UV, TRUE);
			led_set_state(LED_YELLOW_UV, TRUE);
			led_set_state(LED_GREEN_UV, TRUE);
			led_set_state(LED_CENTER_UV, TRUE);
		}

}

static void blink_mode(uint8_t const mode)
{
	int i;

	for (i = 0; i <= mode; i++)
	{
		led_set_state(LED_YELLOW, FALSE);
		timer_delay(1000);
		led_set_state(LED_YELLOW, TRUE);
		timer_delay(1000);
	}

	led_set_state(LED_YELLOW, FALSE);

}
void app_main(void)
{
	accel_data_t accel_data;
	BOOL tap_event;

	/* quick EOL test */
	led_set_state(LED_YELLOW, TRUE);
	timer_delay(500);
	led_set_state(LED_RED, TRUE);
	timer_delay(500);

	led_set_state(LED_YELLOW, FALSE);
	led_set_state(LED_RED, FALSE);

	led_set_state(LED_RED_UV, TRUE);
	led_set_state(LED_YELLOW_UV, TRUE);
	led_set_state(LED_GREEN_UV, TRUE);
	led_set_state(LED_CENTER_UV, TRUE);
	timer_delay(500);

	led_set_state(LED_RED_UV, FALSE);
	led_set_state(LED_YELLOW_UV, FALSE);
	led_set_state(LED_GREEN_UV, FALSE);
	led_set_state(LED_CENTER_UV, FALSE);


	while(FALSE == accel_process(&accel_data, &tap_event))
	{
		led_set_state(LED_YELLOW,TRUE);
		timer_delay(50);
		led_set_state(LED_YELLOW,FALSE);
		timer_delay(50);
	}

	led_set_state(LED_GREEN, TRUE);
	timer_delay(500);
	led_set_state(LED_GREEN, FALSE);




	/*
	 * The following modes are controlled by the accel tap function:
	 *
	 * Standard stoplight timer based
	 * accel detection mode
	 * north detection mode
	 * RF detectction mode
	 * Night on mode
	 * Night blinky mode
	 * Night accel threshold mode (for dancing)
	 *
	 * The leds will blink with the selected mode when it changes.  Number of blinks
	 * shows the mode number (in order with the above list)
	 */
	while(1)
	{
		if (TRUE == accel_process(&accel_data, &tap_event))
		{
			if (tap_event)
			{
				_mode++;
				_timeout = 0;
				if (_mode > 5)
				{
					_mode = 0;
				}
				led_all_off();
				blink_mode(_mode);
			}
		}

		switch(_mode)
		{
			case 0:
				stoplight_mode();
				break;
			case 1:
				blinky_mode();
				break;
			case 2:
				accel_mode(&accel_data);
				break;
			case 3:
				night_on_mode();
				break;
			case 4:
				night_blinky_mode();
				break;
			case 5:
				night_accel_mode(&accel_data);
				break;
			default:
				_mode = 0;
				break;

		}

		/* 10ms loop */
		timer_delay(5);
	}

}
