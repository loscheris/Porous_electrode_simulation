################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/2D\ \ TAceo\ Nernst\ CV.cpp \
../src/2D\ Nernst\ CV\ main.cpp \
../src/TA_class.cpp \
../src/TwoDgrids\ CV.cpp 

OBJS += \
./src/2D\ \ TAceo\ Nernst\ CV.o \
./src/2D\ Nernst\ CV\ main.o \
./src/TA_class.o \
./src/TwoDgrids\ CV.o 

CPP_DEPS += \
./src/2D\ \ TAceo\ Nernst\ CV.d \
./src/2D\ Nernst\ CV\ main.d \
./src/TA_class.d \
./src/TwoDgrids\ CV.d 


# Each subdirectory must supply rules for building sources it contributes
src/2D\ \ TAceo\ Nernst\ CV.o: ../src/2D\ \ TAceo\ Nernst\ CV.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/2D  TAceo Nernst CV.d" -MT"src/2D\ \ TAceo\ Nernst\ CV.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/2D\ Nernst\ CV\ main.o: ../src/2D\ Nernst\ CV\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/2D Nernst CV main.d" -MT"src/2D\ Nernst\ CV\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TwoDgrids\ CV.o: ../src/TwoDgrids\ CV.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/TwoDgrids CV.d" -MT"src/TwoDgrids\ CV.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


