################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application.c \
../button.c \
../gpio.c \
../hc-sr04_ultrasonic.c \
../icu.c \
../lcd.c 

OBJS += \
./Application.o \
./button.o \
./gpio.o \
./hc-sr04_ultrasonic.o \
./icu.o \
./lcd.o 

C_DEPS += \
./Application.d \
./button.d \
./gpio.d \
./hc-sr04_ultrasonic.d \
./icu.d \
./lcd.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


