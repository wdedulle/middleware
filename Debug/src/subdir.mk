################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CreateTCPServerSocket.c \
../src/HandleTCPClient.c \
../src/main.c \
../src/socket.c \
../src/xml.c 

OBJS += \
./src/CreateTCPServerSocket.o \
./src/HandleTCPClient.o \
./src/main.o \
./src/socket.o \
./src/xml.o 

C_DEPS += \
./src/CreateTCPServerSocket.d \
./src/HandleTCPClient.d \
./src/main.d \
./src/socket.d \
./src/xml.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\Data\lib\libxml\includel" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


