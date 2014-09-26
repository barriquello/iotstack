################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(FLASH_EEPROM)/FL_eeprom.c" \

C_SRCS += \
$(FLASH_EEPROM_ESCAPED)/FL_eeprom.c \

OBJS += \
./MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.obj \

OBJS_QUOTED += \
"./MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.obj" \

C_DEPS += \
./MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.d \

OBJS_OS_FORMAT += \
./MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.obj: $(FLASH_EEPROM_ESCAPED)/FL_eeprom.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom.args" -o "MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/DRIVERS/FLASH_EEPROM/FL_eeprom_c.d: $(FLASH_EEPROM_ESCAPED)/FL_eeprom.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


