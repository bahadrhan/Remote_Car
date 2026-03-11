################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/hw/Clock.cpp \
../Core/Src/hw/Gpio.cpp \
../Core/Src/hw/Timebase.cpp \
../Core/Src/hw/Uart.cpp 

OBJS += \
./Core/Src/hw/Clock.o \
./Core/Src/hw/Gpio.o \
./Core/Src/hw/Timebase.o \
./Core/Src/hw/Uart.o 

CPP_DEPS += \
./Core/Src/hw/Clock.d \
./Core/Src/hw/Gpio.d \
./Core/Src/hw/Timebase.d \
./Core/Src/hw/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hw/%.o Core/Src/hw/%.su Core/Src/hw/%.cyclo: ../Core/Src/hw/%.cpp Core/Src/hw/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DDEBUG -DSTM32F091xC -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hw

clean-Core-2f-Src-2f-hw:
	-$(RM) ./Core/Src/hw/Clock.cyclo ./Core/Src/hw/Clock.d ./Core/Src/hw/Clock.o ./Core/Src/hw/Clock.su ./Core/Src/hw/Gpio.cyclo ./Core/Src/hw/Gpio.d ./Core/Src/hw/Gpio.o ./Core/Src/hw/Gpio.su ./Core/Src/hw/Timebase.cyclo ./Core/Src/hw/Timebase.d ./Core/Src/hw/Timebase.o ./Core/Src/hw/Timebase.su ./Core/Src/hw/Uart.cyclo ./Core/Src/hw/Uart.d ./Core/Src/hw/Uart.o ./Core/Src/hw/Uart.su

.PHONY: clean-Core-2f-Src-2f-hw

