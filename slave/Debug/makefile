################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WDT/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/Timer/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXT_INT/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Servo/subdir.mk
-include HAL/SSD/subdir.mk
-include HAL/PB/subdir.mk
-include HAL/LM35/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KeyPad/subdir.mk
-include HAL/DCMotor/subdir.mk
-include HAL/Buzzer/subdir.mk
-include HAL/AT24C16A/subdir.mk
-include APP/Projects/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
509_GROUP.lss \

FLASH_IMAGE += \
509_GROUP.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: 509_GROUP.elf secondary-outputs

# Tool invocations
509_GROUP.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,509_GROUP.map -mmcu=atmega32 -o "509_GROUP.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

509_GROUP.lss: 509_GROUP.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 509_GROUP.elf  >"509_GROUP.lss"
	@echo 'Finished building: $@'
	@echo ' '

509_GROUP.hex: 509_GROUP.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 509_GROUP.elf  "509_GROUP.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 509_GROUP.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t 509_GROUP.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 509_GROUP.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
