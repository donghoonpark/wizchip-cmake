# WIZCHIP-CMake

This library provides SPI communication support for the WIZnet Ethernet chip such as W5500. It is designed to be easily integrated into embedded systems using CMake, providing a streamlined setup process for users.

## Quick Guide

### CMakeLists.txt

```cmake
set(WIZ_CHIP "W5500")  # You may use other chips listed on ioLibrary_Driver but it is not yet been tested
add_subdirectory(path/to/w5500-cmake)
target_link_libraries(your_project_target wizchip)
```

### Example 

For STM32-based systems, register the hardware-specific functions to initialize the W5500 chip

```c
// Example SPI and GPIO handles for STM32
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
}
```