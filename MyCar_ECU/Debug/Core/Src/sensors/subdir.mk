################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/sensors/UltrasonicSensor.cpp 

OBJS += \
./Core/Src/sensors/UltrasonicSensor.o 

CPP_DEPS += \
./Core/Src/sensors/UltrasonicSensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sensors/%.o Core/Src/sensors/%.su Core/Src/sensors/%.cyclo: ../Core/Src/sensors/%.cpp Core/Src/sensors/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DDEBUG -DSTM32F091xC -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sensors

clean-Core-2f-Src-2f-sensors:
	-$(RM) ./Core/Src/sensors/UltrasonicSensor.cyclo ./Core/Src/sensors/UltrasonicSensor.d ./Core/Src/sensors/UltrasonicSensor.o ./Core/Src/sensors/UltrasonicSensor.su

.PHONY: clean-Core-2f-Src-2f-sensors

