################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app.c" \
"../Sources/exceptions.c" \
"../Sources/main.c" \
"../Sources/sensors.c" \
"../Sources/smartmeter.c" \
"../Sources/tasks.c" \

C_SRCS += \
../Sources/app.c \
../Sources/exceptions.c \
../Sources/main.c \
../Sources/sensors.c \
../Sources/smartmeter.c \
../Sources/tasks.c \

OBJS += \
./Sources/app_c.obj \
./Sources/exceptions_c.obj \
./Sources/main_c.obj \
./Sources/sensors_c.obj \
./Sources/smartmeter_c.obj \
./Sources/tasks_c.obj \

OBJS_QUOTED += \
"./Sources/app_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/main_c.obj" \
"./Sources/sensors_c.obj" \
"./Sources/smartmeter_c.obj" \
"./Sources/tasks_c.obj" \

C_DEPS += \
./Sources/app_c.d \
./Sources/exceptions_c.d \
./Sources/main_c.d \
./Sources/sensors_c.d \
./Sources/smartmeter_c.d \
./Sources/tasks_c.d \

OBJS_OS_FORMAT += \
./Sources/app_c.obj \
./Sources/exceptions_c.obj \
./Sources/main_c.obj \
./Sources/sensors_c.obj \
./Sources/smartmeter_c.obj \
./Sources/tasks_c.obj \

C_DEPS_QUOTED += \
"./Sources/app_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/main_c.d" \
"./Sources/sensors_c.d" \
"./Sources/smartmeter_c.d" \
"./Sources/tasks_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/app_c.obj: ../Sources/app.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/app.args" -o "Sources/app_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sensors_c.obj: ../Sources/sensors.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/sensors.args" -o "Sources/sensors_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/smartmeter_c.obj: ../Sources/smartmeter.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/smartmeter.args" -o "Sources/smartmeter_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/tasks_c.obj: ../Sources/tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/tasks.args" -o "Sources/tasks_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


