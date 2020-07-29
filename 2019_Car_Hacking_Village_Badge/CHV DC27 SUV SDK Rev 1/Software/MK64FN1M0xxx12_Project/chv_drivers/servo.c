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
 * @brief Servo driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>
#include "fsl_common.h"
#include "fsl_ftm.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

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
/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void servo_init(void)
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;
	gpio_pin_config_t pin_config = {
		kGPIO_DigitalOutput, 0,
	};

	port_pin_config_t port_config = {
		kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
		kPORT_OpenDrainEnable, kPORT_HighDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister
	};

	/* Configure ftm params with frequency 50HZ */
	ftmParam.chnlNumber            = 5;
	ftmParam.level                 = kFTM_HighTrue;
	ftmParam.dutyCyclePercent      = 0;
	ftmParam.firstEdgeDelayPercent = 0;

	FTM_GetDefaultConfig(&ftmInfo);
	/* Initialize FTM module */
	FTM_Init(FTM3, &ftmInfo);

	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50, CLOCK_GetFreq(kCLOCK_McgFixedFreqClk));

	/* servo is center at 1.5ms pulse of 50Hz frequency, 1ms is -90, 2 ms is +90, timebase is 7500 ticks per
	 * cycle.  So .001/.02*7500 = 375 , .0015/.02*7500 = 563, .002/.02*7500 = 750
	 *
	 * Maximum travel on badge is about +-45 degrees.  So max is 1.25ms/1.75ms or 468 to 656.
	 */
	FTM_UpdatePwmDutycycle(FTM3, 5, kFTM_EdgeAlignedPwm, 0);
	FTM3->CONTROLS[5].CnV = 563;
	FTM_SetSoftwareTrigger(FTM3, true);
	/* Start channel output with updated dutycycle */
	FTM_UpdateChnlEdgeLevelSelect(FTM3, 5, kFTM_HighTrue);

	FTM_StartTimer(FTM3, kFTM_FixedClock);

	/* turn off PSAVE on the 17C724 */
    GPIO_PinInit(GPIOA, 8, &pin_config);
    PORT_SetPinConfig(PORTA, 8, &port_config);


}

void servo_set_position(int8_t const position)
{
		/* position is -3 to 3, inclusive.  0 indicates straight, negative values indicate left, positive right.
	 * Position updates must occur every 200ms or servo will default to straight.
	 */
	FTM_UpdateChnlEdgeLevelSelect(FTM3, 5, kFTM_NoPwmSignal);

	switch (position)
	{
		case -1:
			FTM3->CONTROLS[5].CnV = 563 - 31;
			break;

		case -2:
			FTM3->CONTROLS[5].CnV = 563 - 31 - 31;
			break;

		case -3:
			FTM3->CONTROLS[5].CnV = 563 - 31 - 31 -31;
			break;

		case 1:
			FTM3->CONTROLS[5].CnV = 563 + 31;
			break;

		case 2:
			FTM3->CONTROLS[5].CnV = 563 + 31 + 31;
			break;

		case 3:
			FTM3->CONTROLS[5].CnV = 563 + 31 + 31 + 31;
			break;

		case 0:
		default:
			FTM3->CONTROLS[5].CnV = 563;
			break;
	}

	FTM_SetSoftwareTrigger(FTM3, true);
	/* Start channel output with updated dutycycle */
	FTM_UpdateChnlEdgeLevelSelect(FTM3, 5, kFTM_HighTrue);

}
