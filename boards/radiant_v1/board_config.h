#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Ohio State"
#define PRODUCT_NAME "RADIANTv1.0"
#define VOLUME_LABEL "RADIANTBOOT"
// uh... who cares
#define INDEX_URL "http://adafru.it/"
#define BOARD_ID "SAMD21J18A-RADIANT-v1"

#define USB_VID 0x239A
#define USB_PID 0x0015

#define LED_PIN PIN_PB23

// The BOOT_USART is SERCOM1, using PA00 (TX) and PA01 (RX)
// Note that TX/RX are always from *this* board's perspective.
// PA00 is PAD0 so this means we're doing
// UART_RX_PAD1_TX_PAD0
// 
#define BOOT_USART_MODULE SERCOM1
#define BOOT_USART_MASK APBAMASK
#define BOOT_USART_BUS_CLOCK_INDEX MCLK_APBAMASK_SERCOM1
#define BOOT_USART_PAD_SETTINGS UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD2 PINMUX_UNUSED
#define BOOT_USART_PAD3 PINMUX_UNUSED
#define BOOT_USART_PAD1 PINMUX_PA01D_SERCOM1_PAD1
#define BOOT_USART_PAD0 PINMUX_PA00D_SERCOM1_PAD0
#define BOOT_GCLK_ID_CORE SERCOM1_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW SERCOM1_GCLK_ID_SLOW

#define USE_BOARD_EARLY_STARTUP
// we need to quick-restore the following:
// PA02 : EN2V6
// PB08 : EN3V1
// PA04 : EN1V8
// PA06 : EN2V5
// PB02 : EN1V0
// so port A is bit 2, 4, 6.
// and port B is 2, 8
// to do this, we need to enable the input
// buffer, which is done via
// REG_PORT_WRCONFIG0 = WRCONFIG_WRPINCFG | WRCONFIG_INEN
// then we capture the current state by reading the full input register,
// masking it, and writing it to the output register.
// Then we direction-set the pins.
// In the end this is only a handful of writes.

#define USE_BOARD_EARLY_STARTUP_DEFINES
#define BOARD_EARLY_STARTUP_DEFINES					\
  const uint32_t A_bitmask = (PORT_PA02 | PORT_PA04 | PORT_PA06);	\
  const uint32_t B_bitmask = (PORT_PB02 | PORT_PB08);	                \
  const PORT_WRCONFIG_Type wrconfig_A = {		                \
    .bit.WRPINCFG = 1,							\
    .bit.INEN = 1,	                                                \
    .bit.PINMASK = (uint16_t) (PORT_PA02 | PORT_PA04 | PORT_PA06)	\
  };								        \
  const PORT_WRCONFIG_Type wrconfig_B = {	                        \
    .bit.WRPINCFG = 1,							\
    .bit.INEN = 1,                                                      \
    .bit.PINMASK = (uint16_t) (PORT_PB02 | PORT_PB08)	                \
  }

#define BOARD_EARLY_STARTUP()					    \
  PORT->Group[0].WRCONFIG.reg = wrconfig_A.reg;			    \
  PORT->Group[1].WRCONFIG.reg = wrconfig_B.reg;			    \
  PORT->Group[0].OUT.reg = (PORT->Group[0].IN.reg & A_bitmask);	    \
  PORT->Group[1].OUT.reg = (PORT->Group[1].IN.reg & B_bitmask);	    \
  PORT->Group[0].DIR.reg = A_bitmask;				    \
  PORT->Group[1].DIR.reg = B_bitmask

#endif
