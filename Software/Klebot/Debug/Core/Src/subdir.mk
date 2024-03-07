################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FIRFilter.c \
../Core/Src/PID.c \
../Core/Src/RingBuffer.c \
../Core/Src/drv8836.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/klebot_parser.c \
../Core/Src/klebot_scheduler.c \
../Core/Src/main.c \
../Core/Src/motor_encoder.c \
../Core/Src/motors.c \
../Core/Src/motors_task.c \
../Core/Src/nRF24.c \
../Core/Src/onboard_diode_task.c \
../Core/Src/radio_task.c \
../Core/Src/spi.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_hal_timebase_tim.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/FIRFilter.o \
./Core/Src/PID.o \
./Core/Src/RingBuffer.o \
./Core/Src/drv8836.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/klebot_parser.o \
./Core/Src/klebot_scheduler.o \
./Core/Src/main.o \
./Core/Src/motor_encoder.o \
./Core/Src/motors.o \
./Core/Src/motors_task.o \
./Core/Src/nRF24.o \
./Core/Src/onboard_diode_task.o \
./Core/Src/radio_task.o \
./Core/Src/spi.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_hal_timebase_tim.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/FIRFilter.d \
./Core/Src/PID.d \
./Core/Src/RingBuffer.d \
./Core/Src/drv8836.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/klebot_parser.d \
./Core/Src/klebot_scheduler.d \
./Core/Src/main.d \
./Core/Src/motor_encoder.d \
./Core/Src/motors.d \
./Core/Src/motors_task.d \
./Core/Src/nRF24.d \
./Core/Src/onboard_diode_task.d \
./Core/Src/radio_task.d \
./Core/Src/spi.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_hal_timebase_tim.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/FIRFilter.cyclo ./Core/Src/FIRFilter.d ./Core/Src/FIRFilter.o ./Core/Src/FIRFilter.su ./Core/Src/PID.cyclo ./Core/Src/PID.d ./Core/Src/PID.o ./Core/Src/PID.su ./Core/Src/RingBuffer.cyclo ./Core/Src/RingBuffer.d ./Core/Src/RingBuffer.o ./Core/Src/RingBuffer.su ./Core/Src/drv8836.cyclo ./Core/Src/drv8836.d ./Core/Src/drv8836.o ./Core/Src/drv8836.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/klebot_parser.cyclo ./Core/Src/klebot_parser.d ./Core/Src/klebot_parser.o ./Core/Src/klebot_parser.su ./Core/Src/klebot_scheduler.cyclo ./Core/Src/klebot_scheduler.d ./Core/Src/klebot_scheduler.o ./Core/Src/klebot_scheduler.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor_encoder.cyclo ./Core/Src/motor_encoder.d ./Core/Src/motor_encoder.o ./Core/Src/motor_encoder.su ./Core/Src/motors.cyclo ./Core/Src/motors.d ./Core/Src/motors.o ./Core/Src/motors.su ./Core/Src/motors_task.cyclo ./Core/Src/motors_task.d ./Core/Src/motors_task.o ./Core/Src/motors_task.su ./Core/Src/nRF24.cyclo ./Core/Src/nRF24.d ./Core/Src/nRF24.o ./Core/Src/nRF24.su ./Core/Src/onboard_diode_task.cyclo ./Core/Src/onboard_diode_task.d ./Core/Src/onboard_diode_task.o ./Core/Src/onboard_diode_task.su ./Core/Src/radio_task.cyclo ./Core/Src/radio_task.d ./Core/Src/radio_task.o ./Core/Src/radio_task.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_hal_timebase_tim.cyclo ./Core/Src/stm32f1xx_hal_timebase_tim.d ./Core/Src/stm32f1xx_hal_timebase_tim.o ./Core/Src/stm32f1xx_hal_timebase_tim.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

