################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/button.c \
../Core/Src/command_parser_fsm.c \
../Core/Src/fsm_autorun.c \
../Core/Src/fsm_manual.c \
../Core/Src/fsm_setting.c \
../Core/Src/global.c \
../Core/Src/i2c_lcd.c \
../Core/Src/light_traffic.c \
../Core/Src/main.c \
../Core/Src/server_flag_processing.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/timer.c 

OBJS += \
./Core/Src/button.o \
./Core/Src/command_parser_fsm.o \
./Core/Src/fsm_autorun.o \
./Core/Src/fsm_manual.o \
./Core/Src/fsm_setting.o \
./Core/Src/global.o \
./Core/Src/i2c_lcd.o \
./Core/Src/light_traffic.o \
./Core/Src/main.o \
./Core/Src/server_flag_processing.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/timer.o 

C_DEPS += \
./Core/Src/button.d \
./Core/Src/command_parser_fsm.d \
./Core/Src/fsm_autorun.d \
./Core/Src/fsm_manual.d \
./Core/Src/fsm_setting.d \
./Core/Src/global.d \
./Core/Src/i2c_lcd.d \
./Core/Src/light_traffic.d \
./Core/Src/main.d \
./Core/Src/server_flag_processing.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/command_parser_fsm.cyclo ./Core/Src/command_parser_fsm.d ./Core/Src/command_parser_fsm.o ./Core/Src/command_parser_fsm.su ./Core/Src/fsm_autorun.cyclo ./Core/Src/fsm_autorun.d ./Core/Src/fsm_autorun.o ./Core/Src/fsm_autorun.su ./Core/Src/fsm_manual.cyclo ./Core/Src/fsm_manual.d ./Core/Src/fsm_manual.o ./Core/Src/fsm_manual.su ./Core/Src/fsm_setting.cyclo ./Core/Src/fsm_setting.d ./Core/Src/fsm_setting.o ./Core/Src/fsm_setting.su ./Core/Src/global.cyclo ./Core/Src/global.d ./Core/Src/global.o ./Core/Src/global.su ./Core/Src/i2c_lcd.cyclo ./Core/Src/i2c_lcd.d ./Core/Src/i2c_lcd.o ./Core/Src/i2c_lcd.su ./Core/Src/light_traffic.cyclo ./Core/Src/light_traffic.d ./Core/Src/light_traffic.o ./Core/Src/light_traffic.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/server_flag_processing.cyclo ./Core/Src/server_flag_processing.d ./Core/Src/server_flag_processing.o ./Core/Src/server_flag_processing.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/timer.cyclo ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su

.PHONY: clean-Core-2f-Src

