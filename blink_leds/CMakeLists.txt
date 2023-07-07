cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME PICO_BLINK_LEDS)

# Include SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)


project(${PROJECT_NAME} C CXX ASM)
# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# add_compile_options(-Wall -Wno-format -Wno-unused-function -Wno-maybe-uninitialized -Wno-unused-variable)

add_executable(${PROJECT_NAME}
    blink_leds.cpp
)

# Add pico_stdlib library which aggregates commonly used features

target_link_libraries(${PROJECT_NAME}
  pico_stdlib
  hardware_uart
  hardware_gpio 
  hardware_pwm
)

# Enable USB output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Create map/bin/hex/uf2 file in addition to ELF 
pico_add_extra_outputs(${PROJECT_NAME})
