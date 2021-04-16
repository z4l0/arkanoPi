################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../arkanoPi_3.0/arkanoPi.c \
../arkanoPi_3.0/arkanoPiLib.c \
../arkanoPi_3.0/fsm.c \
../arkanoPi_3.0/kbhit.c \
../arkanoPi_3.0/ledDisplay.c \
../arkanoPi_3.0/pseudoWiringPi.c \
../arkanoPi_3.0/teclado_TL04.c \
../arkanoPi_3.0/tmr.c 

OBJS += \
./arkanoPi_3.0/arkanoPi.o \
./arkanoPi_3.0/arkanoPiLib.o \
./arkanoPi_3.0/fsm.o \
./arkanoPi_3.0/kbhit.o \
./arkanoPi_3.0/ledDisplay.o \
./arkanoPi_3.0/pseudoWiringPi.o \
./arkanoPi_3.0/teclado_TL04.o \
./arkanoPi_3.0/tmr.o 

C_DEPS += \
./arkanoPi_3.0/arkanoPi.d \
./arkanoPi_3.0/arkanoPiLib.d \
./arkanoPi_3.0/fsm.d \
./arkanoPi_3.0/kbhit.d \
./arkanoPi_3.0/ledDisplay.d \
./arkanoPi_3.0/pseudoWiringPi.d \
./arkanoPi_3.0/teclado_TL04.d \
./arkanoPi_3.0/tmr.d 


# Each subdirectory must supply rules for building sources it contributes
arkanoPi_3.0/%.o: ../arkanoPi_3.0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


