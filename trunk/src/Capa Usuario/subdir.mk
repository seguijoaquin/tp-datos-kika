################################################################################
# Automatically-generated file. Do not edit!
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./Capa\ Usuario/AdminIndicesSecundarios.cpp \
./Capa\ Usuario/AdministradorRegistros.cpp \
./Capa\ Usuario/Consultas.cpp \
./Capa\ Usuario/Interfaz.cpp \

OBJS += \
./Capa\ Usuario/AdminIndicesSecundarios.o \
./Capa\ Usuario/AdministradorRegistros.o \
./Capa\ Usuario/Consultas.o \
./Capa\ Usuario/Interfaz.o \

CPP_DEPS += \
./trunk/src/Capa\ Usuario/AdminIndicesSecundarios.d \
./Capa\ Usuario/AdministradorRegistros.d \
./Capa\ Usuario/Consultas.d \
./Capa\ Usuario/Interfaz.d \


# Each subdirectory must supply rules for building sources it contributes
Capa\ Usuario/AdminIndicesSecundarios.o: ./Capa\ Usuario/AdminIndicesSecundarios.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Capa\ Usuario/AdministradorRegistros.o: ./Capa\ Usuario/AdministradorRegistros.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Capa\ Usuario/Consultas.o: ./Capa\ Usuario/Consultas.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Capa\ Usuario/Interfaz.o: ./Capa\ Usuario/Interfaz.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

