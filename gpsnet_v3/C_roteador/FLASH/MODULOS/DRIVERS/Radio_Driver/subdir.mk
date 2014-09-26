################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(RADIO_DRIVER)/MRF24J40.c" \

C_SRCS += \
$(RADIO_DRIVER_ESCAPED)/MRF24J40.c \

OBJS += \
./MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.obj \

OBJS_QUOTED += \
"./MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.obj" \

C_DEPS += \
./MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.d \

OBJS_OS_FORMAT += \
./MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.obj: $(RADIO_DRIVER_ESCAPED)/MRF24J40.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/DRIVERS/Radio_Driver/MRF24J40.args" -o "MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/DRIVERS/Radio_Driver/MRF24J40_c.d: $(RADIO_DRIVER_ESCAPED)/MRF24J40.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


