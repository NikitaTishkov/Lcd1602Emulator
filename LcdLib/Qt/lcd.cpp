/*
 * lcd.c
 *
 *  Created on: Apr 13, 2021
 *      Author: tns
 */
#include "lcd.h"

void lcd_init_qt(Lcd *lcd)
{
    lcd->aCells = new QCell*[2];
    lcd->aCells[0] = new QCell[16];
    for(int i = 0; i < 16; i++)
    {
        lcd->QSymbols->addWidget(&lcd->aCells[0][i], 0, i);
        lcd->aCells[0][i].SetAddr(0x00 + i);
    }

    if(!lcd->bIsSingleRow)
    {
        lcd->aCells[1] = new QCell[16];
        for(int i = 0; i < 16; i++)
        {
            lcd->QSymbols->addWidget(&lcd->aCells[1][i], 1, i);
            lcd->aCells[1][i].SetAddr(0x40 + i);
        }
    }

    lcd_update_qt(lcd);
}

void lcd_cmd_clear_qt(Lcd *lcd)
{
    for(int i = 0; i < 16; i++)
        lcd->aCells[0][i].SetSymbol(' ');
    if(!lcd->bIsSingleRow)
    {
        for(int i = 0; i < 16; i++)
            lcd->aCells[1][i].SetSymbol(' ');
    }
    lcd_update_qt(lcd);
}

void lcd_shift_raw_right_qt(Lcd *lcd, bool is_second_raw)
{
    int raw_num = 0;
    if(is_second_raw)
        raw_num = 1;
    for(int i = 14; i >= 0; i--)
    {
        lcd->aCells[raw_num][i + 1].SetSymbol(lcd->aCells[raw_num][i].GetSymbol());
    }
    lcd->aCells[raw_num][0].SetSymbol(' ');
    lcd_update_qt(lcd);
}

void lcd_shift_raw_left_qt(Lcd *lcd, bool is_second_raw)
{
    int raw_num = 0;
    if(is_second_raw)
        raw_num = 1;
    for(int i = 0; i < 14; i++)
    {
        lcd->aCells[raw_num][i].SetSymbol(lcd->aCells[raw_num][i + 1].GetSymbol());
    }
    lcd->aCells[raw_num][15].SetSymbol(' ');
    lcd_update_qt(lcd);
}

void lcd_shift_cursor_qt(Lcd *lcd)
{
    if(lcd->iCursorAddr == 0x0F)
    {
        lcd_set_cursor_by_addr_qt(lcd, 0x00);
    }
    else if(lcd->iCursorAddr == 0x4F)
    {
        lcd_set_cursor_by_addr_qt(lcd, 0x40);
    }
    else
    {
        lcd_set_cursor_by_addr_qt(lcd, lcd->iCursorAddr + 1);
    }
}

void lcd_cmd_shift_qt(Lcd *lcd, bool is_display_shift, bool is_right)
{
    if(is_display_shift)
    {
        for(int j = 0; j < 2; j++)
        {
            if(is_right)
            {
                lcd_shift_raw_right_qt(lcd, j);
            }
            else
            {
                lcd_shift_raw_left_qt(lcd, j);
            }
            if(lcd->bIsSingleRow)
            {
                break;
            }
        }
    }
    else
    {
        lcd_shift_cursor_qt(lcd);
    }
}

void lcd_cmd_rethome_qt(Lcd *lcd)
{

    lcd_set_cursor_by_addr_qt(lcd, 0x00);

}

void lcd_putchar_qt(Lcd *lcd, char ch)
{

    lcd_set_symbol_by_addr_qt(lcd, lcd->iCursorAddr, ch);
    lcd_shift_cursor_qt(lcd);

}

void lcd_putstring_qt(Lcd *lcd, char* str) // dummy example
{

	char *ptr = str;
	while(*ptr != '\0')
	{
		if(*ptr == ' ')
		{
			lcd_cmd_shift_qt(lcd, 0, 1);
		}
		else
		{
			lcd_putchar_qt(lcd, *ptr);
		}
		ptr++;

	}
}

void lcd_update_qt(Lcd *lcd)
{
    for(int i = 0; i < 16; i++)
        lcd->aCells[0][i].Update();

    if(!lcd->bIsSingleRow)
    {
        for(int i = 0; i < 16; i++)
        {
            lcd->aCells[1][i].Update();
        }
    }
}

void lcd_set_cursor_by_addr_qt(Lcd *lcd, int iCursorAddrNew)
{
    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < 16; i++)
        {
            if(lcd->bIsSingleRow && j == 1)
                break;
            if(lcd->aCells[j][i].GetAddr() == lcd->iCursorAddr)
            {
                lcd->aCells[j][i].CursorOff();
            }
        }
    }

    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < 16; i++)
        {
            if(lcd->bIsSingleRow && j == 1)
                break;
            if(lcd->aCells[j][i].GetAddr() == iCursorAddrNew)
            {
                lcd->aCells[j][i].ActivateCursor();
                lcd->iCursorAddr = iCursorAddrNew;
            }
        }
    }
}

void lcd_set_symbol_by_addr_qt(Lcd *lcd, int iAddr, char chSymbol)
{
    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < 16; i++)
        {
            if(lcd->aCells[j][i].GetAddr() == iAddr)
            {
                lcd->aCells[j][i].SetSymbol(chSymbol);
            }
        }
        if(lcd->bIsSingleRow)
            break;
    }
    lcd_update_qt(lcd);
}


/* WRAPPERS */
void lcd_init(Lcd *lcd)
{
	lcd_init_qt(lcd);
}

void lcd_cmd_shift(Lcd *lcd, bool is_display_shift, bool is_right)
{
	lcd_cmd_shift_qt(lcd, is_display_shift, is_right);
}

void lcd_cmd_clear(Lcd *lcd)
{
	lcd_cmd_clear_qt(lcd);
}

void lcd_cmd_rethome(Lcd *lcd)
{
	lcd_cmd_rethome_qt(lcd);
}

void lcd_putchar(Lcd *lcd, char ch)
{
	lcd_putchar_qt(lcd, ch);
}

void lcd_putstring(Lcd *lcd, char* str)
{
	lcd_putstring_qt(lcd, str);
}

void lcd_set_cursor_by_addr(Lcd *lcd, int iCursorAddrNew)
{
    lcd_set_cursor_by_addr_qt(lcd, iCursorAddrNew);
}
