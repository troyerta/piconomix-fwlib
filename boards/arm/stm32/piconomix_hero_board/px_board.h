#ifndef __PX_BOARD_H__
#define __PX_BOARD_H__
/* =============================================================================
     ____    ___    ____    ___    _   _    ___    __  __   ___  __  __ TM
    |  _ \  |_ _|  / ___|  / _ \  | \ | |  / _ \  |  \/  | |_ _| \ \/ /
    | |_) |  | |  | |     | | | | |  \| | | | | | | |\/| |  | |   \  /
    |  __/   | |  | |___  | |_| | | |\  | | |_| | | |  | |  | |   /  \
    |_|     |___|  \____|  \___/  |_| \_|  \___/  |_|  |_| |___| /_/\_\

    Copyright (c) 2017 Pieter Conradie <https://piconomix.com>
 
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
   
    Title:          board.h : Piconomix STM32 Hero Board
    Author(s):      Pieter Conradie
    Creation Date:  2017-11-13

============================================================================= */
/** 
 *  @ingroup BOARDS_STM32
 *  @defgroup BOARDS_STM32_PICONOMIX_HERO px_board.h : Piconomix STM32 Hero Board
 *  
 *  File(s):
 *  - boards/arm/stm32/piconomix_hero_board/px_board.h 
 *  - boards/arm/stm32/piconomix_hero_board/px_board_gpio.h 
 *  - boards/arm/stm32/piconomix_hero_board/px_board.c
 */   
/// @{

/* _____STANDARD INCLUDES____________________________________________________ */

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "px_defines.h"
#include "px_board_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif
/* _____DEFINITIONS__________________________________________________________ */
/// Board name
#define PX_BOARD_PICONOMIX_HERO_BOARD

/// System clock frequency in Hz
#define PX_BOARD_SYS_CLK_HZ     32000000ul

/// Peripheral clock frequency in Hz
#define PX_BOARD_PER_CLK_HZ     PX_BOARD_SYS_CLK_HZ

/* _____TYPE DEFINITIONS_____________________________________________________ */
/// Identify which GPIO pins are used for CS in px_board_spi_cs_lo() and px_board_spi_cs_hi()
typedef enum
{
    PX_BOARD_SPI_CS_NONE,      ///< Do not perform a chip select
    PX_BOARD_SPI1_CS,          ///< Peripheral CS
    PX_BOARD_SPI1_CS_SD,       ///< SD Card
    PX_BOARD_SPI2_CS_LCD,      ///< JHD JHD12864-G176BSW 128x64 monochrome LCD
    PX_BOARD_SPI2_CS_SF,       ///< Adesto AT45D DataFLASH    
} px_board_spi_cs_t;

/// @name Mapping of board's ADC pins to ADC channels
//@{
#define PX_BOARD_ADC0       PX_ADC_CH8
#define PX_BOARD_ADC1       PX_ADC_CH15
#define PX_BOARD_ADC2       PX_ADC_CH14
#define PX_BOARD_ADC3       PX_ADC_CH7
#define PX_BOARD_ADC_VBAT   PX_ADC_CH9
//@}

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION DECLARATIONS_________________________________________ */
/// Initialise the board hardware
void px_board_init(void);

/**
 *  Set specified SPI Chip Select low
 *  
 *  @param cs_id    ID which GPIO pin must be used for Chip Select
 */
void px_board_spi_cs_lo(uint8_t cs_id);

/**
 *  Set specified SPI Chip Select high
 *  
 *  @param cs_id    ID which GPIO pin must be used for Chip Select
 */
void px_board_spi_cs_hi(uint8_t cs_id);

/**
 *  Initialise Timer 6 with 1 us clock ticks for delay use
 *  
 */
void px_board_delay_init(void);

/**
 *  Disable Timer 6
 *  
 */
void px_board_delay_deinit(void);

/**
 *  Blocking delay for specified number of microseconds.
 *  
 *  @param delay_us  Number of microseconds to block
 */
void px_board_delay_us(uint16_t delay_us);

/**
 *  Blocking delay for specified number of milliseconds.
 *  
 *  @param delay_ms  Number of milliseconds to block
 */
void px_board_delay_ms(uint16_t delay_ms);

/**
 *  Enable PWM output to piezo buzzer at specified frequency.
 *  
 *  @param freq_hz PWM frequency in Hz
 */
void px_board_buzzer_on(uint16_t freq_hz);

/** 
 *  Disable PWM output to piezo buzzer.
 */
void px_board_buzzer_off(void);

/**
 *  Disable DBG module.
 */
void px_board_dbg_disable(void);

/**
 *  Enter low power STOP mode and wait for interrupt to wake up core
 *  
 *  NB! Debug module must be disabled during STOP mode, otherwise SysTick
 *  interrupt will wake up core.
 */
void px_board_stop_mode(void);


/* _____MACROS_______________________________________________________________ */
/// User button
#define PX_USR_PB_IS_PRESSED()      px_gpio_pin_is_lo(&px_gpio_lcd_btn_6_yes)

/// User LED
#define PX_USR_LED_ON()             px_gpio_pin_set_hi(&px_gpio_usr_led)
#define PX_USR_LED_OFF()            px_gpio_pin_set_lo(&px_gpio_usr_led)
#define PX_USR_LED_TOGGLE()         px_gpio_pin_toggle(&px_gpio_usr_led)

/// LCD
#define PX_LCD_RS_LO()              px_gpio_pin_set_lo(&px_gpio_lcd_rs)
#define PX_LCD_RS_HI()              px_gpio_pin_set_hi(&px_gpio_lcd_rs)
#define PX_LCD_BACKLIGHT_ON()       px_gpio_pin_set_lo(&px_gpio_lcd_backlight)
#define PX_LCD_BACKLIGHT_OFF()      px_gpio_pin_set_hi(&px_gpio_lcd_backlight)

// SD Card
#define PX_SD_CARD_DETECTED()       px_gpio_pin_is_lo(&px_gpio_7_sd_cd)

// Battery voltage measurement
#define PX_VBAT_MEAS_ENABLE()       px_gpio_pin_set_hi(&px_gpio_vbat_meas_en)
#define PX_VBAT_MEAS_DISABLE()      px_gpio_pin_set_lo(&px_gpio_vbat_meas_en)

// Power hold
#define PX_POWER_OFF()              px_gpio_pin_set_lo(&px_gpio_3v3_hold)

/// @}
#ifdef __cplusplus
}
#endif

#endif // #ifndef __PX_BOARD_H__
