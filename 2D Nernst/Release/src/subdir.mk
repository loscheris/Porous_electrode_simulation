################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/2D\ \ TAceo\ Nernst.cpp \
../src/2D\ Nernst\ main.cpp \
../src/TA_class.cpp \
../src/TwoDgrids.cpp 

OBJS += \
./src/2D\ \ TAceo\ Nernst.o \
./src/2D\ Nernst\ main.o \
./src/TA_class.o \
./src/TwoDgrids.o 

CPP_DEPS += \
./src/2D\ \ TAceo\ Nernst.d \
./src/2D\ Nernst\ main.d \
./src/TA_class.d \
./src/TwoDgrids.d 


# Each subdirectory must supply rules for building sources it contributes
src/2D\ \ TAceo\ Nernst.o: ../src/2D\ \ TAceo\ Nernst.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/2D  TAceo Nernst.d" -MT"src/2D\ \ TAceo\ Nernst.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/2D\ Nernst\ main.o: ../src/2D\ Nernst\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/2D Nernst main.d" -MT"src/2D\ Nernst\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


