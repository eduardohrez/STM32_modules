/*
 * font_lcd.h
 *
 *  Created on: 6 abr. 2022
 *      Author: eduar
 */

#ifndef FONTS_USE_FONT_LCD_H_
#define FONTS_USE_FONT_LCD_H_
#include "stm32f4xx.h"
typedef uint8_t font_little;

#define point (font_little)0;
#define comma (font_little)1;
extern uint8_t* test_swicht(uint8_t value);
extern uint8_t* p_c_get(uint8_t value);

/* Image function declaration*/
typedef uint8_t Layer_image;
extern uint8_t* Get_image(Layer_image Get_layer);
extern uint8_t* Get_image_humed(Layer_image Get_layer);

#define Max_layer_y		((uint8_t)7)
#define Max_layer_x		((uint8_t)63)

#endif /* FONTS_USE_FONT_LCD_H_ */
