#ifndef __PIN_H__
#define __PIN_H__

#include <reg52.h>
/**
   LCD12864引脚，命令，地址定义
 */
#define LCD_DATA         P2
#define SEND_CMD         0
#define SEND_DATA        1
#define LCD_LEFT_ON      0
#define LCD_LEFT_OFF     1
#define LCD_RIGHT_ON     0
#define LCD_RIGHT_OFF    1
#define LCD_VIEW_16_16   16
#define LCD_VIEW_8_16    8

#define LCD_NO_VIEW      0x3e
#define LCD_VIEW         0x3f
#define PAGE_ADDR        0xb8
#define COL_ADDR         0x40
#define LINE_ADDR        0xc0

sbit lcd_en   =  P3^0;
sbit lcd_rw   =  P3^1;
sbit lcd_di   =  P3^2;
sbit lcd_cs1  =  P3^3;
sbit lcd_cs2  =  P3^4;

#endif