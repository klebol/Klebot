################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Programs/DiodeTest_Prog.c \
../Core/Src/Programs/MotorsDebug_Prog.c \
../Core/Src/Programs/klebot_programs.c 

OBJS += \
./Core/Src/Programs/DiodeTest_Prog.o \
./Core/Src/Programs/MotorsDebug_Prog.o \
./Core/Src/Programs/klebot_programs.o 

C_DEPS += \
./Core/Src/Programs/DiodeTest_Prog.d \
./Core/Src/Programs/MotorsDebug_Prog.d \
./Core/Src/Programs/klebot_programs.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Programs/%.o Core/Src/Programs/%.su Core/Src/Programs/%.cyclo: ../Core/Src/Programs/%.c Core/Src/Programs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Programs

clean-Core-2f-Src-2f-Programs:
	-$(RM) ./Core/Src/Programs/DiodeTest_Prog.cyclo ./Core/Src/Programs/DiodeTest_Prog.d ./Core/Src/Programs/DiodeTest_Prog.o ./Core/Src/Programs/DiodeTest_Prog.su ./Core/Src/Programs/MotorsDebug_Prog.cyclo ./Core/Src/Programs/MotorsDebug_Prog.d ./Core/Src/Programs/MotorsDebug_Prog.o ./Core/Src/Programs/MotorsDebug_Prog.su ./Core/Src/Programs/klebot_programs.cyclo ./Core/Src/Programs/klebot_programs.d ./Core/Src/Programs/klebot_programs.o ./Core/Src/Programs/klebot_programs.su

.PHONY: clean-Core-2f-Src-2f-Programs

