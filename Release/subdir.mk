################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../Helpers.ino \
../Nixieklok.ino 

CPP_SRCS += \
../sloeber.ino.cpp 

LINK_OBJ += \
./sloeber.ino.cpp.o 

INO_DEPS += \
./Helpers.ino.d \
./Nixieklok.ino.d 

CPP_DEPS += \
./sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Helpers.o: ../Helpers.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/libraries/Wire" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Nixieklok.o: ../Nixieklok.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/libraries/Wire" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

sloeber.ino.cpp.o: ../sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/cores/arduino" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/variants/eightanaloginputs" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/libraries/Wire" -I"/Applications/Eclipse/arduino-oxygen/Eclipse.app/Contents/MacOS/arduinoPlugin/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


