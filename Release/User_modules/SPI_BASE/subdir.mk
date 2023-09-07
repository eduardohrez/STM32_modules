################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/SPI_BASE/SPI_BASE.c 

OBJS += \
./User_modules/SPI_BASE/SPI_BASE.o 

C_DEPS += \
./User_modules/SPI_BASE/SPI_BASE.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/SPI_BASE/%.o User_modules/SPI_BASE/%.su User_modules/SPI_BASE/%.cyclo: ../User_modules/SPI_BASE/%.c User_modules/SPI_BASE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-SPI_BASE

clean-User_modules-2f-SPI_BASE:
	-$(RM) ./User_modules/SPI_BASE/SPI_BASE.cyclo ./User_modules/SPI_BASE/SPI_BASE.d ./User_modules/SPI_BASE/SPI_BASE.o ./User_modules/SPI_BASE/SPI_BASE.su

.PHONY: clean-User_modules-2f-SPI_BASE

