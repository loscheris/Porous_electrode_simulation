################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/2D\ \ TAceo\ BVC.cpp \
../src/2D\ BVC\ main.cpp \
../src/TA_class.cpp \
../src/TwoDgrids.cpp 

OBJS += \
./src/2D\ \ TAceo\ BVC.o \
./src/2D\ BVC\ main.o \
./src/TA_class.o \
./src/TwoDgrids.o 

CPP_DEPS += \
./src/2D\ \ TAceo\ BVC.d \
./src/2D\ BVC\ main.d \
./src/TA_class.d \
./src/TwoDgrids.d 


# Each subdirectory must supply rules for building sources it contributes
src/2D\ \ TAceo\ BVC.o: ../src/2D\ \ TAceo\ BVC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/2D  TAceo BVC.d" -MT"src/2D\ \ TAceo\ BVC.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/2D\ BVC\ main.o: ../src/2D\ BVC\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/2D BVC main.d" -MT"src/2D\ BVC\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

