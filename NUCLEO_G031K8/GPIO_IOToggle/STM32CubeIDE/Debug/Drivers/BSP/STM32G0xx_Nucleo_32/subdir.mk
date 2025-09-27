################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/akash/Documents/git/STMPlayground/NUCLEO_G031K8/GPIO_IOToggle/Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.c 

OBJS += \
./Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.o 

C_DEPS += \
./Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.o: C:/Users/akash/Documents/git/STMPlayground/NUCLEO_G031K8/GPIO_IOToggle/Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.c Drivers/BSP/STM32G0xx_Nucleo_32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32G031xx -c -I../../Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/STM32G0xx_Nucleo_32 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32G0xx_Nucleo_32

clean-Drivers-2f-BSP-2f-STM32G0xx_Nucleo_32:
	-$(RM) ./Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.cyclo ./Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.d ./Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.o ./Drivers/BSP/STM32G0xx_Nucleo_32/stm32g0xx_nucleo_32.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32G0xx_Nucleo_32

