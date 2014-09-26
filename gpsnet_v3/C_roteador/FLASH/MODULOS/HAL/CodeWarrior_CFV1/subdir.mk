################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(CODEWARRIOR_CFV1)/HAL.c" \

C_SRCS += \
$(CODEWARRIOR_CFV1_ESCAPED)/HAL.c \

OBJS += \
./MODULOS/HAL/CodeWarrior_CFV1/HAL_c.obj \

OBJS_QUOTED += \
"./MODULOS/HAL/CodeWarrior_CFV1/HAL_c.obj" \

C_DEPS += \
./MODULOS/HAL/CodeWarrior_CFV1/HAL_c.d \

OBJS_OS_FORMAT += \
./MODULOS/HAL/CodeWarrior_CFV1/HAL_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/HAL/CodeWarrior_CFV1/HAL_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/HAL/CodeWarrior_CFV1/HAL_c.obj: $(CODEWARRIOR_CFV1_ESCAPED)/HAL.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/HAL/CodeWarrior_CFV1/HAL.args" -o "MODULOS/HAL/CodeWarrior_CFV1/HAL_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/HAL/CodeWarrior_CFV1/HAL_c.d: $(CODEWARRIOR_CFV1_ESCAPED)/HAL.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


