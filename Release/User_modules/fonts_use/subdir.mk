################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/fonts_use/font_lcd.c 

OBJS += \
./User_modules/fonts_use/font_lcd.o 

C_DEPS += \
./User_modules/fonts_use/font_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/fonts_use/%.o User_modules/fonts_use/%.su User_modules/fonts_use/%.cyclo: ../User_modules/fonts_use/%.c User_modules/fonts_use/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-fonts_use

clean-User_modules-2f-fonts_use:
	-$(RM) ./User_modules/fonts_use/font_lcd.cyclo ./User_modules/fonts_use/font_lcd.d ./User_modules/fonts_use/font_lcd.o ./User_modules/fonts_use/font_lcd.su

.PHONY: clean-User_modules-2f-fonts_use

