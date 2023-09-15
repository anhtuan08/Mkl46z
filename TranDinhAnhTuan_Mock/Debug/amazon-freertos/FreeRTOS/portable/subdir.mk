################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/FreeRTOS/portable/port.c 

C_DEPS += \
./amazon-freertos/FreeRTOS/portable/port.d 

OBJS += \
./amazon-freertos/FreeRTOS/portable/port.o 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/FreeRTOS/portable/%.o: ../amazon-freertos/FreeRTOS/portable/%.c amazon-freertos/FreeRTOS/portable/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\board" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\source" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\amazon-freertos\FreeRTOS\portable" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\freertos\portable" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\amazon-freertos\include" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\CMSIS" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Ass5\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-amazon-2d-freertos-2f-FreeRTOS-2f-portable

clean-amazon-2d-freertos-2f-FreeRTOS-2f-portable:
	-$(RM) ./amazon-freertos/FreeRTOS/portable/port.d ./amazon-freertos/FreeRTOS/portable/port.o

.PHONY: clean-amazon-2d-freertos-2f-FreeRTOS-2f-portable

