################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/I2C_conf_base/I2C_base.c 

OBJS += \
./User_modules/I2C_conf_base/I2C_base.o 

C_DEPS += \
./User_modules/I2C_conf_base/I2C_base.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/I2C_conf_base/%.o User_modules/I2C_conf_base/%.su User_modules/I2C_conf_base/%.cyclo: ../User_modules/I2C_conf_base/%.c User_modules/I2C_conf_base/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-I2C_conf_base

clean-User_modules-2f-I2C_conf_base:
	-$(RM) ./User_modules/I2C_conf_base/I2C_base.cyclo ./User_modules/I2C_conf_base/I2C_base.d ./User_modules/I2C_conf_base/I2C_base.o ./User_modules/I2C_conf_base/I2C_base.su

.PHONY: clean-User_modules-2f-I2C_conf_base

