################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prg.c \
../DIO_prg.c \
../EEPROM_program.c \
../GI_program.c \
../I2C_program.c \
../LCD_prg.c \
../TIMER0_program.c \
../UART_program.c \
../main.c 

OBJS += \
./ADC_prg.o \
./DIO_prg.o \
./EEPROM_program.o \
./GI_program.o \
./I2C_program.o \
./LCD_prg.o \
./TIMER0_program.o \
./UART_program.o \
./main.o 

C_DEPS += \
./ADC_prg.d \
./DIO_prg.d \
./EEPROM_program.d \
./GI_program.d \
./I2C_program.d \
./LCD_prg.d \
./TIMER0_program.d \
./UART_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


