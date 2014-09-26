################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/HARDWARE/MCUinit.c" \
"../Sources/HARDWARE/exceptions.c" \
"../Sources/HARDWARE/startcf.c" \
"../Sources/HARDWARE/usr_entry.c" \

C_SRCS += \
../Sources/HARDWARE/MCUinit.c \
../Sources/HARDWARE/exceptions.c \
../Sources/HARDWARE/startcf.c \
../Sources/HARDWARE/usr_entry.c \

OBJS += \
./Sources/HARDWARE/MCUinit_c.obj \
./Sources/HARDWARE/exceptions_c.obj \
./Sources/HARDWARE/startcf_c.obj \
./Sources/HARDWARE/usr_entry_c.obj \

OBJS_QUOTED += \
"./Sources/HARDWARE/MCUinit_c.obj" \
"./Sources/HARDWARE/exceptions_c.obj" \
"./Sources/HARDWARE/startcf_c.obj" \
"./Sources/HARDWARE/usr_entry_c.obj" \

C_DEPS += \
./Sources/HARDWARE/MCUinit_c.d \
./Sources/HARDWARE/exceptions_c.d \
./Sources/HARDWARE/startcf_c.d \
./Sources/HARDWARE/usr_entry_c.d \

OBJS_OS_FORMAT += \
./Sources/HARDWARE/MCUinit_c.obj \
./Sources/HARDWARE/exceptions_c.obj \
./Sources/HARDWARE/startcf_c.obj \
./Sources/HARDWARE/usr_entry_c.obj \

C_DEPS_QUOTED += \
"./Sources/HARDWARE/MCUinit_c.d" \
"./Sources/HARDWARE/exceptions_c.d" \
"./Sources/HARDWARE/startcf_c.d" \
"./Sources/HARDWARE/usr_entry_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/HARDWARE/MCUinit_c.obj: ../Sources/HARDWARE/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/HARDWARE/MCUinit.args" -o "Sources/HARDWARE/MCUinit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/HARDWARE/%.d: ../Sources/HARDWARE/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/HARDWARE/exceptions_c.obj: ../Sources/HARDWARE/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/HARDWARE/exceptions.args" -o "Sources/HARDWARE/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/HARDWARE/startcf_c.obj: ../Sources/HARDWARE/startcf.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/HARDWARE/startcf.args" -o "Sources/HARDWARE/startcf_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/HARDWARE/usr_entry_c.obj: ../Sources/HARDWARE/usr_entry.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/HARDWARE/usr_entry.args" -o "Sources/HARDWARE/usr_entry_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


