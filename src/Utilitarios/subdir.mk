################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./Utilitarios/StringUtil.cpp 

OBJS += \
./Utilitarios/StringUtil.o 

CPP_DEPS += \
./Utilitarios/StringUtil.d 


# Each subdirectory must supply rules for building sources it contributes
Utilitarios/%.o: ./Utilitarios/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


