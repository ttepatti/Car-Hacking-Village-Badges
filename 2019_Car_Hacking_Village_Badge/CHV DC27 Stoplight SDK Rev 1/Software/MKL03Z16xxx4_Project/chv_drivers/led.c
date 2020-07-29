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
 * @brief LED driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "led.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_tpm.h"
#include "fsl_clock.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/
/* each timer tick is 2.048 ms */
#define ON_TICKS (1)
#define OFF_TICKS (5)

/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
static BOOL _led_states[7] = {0};
static BOOL _led_isr_states[7] = {0};
static uint8_t _led_isr_count[7] = {0};

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
static void set_state(led_t const led, BOOL const state)
{
	switch (led)
	{
		case LED_RED:
			GPIO_PinWrite(GPIOA, 7, !state);
			break;
		case LED_YELLOW:
			GPIO_PinWrite(GPIOA, 4, !state);
			break;
		case LED_GREEN:
			GPIO_PinWrite(GPIOA, 6, !state);
			break;
		case LED_RED_UV:
			GPIO_PinWrite(GPIOB, 0, !state);
			break;
		case LED_YELLOW_UV:
			GPIO_PinWrite(GPIOA, 3, !state);
			break;
		case LED_GREEN_UV:
			GPIO_PinWrite(GPIOA, 5, !state);
			break;
		case LED_CENTER_UV:
			GPIO_PinWrite(GPIOB, 1, !state);
			break;

		default:
			break;

	}

}

void TPM0_IRQHandler(void)
{
	int i;

	TPM_ClearStatusFlags(TPM0, kTPM_TimeOverflowFlag);

	for (i = 0; i < 7; i++)
	{
		if (_led_states[i] == TRUE)
		{
			if (_led_isr_states[i] == TRUE)
			{
				if (_led_isr_count[i] > 0)
				{
					_led_isr_count[i]--;
				}
				else if (_led_isr_count[i] == 0)
				{
					set_state(i, FALSE);
					_led_isr_count[i] = OFF_TICKS;
					_led_isr_states[i] = FALSE;
				}
			}

			if (_led_isr_states[i] == FALSE)
			{
				if (_led_isr_count[i] > 0)
				{
					_led_isr_count[i]--;
				}
				else if (_led_isr_count[i] == 0)
				{
					set_state(i, TRUE);
					_led_isr_count[i] = ON_TICKS;
					_led_isr_states[i] = TRUE;
				}
			}
		}
		else
		{
			set_state(i, FALSE);
		}
	}

#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void led_init(void)
{
	tpm_config_t tpmInfo;

	/* init all to off (active low) */
	GPIOA->PSOR = 0xF8;
	GPIOB->PSOR = 0x03;

	GPIOA->PDDR |= 0xF8;
	GPIOB->PDDR |= 0x03;

	/* set to MCGIRCLK (1Mhz) */
	CLOCK_SetTpmClock(3U);

	TPM_GetDefaultConfig(&tpmInfo);


	/* TPM clock divide by 128, so each tick is 128us */
	tpmInfo.prescale = kTPM_Prescale_Divide_128;

	/* Initialize TPM module */
	TPM_Init(TPM0, &tpmInfo);

	/* Set timer period at 16 ticks or 2.048ms */
	TPM_SetTimerPeriod(TPM0, 16);

	TPM_EnableInterrupts(TPM0, kTPM_TimeOverflowInterruptEnable);

	EnableIRQ(TPM0_IRQn);

	TPM_StartTimer(TPM0, kTPM_SystemClock);

}

void led_set_state(led_t const led, BOOL const state)
{
	_led_states[led] = state;
}

void led_all_off(void)
{
	int i;

	for (i = 0; i < 7; i++)
	{
		_led_states[i] = FALSE;
	}
}

