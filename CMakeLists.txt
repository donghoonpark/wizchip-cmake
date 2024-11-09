cmake_minimum_required(VERSION 3.16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=nosys.specs")

project(w5500-cmake)

if(NOT DEFINED WIZ_CHIP)
    set(WIZ_CHIP "W5500")
endif()

include(FetchContent)
message("${WIZ_CHIP} ioLibrary Configuration")

string(TOLOWER "${WIZ_CHIP}" WIZ_CHIP_LOWER)

FetchContent_Declare(
  ioLibrary_Driver
  GIT_REPOSITORY https://github.com/Wiznet/ioLibrary_Driver
  GIT_TAG b981401e7f3d07015619adf44c13998e13e777f9
  GIT_SHALLOW TRUE
)

FetchContent_GetProperties(iolibrary_driver)
if(NOT iolibrary_driver_POPULATED)
    message(STATUS "Fetching ioLibrary_Driver...")
    FetchContent_MakeAvailable(ioLibrary_Driver)
else()
    message(STATUS "ioLibrary_Driver already populated")
endif()

set(DRIVER_DIR ${iolibrary_driver_SOURCE_DIR})

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

add_library(wizchip ${DRIVER_SRC})
target_include_directories(wizchip PUBLIC ${DRIVER_INC})
target_compile_options(wizchip PRIVATE ${WIZ_COMPILE_OPTIONS})