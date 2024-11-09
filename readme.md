# WIZCHIP-CMake

This library provides SPI communication support for the WIZnet Ethernet chip such as W5500. It is designed to be easily integrated into embedded systems using CMake, providing a streamlined setup process for users.

## Quick Guide

### CMakeLists.txt

```cmake
set(WIZ_CHIP "W5500")  # You may use other chips listed on ioLibrary_Driver
#set(WIZ_COMPILE_OPTIONS ...) # Auxiliary options for library compilation

FetchContent_Declare(
  wizchip
  GIT_REPOSITORY https://github.com/donghoonpark/wizchip-cmake
  GIT_SHALLOW TRUE
)

FetchContent_GetProperties(wizchip)
if(NOT wizchip_POPULATED)
    message(STATUS "Fetching wizchip...")
    FetchContent_MakeAvailable(wizchip)
else()
    message(STATUS "wizchip already populated")
endif()

target_link_libraries(your_project_target wizchip)
```

### Example 

For STM32-based systems, register the hardware-specific functions to initialize the W5500 chip

```c
// Example SPI and GPIO handles for STM32
#include <wizchip.h>

SPI_HandleTypeDef hspi1;

int main()
{
    //Initialize system
    ...
    wizchip_register_hal(
        &hspix,                        // SPI handle (e.g., hspi1 for STM32)
        HAL_SPI_Receive,               // SPI receive function
        HAL_SPI_Transmit,              // SPI transmit function
        HAL_SPI_Receive_DMA,           // SPI receive DMA function (use NULL if not available)
        HAL_SPI_Transmit_DMA,          // SPI transmit DMA function (use NULL if not available)
        GPIOx,                  // GPIO port for CS pin
        GPIO_PIN_xx,                   // GPIO pin for CS
        HAL_GPIO_WritePin              // GPIO write function
    );

    // You can w5500 socket from here!
}

// DMA transaction complete callbacks
// interrupt must be enabled by default

#if USE_HAL_SPI_REGISTER_CALLBACKS == 0

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    wizchip_dma_rx_cplt((void*) hspi);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    wizchip_dma_tx_cplt((void*) hspi);
}

#endif
```