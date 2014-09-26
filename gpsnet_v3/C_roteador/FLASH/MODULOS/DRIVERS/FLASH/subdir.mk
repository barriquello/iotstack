################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(FLASH)/flash.c" \

C_SRCS += \
$(FLASH_ESCAPED)/flash.c \

OBJS += \
./MODULOS/DRIVERS/FLASH/flash_c.obj \

OBJS_QUOTED += \
"./MODULOS/DRIVERS/FLASH/flash_c.obj" \

C_DEPS += \
./MODULOS/DRIVERS/FLASH/flash_c.d \

OBJS_OS_FORMAT += \
./MODULOS/DRIVERS/FLASH/flash_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/DRIVERS/FLASH/flash_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/DRIVERS/FLASH/flash_c.obj: $(FLASH_ESCAPED)/flash.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/DRIVERS/FLASH/flash.args" -o "MODULOS/DRIVERS/FLASH/flash_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/DRIVERS/FLASH/flash_c.d: $(FLASH_ESCAPED)/flash.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


