################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(UTILS)/math_utils.c" \

C_SRCS += \
$(UTILS_ESCAPED)/math_utils.c \

OBJS += \
./MODULOS/APPS/UTILS/math_utils_c.obj \

OBJS_QUOTED += \
"./MODULOS/APPS/UTILS/math_utils_c.obj" \

C_DEPS += \
./MODULOS/APPS/UTILS/math_utils_c.d \

OBJS_OS_FORMAT += \
./MODULOS/APPS/UTILS/math_utils_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/APPS/UTILS/math_utils_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/APPS/UTILS/math_utils_c.obj: $(UTILS_ESCAPED)/math_utils.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/APPS/UTILS/math_utils.args" -o "MODULOS/APPS/UTILS/math_utils_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/APPS/UTILS/math_utils_c.d: $(UTILS_ESCAPED)/math_utils.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


