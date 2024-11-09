cmake_minimum_required(VERSION 3.16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=nosys.specs")

project(w5500-cmake)

if(NOT DEFINED WIZ_CHIP)
    set(WIZ_CHIP "W5500")
endif()

message("${WIZ_CHIP} ioLibrary Configuration")

set(DRIVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Driver)

string(TOLOWER "${WIZ_CHIP}" WIZ_CHIP_LOWER)

set(DRIVER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/wizchip_port.c
    ${DRIVER_DIR}/Ethernet/${WIZ_CHIP}/${WIZ_CHIP_LOWER}.c
    ${DRIVER_DIR}/Ethernet/socket.c
    ${DRIVER_DIR}/Ethernet/wizchip_conf.c
    ${DRIVER_DIR}/Application/loopback/loopback.c
)

set(DRIVER_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Application/loopback
)

message(${DRIVER_DIR}/${WIZ_CHIP}/${WIZ_CHIP_LOWER}.c)

add_library(wizchip ${DRIVER_SRC})
target_include_directories(wizchip PUBLIC ${DRIVER_INC})
target_compile_options(wizchip PRIVATE ${WIZ_COMPILE_OPTIONS})