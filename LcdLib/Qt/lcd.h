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

#include <QGridLayout>
#include "QCell.h"

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
    bool bIsCursorShift;
    bool bIsBlink;
    bool bIsSingleRow;
    QGridLayout *QSymbols;
    QCell **aCells;
    int iCursorAddr;
};
typedef struct lcd Lcd;

/*
 * 4-bit interface initialization
 *
 */
void lcd_init_qt(Lcd *lcd);

/*
 *	lcd command for shifting cursor on one symbol
 */
void lcd_cmd_shift_qt(Lcd *lcd, bool is_display_shift, bool is_right);

/*
 *	lcd command for cleaning display
 */
void lcd_cmd_clear_qt(Lcd *lcd);

/*
 * Return curor to the start position
 * (0x00)
 */
void lcd_cmd_rethome_qt(Lcd *lcd);

/*
 * Write character to the cursor position
 */
void lcd_putchar_qt(Lcd *lcd, char ch);

/*
 * Write string from the current cursor position
 */
void lcd_putstring_qt(Lcd *lcd, char* str);

/*
 * EMULATOR ONLY
 * Update cell values
 */
void lcd_update_qt(Lcd *lcd);


/*
 * EMULATOR ONLY
 */
void lcd_shift_raw_left_qt(Lcd *lcd, bool is_second_raw);
void lcd_shift_raw_right_qt(Lcd *lcd, bool is_second_raw);
void lcd_set_cursor_by_addr_qt(Lcd *lcd, int iCursorAddrNew);
void lcd_set_symbol_by_addr_qt(Lcd *lcd, int iAddr, char chSymbol);
void lcd_shift_cursor_qt(Lcd *lcd);

extern "C"
{
    void lcd_init(Lcd *lcd);

    void lcd_cmd_shift(Lcd *lcd, bool is_display_shift, bool is_right);

    void lcd_cmd_clear(Lcd *lcd);

    void lcd_cmd_rethome(Lcd *lcd);

    void lcd_putchar(Lcd *lcd, char ch);

    void lcd_putstring(Lcd *lcd, char* str);

    void lcd_set_cursor_by_addr(Lcd *lcd, int iCursorAddrNew);
}

#endif /* INC_LCD_H_ */
