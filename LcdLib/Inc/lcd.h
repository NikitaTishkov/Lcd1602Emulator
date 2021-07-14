/*
 * lcd.h
 *
 *  Created on: Apr 13, 2021
 *      Author: tns
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
#include <stdint.h>
#include <stdbool.h>
#include "LcdLib/Inc/pin.h"
// Emulator includes
#if USE_EMULATOR
    #include <QGridLayout>
    #include "LcdLib/Inc/QCell.h"
#endif
// Clear Display and Return Home commands
static const uint32_t DELAY_CLRRET_US = 15300;
// Read Data from RAM and Write Data to RAM commands
static const uint32_t DELAY_READWRITE_US = 430;
// Read Busy Flag and Address command
static const uint32_t DELAY_BUSYFLAG_US = 0;
// Entry Mode Set, Display ON/OFF Control, Cursor or Display Shift,
// Function Set, Set CGRAM Address, Set DDRAM Address commands
static const uint32_t DELAY_CONTROL_US = 390;
// LCD Enable (E) should be asserted for at least some time. Below is half period delay value
static const uint32_t DELAY_ENA_STROBE_US = 1;
// Initialization procedure have some specific delays. Here we have 2 delays for each init step
static const uint32_t DELAY_INIT0_US = 41000;
static const uint32_t DELAY_INIT1_US = 1000;

typedef void (*delay_func_t)(uint16_t);

/* Struct that represents Lcd in scope of library
 * 4-bit conversation
 *
 * */
struct lcd{
#if (!USE_EMULATOR)
	Pin data_pins[4];
	Pin rs_pin;
	Pin rw_pin;
	Pin e_pin;
	delay_func_t func_delay_us;
	delay_func_t func_delay_ms;
#else
    bool bIsCursorShift;
    bool bIsBlink;
    bool bIsSingleRow;
    QGridLayout *QSymbols;
    QCell **aCells;
    int iCursorAddr;
#endif

};
typedef struct lcd Lcd;

/*
 * ON_BOARD ONLY
 * Function for setting 4 bits on
 * 4-bit interface gpios
 */
void lcd_set_halfbyte(Lcd *lcd, uint8_t half);

/*
 * ON_BOARD ONLY
 * delay function with useconds that used by lib
 *
 */
void lcd_delay_us(Lcd *lcd, uint16_t usec);

/*
 * ON_BOARD ONLY
 * delay function with mseconds that used by lib
 *
 */
void lcd_delay_ms(Lcd *lcd, uint16_t msec);

/*
 * ON_BOARD ONLY
 * Helper function for setting rs and rw gpios
 */
void lcd_set_rsrw(Lcd *lcd, uint8_t rs, uint8_t rw);

/*
 * ON_BOARD ONLY
 * Setting byte on 4-bit interface
 */
void lcd_data_set_byte(Lcd *lcd, uint8_t byte);

/*
 * ON_BOARD ONLY
 * Setting all data and control pins
 * in scope of 4-bit interface
 */
void lcd_send_byte(Lcd *lcd, uint8_t rs, uint8_t rw, uint8_t byte);

/*
 * ON_BOARD ONLY
 * Additional function for setting byte on
 * 4-bit interface, but with with a delay
 * between two 4-bit transactions
 */
void lcd_data_set_byte_with_delay(Lcd *lcd, uint8_t byte, uint16_t delay);

/*
 * ON_BOARD ONLY
 * Setting all data and control pins, but
 * with delay between two 4-bit transaction
 *  using lcd_data_set_byte_wit_delay(...)
 */
void lcd_send_byte_with_delay(Lcd *lcd, uint8_t rs, uint8_t rw, uint8_t byte, uint16_t delay);

/*
 * 4-bit interface initialization
 *
 */
void lcd_init(Lcd *lcd);

/*
 *	lcd command for shifting cursor on one symbol
 */
void lcd_cmd_shift(Lcd *lcd, bool is_display_shift, bool is_right);

/*
 *	lcd command for cleaning display
 */
void lcd_cmd_clear(Lcd *lcd);

/*
 * ON_BOARD ONLY
 * Converts chars to byte representation
 */
uint8_t lcd_latin_charmap(char ch);

/*
 * Return curor to the start position
 * (0x00)
 */
void lcd_cmd_rethome(Lcd *lcd);

/*
 * Write character to the cursor position
 */
void lcd_putchar(Lcd *lcd, char ch);

/*
 * Write string from the current cursor position
 */
void lcd_putstring(Lcd *lcd, char* str);

/*
 * EMULATOR ONLY
 */
#if (USE_EMULATOR)
void lcd_update(Lcd *lcd);
#endif

/*
 * EMULATOR ONLY
 */
#if (USE_EMULATOR)
void lcd_shift_raw_left(Lcd *lcd, bool is_second_raw);
void lcd_shift_raw_right(Lcd *lcd, bool is_second_raw);
void lcd_set_cursor_by_addr(Lcd *lcd, int iCursorAddrNew);
void lcd_set_symbol_by_addr(Lcd *lcd, int iAddr, char chSymbol);
void lcd_shift_cursor(Lcd *lcd);
#endif
#endif /* INC_LCD_H_ */
