/******************************************************************************
 * @file
 *
 * Copyright 2017-2018 Specialized Solutions LLC
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
#include <string.h>
#include "fsl_common.h"
#include "fsl_pit.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/
#define PIN_MR_SET (GPIOA->PSOR = (1 << 28))
#define PIN_MR_CLEAR (GPIOA->PCOR = (1 << 28))

#define PIN_SHCP_SET (GPIOA->PSOR = (1 << 27))
#define PIN_SHCP_CLEAR (GPIOA->PCOR = (1 << 27))

#define PIN_STCP_SET (GPIOA->PSOR = (1 << 26))
#define PIN_STCP_CLEAR (GPIOA->PCOR = (1 << 26))

#define PIN_OE_SET (GPIOA->PSOR = (1 << 25))
#define PIN_OE_CLEAR (GPIOA->PCOR = (1 << 25))

#define PIN_DATA_SET (GPIOA->PSOR = (1 << 24))
#define PIN_DATA_CLEAR (GPIOA->PCOR = (1 << 24))

#define PULSE_DURATION_CYCLES (50)

#define ROW_TICK_US (200)
/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
/* RGB's organized as 8 columns of 5 rows of RGB -
 * Row 1 - Driver Side (1 front, 8 rear)
 * Row 2 - Passenger Side (1 front, 8 rear)
 * Row 3 - Passenger Side Top (1 front, 8 rear)
 * Row 4 - Driver Side Top (1 front, 8 rear)
 * Row 5 - Rear (1,2 driver encoder side, 3,4 driver tail light, 5,6 passenger encoder, 7,8 passenger tail light
 *
 * Headlights are driver and passenger
 * Reverse Lights are tied together
 *
 */

/* buffer is organized as 8-bit words representing the color intensity for BRG for all 5 rows (in order of PORTD usage - see schematic)
 */
static uint8_t _framebuffer[8*15];
static uint8_t _row_buffer[15];
static uint8_t _column_index;
static uint8_t _row_tick;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/

static inline void delay(void)
{
    volatile int i = 0;

    for (i = 0; i < PULSE_DURATION_CYCLES; i++);
}

static inline void delay_fast(void)
{
    volatile int i = 0;

    for (i = 0; i < 5; i++);
}


static inline void reset_rows(void)
{
	GPIOD->PCOR = 0x7FFF;
}


void led_init( void )
{
    int i;
    pit_config_t pitConfig;

    gpio_pin_config_t pin_config = {
           kGPIO_DigitalOutput, 0,
       };

   	port_pin_config_t port_config = {
   		kPORT_PullDisable, kPORT_FastSlewRate, kPORT_PassiveFilterDisable,
   		kPORT_OpenDrainDisable, kPORT_HighDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister
   	};

    /* init gpio pins for latch */
    GPIO_PinInit(GPIOA, 24, &pin_config);
	GPIO_PinInit(GPIOA, 25, &pin_config);
	GPIO_PinInit(GPIOA, 26, &pin_config);
	GPIO_PinInit(GPIOA, 27, &pin_config);
	GPIO_PinInit(GPIOA, 28, &pin_config);
   	PORT_SetPinConfig(PORTA, 24, &port_config);
   	PORT_SetPinConfig(PORTA, 25, &port_config);
   	PORT_SetPinConfig(PORTA, 26, &port_config);
   	PORT_SetPinConfig(PORTA, 27, &port_config);
   	PORT_SetPinConfig(PORTA, 28, &port_config);


    /* configure all row drivers for RGB's */
    PORT_SetMultiplePinsConfig(PORTD, 0x7FFF, &port_config);
    GPIOD->PCOR = 0x7FFF;
    GPIOD->PDDR = 0x7FFF;

    /* configure Headlights */
    GPIO_PinInit(GPIOE, 7, &pin_config);
    GPIO_PinInit(GPIOE, 26, &pin_config);

    PORT_SetPinConfig(PORTE, 7, &port_config);
    PORT_SetPinConfig(PORTE, 26, &port_config);

    /* configure reverse lights */
    GPIO_PinInit(GPIOB, 11, &pin_config);
    PORT_SetPinConfig(PORTB, 11, &port_config);

    memset(_framebuffer, 0x00, sizeof(_framebuffer));
    memcpy(_row_buffer, &(_framebuffer[0]), sizeof(_row_buffer));
    _column_index = 0;
    _row_tick = 0;

    /* load the latches with ones */
    delay();
    PIN_MR_SET;
    delay();
    PIN_DATA_SET;
    delay();

    for (i = 0; i < 8; i++)
    {
        PIN_SHCP_SET;
        delay();
        PIN_SHCP_CLEAR;
        delay();

    }

    delay();
    PIN_STCP_SET;
    delay();
    PIN_STCP_CLEAR;

    PIT_GetDefaultConfig(&pitConfig);
	/* Init pit module */
	PIT_Init(PIT, &pitConfig);

	/* Set timer period for channel 0 */
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(ROW_TICK_US, CLOCK_GetFreq(kCLOCK_BusClk))); /* Sample rate ~390.625us */

	/* Enable timer interrupts for channel 0 */
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(PIT0_IRQn);

	PIT_StartTimer(PIT, kPIT_Chnl_0);

}


static void reset_columns(void)
{
    /* shift a 0 into the first column */
    PIN_DATA_CLEAR;
    delay_fast();
    PIN_SHCP_SET;
    delay_fast();
    PIN_SHCP_CLEAR;
    PIN_STCP_SET;
    delay_fast();
    PIN_STCP_CLEAR;
    PIN_DATA_SET;



}

static void shift_column(void)
{
    PIN_SHCP_SET;
    delay_fast();
    PIN_SHCP_CLEAR;
    delay_fast();
    PIN_STCP_SET;
    delay_fast();
    PIN_STCP_CLEAR;
}


/* PIT channel 0 controls the column on times (each column is segmented into 16 levels to PWM the LED's at different
 * brightnesses
 */
void PIT0_IRQHandler(void)
{
	int i;
	uint16_t state = 0;

	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);

	if (_row_tick >= 15)
	{
		_row_tick = 0;
		memcpy(_row_buffer, &(_framebuffer[_column_index*15]), sizeof(_row_buffer));
		_column_index++;
		if (_column_index > 7)
		{
			_column_index = 0;
			reset_columns();
		}
		else
		{
			shift_column();
		}
	}

	/* decrement counters */
	for (i = 0; i < 15; i++)
	{
		state >>= 1;
		if ((_row_buffer[i] > 0) && (_row_buffer[i] < 16))
		{
			state |= 0x8000;
		}
		_row_buffer[i]--;
	}

	/* use bits 0-14 for port D */
	state >>= 1;

	/* write state to PORTD */
	GPIOD->PCOR = ~state & 0x7FFF;
	GPIOD->PSOR = state & 0x7FFF;

	_row_tick++;

exit:

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif

}

uint8_t *led_get_framebuffer_address(void)
{
    return _framebuffer;
}

void led_set_led(uint8_t const x, uint8_t const y, uint8_t const red, uint8_t const blue, uint8_t const green)
{
	/* LED's are organized as a 5x8 array */
	_framebuffer[(x*15) + (y * 3)] = blue;
	_framebuffer[(x*15) + (y * 3) + 1] = red;
	_framebuffer[(x*15) + (y * 3) + 2] = green;
}

void led_set_driver_headlight(BOOL const state)
{
	GPIO_PinWrite(GPIOE, 26, state);
}

void led_set_passenger_headlight(BOOL const state)
{
	GPIO_PinWrite(GPIOE, 7, state);
}

void led_set_reverse_lights(BOOL const state)
{
	GPIO_PinWrite(GPIOB, 11, state);
}

void led_all_off(void)
{
	led_set_driver_headlight(FALSE);
	led_set_passenger_headlight(FALSE);
	led_set_reverse_lights(FALSE);
	memset(_framebuffer, 0, sizeof(_framebuffer));
}
