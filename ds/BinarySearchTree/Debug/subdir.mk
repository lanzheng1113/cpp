################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TestDrive.cpp \
../avltree.cpp \
../bst.cpp \
../dswtree.cpp \
../splaytree.cpp \
../treeprinter.cpp 

OBJS += \
./TestDrive.o \
./avltree.o \
./bst.o \
./dswtree.o \
./splaytree.o \
./treeprinter.o 

CPP_DEPS += \
./TestDrive.d \
./avltree.d \
./bst.d \
./dswtree.d \
./splaytree.d \
./treeprinter.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


