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
 * @brief GPIO driver routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include <string.h>
#include "fsl_common.h"
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
void gpio_init(void)
{
	 gpio_pin_config_t pin_config = {
	        kGPIO_DigitalInput, 0,
	    };

		port_pin_config_t port_config = {
			kPORT_PullUp, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
			kPORT_OpenDrainDisable, kPORT_HighDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister
		};

	/* init pins to have pullups */
	PORT_SetPinConfig(PORTA, 29, &port_config);
	GPIO_PinInit(GPIOA, 29, &pin_config);

}

BOOL gpio_switch_get(void)
{
	return (GPIO_PinRead(GPIOA, 29) == 0);
}
