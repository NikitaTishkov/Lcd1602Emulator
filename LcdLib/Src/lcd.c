/*
 * lcd.c
 *
 *  Created on: Apr 13, 2021
 *      Author: tns
 */
#include "LcdLib/Inc/lcd.h"
#if (!USE_EMULATOR)
    void lcd_delay_us(Lcd *lcd, uint16_t usec)
    {
        lcd->func_delay_us(usec);
    }

    void lcd_delay_ms(Lcd *lcd, uint16_t msec)
    {
        lcd->func_delay_ms(msec);
    }

    void lcd_set_halfbyte(Lcd *lcd, uint8_t half)
    {
        gpio_clear(&lcd->e_pin);

        uint8_t bit;
        for (uint8_t i = 0; i < 4; i++)
        {
            bit = half & (1 << i);
            if(bit >= 1)
            {
                HAL_GPIO_WritePin(lcd->data_pins[i].port, lcd->data_pins[i].pin, 1);
            }
            else
            {
                HAL_GPIO_WritePin(lcd->data_pins[i].port, lcd->data_pins[i].pin, 0);
            }

        }
        lcd_delay_us(lcd, DELAY_ENA_STROBE_US);
        gpio_set(&lcd->e_pin);
        lcd_delay_us(lcd, DELAY_ENA_STROBE_US);
        gpio_clear(&lcd->e_pin);
        lcd_delay_us(lcd, DELAY_ENA_STROBE_US);

    }

    void lcd_set_rsrw(Lcd *lcd, uint8_t rs, uint8_t rw)
    {
        gpio_write(&lcd->rs_pin, rs);

        gpio_write(&lcd->rw_pin, rw);

    }

    void lcd_data_set_byte(Lcd *lcd, uint8_t byte)
    {
        lcd_set_halfbyte(lcd, byte >> 4);
        //lcd_delay_us(lcd, DELAY_CONTROL_US/10);
        lcd_set_halfbyte(lcd, byte & 0x0F);
    }

    void lcd_data_set_byte_with_delay(Lcd *lcd, uint8_t byte, uint16_t delay)
    {
        lcd_set_halfbyte(lcd, byte >> 4);
        lcd_delay_us(lcd, delay);
        lcd_set_halfbyte(lcd, byte & 0x0F);
    }

    void lcd_send_byte(Lcd *lcd, uint8_t rs, uint8_t rw, uint8_t byte)
    {
        lcd_set_rsrw(lcd, rs, rw);
        lcd_data_set_byte(lcd, byte);
    }

    void lcd_send_byte_with_delay(Lcd *lcd, uint8_t rs, uint8_t rw, uint8_t byte, uint16_t delay)
    {
        lcd_set_rsrw(lcd, rs, rw);
        lcd_data_set_byte_with_delay(lcd, byte, delay);
    }
#endif
void lcd_init(Lcd *lcd)
{
#if (!USE_EMULATOR)
	HAL_Delay(40);

	lcd_set_rsrw(lcd, 0, 0);
	lcd_set_halfbyte(lcd, 0b0011);
	lcd_delay_us(lcd, DELAY_INIT0_US);

	lcd_set_rsrw(lcd, 0, 0);
	lcd_data_set_byte(lcd, 0b00100100);
	lcd_delay_us(lcd, DELAY_INIT1_US);

	lcd_set_rsrw(lcd, 0, 0);
	lcd_data_set_byte(lcd, 0b00100100);
	lcd_delay_us(lcd, DELAY_INIT1_US);

	lcd_set_rsrw(lcd, 0, 0);
	lcd_data_set_byte(lcd, 0b00001110);
	lcd_delay_us(lcd, DELAY_CONTROL_US);

	lcd_set_rsrw(lcd, 0, 0);
	lcd_data_set_byte(lcd, 0b00000001);
	lcd_delay_us(lcd, DELAY_CLRRET_US);

	lcd_set_rsrw(lcd, 0, 0);
	lcd_data_set_byte(lcd, 0b00000110);
	lcd_delay_us(lcd, DELAY_CONTROL_US);
#else
    if(lcd->bIsSingleRow)
    {
        lcd->aCells[0] = new QCell[16];
        for(int i = 0; i < 16; i++)
        {

        }
    }
#endif
}


void lcd_cmd_clear(Lcd *lcd)
{
	lcd_set_rsrw(lcd, 0, 0);
	lcd_data_set_byte(lcd, 0b00000001);
	lcd_delay_us(lcd, DELAY_CLRRET_US);
}

void lcd_cmd_shift(Lcd *lcd, bool is_display_shift, bool is_right)
{
	uint8_t cmd_byte = 0b00010000;
	if(is_display_shift)
		cmd_byte = cmd_byte | 0b00001000;

	if(is_right)
		cmd_byte = cmd_byte | 0b00000100;

	lcd_send_byte_with_delay(lcd, 0, 0, cmd_byte, 39);
	lcd_delay_us(lcd, DELAY_CONTROL_US);
}

void lcd_cmd_set_addr(Lcd *lcd, uint8_t addr)
{
	if( (addr >= 0x00 && addr <= 0x0F) || (addr >= 0x40 && addr <= 0x4F) )
	{
		addr |= 0b10000000;
		lcd_send_byte_with_delay(lcd, 0, 0, addr, 39);
		lcd_delay_us(lcd, DELAY_CONTROL_US);
	}
}

void lcd_cmd_rethome(Lcd *lcd)
{
	lcd_send_byte_with_delay(lcd, 0, 0, 0b00000010, 39);
	lcd_delay_us(lcd, DELAY_CLRRET_US);
}

void lcd_putchar(Lcd *lcd, char ch)
{
	lcd_send_byte_with_delay(lcd, 1, 0, lcd_latin_charmap(ch), 39);
	lcd_delay_us(lcd, DELAY_CONTROL_US);
}

void lcd_putstring(Lcd *lcd, char* str) // dummy example
{
	char *ptr = str;
	while(*ptr != '\0')
	{
		if(*ptr == ' ')
		{
			lcd_cmd_shift(lcd, 0, 1);
		}
		else
		{
			lcd_putchar(lcd, *ptr);
		}
		ptr++;

	}
}



uint8_t lcd_latin_charmap(char ch)
{
	switch(ch)
	{

	case '!':
			return 0x21;
		break;
	case '"':
			return 0x22;
		break;
	case '#':
			return 0x23;
		break;
	case '$':
			return 0x24;
		break;
	case '%':
			return 0x25;
		break;
	case '&':
			return 0x26;
		break;
	case '\'':
			return 0x27;
		break;
	case '(':
			return 0x28;
		break;
	case ')':
			return 0x29;
		break;
	case '*':
			return 0x2A;
		break;
	case '+':
			return 0x2B;
		break;
	case ',':
			return 0x2C;
		break;
	case '-':
			return 0x2D;
		break;
	case '.':
			return 0x2E;
		break;
	case '/':
			return 0x2F;
		break;
/*----------------------*/

	case '0':
			return 0x30;
		break;
	case '1':
			return 0x31;
		break;
	case '2':
			return 0x32;
		break;
	case '3':
			return 0x33;
		break;
	case '4':
			return 0x34;
		break;
	case '5':
			return 0x35;
		break;
	case '6':
			return 0x36;
		break;
	case '7':
			return 0x37;
		break;
	case '8':
			return 0x38;
		break;
	case '9':
			return 0x39;
		break;
	case ':':
			return 0x3A;
		break;
	case ';':
			return 0x3B;
		break;
	case '<':
			return 0x3C;
		break;
	case '=':
			return 0x3D;
		break;
	case '>':
			return 0x3E;
		break;
	case '?':
			return 0x3F;
		break;
/* -------------------*/

	case '@':
			return 0x40;
		break;
	case 'A':
			return 0x41;
		break;
	case 'B':
			return 0x42;
		break;
	case 'C':
			return 0x43;
		break;
	case 'D':
			return 0x44;
		break;
	case 'E':
			return 0x45;
		break;
	case 'F':
			return 0x46;
		break;
	case 'G':
			return 0x47;
		break;
	case 'H':
			return 0x48;
		break;
	case 'I':
			return 0x49;
		break;
	case 'J':
			return 0x4A;
		break;
	case 'K':
			return 0x4B;
		break;
	case 'L':
			return 0x4C;
		break;
	case 'M':
			return 0x4D;
		break;
	case 'N':
			return 0x4E;
		break;
	case 'O':
			return 0x4F;
		break;

/*----------------------*/

	case 'P':
			return 0x50;
		break;
	case 'Q':
			return 0x51;
		break;
	case 'R':
			return 0x52;
		break;
	case 'S':
			return 0x53;
		break;
	case 'T':
			return 0x54;
		break;
	case 'U':
			return 0x55;
		break;
	case 'V':
			return 0x56;
		break;
	case 'W':
			return 0x57;
		break;
	case 'X':
			return 0x58;
		break;
	case 'Y':
			return 0x59;
		break;
	case 'Z':
			return 0x5A;
		break;
	case '[':
			return 0x5B;
		break;
	case ']':
			return 0x5D;
		break;
	case '^':
			return 0x5E;
		break;
	case '_':
			return 0x5F;

/*----------------------*/

	case '`':
			return 0x60;
		break;
	case 'a':
			return 0x61;
		break;
	case 'b':
			return 0x62;
		break;
	case 'c':
			return 0x63;
		break;
	case 'd':
			return 0x64;
		break;
	case 'e':
			return 0x65;
		break;
	case 'f':
			return 0x66;
		break;
	case 'g':
			return 0x67;
		break;
	case 'h':
			return 0x68;
		break;
	case 'i':
			return 0x69;
		break;
	case 'j':
			return 0x6A;
		break;
	case 'k':
			return 0x6B;
		break;
	case 'l':
			return 0x6C;
		break;
	case 'm':
			return 0x6D;
		break;
	case 'n':
			return 0x6E;
		break;
	case 'o':
			return 0x6F;
		break;
/*---------------------*/

	case 'p':
			return 0x70;
		break;
	case 'q':
			return 0x71;
		break;
	case 'r':
			return 0x72;
		break;
	case 's':
			return 0x73;
		break;
	case 't':
			return 0x74;
		break;
	case 'u':
			return 0x75;
		break;
	case 'v':
			return 0x76;
		break;
	case 'w':
			return 0x77;
		break;
	case 'x':
			return 0x78;
		break;
	case 'y':
			return 0x79;
		break;
	case 'z':
			return 0x7A;
		break;
	default:
			return 0;
		break;
	}
}
