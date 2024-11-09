#ifndef WIZCHIP_PORT_H
#define WIZCHIP_PORTH_H

#include <stdint.h>

typedef enum {
    __OK       = 0x00U,
    __ERROR    = 0x01U,
    __BUSY     = 0x02U,
    __TIMEOUT  = 0x03U
}eHalStatus;

typedef enum {
    __RESET = 0,
    __SET
}eGpioPinState;

typedef eHalStatus (*fHalSpiTransaction)   (volatile void* handle, uint8_t* buf, uint16_t size, uint32_t timeout);
typedef eHalStatus (*fHalSpiTransactionDma)(volatile void* handle, uint8_t* buf, uint16_t size);
typedef void (*fHalGpioWritePin)(volatile void* handle, uint16_t pin, eGpioPinState state);


void wizchip_register_hal(
    void* _hspi,
    fHalSpiTransaction      _hal_spi_receive,
    fHalSpiTransaction      _hal_spi_transmit,
    fHalSpiTransactionDma   _hal_spi_receive_dma,
    fHalSpiTransactionDma   _hal_spi_transmit_dma,
    void*                   _cs_gpiox,
    uint16_t                _cs_gpio_pin,
    fHalGpioWritePin        _hal_gpio_write_pin
);

void wizchip_dma_tx_cplt(void* handle);
void wizchip_dma_rx_cplt(void* handle);

#endif