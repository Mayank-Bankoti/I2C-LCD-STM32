/*
 * LCD_I2C.c
 *
 *  Created on: Sep 14, 2023
 *      Author: mayan
 */


#include "LCD_I2C.h"

extern I2C_HandleTypeDef hi2c1;

#define SLAVE_ADDRESS_LCD 0x4E

void LCD_I2C_cmd(char cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = cmd & 0xF0;
	data_l =  ((cmd <<4) & 0xF0);
	data_t[0] = data_u | 0x0C;
	data_t[1] = data_u | 0x08;
	data_t[2] = data_l | 0x0C;
	data_t[3] = data_l | 0x08;
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);

}

void lcd_send_data(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data & 0xf0);
	data_l = (data <<4 ) & 0xF0;
	data_t[0] = data_u |0x0D;
	data_t[1] = data_u |0x09;
	data_t[2] = data_l | 0x0D;
	data_t[3] = data_l | 0x09;
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void LCD_I2C_init(void)
{
	LCD_I2C_cmd(0x02);
	LCD_I2C_cmd(0x28);
	LCD_I2C_cmd(0x0c);
	LCD_I2C_cmd(0x80);
	LCD_I2C_cmd(LCD_CLEAR);
}

void LCD_I2C_write_text(char *str)
{
	while (*str) lcd_send_data (*str++);
}




