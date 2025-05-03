cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

set(FREERTOS_KERNEL_PATH "/home/yohanan/pj/clone/FreeRTOS-Kernel")
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

set(PROJECT rtos_leds)
project(${PROJECT} C CXX ASM)
include_directories(${PROJECT} ${CMAKE_SOURCE_DIR}/src)

pico_sdk_init()

add_executable(${PROJECT}
    src/main.c
)

target_link_libraries(${PROJECT}
    pico_stdlib
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)

pico_add_extra_outputs(${PROJECT})
