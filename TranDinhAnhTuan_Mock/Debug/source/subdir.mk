################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/TranDinhAnhTuan_mock.c \
../source/fun.c \
../source/mtb.c 

C_DEPS += \
./source/TranDinhAnhTuan_mock.d \
./source/fun.d \
./source/mtb.d 

OBJS += \
./source/TranDinhAnhTuan_mock.o \
./source/fun.o \
./source/mtb.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Mock\board" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Mock\source" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Mock" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Mock\CMSIS" -I"C:\Users\ASUS\Documents\MCUXpressoIDE_11.7.1_9221\workspace\TranDinhAnhTuan_Mock\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/TranDinhAnhTuan_mock.d ./source/TranDinhAnhTuan_mock.o ./source/fun.d ./source/fun.o ./source/mtb.d ./source/mtb.o

.PHONY: clean-source

