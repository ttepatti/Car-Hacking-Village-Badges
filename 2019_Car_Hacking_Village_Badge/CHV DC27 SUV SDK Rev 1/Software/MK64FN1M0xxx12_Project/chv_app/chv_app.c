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
 * @brief CHV Application routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "oled.h"
#include "graphics.h"
#include "led_graphics.h"
#include "encoder.h"
#include "i2c.h"
#include "oled.h"
#include "servo.h"
#include "motor.h"
#include "gpio.h"
#include "led.h"


/******************************************************************************
 * Macros and Constants
 *****************************************************************************/
#define MAX_STRING_SIZE (40)

/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Global Variables
 *****************************************************************************/
extern const tImage NXP;
extern const tImage rapid7;
extern const tImage eyes1;
extern const tImage eyes2;
extern const tImage eyes3;
extern const tImage eyes4;
extern const tImage eyes5;

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/

/* Must match led_graphics_pattern_t */
static const char *_menu_items[] =
{
		"Racer",
		"Bling",
		"Fade",
		"Police",
		"Fire",
		"EOL"
};

static uint8_t _current_menu_index = 0;
static uint32_t _eyes_timer = 30;
static uint8_t _eyes_state = 0;

static const tImage *_eyes[] =
{
	&eyes1,
	&eyes2,
	&eyes3,
	&eyes4,
	&eyes5
};

/******************************************************************************
 * Functions
 *****************************************************************************/


static void vCHVTask(void *pvParams)
{
	BOOL do_menu = FALSE;
	led_graphics_pattern_t current_pattern = LED_GRAPHICS_PATTERN_RACER;
	uint8_t menu_index;

	encoder_ui_direction_t encoder_ui;

	i2c_init();

	led_init();

	oled_init();


	graphics_draw_bitmap_mono(0, 16, &NXP);
	oled_write_framebuffer();


	motor_set_speed(5);
	vTaskDelay(OS_MS_TO_TICKS(500));
	motor_set_speed(-5);
	vTaskDelay(OS_MS_TO_TICKS(500));
	motor_set_speed(0);
	servo_set_position(-3);
	vTaskDelay(OS_MS_TO_TICKS(500));
	servo_set_position(3);
	vTaskDelay(OS_MS_TO_TICKS(500));
	servo_set_position(0);

	oled_clear();
	graphics_draw_bitmap_mono(0, 29, &rapid7);
	oled_write_framebuffer();
	vTaskDelay(OS_MS_TO_TICKS(2000));

	oled_clear();

	led_graphics_init();
	led_graphics_set_pattern(LED_GRAPHICS_PATTERN_FADE);

	while(1)
	{
		/* on button press go into menu */
		if (gpio_switch_get())
		{
			vTaskDelay(25);

			while (gpio_switch_get())
			{
				vTaskDelay(25);
			}

			if (!do_menu)
			{
				do_menu = TRUE;
				graphics_draw_menu(_menu_items, LED_GRAPHICS_PATTERN_COUNT, "Set Demo", _current_menu_index);
			}
			else
			{
				/* set the current light demo */
				led_graphics_set_pattern(_current_menu_index);
				do_menu = FALSE;
				oled_clear();
				graphics_draw_bitmap_mono(0, 16, _eyes[_eyes_state]);
				oled_write_framebuffer();
				_eyes_timer = 30;
			}
		}

		if (do_menu)
		{


			encoder_ui = encoder_ui_get();

			if (encoder_ui == ENCODER_UI_DIRECTION_CW)
			{
				_current_menu_index++;

				if (_current_menu_index >= LED_GRAPHICS_PATTERN_COUNT)
				{
					_current_menu_index = LED_GRAPHICS_PATTERN_COUNT - 1;
				}

				graphics_draw_menu(_menu_items, LED_GRAPHICS_PATTERN_COUNT, "Set Demo", _current_menu_index);

			}
			else if (encoder_ui == ENCODER_UI_DIRECTION_CCW)
			{
				_current_menu_index--;

				if (_current_menu_index >= LED_GRAPHICS_PATTERN_COUNT)
				{
					_current_menu_index = 0;
				}

				graphics_draw_menu(_menu_items, LED_GRAPHICS_PATTERN_COUNT, "Set Demo", _current_menu_index);
			}


		}
		else
		{
			_eyes_timer--;

			if (_eyes_timer == 0)
			{
				_eyes_timer = 30;

				_eyes_state++;

				if (_eyes_state >= 5)
				{
					_eyes_state = 0;
				}

				oled_clear();
				graphics_draw_bitmap_mono(0, 16, _eyes[_eyes_state]);
				oled_write_framebuffer();
			}
		}

		vTaskDelay(OS_MS_TO_TICKS(100));

	}
}

void chv_app_init(void)
{
	/* start task */
	xTaskCreate(vCHVTask , ( signed portCHAR * ) TASK_APP_NAME, TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL);
}
