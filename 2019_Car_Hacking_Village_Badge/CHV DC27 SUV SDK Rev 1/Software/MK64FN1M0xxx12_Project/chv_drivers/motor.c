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
 * @brief Motor driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>
#include "fsl_common.h"
#include "fsl_ftm.h"

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
void motor_init(void)
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;

	/* Configure ftm params with frequency 24kHZ */
	ftmParam.chnlNumber            = 3;
	ftmParam.level                 = kFTM_NoPwmSignal;
	ftmParam.dutyCyclePercent      = 0;
	ftmParam.firstEdgeDelayPercent = 0;

	FTM_GetDefaultConfig(&ftmInfo);
	/* Initialize FTM module */
	FTM_Init(FTM0, &ftmInfo);
	FTM_SetupPwm(FTM0, &ftmParam, 1U, kFTM_CenterAlignedPwm, 400, CLOCK_GetFreq(kCLOCK_McgFixedFreqClk));
	ftmParam.chnlNumber = 4;
	FTM_SetupPwm(FTM0, &ftmParam, 1U, kFTM_CenterAlignedPwm, 400, CLOCK_GetFreq(kCLOCK_McgFixedFreqClk));

	/* use 375kHz clock */
	FTM_StartTimer(FTM0, kFTM_FixedClock);


}

void motor_set_speed(int8_t const speed)
{
	int duty;

	/* speed is -5 to 5, inclusive.  0 indicates stopped
	 * Motor speed updates must occur every 200ms or motor will stop
	 *
	 */

	if (speed == 0)
	{
		/* Disable channel output before updating the dutycycle */
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 3, kFTM_NoPwmSignal);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 4, kFTM_NoPwmSignal);
		FTM_UpdatePwmDutycycle(FTM0, 3, kFTM_CenterAlignedPwm, 0);
		FTM_UpdatePwmDutycycle(FTM0, 4, kFTM_CenterAlignedPwm, 0);
		FTM_SetSoftwareTrigger(FTM0, true);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 3, kFTM_HighTrue);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 4, kFTM_HighTrue);


	}
	else if (speed > 0)
	{
		duty = 20 * speed;
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 3, kFTM_NoPwmSignal);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 4, kFTM_NoPwmSignal);
		FTM_UpdatePwmDutycycle(FTM0, 3, kFTM_CenterAlignedPwm, duty);
		FTM_UpdatePwmDutycycle(FTM0, 4, kFTM_CenterAlignedPwm, 0);
		FTM_SetSoftwareTrigger(FTM0, true);
		/* Start channel output with updated dutycycle */
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 3, kFTM_HighTrue);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 4, kFTM_HighTrue);

	}
	else
	{
		duty = 20 * -speed;
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 3, kFTM_NoPwmSignal);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 4, kFTM_NoPwmSignal);
		FTM_UpdatePwmDutycycle(FTM0, 3, kFTM_CenterAlignedPwm, 0);
		FTM_UpdatePwmDutycycle(FTM0, 4, kFTM_CenterAlignedPwm, duty);
		FTM_SetSoftwareTrigger(FTM0, true);
		/* Start channel output with updated dutycycle */
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 3, kFTM_HighTrue);
		FTM_UpdateChnlEdgeLevelSelect(FTM0, 4, kFTM_HighTrue);
	}

}
