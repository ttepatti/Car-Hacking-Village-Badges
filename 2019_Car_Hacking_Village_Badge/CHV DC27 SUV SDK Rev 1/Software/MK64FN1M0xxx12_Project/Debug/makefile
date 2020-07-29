################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include usb/phy/subdir.mk
-include usb/device/source/lpcip3511/subdir.mk
-include usb/device/source/khci/subdir.mk
-include usb/device/source/ehci/subdir.mk
-include usb/device/source/subdir.mk
-include usb/device/class/subdir.mk
-include startup/subdir.mk
-include source/generated/subdir.mk
-include source/subdir.mk
-include sdmmc/src/subdir.mk
-include sdmmc/subdir.mk
-include osa/subdir.mk
-include graphics/subdir.mk
-include fatfs/fatfs_source/subdir.mk
-include drivers/freertos/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include chv_drivers/subdir.mk
-include chv_app/subdir.mk
-include board/subdir.mk
-include amazon-freertos/freertos/portable/subdir.mk
-include amazon-freertos/freertos/subdir.mk
-include accel/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MK64FN1M0xxx12_Project.axf

# Tool invocations
MK64FN1M0xxx12_Project.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="MK64FN1M0xxx12_Project.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T MK64FN1M0xxx12_Project_Debug.ld -u _printf_float -u _scanf_float -o "MK64FN1M0xxx12_Project.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MK64FN1M0xxx12_Project.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "MK64FN1M0xxx12_Project.axf"; # arm-none-eabi-objcopy -v -O binary "MK64FN1M0xxx12_Project.axf" "MK64FN1M0xxx12_Project.bin" ; # checksum -p MK64FN1M0xxx12 -d "MK64FN1M0xxx12_Project.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
