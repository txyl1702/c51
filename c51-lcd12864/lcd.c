#include <stdlib.h>
#include "font.h"
#include "pin.h"
#include "lcd.h"

void delay_ms(uint t)
{
	uint i, j;
	
	for (i = 0; i < t; i++)
		for (j = 0; j < 125; j++);
}

void ctrl_lcd_view(uchar ctrl_cs1, uchar ctrl_cs2)
{
	lcd_cs1 = ctrl_cs1;
	lcd_cs2 = ctrl_cs2;
}

void lcd_check_busy(void)
{
	do {
		lcd_en = 1;
		lcd_di = 0;
		lcd_rw = 1;
//		LCD_DATA = 0xff;
//		lcd_en = 0;
	} while (LCD_DATA & 0x80);
}

void lcd_write_data(uchar write_data, uchar type)
{
//	lcd_check_busy();
	lcd_di = type;
	lcd_rw = 0;
	LCD_DATA = write_data;
	delay_ms(1);
	lcd_en = 1;
	delay_ms(2);
	lcd_en = 0;
}

void lcd_init(void)
{
	// 关闭左右屏幕
	ctrl_lcd_view(LCD_LEFT_OFF, LCD_RIGHT_OFF);
	delay_ms(100);
	// 显示关
	lcd_write_data(LCD_NO_VIEW, SEND_CMD);
	// 页地址
	lcd_write_data(PAGE_ADDR+0, SEND_CMD);
	// 起始地址
	lcd_write_data(LINE_ADDR+0, SEND_CMD);
	// 列地址
	lcd_write_data(COL_ADDR+0, SEND_CMD);
	// 显示开
	lcd_write_data(LCD_VIEW, SEND_CMD);
}
// 清屏函数，将所有字符清空
void lcd_clear(void)
{
	uint i, j;
	
	ctrl_lcd_view(LCD_LEFT_ON, LCD_RIGHT_ON);
	lcd_write_data(PAGE_ADDR, SEND_CMD);
	lcd_write_data(COL_ADDR, SEND_CMD);
	for (i = 0; i < 8; i++)
	{
		lcd_write_data(PAGE_ADDR+i, SEND_CMD);
		for (j = 0; j < 64; j++)
		{
			lcd_write_data(COL_ADDR+j, SEND_CMD);
			lcd_write_data(0x00, SEND_DATA);
		}
	}
}
/**
	lcd_view_string: 在LCD12864上显示数据，可以显示8*16与16*16的字符
	@line: 将要显示的行，范围0-3
	@col:  将要显示的列，范围根据显示的字符大小而定，如16*16范围为0-7
	@str:  需要显示的字符数组
	@num:  需要显示字符数组的个数
	@type: 显示的类型，是16*16还是8*16,参数可为LCD_VIEW_16_16，LCD_VIEW_8_16
 */
void lcd_view_string(uchar line, uchar col, const arr_t str, uchar num, uchar type)
{
	uchar i, j, k;
	uchar page = line * 2;
	if (type == LCD_VIEW_16_16)
		col *= 16;
	else 
		col *= 8;
	
	for (k = 0; k < num; k++)
	{
		// 显示数据
		for (i = 0; i < 2; i++)
		{
			if (col < 64)
			{
				ctrl_lcd_view(LCD_LEFT_ON, LCD_RIGHT_OFF);
				lcd_write_data(COL_ADDR+col, SEND_CMD);
			}
			else
			{	
				ctrl_lcd_view(LCD_LEFT_OFF, LCD_RIGHT_ON);
				lcd_write_data(COL_ADDR+col-64, SEND_CMD);
			}
			lcd_write_data(PAGE_ADDR+i+page, SEND_CMD);
			for (j = 0; j < type; j++)
				lcd_write_data(str[k][type*i+j], SEND_DATA);
		}
		
		if (type == LCD_VIEW_16_16)	
			col += 16;
		else 
			col += 8;
	}
}

void lcd_view_num(float num, uchar line, uchar col) reentrant
{
	uint tmp = abs(num);
	uint integer = 0;
	uint point;
	
	if (num < 0)
	{
		lcd_view_char(line, col++, (arr_t)digital[11], 1);
		point = (-num - tmp)*100;
	}
	else
	{
		point = (num - tmp)*100;
	}
	while (tmp)
	{
		integer = integer*10 + tmp%10;
		tmp /= 10;
	}	
	while (integer)
	{
		lcd_view_char(line, col, (arr_t)digital[integer%10], 1);
		integer /= 10;
		col += 1;
	}
	if (point > 0)
	{
		lcd_view_char(line, col, (arr_t)digital[10], 1);
		lcd_view_num(point, line, col+1);
	}
}

void main(void)
{
	lcd_init();
	lcd_clear();
//	lcd_view_word(1, 2, str+1, 3);
	lcd_view_num(-123.12, 0, 0);
	while (1)
	{
		
	}
}
