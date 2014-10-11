################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./Capa\ Fisica/AdministradorEntidades.cpp \
./Capa\ Fisica/Bloque.cpp \
./Capa\ Fisica/Entidad.cpp \
./Capa\ Fisica/Instancia.cpp 

OBJS += \
./Capa\ Fisica/AdministradorEntidades.o \
./Capa\ Fisica/Bloque.o \
./Capa\ Fisica/Entidad.o \
./Capa\ Fisica/Instancia.o 

CPP_DEPS += \
./Capa\ Fisica/AdministradorEntidades.d \
./Capa\ Fisica/Bloque.d \
./Capa\ Fisica/Entidad.d \
./Capa\ Fisica/Instancia.d 


# Each subdirectory must supply rules for building sources it contributes
Capa\ Fisica/AdministradorEntidades.o: ./Capa\ Fisica/AdministradorEntidades.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Capa\ Fisica/Bloque.o: ./Capa\ Fisica/Bloque.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Capa\ Fisica/Entidad.o: ./Capa\ Fisica/Entidad.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Capa\ Fisica/Instancia.o: ./Capa\ Fisica/Instancia.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


