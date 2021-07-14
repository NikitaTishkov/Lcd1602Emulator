#include "LcdLib/Inc/mainfunction.h"

void WorkCycle(Lcd *lcd)
{
    lcd_set_cursor_by_addr(lcd, 0x00);
    lcd_putstring(lcd, "Hello");
}
