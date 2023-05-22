################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Headers/kinetis_sysinit.c" \

C_SRCS += \
../Project_Headers/kinetis_sysinit.c \

OBJS += \
./Project_Headers/kinetis_sysinit.o \

C_DEPS += \
./Project_Headers/kinetis_sysinit.d \

OBJS_QUOTED += \
"./Project_Headers/kinetis_sysinit.o" \

C_DEPS_QUOTED += \
"./Project_Headers/kinetis_sysinit.d" \

OBJS_OS_FORMAT += \
./Project_Headers/kinetis_sysinit.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Headers/kinetis_sysinit.o: ../Project_Headers/kinetis_sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Headers/kinetis_sysinit.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Headers/kinetis_sysinit.o"
	@echo 'Finished building: $<'
	@echo ' '


