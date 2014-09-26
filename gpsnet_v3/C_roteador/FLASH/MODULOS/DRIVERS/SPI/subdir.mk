################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(SPI)/SPI.c" \

C_SRCS += \
$(SPI_ESCAPED)/SPI.c \

OBJS += \
./MODULOS/DRIVERS/SPI/SPI_c.obj \

OBJS_QUOTED += \
"./MODULOS/DRIVERS/SPI/SPI_c.obj" \

C_DEPS += \
./MODULOS/DRIVERS/SPI/SPI_c.d \

OBJS_OS_FORMAT += \
./MODULOS/DRIVERS/SPI/SPI_c.obj \

C_DEPS_QUOTED += \
"./MODULOS/DRIVERS/SPI/SPI_c.d" \


# Each subdirectory must supply rules for building sources it contributes
MODULOS/DRIVERS/SPI/SPI_c.obj: $(SPI_ESCAPED)/SPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"MODULOS/DRIVERS/SPI/SPI.args" -o "MODULOS/DRIVERS/SPI/SPI_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

MODULOS/DRIVERS/SPI/SPI_c.d: $(SPI_ESCAPED)/SPI.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


