################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/RingBuffer.c \
../Core/Src/adc.c \
../Core/Src/bitmaps.c \
../Core/Src/controller_inputs.c \
../Core/Src/debounce.c \
../Core/Src/dma.c \
../Core/Src/fonts.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/joystick.c \
../Core/Src/klebot_commands.c \
../Core/Src/klebot_parser.c \
../Core/Src/klebot_radio.c \
../Core/Src/main.c \
../Core/Src/menu.c \
../Core/Src/nRF24.c \
../Core/Src/simple_scheduler.c \
../Core/Src/spi.c \
../Core/Src/ssd1106.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/RingBuffer.o \
./Core/Src/adc.o \
./Core/Src/bitmaps.o \
./Core/Src/controller_inputs.o \
./Core/Src/debounce.o \
./Core/Src/dma.o \
./Core/Src/fonts.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/joystick.o \
./Core/Src/klebot_commands.o \
./Core/Src/klebot_parser.o \
./Core/Src/klebot_radio.o \
./Core/Src/main.o \
./Core/Src/menu.o \
./Core/Src/nRF24.o \
./Core/Src/simple_scheduler.o \
./Core/Src/spi.o \
./Core/Src/ssd1106.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/RingBuffer.d \
./Core/Src/adc.d \
./Core/Src/bitmaps.d \
./Core/Src/controller_inputs.d \
./Core/Src/debounce.d \
./Core/Src/dma.d \
./Core/Src/fonts.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/joystick.d \
./Core/Src/klebot_commands.d \
./Core/Src/klebot_parser.d \
./Core/Src/klebot_radio.d \
./Core/Src/main.d \
./Core/Src/menu.d \
./Core/Src/nRF24.d \
./Core/Src/simple_scheduler.d \
./Core/Src/spi.d \
./Core/Src/ssd1106.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/RingBuffer.cyclo ./Core/Src/RingBuffer.d ./Core/Src/RingBuffer.o ./Core/Src/RingBuffer.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/bitmaps.cyclo ./Core/Src/bitmaps.d ./Core/Src/bitmaps.o ./Core/Src/bitmaps.su ./Core/Src/controller_inputs.cyclo ./Core/Src/controller_inputs.d ./Core/Src/controller_inputs.o ./Core/Src/controller_inputs.su ./Core/Src/debounce.cyclo ./Core/Src/debounce.d ./Core/Src/debounce.o ./Core/Src/debounce.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/joystick.cyclo ./Core/Src/joystick.d ./Core/Src/joystick.o ./Core/Src/joystick.su ./Core/Src/klebot_commands.cyclo ./Core/Src/klebot_commands.d ./Core/Src/klebot_commands.o ./Core/Src/klebot_commands.su ./Core/Src/klebot_parser.cyclo ./Core/Src/klebot_parser.d ./Core/Src/klebot_parser.o ./Core/Src/klebot_parser.su ./Core/Src/klebot_radio.cyclo ./Core/Src/klebot_radio.d ./Core/Src/klebot_radio.o ./Core/Src/klebot_radio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/menu.cyclo ./Core/Src/menu.d ./Core/Src/menu.o ./Core/Src/menu.su ./Core/Src/nRF24.cyclo ./Core/Src/nRF24.d ./Core/Src/nRF24.o ./Core/Src/nRF24.su ./Core/Src/simple_scheduler.cyclo ./Core/Src/simple_scheduler.d ./Core/Src/simple_scheduler.o ./Core/Src/simple_scheduler.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/ssd1106.cyclo ./Core/Src/ssd1106.d ./Core/Src/ssd1106.o ./Core/Src/ssd1106.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

