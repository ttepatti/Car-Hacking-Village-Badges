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
 * @brief Timer driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "fsl_common.h"
#include "fsl_lptmr.h"
#include "cmsis_gcc.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/
#define TIMER_TICK_MS (10)

#define DEMO_LPTMR_BASE LPTMR0
#define DEMO_LPTMR_IRQn LPTMR0_IRQn
#define LPTMR_LED_HANDLER LPTMR0_IRQHandler
/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
/* Define LPTMR microseconds counts value */
#define LPTMR_USEC_COUNT 1000000U
#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()
/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
static uint32_t _system_time = 0;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/

void LPTMR0_IRQHandler(void)
{
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
    _system_time += TIMER_TICK_MS;
    /*
     * Workaround for TWR-KV58: because write buffer is enabled, adding
     * memory barrier instructions to make sure clearing interrupt flag completed
     * before go out ISR
     */
    __DSB();
    __ISB();
}


void timer_init(void)
{
	lptmr_config_t lptmrConfig;

	/* Configure LPTMR */
	/*
	 * lptmrConfig.timerMode = kLPTMR_TimerModeTimeCounter;
	 * lptmrConfig.pinSelect = kLPTMR_PinSelectInput_0;
	 * lptmrConfig.pinPolarity = kLPTMR_PinPolarityActiveHigh;
	 * lptmrConfig.enableFreeRunning = false;
	 * lptmrConfig.bypassPrescaler = true;
	 * lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
	 * lptmrConfig.value = kLPTMR_Prescale_Glitch_0;
	 */
	LPTMR_GetDefaultConfig(&lptmrConfig);

	/* Initialize the LPTMR */
	LPTMR_Init(LPTMR0, &lptmrConfig);

	/*
	 * Set timer period.  Input clock is 1kHz, so each tick is 1ms.  Set to 1ms tick.
	 * Note : the parameter "ticks" of LPTMR_SetTimerPeriod should be equal or greater than 1.
	*/
	LPTMR_SetTimerPeriod(LPTMR0, 8);

	/* Enable timer interrupt */
	LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(LPTMR0_IRQn);

	/* Start counting */
	LPTMR_StartTimer(LPTMR0);
}

uint32_t timer_get_system_time(void)
{
	return _system_time;
}

void timer_delay(uint32_t const ms)
{
	uint32_t timeout;

	if (ms < TIMER_TICK_MS)
	{
		timeout = _system_time + 1;
	}
	else
	{
		timeout = _system_time + (ms / TIMER_TICK_MS);
	}

	while (timeout > _system_time)
	{
		/* go into low power mode */
		__WFI();
	}


}
