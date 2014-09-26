################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(BOOTLOADER)/Bootloader_wireless.c" \
"$(BOOTLOADER)/MCF51_Bootloader.c" \

C_SRCS += \
$(BOOTLOADER_ESCAPED)/Bootloader_wireless.c \
$(BOOTLOADER_ESCAPED)/MCF51_Bootloader.c \

OBJS += \
./MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.obj \
./MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.obj \

OBJS_QUOTED += \
"./MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.obj" \
"./MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.obj" \

C_DEPS += \
./MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.d \
./MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.d \

OBJS_OS_FORMAT += \
./MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.obj \
./MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.d" \
"./MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.obj: $(BOOTLOADER_ESCAPED)/Bootloader_wireless.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/APPS/BOOTLOADER/Bootloader_wireless.args" -o "MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/APPS/BOOTLOADER/Bootloader_wireless_c.d: $(BOOTLOADER_ESCAPED)/Bootloader_wireless.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.obj: $(BOOTLOADER_ESCAPED)/MCF51_Bootloader.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/APPS/BOOTLOADER/MCF51_Bootloader.args" -o "MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/APPS/BOOTLOADER/MCF51_Bootloader_c.d: $(BOOTLOADER_ESCAPED)/MCF51_Bootloader.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


