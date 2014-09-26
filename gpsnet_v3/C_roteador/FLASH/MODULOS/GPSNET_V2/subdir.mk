################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(GPSNET_V2)/gpsnet_core.c" \
"$(GPSNET_V2)/gpsr.c" \
"$(GPSNET_V2)/mac.c" \
"$(GPSNET_V2)/network.c" \

C_SRCS += \
$(GPSNET_V2_ESCAPED)/gpsnet_core.c \
$(GPSNET_V2_ESCAPED)/gpsr.c \
$(GPSNET_V2_ESCAPED)/mac.c \
$(GPSNET_V2_ESCAPED)/network.c \

OBJS += \
./MODULOS/GPSNET_V2/gpsnet_core_c.obj \
./MODULOS/GPSNET_V2/gpsr_c.obj \
./MODULOS/GPSNET_V2/mac_c.obj \
./MODULOS/GPSNET_V2/network_c.obj \

OBJS_QUOTED += \
"./MODULOS/GPSNET_V2/gpsnet_core_c.obj" \
"./MODULOS/GPSNET_V2/gpsr_c.obj" \
"./MODULOS/GPSNET_V2/mac_c.obj" \
"./MODULOS/GPSNET_V2/network_c.obj" \

C_DEPS += \
./MODULOS/GPSNET_V2/gpsnet_core_c.d \
./MODULOS/GPSNET_V2/gpsr_c.d \
./MODULOS/GPSNET_V2/mac_c.d \
./MODULOS/GPSNET_V2/network_c.d \

OBJS_OS_FORMAT += \
./MODULOS/GPSNET_V2/gpsnet_core_c.obj \
./MODULOS/GPSNET_V2/gpsr_c.obj \
./MODULOS/GPSNET_V2/mac_c.obj \
./MODULOS/GPSNET_V2/network_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/GPSNET_V2/gpsnet_core_c.d" \
"./MODULOS/GPSNET_V2/gpsr_c.d" \
"./MODULOS/GPSNET_V2/mac_c.d" \
"./MODULOS/GPSNET_V2/network_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/GPSNET_V2/gpsnet_core_c.obj: $(GPSNET_V2_ESCAPED)/gpsnet_core.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/GPSNET_V2/gpsnet_core.args" -o "MODULOS/GPSNET_V2/gpsnet_core_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/GPSNET_V2/gpsnet_core_c.d: $(GPSNET_V2_ESCAPED)/gpsnet_core.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/GPSNET_V2/gpsr_c.obj: $(GPSNET_V2_ESCAPED)/gpsr.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/GPSNET_V2/gpsr.args" -o "MODULOS/GPSNET_V2/gpsr_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/GPSNET_V2/gpsr_c.d: $(GPSNET_V2_ESCAPED)/gpsr.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/GPSNET_V2/mac_c.obj: $(GPSNET_V2_ESCAPED)/mac.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/GPSNET_V2/mac.args" -o "MODULOS/GPSNET_V2/mac_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/GPSNET_V2/mac_c.d: $(GPSNET_V2_ESCAPED)/mac.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/GPSNET_V2/network_c.obj: $(GPSNET_V2_ESCAPED)/network.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/GPSNET_V2/network.args" -o "MODULOS/GPSNET_V2/network_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/GPSNET_V2/network_c.d: $(GPSNET_V2_ESCAPED)/network.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


