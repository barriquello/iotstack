################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(ADC)/adc.c" \

C_SRCS += \
$(ADC_ESCAPED)/adc.c \

OBJS += \
./MODULOS/DRIVERS/ADC/adc_c.obj \

OBJS_QUOTED += \
"./MODULOS/DRIVERS/ADC/adc_c.obj" \

C_DEPS += \
./MODULOS/DRIVERS/ADC/adc_c.d \

OBJS_OS_FORMAT += \
./MODULOS/DRIVERS/ADC/adc_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/DRIVERS/ADC/adc_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/DRIVERS/ADC/adc_c.obj: $(ADC_ESCAPED)/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/DRIVERS/ADC/adc.args" -o "MODULOS/DRIVERS/ADC/adc_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/DRIVERS/ADC/adc_c.d: $(ADC_ESCAPED)/adc.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


