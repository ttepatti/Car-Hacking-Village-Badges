/******************************************************************************
 * @file
 *
 * Copyright 2014-2019 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 *
 * @brief OLED management routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "oled.h"
#include "i2c.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/
#define OLED_I2C_ADDR (0x3C)

/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
static uint8_t frame_buffer[128 * (64 / 8)];
static BOOL buffer_modified;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
static void i2c_send_command(uint8_t const command)
{
	i2c_write(OLED_I2C_ADDR, 0x00, 1, &command, 1);
}


void oled_init(void)
{
    gpio_pin_config_t pin_config = {
        kGPIO_DigitalOutput, 0,
    };

	port_pin_config_t port_config = {
		kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
		kPORT_OpenDrainDisable, kPORT_HighDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister
	};

    /* init gpio pins */
	PORT_SetPinConfig(PORTB, 9, &port_config);
    GPIO_PinInit(GPIOB, 9, &pin_config);
    PORT_SetPinConfig(PORTB, 7, &port_config);
    GPIO_PinInit(GPIOB, 7, &pin_config);
    PORT_SetPinConfig(PORTB, 8, &port_config);
    GPIO_PinInit(GPIOB, 8, &pin_config);

    port_config.openDrainEnable = kPORT_OpenDrainEnable;

    PORT_SetPinConfig(PORTB, 10, &port_config);
    pin_config.outputLogic = 1;
    GPIO_PinInit(GPIOB, 10, &pin_config);

    /* Assert VDD */
    GPIO_PinWrite(GPIOB, 9, 1);

    vTaskDelay(OS_MS_TO_TICKS(50));

    /* de-assert reset */
    GPIO_PinWrite(GPIOB, 8, 1);

    vTaskDelay(OS_MS_TO_TICKS(50));

    /* panel off */
    i2c_send_command(0xAE);

	/* set addressing mode */
    i2c_send_command(0x00);

    i2c_send_command(0x10);

    i2c_send_command(0x40);


    i2c_send_command(0x20);
    i2c_send_command(0x00);


	/* set position */
    i2c_send_command(0x21);
    i2c_send_command(0);
    i2c_send_command(127);

	/* contrast control */
	i2c_send_command(0x81);
	i2c_send_command(0x7F);

	/* segment remap */
	i2c_send_command(0xA1);

	/* normal display */
	i2c_send_command(0xA6);

	/* multiplex ratio */
	i2c_send_command(0xA8);
	i2c_send_command(0x3F);

	/* display clock */
	i2c_send_command(0xD3);
	i2c_send_command(0x00);

	i2c_send_command(0xD5);
	i2c_send_command(0x80);



	/* pre-charge */
	//i2c_send_command(0xD9);
	//i2c_send_command(0xF1);

	/* com pins */
	//i2c_send_command(0xDA);
	//i2c_send_command(0x12);


	/* vcomh */
	//i2c_send_command(0xDB);
	//i2c_send_command(0x30);

    oled_clear();
    oled_write_framebuffer();

    /* Assert VBAT */
    GPIO_PinWrite(GPIOB, 10, 0);

    vTaskDelay(OS_MS_TO_TICKS(50));

    /* charge pump enable */
	i2c_send_command(0x8D);
	i2c_send_command(0x14);

	/* panel on */
    i2c_send_command(0xAF);

}

void oled_write_framebuffer(void)
{
    if (!buffer_modified)
    {
        return;
    }

    i2c_write(OLED_I2C_ADDR, 0x40, 1, frame_buffer, sizeof(frame_buffer));

    buffer_modified = FALSE;
}

void oled_put_pixel(uint8_t const x, uint8_t const y)
{
    int temp_y;
    int bit_y;
    int new_y;

    /* remap y to be at top left */
    new_y = 63 - y;

    /* figure out location in frame buffer, given 1bpp */
    temp_y = new_y / 8;

    bit_y = new_y - (temp_y * 8);

    frame_buffer[x + (128 * temp_y)] |=  (1 << (bit_y));

    buffer_modified = TRUE;
}

void oled_clear(void)
{
    unsigned long i;

    for(i = 0; i < (128 * (64 / 8)); i++)
    {
        frame_buffer[i] = 0x00;
    }

    buffer_modified = TRUE;
}

