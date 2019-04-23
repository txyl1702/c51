#ifndef __LCD_H__
#define __LCD_H__

#define ARRAY_SIZE(arr)  (sizeof(arr) / sizeof((arr)[0]))
#define lcd_view_char(line, col, str, num) \
						lcd_view_string(line, col, str, num, LCD_VIEW_8_16)
#define lcd_view_word(line, col, str, num) \
						lcd_view_string(line, col, str, num, LCD_VIEW_16_16)

typedef  unsigned int uint;
typedef  unsigned char uchar;
typedef  uchar (*arr_t)[32];

extern void lcd_init(void);

extern void lcd_clear(void);

/**
	lcd_view_string: 在LCD12864上显示数据，可以显示8*16与16*16的字符
	@line: 将要显示的行，范围0-3
	@col:  将要显示的列，范围根据显示的字符大小而定，如16*16范围为0-7
	@str:  需要显示的字符数组
	@num:  需要显示字符数组的个数
	@type: 显示的类型，是16*16还是8*16,参数可为LCD_VIEW_16_16，LCD_VIEW_8_16
 */
extern void lcd_view_string(uchar line, uchar col, const arr_t str, 
								uchar num, uchar type);

extern void lcd_view_num(float num, uchar line, uchar col) reentrant;

#endif