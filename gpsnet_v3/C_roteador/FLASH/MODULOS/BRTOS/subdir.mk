################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(BRTOS)/BRTOS.c" \
"$(BRTOS)/OS_RTC.c" \
"$(BRTOS)/mbox.c" \
"$(BRTOS)/mutex.c" \
"$(BRTOS)/queue.c" \
"$(BRTOS)/semaphore.c" \
"$(BRTOS)/timers.c" \

C_SRCS += \
$(BRTOS_ESCAPED)/BRTOS.c \
$(BRTOS_ESCAPED)/OS_RTC.c \
$(BRTOS_ESCAPED)/mbox.c \
$(BRTOS_ESCAPED)/mutex.c \
$(BRTOS_ESCAPED)/queue.c \
$(BRTOS_ESCAPED)/semaphore.c \
$(BRTOS_ESCAPED)/timers.c \

OBJS += \
./MODULOS/BRTOS/BRTOS_c.obj \
./MODULOS/BRTOS/OS_RTC_c.obj \
./MODULOS/BRTOS/mbox_c.obj \
./MODULOS/BRTOS/mutex_c.obj \
./MODULOS/BRTOS/queue_c.obj \
./MODULOS/BRTOS/semaphore_c.obj \
./MODULOS/BRTOS/timers_c.obj \

OBJS_QUOTED += \
"./MODULOS/BRTOS/BRTOS_c.obj" \
"./MODULOS/BRTOS/OS_RTC_c.obj" \
"./MODULOS/BRTOS/mbox_c.obj" \
"./MODULOS/BRTOS/mutex_c.obj" \
"./MODULOS/BRTOS/queue_c.obj" \
"./MODULOS/BRTOS/semaphore_c.obj" \
"./MODULOS/BRTOS/timers_c.obj" \

C_DEPS += \
./MODULOS/BRTOS/BRTOS_c.d \
./MODULOS/BRTOS/OS_RTC_c.d \
./MODULOS/BRTOS/mbox_c.d \
./MODULOS/BRTOS/mutex_c.d \
./MODULOS/BRTOS/queue_c.d \
./MODULOS/BRTOS/semaphore_c.d \
./MODULOS/BRTOS/timers_c.d \

OBJS_OS_FORMAT += \
./MODULOS/BRTOS/BRTOS_c.obj \
./MODULOS/BRTOS/OS_RTC_c.obj \
./MODULOS/BRTOS/mbox_c.obj \
./MODULOS/BRTOS/mutex_c.obj \
./MODULOS/BRTOS/queue_c.obj \
./MODULOS/BRTOS/semaphore_c.obj \
./MODULOS/BRTOS/timers_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/BRTOS/BRTOS_c.d" \
"./MODULOS/BRTOS/OS_RTC_c.d" \
"./MODULOS/BRTOS/mbox_c.d" \
"./MODULOS/BRTOS/mutex_c.d" \
"./MODULOS/BRTOS/queue_c.d" \
"./MODULOS/BRTOS/semaphore_c.d" \
"./MODULOS/BRTOS/timers_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/BRTOS/BRTOS_c.obj: $(BRTOS_ESCAPED)/BRTOS.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/BRTOS.args" -o "MODULOS/BRTOS/BRTOS_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/BRTOS_c.d: $(BRTOS_ESCAPED)/BRTOS.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/BRTOS/OS_RTC_c.obj: $(BRTOS_ESCAPED)/OS_RTC.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/OS_RTC.args" -o "MODULOS/BRTOS/OS_RTC_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/OS_RTC_c.d: $(BRTOS_ESCAPED)/OS_RTC.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/BRTOS/mbox_c.obj: $(BRTOS_ESCAPED)/mbox.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/mbox.args" -o "MODULOS/BRTOS/mbox_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/mbox_c.d: $(BRTOS_ESCAPED)/mbox.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/BRTOS/mutex_c.obj: $(BRTOS_ESCAPED)/mutex.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/mutex.args" -o "MODULOS/BRTOS/mutex_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/mutex_c.d: $(BRTOS_ESCAPED)/mutex.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/BRTOS/queue_c.obj: $(BRTOS_ESCAPED)/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/queue.args" -o "MODULOS/BRTOS/queue_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/queue_c.d: $(BRTOS_ESCAPED)/queue.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/BRTOS/semaphore_c.obj: $(BRTOS_ESCAPED)/semaphore.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/semaphore.args" -o "MODULOS/BRTOS/semaphore_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/semaphore_c.d: $(BRTOS_ESCAPED)/semaphore.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

MODULOS/BRTOS/timers_c.obj: $(BRTOS_ESCAPED)/timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/BRTOS/timers.args" -o "MODULOS/BRTOS/timers_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/BRTOS/timers_c.d: $(BRTOS_ESCAPED)/timers.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


