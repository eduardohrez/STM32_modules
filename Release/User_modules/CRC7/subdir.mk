################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/CRC7/crc7_soft.c 

OBJS += \
./User_modules/CRC7/crc7_soft.o 

C_DEPS += \
./User_modules/CRC7/crc7_soft.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/CRC7/%.o User_modules/CRC7/%.su User_modules/CRC7/%.cyclo: ../User_modules/CRC7/%.c User_modules/CRC7/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-CRC7

clean-User_modules-2f-CRC7:
	-$(RM) ./User_modules/CRC7/crc7_soft.cyclo ./User_modules/CRC7/crc7_soft.d ./User_modules/CRC7/crc7_soft.o ./User_modules/CRC7/crc7_soft.su

.PHONY: clean-User_modules-2f-CRC7

