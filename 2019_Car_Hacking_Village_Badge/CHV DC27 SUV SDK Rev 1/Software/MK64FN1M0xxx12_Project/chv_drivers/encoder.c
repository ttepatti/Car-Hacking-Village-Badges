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
 * @brief Encoder driver routines
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
#include "encoder.h"


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
static uint32_t last_ui_count = 0;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
void encoder_init(void)
{
	 ftm_config_t ftmInfo;
	 ftm_phase_params_t phaseParamsConfigStruct;
	 gpio_pin_config_t pin_config = {
	        kGPIO_DigitalInput, 0,
	    };

		port_pin_config_t port_config = {
			kPORT_PullUp, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
			kPORT_OpenDrainDisable, kPORT_HighDriveStrength, kPORT_MuxAlt6, kPORT_UnlockRegister
		};

	/* init pins to have pullups */
	PORT_SetPinConfig(PORTB, 0, &port_config);
	GPIO_PinInit(GPIOB, 0, &pin_config);
	PORT_SetPinConfig(PORTB, 1, &port_config);
	GPIO_PinInit(GPIOB, 1, &pin_config);
	PORT_SetPinConfig(PORTA, 10, &port_config);
	GPIO_PinInit(GPIOA, 10, &pin_config);
	PORT_SetPinConfig(PORTA, 11, &port_config);
	GPIO_PinInit(GPIOA, 11, &pin_config);

	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = kFTM_Prescale_Divide_1;
	FTM_Init(FTM1, &ftmInfo);

	/* Set the modulo values for Quad Decoder. */
	FTM_SetQuadDecoderModuloValue(FTM1, 0U, ~0);

	/* Enable the Quad Decoder mode. */
	phaseParamsConfigStruct.enablePhaseFilter = true;
	phaseParamsConfigStruct.phaseFilterVal    = 1000U;
	phaseParamsConfigStruct.phasePolarity     = kFTM_QuadPhaseNormal;
	FTM_SetupQuadDecode(FTM1, &phaseParamsConfigStruct, /* Phase A. */
					 &phaseParamsConfigStruct,       /* Phase B. */
					 kFTM_QuadPhaseEncode);

	FTM_Init(FTM2, &ftmInfo);

	/* Set the modulo values for Quad Decoder. */
	FTM_SetQuadDecoderModuloValue(FTM2, 0U, 0xFFFFFFFF);

	/* Enable the Quad Decoder mode. */
	phaseParamsConfigStruct.enablePhaseFilter = true;
	phaseParamsConfigStruct.phaseFilterVal    = 1U;
	phaseParamsConfigStruct.phasePolarity     = kFTM_QuadPhaseNormal;
	FTM_SetupQuadDecode(FTM2, &phaseParamsConfigStruct, /* Phase A. */
					 &phaseParamsConfigStruct,       /* Phase B. */
					 kFTM_QuadPhaseEncode);

}

void encoder_ui_reset(void)
{
	FTM_ClearQuadDecoderCounterValue(FTM1);
}

void encoder_motor_reset(void)
{
	FTM_ClearQuadDecoderCounterValue(FTM2);
}

encoder_ui_direction_t encoder_ui_get(void)
{
	encoder_ui_direction_t ret_val = ENCODER_UI_DIRECTION_NONE;

	uint32_t cur_value = FTM_GetQuadDecoderCounterValue(FTM1);
	if (cur_value > last_ui_count)
	{
		ret_val = ENCODER_UI_DIRECTION_CW;
	}
	else if (cur_value < last_ui_count)
	{
		ret_val = ENCODER_UI_DIRECTION_CCW;
	}
	else
	{
		/* fall through */
	}

	last_ui_count = cur_value;
	return ret_val;

}

uint32_t encoder_motor_get(void)
{
	return FTM_GetQuadDecoderCounterValue(FTM2);
}
