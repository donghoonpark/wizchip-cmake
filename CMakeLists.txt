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
  GIT_TAG master
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
    ${DRIVER_DIR}/Application/multicast/multicast.c
)

set(DRIVER_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Application/loopback
    ${DRIVER_DIR}/Application/multicast
)

add_library(wizchip ${DRIVER_SRC})
target_include_directories(wizchip PUBLIC ${DRIVER_INC})
target_compile_options(wizchip PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(dhcp ${DRIVER_DIR}/Internet/DHCP/dhcp.c)
target_include_directories(dhcp PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/DHCP
    )
target_compile_options(dhcp PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(dns ${DRIVER_DIR}/Internet/DNS/dns.c)
target_include_directories(dns PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/DNS
    )
target_compile_options(dns PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(ftp_client ${DRIVER_DIR}/Internet/FTPClient/ftpc.c)
target_include_directories(ftp_client PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/FTPClient
    )
target_compile_options(ftp_client PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(ftp_server ${DRIVER_DIR}/Internet/FTPServer/ftpd.c)
target_include_directories(ftp_server PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/FTPServer
    )
target_compile_options(ftp_server PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(http_server 
    ${DRIVER_DIR}/Internet/httpServer/httpParser.c
    ${DRIVER_DIR}/Internet/httpServer/httpServer.c
    ${DRIVER_DIR}/Internet/httpServer/httpUtil.c
    )
target_include_directories(http_server PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/httpServer
    )
target_compile_options(http_server PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(mqtt 
    ${DRIVER_DIR}/Internet/MQTT/mqtt_interface.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTClient.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTFormat.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTPacket.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c
    )
target_include_directories(mqtt PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/MQTT
    ${DRIVER_DIR}/Internet/MQTT/MQTTPacket/src
    )
target_compile_options(mqtt PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(snmp 
    ${DRIVER_DIR}/Internet/SNMP/snmp.c
    ${DRIVER_DIR}/Internet/SNMP/snmp_custom.c
    )
target_include_directories(snmp PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/SNMP
    )
target_compile_options(snmp PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(sntp ${DRIVER_DIR}/Internet/SNTP/sntp.c)
target_include_directories(sntp PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/SNTP
    )
target_compile_options(sntp PRIVATE ${WIZ_COMPILE_OPTIONS})

add_library(tftp 
    ${DRIVER_DIR}/Internet/TFTP/tftp.c
    ${DRIVER_DIR}/Internet/TFTP/netutil.c
    )
target_include_directories(tftp PUBLIC 
    ${DRIVER_DIR}/Ethernet
    ${DRIVER_DIR}/Internet/TFTP
    )
target_compile_options(tftp PRIVATE ${WIZ_COMPILE_OPTIONS})
