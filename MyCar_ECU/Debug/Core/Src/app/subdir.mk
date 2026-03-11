################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/app/AutonomyController.cpp \
../Core/Src/app/CommandExecutor.cpp \
../Core/Src/app/ControlManager.cpp \
../Core/Src/app/Lights.cpp \
../Core/Src/app/MotorDriver.cpp 

OBJS += \
./Core/Src/app/AutonomyController.o \
./Core/Src/app/CommandExecutor.o \
./Core/Src/app/ControlManager.o \
./Core/Src/app/Lights.o \
./Core/Src/app/MotorDriver.o 

CPP_DEPS += \
./Core/Src/app/AutonomyController.d \
./Core/Src/app/CommandExecutor.d \
./Core/Src/app/ControlManager.d \
./Core/Src/app/Lights.d \
./Core/Src/app/MotorDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/app/%.o Core/Src/app/%.su Core/Src/app/%.cyclo: ../Core/Src/app/%.cpp Core/Src/app/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DDEBUG -DSTM32F091xC -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-app

clean-Core-2f-Src-2f-app:
	-$(RM) ./Core/Src/app/AutonomyController.cyclo ./Core/Src/app/AutonomyController.d ./Core/Src/app/AutonomyController.o ./Core/Src/app/AutonomyController.su ./Core/Src/app/CommandExecutor.cyclo ./Core/Src/app/CommandExecutor.d ./Core/Src/app/CommandExecutor.o ./Core/Src/app/CommandExecutor.su ./Core/Src/app/ControlManager.cyclo ./Core/Src/app/ControlManager.d ./Core/Src/app/ControlManager.o ./Core/Src/app/ControlManager.su ./Core/Src/app/Lights.cyclo ./Core/Src/app/Lights.d ./Core/Src/app/Lights.o ./Core/Src/app/Lights.su ./Core/Src/app/MotorDriver.cyclo ./Core/Src/app/MotorDriver.d ./Core/Src/app/MotorDriver.o ./Core/Src/app/MotorDriver.su

.PHONY: clean-Core-2f-Src-2f-app

