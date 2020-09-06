################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AIComponent.cpp \
../AIState.cpp \
../Bullet.cpp \
../CircleComponent.cpp \
../Component.cpp \
../Enemy.cpp \
../Game.cpp \
../GameObject.cpp \
../Grid.cpp \
../Math.cpp \
../MoveComponent.cpp \
../NavigationComponent.cpp \
../SpriteComponent.cpp \
../Tile.cpp \
../Tower.cpp \
../main.cpp 

OBJS += \
./AIComponent.o \
./AIState.o \
./Bullet.o \
./CircleComponent.o \
./Component.o \
./Enemy.o \
./Game.o \
./GameObject.o \
./Grid.o \
./Math.o \
./MoveComponent.o \
./NavigationComponent.o \
./SpriteComponent.o \
./Tile.o \
./Tower.o \
./main.o 

CPP_DEPS += \
./AIComponent.d \
./AIState.d \
./Bullet.d \
./CircleComponent.d \
./Component.d \
./Enemy.d \
./Game.d \
./GameObject.d \
./Grid.d \
./Math.d \
./MoveComponent.d \
./NavigationComponent.d \
./SpriteComponent.d \
./Tile.d \
./Tower.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


