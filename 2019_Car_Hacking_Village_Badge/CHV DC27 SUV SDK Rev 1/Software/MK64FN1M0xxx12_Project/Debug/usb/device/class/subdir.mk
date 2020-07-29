################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/device/class/usb_device_audio.c \
../usb/device/class/usb_device_ccid.c \
../usb/device/class/usb_device_cdc_acm.c \
../usb/device/class/usb_device_cdc_rndis.c \
../usb/device/class/usb_device_class.c \
../usb/device/class/usb_device_hid.c \
../usb/device/class/usb_device_msc.c \
../usb/device/class/usb_device_msc_ufi.c \
../usb/device/class/usb_device_phdc.c \
../usb/device/class/usb_device_printer.c \
../usb/device/class/usb_device_video.c 

OBJS += \
./usb/device/class/usb_device_audio.o \
./usb/device/class/usb_device_ccid.o \
./usb/device/class/usb_device_cdc_acm.o \
./usb/device/class/usb_device_cdc_rndis.o \
./usb/device/class/usb_device_class.o \
./usb/device/class/usb_device_hid.o \
./usb/device/class/usb_device_msc.o \
./usb/device/class/usb_device_msc_ufi.o \
./usb/device/class/usb_device_phdc.o \
./usb/device/class/usb_device_printer.o \
./usb/device/class/usb_device_video.o 

C_DEPS += \
./usb/device/class/usb_device_audio.d \
./usb/device/class/usb_device_ccid.d \
./usb/device/class/usb_device_cdc_acm.d \
./usb/device/class/usb_device_cdc_rndis.d \
./usb/device/class/usb_device_class.d \
./usb/device/class/usb_device_hid.d \
./usb/device/class/usb_device_msc.d \
./usb/device/class/usb_device_msc_ufi.d \
./usb/device/class/usb_device_phdc.d \
./usb/device/class/usb_device_printer.d \
./usb/device/class/usb_device_video.d 


# Each subdirectory must supply rules for building sources it contributes
usb/device/class/%.o: ../usb/device/class/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLQ12 -DCPU_MK64FN1M0VLQ12_cm4 -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../drivers/freertos -I"C:\Users\nhoch.SPECSOL\Documents\MCUXpressoIDE_11.0.0_2516\workspace\MK64FN1M0xxx12_Project\chv_include" -I../amazon-freertos/freertos/portable -I../amazon-freertos/include -I../sdmmc/inc -I../CMSIS -I../drivers -I../usb/host/class -I../fatfs/fatfs_include -I../usb/device/class -I../usb/device/include -I../usb/device/source -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source -I../source/generated -I../fatfs -I../accel -I../usb/host -I../device -I../usb/include -I../osa -I../usb/phy -I../board -I../ -Og -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


