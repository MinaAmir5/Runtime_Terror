################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/AT24C16A/AT24C16A_Prog.c 

OBJS += \
./HAL/AT24C16A/AT24C16A_Prog.o 

C_DEPS += \
./HAL/AT24C16A/AT24C16A_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/AT24C16A/%.o: ../HAL/AT24C16A/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\dell\Desktop\slave\APP" -I"C:\Users\dell\Desktop\slave\HAL\AT24C16A" -I"C:\Users\dell\Desktop\slave\HAL\AT24C16A" -I"C:\Users\dell\Desktop\slave\MCAL\I2C" -I"C:\Users\dell\Desktop\slave\MCAL\SPI" -I"C:\Users\dell\Desktop\slave\MCAL\UART" -I"C:\Users\dell\Desktop\slave\HAL\Servo" -I"C:\Users\dell\Desktop\slave\HAL\DCMotor" -I"C:\Users\dell\Desktop\slave\MCAL\WDT" -I"C:\Users\dell\Desktop\slave\MCAL\GIE" -I"C:\Users\dell\Desktop\slave\MCAL\Timer" -I"C:\Users\dell\Desktop\slave\HAL\LM35" -I"C:\Users\dell\Desktop\slave\MCAL\ADC" -I"C:\Users\dell\Desktop\slave\HAL\KeyPad" -I"C:\Users\dell\Desktop\slave\MCAL\EXT_INT" -I"C:\Users\dell\Desktop\slave\HAL\LCD" -I"C:\Users\dell\Desktop\slave\APP\Projects" -I"C:\Users\dell\Desktop\slave\HAL\SSD" -I"C:\Users\dell\Desktop\slave\HAL\PB" -I"C:\Users\dell\Desktop\slave\HAL\Buzzer" -I"C:\Users\dell\Desktop\slave" -I"C:\Users\dell\Desktop\slave\HAL" -I"C:\Users\dell\Desktop\slave\MCAL" -I"C:\Users\dell\Desktop\slave\MCAL\DIO" -I"C:\Users\dell\Desktop\slave\HAL\LED" -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


