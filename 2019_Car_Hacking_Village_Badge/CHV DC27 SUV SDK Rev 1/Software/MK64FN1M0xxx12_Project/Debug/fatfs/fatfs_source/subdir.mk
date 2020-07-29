################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fatfs/fatfs_source/diskio.c \
../fatfs/fatfs_source/ff.c \
../fatfs/fatfs_source/ffsystem.c \
../fatfs/fatfs_source/ffunicode.c \
../fatfs/fatfs_source/fsl_mmc_disk.c \
../fatfs/fatfs_source/fsl_nand_disk.c \
../fatfs/fatfs_source/fsl_ram_disk.c \
../fatfs/fatfs_source/fsl_sd_disk.c \
../fatfs/fatfs_source/fsl_sdspi_disk.c \
../fatfs/fatfs_source/fsl_usb_disk_bm.c 

OBJS += \
./fatfs/fatfs_source/diskio.o \
./fatfs/fatfs_source/ff.o \
./fatfs/fatfs_source/ffsystem.o \
./fatfs/fatfs_source/ffunicode.o \
./fatfs/fatfs_source/fsl_mmc_disk.o \
./fatfs/fatfs_source/fsl_nand_disk.o \
./fatfs/fatfs_source/fsl_ram_disk.o \
./fatfs/fatfs_source/fsl_sd_disk.o \
./fatfs/fatfs_source/fsl_sdspi_disk.o \
./fatfs/fatfs_source/fsl_usb_disk_bm.o 

C_DEPS += \
./fatfs/fatfs_source/diskio.d \
./fatfs/fatfs_source/ff.d \
./fatfs/fatfs_source/ffsystem.d \
./fatfs/fatfs_source/ffunicode.d \
./fatfs/fatfs_source/fsl_mmc_disk.d \
./fatfs/fatfs_source/fsl_nand_disk.d \
./fatfs/fatfs_source/fsl_ram_disk.d \
./fatfs/fatfs_source/fsl_sd_disk.d \
./fatfs/fatfs_source/fsl_sdspi_disk.d \
./fatfs/fatfs_source/fsl_usb_disk_bm.d 


# Each subdirectory must supply rules for building sources it contributes
fatfs/fatfs_source/%.o: ../fatfs/fatfs_source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLQ12 -DCPU_MK64FN1M0VLQ12_cm4 -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../drivers/freertos -I"C:\Users\nhoch.SPECSOL\Documents\MCUXpressoIDE_11.0.0_2516\workspace\MK64FN1M0xxx12_Project\chv_include" -I../amazon-freertos/freertos/portable -I../amazon-freertos/include -I../sdmmc/inc -I../CMSIS -I../drivers -I../usb/host/class -I../fatfs/fatfs_include -I../usb/device/class -I../usb/device/include -I../usb/device/source -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source -I../source/generated -I../fatfs -I../accel -I../usb/host -I../device -I../usb/include -I../osa -I../usb/phy -I../board -I../ -Og -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


