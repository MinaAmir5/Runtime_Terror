################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SPI/SPI_Prog.c 

OBJS += \
./MCAL/SPI/SPI_Prog.o 

C_DEPS += \
./MCAL/SPI/SPI_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SPI/%.o: ../MCAL/SPI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\APP" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\SSD" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\SSD" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\Servo" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\PB" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\LM35" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\LED" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\LCD" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\KeyPad" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\DCMotor" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\Buzzer" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL\AT24C16A" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\HAL" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\WDT" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\UART" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\Timer" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\SPI" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\I2C" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\GIE" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\EXT_INT" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\DIO" -I"C:\Users\HODA2\Downloads\Mahmoud_s_Project_Template\need comments\slave\MCAL\ADC" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


