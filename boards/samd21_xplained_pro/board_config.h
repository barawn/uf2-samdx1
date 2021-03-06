#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Atmel Corp"
#define PRODUCT_NAME "Atmel SAMD21-XPRO"
#define VOLUME_LABEL "SAMD21BOOT"
#define INDEX_URL "http://microchip.com/"
#define BOARD_ID "SAMD21-XPRO"

#define USB_VID 0x03EB
#define USB_PID 0x6124

#define LED_PIN PIN_PB30
#define LED_INVERTED

#define BOOT_USART_MODULE SERCOM3
#define BOOT_USART_MASK APBAMASK
#define BOOT_USART_BUS_CLOCK_INDEX MCLK_APBAMASK_SERCOM3
#define BOOT_USART_PAD_SETTINGS UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD0 PINMUX_PA22C_SERCOM3_PAD0
#define BOOT_USART_PAD1 PINMUX_PA23C_SERCOM3_PAD1
#define BOOT_USART_PAD2 PINMUX_UNUSED
#define BOOT_USART_PAD3 PINMUX_UNUSED
#define BOOT_GCLK_ID_CORE SERCOM3_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW SERCOM3_GCLK_ID_SLOW

#endif
