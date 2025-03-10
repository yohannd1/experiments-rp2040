# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(buzzer_shenanigans C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(buzzer_shenanigans
    src/main.c
    src/buzzer.c
)

pico_set_program_name(buzzer_shenanigans "buzzer shenanigans")
pico_set_program_version(buzzer_shenanigans "0.1")

pico_enable_stdio_uart(buzzer_shenanigans 0)
pico_enable_stdio_usb(buzzer_shenanigans 1)

# Add the standard library to the build
target_link_libraries(buzzer_shenanigans
    pico_stdlib
    hardware_pwm
)

# Add the standard include files to the build
target_include_directories(buzzer_shenanigans PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(buzzer_shenanigans
)

pico_add_extra_outputs(buzzer_shenanigans)
