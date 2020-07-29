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
 * @brief Accelerometer management routines
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "datatypes.h"
#include "accel.h"
#include "fsl_common.h"
#include "fsl_i2c.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "timer.h"

/******************************************************************************
 * Macros and Constants
 *****************************************************************************/
#define FXOS8700CQ_ADDR (0x1E)
#define FXOS8700CQ_STATUS 0x00
#define FXOS8700CQ_INT_SOURCE 0x0C
#define FXOS8700CQ_XYZ_DATA_CFG 0x0E
#define FXOS8700CQ_PULSE_SRC 0x22
#define FXOS8700CQ_CTRL_REG1 0x2A
#define FXOS8700CQ_CTRL_REG4 0x2D
#define FXOS8700CQ_CTRL_REG5 0x2E
#define FXOS8700CQ_M_CTRL_REG1 0x5B
#define FXOS8700CQ_M_CTRL_REG2 0x5C

/******************************************************************************
 * Typedefs
 *****************************************************************************/

/******************************************************************************
 * Local Function Prototypes
 *****************************************************************************/

/******************************************************************************
 * Local Variables
 *****************************************************************************/
static i2c_master_handle_t g_m_handle;
static volatile BOOL _completionFlag = FALSE;
static volatile BOOL _nakFlag = FALSE;
static volatile BOOL _accel_interrupt = FALSE;
static volatile BOOL _eol_pass = FALSE;

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
    	_completionFlag = TRUE;
    }
    /* Signal transfer success when received success status. */
    if ((status == kStatus_I2C_Nak) || (status == kStatus_I2C_Addr_Nak))
    {
    	_nakFlag = TRUE;
    }
}

static bool I2C_WriteAccelReg(I2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t value)
{
    i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    uint32_t timeout;

    masterXfer.slaveAddress = device_addr;
    masterXfer.direction = kI2C_Write;
    masterXfer.subaddress = reg_addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data = &value;
    masterXfer.dataSize = 1;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    /*  direction=write : start+device_write;cmdbuff;xBuff; */
    /*  direction=recive : start+device_write;cmdbuff;repeatStart+device_read;xBuff; */

    I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);

    /*  wait for transfer completed. */
    timeout = timer_get_system_time() + 100;

    while ((!_nakFlag) && (!_completionFlag) && (timeout > timer_get_system_time()))
    {
    	asm("NOP");
    }

    _nakFlag = FALSE;

    if (_completionFlag == true)
    {
    	_completionFlag = FALSE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static bool I2C_ReadAccelRegs(I2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t *rxBuff, uint32_t rxSize)
{
    uint32_t timeout;
	i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress = device_addr;
    masterXfer.direction = kI2C_Read;
    masterXfer.subaddress = reg_addr;
    masterXfer.subaddressSize = 1;
    masterXfer.data = rxBuff;
    masterXfer.dataSize = rxSize;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    /*  direction=write : start+device_write;cmdbuff;xBuff; */
    /*  direction=recive : start+device_write;cmdbuff;repeatStart+device_read;xBuff; */

    I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);

    /*  wait for transfer completed. */
    timeout = timer_get_system_time() + 100;

    while ((!_nakFlag) && (!_completionFlag) && (timeout > timer_get_system_time()))
	{
		asm("NOP");
	}

    _nakFlag = FALSE;

    if (_completionFlag == TRUE)
    {
    	_completionFlag = FALSE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* called periodically to handle accel events */
BOOL accel_process(accel_data_t * const accel_data, BOOL * const tap_event)
{
	BOOL ret_value = FALSE;
	uint8_t status;

	uint8_t data_buffer[13];

    if (_accel_interrupt)
    {
    	_accel_interrupt = FALSE;
    	*tap_event = FALSE;

    	/* get interrupt type */
    	status = 0xFF;

    	while (status != 0x00)
    	{
			if (I2C_ReadAccelRegs(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_INT_SOURCE, data_buffer, 1))
			{
				status = data_buffer[0];

				if (status & 0x01)
				{
					/* data is ready */
					if (I2C_ReadAccelRegs(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_STATUS, data_buffer, 13))
					{
						accel_data->accel_x = (int16_t)(((data_buffer[1] << 8) | data_buffer[2]))>> 2;
						accel_data->accel_y = (int16_t)(((data_buffer[3] << 8) | data_buffer[4]))>> 2;
						accel_data->accel_z = (int16_t)(((data_buffer[5] << 8) | data_buffer[6]))>> 2;

						// copy the magnetometer byte data into 16 bit words
						accel_data->magn_x = (data_buffer[7] << 8) | data_buffer[8];
						accel_data->magn_y = (data_buffer[9] << 8) | data_buffer[10];
						accel_data->magn_z = (data_buffer[11] << 8) | data_buffer[12];

						ret_value = TRUE;
					}
				}

				if (status & 0x08)
				{
					/* pulse event */
					*tap_event = TRUE;
					ret_value = TRUE;
					I2C_ReadAccelRegs(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_PULSE_SRC, data_buffer, 1);
				}
			}
    	}
    }

    return ret_value;
}

void accel_init(void)
{
    i2c_master_config_t masterConfig;

    I2C_MasterGetDefaultConfig(&masterConfig);

    masterConfig.baudRate_Bps = 250000;

    I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));

    I2C_MasterTransferCreateHandle(I2C0, &g_m_handle, i2c_master_callback, NULL);

    timer_delay(10);

    /* standby mode */
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_CTRL_REG1, 0x00);

    // write 0001 1111 = 0x1F to magnetometer control register 1
    // [7]: m_acal=0: auto calibration disabled
    // [6]: m_rst=0: no one-shot magnetic reset
    // [5]: m_ost=0: no one-shot magnetic measurement
    // [4-2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
    // [1-0]: m_hms=11=3: select hybrid mode with accel and magnetometer active
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_M_CTRL_REG1, 0x1F);

    // write 0010 0000 = 0x20 to magnetometer control register 2
    // [7]: reserved
    // [6]: reserved
    // [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the
    // accelerometer registers
    // [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
    // [3]: m_maxmin_dis_ths=0
    // [2]: m_maxmin_rst=0
    // [1-0]: m_rst_cnt=00 to enable magnetic reset each cycle
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_M_CTRL_REG2, 0x20);

    // write to XYZ_DATA_CFG register
    // [7]: reserved
    // [6]: reserved
    // [5]: reserved
    // [4]: hpf_out=0
    // [3]: reserved
    // [2]: reserved
    // [1-0]: fs=00 for accelerometer range of +/-2g range
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_XYZ_DATA_CFG, 0x00);

    /* enable double-tap event on Z-axis */
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x21, 0b01100000);
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x23, 0x10);
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x24, 0x10);
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x25, 0x10);
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x26, 0x06);
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x27, 0x28);
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, 0x28, 0x0F);

    /* setup DR and pulse on INT1 */
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_CTRL_REG5, 0x09);

    // write 0000 0001= 0x01 to accelerometer control register 4
    // to enable DR int on INT1
    // enable double tap event in INT1
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_CTRL_REG4, 0x09);


    PORT_SetPinInterruptConfig(PORTB, 5, kPORT_InterruptFallingEdge);
    EnableIRQ(PORTB_IRQn);

    // write to accelerometer control register 1
    // [7-6]: aslp_rate=00
    // [5-3]: dr=010 for 200Hz data rate
    // [2]: lnoise=1 for no low noise mode
    // [1]: f_read=0 for normal 16 bit reads
    // [0]: active=1 to take the part out of standby and enable sampling
    I2C_WriteAccelReg(I2C0, FXOS8700CQ_ADDR, FXOS8700CQ_CTRL_REG1, 0b00010101);


}

void PORTB_IRQHandler(void)
{
   GPIO_ClearPinsInterruptFlags(GPIOB, 1U << 5);
   _accel_interrupt = TRUE;
}
