################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/util_funct/util.c 

OBJS += \
./User_modules/util_funct/util.o 

C_DEPS += \
./User_modules/util_funct/util.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/util_funct/%.o User_modules/util_funct/%.su User_modules/util_funct/%.cyclo: ../User_modules/util_funct/%.c User_modules/util_funct/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/ATH10" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/SSD1306_lcd" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/fonts_use" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/SPI_BASE" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/ST7789V2_LCD" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/run_time" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/Imag_arr_save" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/CRC7" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/SD_Base_SPI" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/I2C_conf_base" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/Files_manager" -I"C:/Users/eduar/OneDrive/Documentos/programing/microcontroller/stm32/Black_pell/User_modules/util_funct" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-util_funct

clean-User_modules-2f-util_funct:
	-$(RM) ./User_modules/util_funct/util.cyclo ./User_modules/util_funct/util.d ./User_modules/util_funct/util.o ./User_modules/util_funct/util.su

.PHONY: clean-User_modules-2f-util_funct
