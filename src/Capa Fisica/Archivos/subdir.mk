################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./Capa\ Fisica/Archivos/Archivo.cpp 

OBJS += \
./Capa\ Fisica/Archivos/Archivo.o 

CPP_DEPS += \
./Capa\ Fisica/Archivos/Archivo.d 


# Each subdirectory must supply rules for building sources it contributes
Capa\ Fisica/Archivos/Archivo.o: ./Capa\ Fisica/Archivos/Archivo.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


