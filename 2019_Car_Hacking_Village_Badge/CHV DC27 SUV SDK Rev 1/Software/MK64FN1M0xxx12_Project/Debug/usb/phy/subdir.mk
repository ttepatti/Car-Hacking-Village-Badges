################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/phy/usb_phy.c 

OBJS += \
./usb/phy/usb_phy.o 

C_DEPS += \
./usb/phy/usb_phy.d 


# Each subdirectory must supply rules for building sources it contributes
usb/phy/%.o: ../usb/phy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLQ12 -DCPU_MK64FN1M0VLQ12_cm4 -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../drivers/freertos -I"C:\Users\nhoch.SPECSOL\Documents\MCUXpressoIDE_11.0.0_2516\workspace\MK64FN1M0xxx12_Project\chv_include" -I../amazon-freertos/freertos/portable -I../amazon-freertos/include -I../sdmmc/inc -I../CMSIS -I../drivers -I../usb/host/class -I../fatfs/fatfs_include -I../usb/device/class -I../usb/device/include -I../usb/device/source -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source -I../source/generated -I../fatfs -I../accel -I../usb/host -I../device -I../usb/include -I../osa -I../usb/phy -I../board -I../ -Og -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


