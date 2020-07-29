################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chv_drivers/accel.c \
../chv_drivers/adc.c \
../chv_drivers/led.c \
../chv_drivers/timer.c \
../chv_drivers/uart.c 

OBJS += \
./chv_drivers/accel.o \
./chv_drivers/adc.o \
./chv_drivers/led.o \
./chv_drivers/timer.o \
./chv_drivers/uart.o 

C_DEPS += \
./chv_drivers/accel.d \
./chv_drivers/adc.d \
./chv_drivers/led.d \
./chv_drivers/timer.d \
./chv_drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
chv_drivers/%.o: ../chv_drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL03Z32VFG4 -DCPU_MKL03Z32VFG4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../startup -I../chv_include -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


