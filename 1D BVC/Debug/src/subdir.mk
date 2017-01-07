################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/1D\ BVC\ main.cpp \
../src/1D\ TAceo\ BVC.cpp \
../src/1D\ grid\ BVC.cpp \
../src/TA_class.cpp 

OBJS += \
./src/1D\ BVC\ main.o \
./src/1D\ TAceo\ BVC.o \
./src/1D\ grid\ BVC.o \
./src/TA_class.o 

CPP_DEPS += \
./src/1D\ BVC\ main.d \
./src/1D\ TAceo\ BVC.d \
./src/1D\ grid\ BVC.d \
./src/TA_class.d 


# Each subdirectory must supply rules for building sources it contributes
src/1D\ BVC\ main.o: ../src/1D\ BVC\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D BVC main.d" -MT"src/1D\ BVC\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ TAceo\ BVC.o: ../src/1D\ TAceo\ BVC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D TAceo BVC.d" -MT"src/1D\ TAceo\ BVC.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ grid\ BVC.o: ../src/1D\ grid\ BVC.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D grid BVC.d" -MT"src/1D\ grid\ BVC.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


