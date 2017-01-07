################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/1D\ BV\ main.cpp \
../src/1D\ TAcoe\ BV.cpp \
../src/1D\ grid\ BV.cpp \
../src/TA_class.cpp 

OBJS += \
./src/1D\ BV\ main.o \
./src/1D\ TAcoe\ BV.o \
./src/1D\ grid\ BV.o \
./src/TA_class.o 

CPP_DEPS += \
./src/1D\ BV\ main.d \
./src/1D\ TAcoe\ BV.d \
./src/1D\ grid\ BV.d \
./src/TA_class.d 


# Each subdirectory must supply rules for building sources it contributes
src/1D\ BV\ main.o: ../src/1D\ BV\ main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D BV main.d" -MT"src/1D\ BV\ main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ TAcoe\ BV.o: ../src/1D\ TAcoe\ BV.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D TAcoe BV.d" -MT"src/1D\ TAcoe\ BV.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/1D\ grid\ BV.o: ../src/1D\ grid\ BV.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1D grid BV.d" -MT"src/1D\ grid\ BV.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


