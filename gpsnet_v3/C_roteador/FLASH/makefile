################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 32
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/HARDWARE/subdir.mk
-include MODULOS/HAL/CodeWarrior_CFV1/subdir.mk
-include MODULOS/GPSNET_V2/subdir.mk
-include MODULOS/DRIVERS/SPI/subdir.mk
-include MODULOS/DRIVERS/Radio_Driver/subdir.mk
-include MODULOS/DRIVERS/GPIO/subdir.mk
-include MODULOS/DRIVERS/FLASH_EEPROM/subdir.mk
-include MODULOS/DRIVERS/FLASH/subdir.mk
-include MODULOS/DRIVERS/ADC/subdir.mk
-include MODULOS/BRTOS/subdir.mk
-include MODULOS/APPS/UTILS/subdir.mk
-include MODULOS/APPS/COMM2PC/project_for_coding/XMACRO_cmds/bin/subdir.mk
-include MODULOS/APPS/BOOTLOADER/subdir.mk
-include Lib/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
C_roteador.elf \

EXECUTABLES_QUOTED += \
"C_roteador.elf" \

EXECUTABLES_OS_FORMAT += \
C_roteador.elf \

_OUTPUTTYPE_NAME_BURNER_OUTPUT_OUTPUTS += \
C_roteador.elf.s19 \

_OUTPUTTYPE_NAME_BURNER_OUTPUT_OUTPUTS_QUOTED += \
"C_roteador.elf.s19" \

_OUTPUTTYPE_NAME_BURNER_OUTPUT_OUTPUTS_OS_FORMAT += \
C_roteador.elf.s19 \


# All Target
call-burner := 0
ifneq ($(strip $(EXECUTABLES)),)
ifneq ($(strip $(BBL_SRCS_QUOTED)),)
call-burner := 1
endif
endif
ifeq ($(call-burner),1)
all: C_roteador.elf C_roteador.elf.s19
else
all: C_roteador.elf
endif

# Tool invocations
C_roteador.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/Project.lcf
	@echo 'Building target: $@'
	@echo 'Executing target #33 $@'
	@echo 'Invoking: ColdFire Linker'
	"$(CF_ToolsDirEnv)/mwldmcf" -o "C_roteador.elf" @@"C_roteador.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

C_roteador.elf.s19: $(BBL_SRCS) $(EXECUTABLES)
	@echo 'Executing target #34 $@'
	@echo 'Invoking: Burner'
	"$(HC08ToolsEnv)/burner.exe"  -f="$<" -env"ABS_FILE=$(strip $(EXECUTABLES_OS_FORMAT))"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*.obj" "./*/*/*/*.obj" "./*/*/*.obj"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(_OUTPUTTYPE_NAME_BURNER_OUTPUT_OUTPUTS_QUOTED) $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*/*.d" "./*/*/*.d"  $(ProjDirPath)/FLASH/C_roteador.elf $(ProjDirPath)/FLASH/C_roteador.args $(ProjDirPath)/FLASH/C_roteador.elf $(ProjDirPath)/FLASH/C_roteador.elf.S19 $(ProjDirPath)/FLASH/C_roteador.elf.xMAP
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/Project.lcf 

warning-messages: 

