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
 * @brief ADC driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "fsl_common.h"
#include "fsl_adc16.h"

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
static uint32_t _conversion_result = 0;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/

void ADC0_IRQHandler(void)
{
    /* Read conversion result to clear the conversion completed flag. */
	_conversion_result = ADC16_GetChannelConversionValue(ADC0, 0);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}


void adc_init(void)
{
	adc16_config_t adc16ConfigStruct;
	adc16_channel_config_t adc16ChannelConfigStruct;

    ADC16_GetDefaultConfig(&adc16ConfigStruct);

    adc16ConfigStruct.enableContinuousConversion = true;

    ADC16_Init(ADC0, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */

    ADC16_DoAutoCalibration(ADC0);

    adc16ChannelConfigStruct.channelNumber = 8;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true;

    ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);

    EnableIRQ(ADC0_IRQn);
}

uint16_t adc_get_value(void)
{
	return _conversion_result;
}
