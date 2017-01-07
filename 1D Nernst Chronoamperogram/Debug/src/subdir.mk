################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/1D\ NernstC\ main.cpp \
../src/1D\ TAceo\ NernstC.cpp \
../src/1D\ gird\ NernstC.cpp \
../src/TA_class.cpp 

OBJS += \
./src/1D\ NernstC\ main.o \
./src/1D\ TAceo\ NernstC.o \
./src/1D\ gird\ NernstC.o \
./src/TA_class.o 

CPP_DEPS += \
./src/1D\ NernstC\ main.d \
./src/1D\ TAceo\ NernstC.d \
./src/1D\ gird\ NernstC.d \
./src/TA_class.d 


# Each subdirectory must supply rules for building sources it contributes
src/1D\ NernstC\ main.o: ../src/1D\ NernstC\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D NernstC main.d" -MT"src/1D\ NernstC\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ TAceo\ NernstC.o: ../src/1D\ TAceo\ NernstC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D TAceo NernstC.d" -MT"src/1D\ TAceo\ NernstC.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ gird\ NernstC.o: ../src/1D\ gird\ NernstC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D gird NernstC.d" -MT"src/1D\ gird\ NernstC.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


