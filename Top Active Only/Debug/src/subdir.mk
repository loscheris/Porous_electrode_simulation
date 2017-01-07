################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Porous\ \ TAceo\ BV.cpp \
../src/Porous\ Main.cpp \
../src/PorousTwoDgrids.cpp \
../src/TA_class.cpp 

OBJS += \
./src/Porous\ \ TAceo\ BV.o \
./src/Porous\ Main.o \
./src/PorousTwoDgrids.o \
./src/TA_class.o 

CPP_DEPS += \
./src/Porous\ \ TAceo\ BV.d \
./src/Porous\ Main.d \
./src/PorousTwoDgrids.d \
./src/TA_class.d 


# Each subdirectory must supply rules for building sources it contributes
src/Porous\ \ TAceo\ BV.o: ../src/Porous\ \ TAceo\ BV.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/Porous  TAceo BV.d" -MT"src/Porous\ \ TAceo\ BV.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Porous\ Main.o: ../src/Porous\ Main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"src/Porous Main.d" -MT"src/Porous\ Main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


