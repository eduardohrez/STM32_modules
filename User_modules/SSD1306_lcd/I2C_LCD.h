/*
 * I2C_LCD.h
 *
 *  Created on: Mar 17, 2022
 *      Author: eduar
 */

#ifndef SSD1306_LCD_I2C_LCD_H_
#define SSD1306_LCD_I2C_LCD_H_
#include  "stm32f4xx.h"

#define Err_int_LCD			(Status_LCD)(0)
#define COR_int_LCD			(Status_LCD)(1)
#define SET_TEMP			(uint8_t(0))
#define SET_HUM				(uint8_t(1))
typedef uint8_t Status_LCD;

#define erase_sec 0xFFu

extern Status_LCD verify_LCD();
extern Status_LCD Configure_LCD(uint8_t contraste);
extern void write_value();
extern void clear_lcd();
extern void fill_lcd();
extern void funct_dummy();

//functionals
extern void set_number(uint8_t number);
extern void set_colum_cords(uint8_t x_start,uint8_t x_end, uint8_t y_start,uint8_t y_end);

extern void wr_sectors(uint8_t avalib,uint8_t sec1,uint8_t sec2,uint8_t sec3, uint8_t sec4);
extern void wr_number(uint16_t number);

extern void set_colum();
extern void funct_dummy2();

//write temp_humed
extern void wr_com_poin(uint8_t set_c_p);
extern void show_h_t(uint8_t t_h);

//clear lcd
extern void wr_sector(uint8_t sec,uint8_t value);
extern void clear_seg_lcd(uint8_t seg_lcd);
extern void clear_all_seg_lcd();
extern void reset_value_cont(void);

/*Set image draw */
extern void write_image(uint8_t Imagen_select);

#endif /* SSD1306_LCD_I2C_LCD_H_ */
