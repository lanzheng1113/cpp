################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/adjlist.cpp \
../src/adjmatrix.cpp \
../src/adjmulist.cpp \
../src/common.cpp \
../src/graph.cpp \
../src/orthlist.cpp \
../src/testDrive.cpp 

OBJS += \
./src/adjlist.o \
./src/adjmatrix.o \
./src/adjmulist.o \
./src/common.o \
./src/graph.o \
./src/orthlist.o \
./src/testDrive.o 

CPP_DEPS += \
./src/adjlist.d \
./src/adjmatrix.d \
./src/adjmulist.d \
./src/common.d \
./src/graph.d \
./src/orthlist.d \
./src/testDrive.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


