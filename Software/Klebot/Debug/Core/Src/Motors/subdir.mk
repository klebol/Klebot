################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Motors/drv8836.c \
../Core/Src/Motors/motor_encoder.c \
../Core/Src/Motors/motors.c 

OBJS += \
./Core/Src/Motors/drv8836.o \
./Core/Src/Motors/motor_encoder.o \
./Core/Src/Motors/motors.o 

C_DEPS += \
./Core/Src/Motors/drv8836.d \
./Core/Src/Motors/motor_encoder.d \
./Core/Src/Motors/motors.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Motors/%.o Core/Src/Motors/%.su Core/Src/Motors/%.cyclo: ../Core/Src/Motors/%.c Core/Src/Motors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Motors

clean-Core-2f-Src-2f-Motors:
	-$(RM) ./Core/Src/Motors/drv8836.cyclo ./Core/Src/Motors/drv8836.d ./Core/Src/Motors/drv8836.o ./Core/Src/Motors/drv8836.su ./Core/Src/Motors/motor_encoder.cyclo ./Core/Src/Motors/motor_encoder.d ./Core/Src/Motors/motor_encoder.o ./Core/Src/Motors/motor_encoder.su ./Core/Src/Motors/motors.cyclo ./Core/Src/Motors/motors.d ./Core/Src/Motors/motors.o ./Core/Src/Motors/motors.su

.PHONY: clean-Core-2f-Src-2f-Motors

