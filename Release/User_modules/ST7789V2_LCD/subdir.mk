################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/ST7789V2_LCD/LCD_ST7.c 

OBJS += \
./User_modules/ST7789V2_LCD/LCD_ST7.o 

C_DEPS += \
./User_modules/ST7789V2_LCD/LCD_ST7.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/ST7789V2_LCD/%.o User_modules/ST7789V2_LCD/%.su User_modules/ST7789V2_LCD/%.cyclo: ../User_modules/ST7789V2_LCD/%.c User_modules/ST7789V2_LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-ST7789V2_LCD

clean-User_modules-2f-ST7789V2_LCD:
	-$(RM) ./User_modules/ST7789V2_LCD/LCD_ST7.cyclo ./User_modules/ST7789V2_LCD/LCD_ST7.d ./User_modules/ST7789V2_LCD/LCD_ST7.o ./User_modules/ST7789V2_LCD/LCD_ST7.su

.PHONY: clean-User_modules-2f-ST7789V2_LCD

