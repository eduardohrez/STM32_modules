################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_modules/Imag_arr_save/Save_Img.c 

OBJS += \
./User_modules/Imag_arr_save/Save_Img.o 

C_DEPS += \
./User_modules/Imag_arr_save/Save_Img.d 


# Each subdirectory must supply rules for building sources it contributes
User_modules/Imag_arr_save/%.o User_modules/Imag_arr_save/%.su User_modules/Imag_arr_save/%.cyclo: ../User_modules/Imag_arr_save/%.c User_modules/Imag_arr_save/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_modules-2f-Imag_arr_save

clean-User_modules-2f-Imag_arr_save:
	-$(RM) ./User_modules/Imag_arr_save/Save_Img.cyclo ./User_modules/Imag_arr_save/Save_Img.d ./User_modules/Imag_arr_save/Save_Img.o ./User_modules/Imag_arr_save/Save_Img.su

.PHONY: clean-User_modules-2f-Imag_arr_save

