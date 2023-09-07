/*
 * LCD_ST7.h
 *
 *  Created on: 7 ago. 2022
 *      Author: eduar
 */

#ifndef ST7789V2_LCD_LCD_ST7_H_
#define ST7789V2_LCD_LCD_ST7_H_

#include "stm32f4xx.h"


#define SWREST 		((uint8_t)0x01)
#define SLP_OUT 	((uint8_t)0x11)
#define Invert	 	((uint8_t)0x21)
#define Partial_off	((uint8_t)0x13)
#define Partial_on	((uint8_t)0x29)


typedef struct Data_Acces
{
	uint8_t dumy :1;			//0
	uint8_t dumy1 :1;			//1
	uint8_t Disp_Dat_Latch :1;	//2
	uint8_t Color_Order :1;		//3
	uint8_t Line_Adrr_Ord :1;	//4
	uint8_t Pge_Colum_Ord :1;	//5
	uint8_t Colum_Adr_Ord :1;	//6
	uint8_t Pge_Addrs_Ord :1;	//7
} Data_Accss;

typedef enum Color_IF_Form
{
	Bits_12 	= 0b011,
	Bits_16 	= 0b101,
	Bits_18 	= 0b110,
	Bits_16M 	= 0b111
};

typedef enum RGB_IF_Color_Form
{
	RGB_65K 	= 0b101,
	RGB_262K 	= 0b101,
};


typedef struct Pix_Form
{
	uint8_t Color_IF_Frm 	: 3;
	uint8_t RGB_IF_Col_frm	: 3;

}Pixel_Format ;

typedef struct
{
	uint16_t RGB_color;
	uint16_t num_pix ;

}Def_imag ;


typedef struct
{
	uint16_t RGB_color;
	uint16_t num_pix ;
	uint8_t  transparent;
}Def_imag_PNG_type ;

extern void init_Pins(void);
extern void init_LCD_S7(void);
extern void SIG_RESET_LCD(void);
extern void Set_Pix_Format(void);
extern void Disp_Invers(void);
extern void Domi_test(void);
extern void Partial_Reset(void);
extern void Set_brightness(uint8_t brightness); /*Doesn't work*/
extern void Pixel_format(Pixel_Format Format_Pix);
extern void Mem_acces_crt(uint8_t Acc_Crt);
extern void Set_X_Y(uint8_t axis_X, uint16_t axis_Y);
extern void Set_Etart_X_Y_End(uint8_t axis_X_Start, uint8_t axis_X_End,   uint16_t axis_Y_Start, uint16_t axis_Y_End );
extern void Set_All_LCD_RGB(uint8_t R, uint8_t G , uint8_t B);
extern void RGB_Pix_Num(uint8_t R, uint8_t G , uint8_t B, uint32_t number);
extern void RGB_1DAT_Pix_Num(uint16_t RGB_color, uint32_t number);



/*functions tools*/
static uint16_t RGB_8b_to_5b_(uint8_t R, uint8_t G , uint8_t B);

/*Draw imagen on LCD*/
extern void WR_IMAGE_type_JPG(uint8_t ID_Image_JPG);
extern void WR_IMAGE_type_PNG(uint8_t ID_Image_PNG);


#endif /* ST7789V2_LCD_LCD_ST7_H_ */
