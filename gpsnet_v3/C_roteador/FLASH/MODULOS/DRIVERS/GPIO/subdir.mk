################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(GPIO)/gpio.c" \

C_SRCS += \
$(GPIO_ESCAPED)/gpio.c \

OBJS += \
./MODULOS/DRIVERS/GPIO/gpio_c.obj \

OBJS_QUOTED += \
"./MODULOS/DRIVERS/GPIO/gpio_c.obj" \

C_DEPS += \
./MODULOS/DRIVERS/GPIO/gpio_c.d \

OBJS_OS_FORMAT += \
./MODULOS/DRIVERS/GPIO/gpio_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/DRIVERS/GPIO/gpio_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/DRIVERS/GPIO/gpio_c.obj: $(GPIO_ESCAPED)/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/DRIVERS/GPIO/gpio.args" -o "MODULOS/DRIVERS/GPIO/gpio_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/DRIVERS/GPIO/gpio_c.d: $(GPIO_ESCAPED)/gpio.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


