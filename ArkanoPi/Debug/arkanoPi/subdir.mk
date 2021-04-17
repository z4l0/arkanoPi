################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../arkanoPi/arkanoPi.c \
../arkanoPi/arkanoPiLib.c \
../arkanoPi/fsm.c \
../arkanoPi/kbhit.c \
../arkanoPi/ledDisplay.c \
../arkanoPi/teclado_TL04.c \
../arkanoPi/tmr.c 

OBJS += \
./arkanoPi/arkanoPi.o \
./arkanoPi/arkanoPiLib.o \
./arkanoPi/fsm.o \
./arkanoPi/kbhit.o \
./arkanoPi/ledDisplay.o \
./arkanoPi/teclado_TL04.o \
./arkanoPi/tmr.o 

C_DEPS += \
./arkanoPi/arkanoPi.d \
./arkanoPi/arkanoPiLib.d \
./arkanoPi/fsm.d \
./arkanoPi/kbhit.d \
./arkanoPi/ledDisplay.d \
./arkanoPi/teclado_TL04.d \
./arkanoPi/tmr.d 


# Each subdirectory must supply rules for building sources it contributes
arkanoPi/%.o: ../arkanoPi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I/home/z4l0/wiringPi -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


