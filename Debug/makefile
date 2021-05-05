################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
IMTOnine_Graduation_Project.lss \

FLASH_IMAGE += \
IMTOnine_Graduation_Project.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: IMTOnine_Graduation_Project.elf secondary-outputs

# Tool invocations
IMTOnine_Graduation_Project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,IMTOnine_Graduation_Project.map -mmcu=atmega32 -o "IMTOnine_Graduation_Project.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

IMTOnine_Graduation_Project.lss: IMTOnine_Graduation_Project.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S IMTOnine_Graduation_Project.elf  >"IMTOnine_Graduation_Project.lss"
	@echo 'Finished building: $@'
	@echo ' '

IMTOnine_Graduation_Project.hex: IMTOnine_Graduation_Project.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex IMTOnine_Graduation_Project.elf  "IMTOnine_Graduation_Project.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: IMTOnine_Graduation_Project.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 IMTOnine_Graduation_Project.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: IMTOnine_Graduation_Project.elf
	@echo 'Invoking: AVRDude'
	D:\IMT Diploma\Tools\SDK\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm32 -cusbasp -Uflash:w:IMTOnine_Graduation_Project.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) IMTOnine_Graduation_Project.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
