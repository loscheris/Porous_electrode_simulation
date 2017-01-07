################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/1D\ \ TAceo\ Nernst.cpp \
../src/1D\ Nernst\ main.cpp \
../src/1D\ grid\ Nernst.cpp \
../src/TA_class.cpp 

OBJS += \
./src/1D\ \ TAceo\ Nernst.o \
./src/1D\ Nernst\ main.o \
./src/1D\ grid\ Nernst.o \
./src/TA_class.o 

CPP_DEPS += \
./src/1D\ \ TAceo\ Nernst.d \
./src/1D\ Nernst\ main.d \
./src/1D\ grid\ Nernst.d \
./src/TA_class.d 


# Each subdirectory must supply rules for building sources it contributes
src/1D\ \ TAceo\ Nernst.o: ../src/1D\ \ TAceo\ Nernst.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D  TAceo Nernst.d" -MT"src/1D\ \ TAceo\ Nernst.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ Nernst\ main.o: ../src/1D\ Nernst\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D Nernst main.d" -MT"src/1D\ Nernst\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ grid\ Nernst.o: ../src/1D\ grid\ Nernst.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D grid Nernst.d" -MT"src/1D\ grid\ Nernst.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


