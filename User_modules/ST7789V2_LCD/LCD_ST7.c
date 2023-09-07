/*
 * LCD_ST7.c
 *
 *  Created on: 7 ago. 2022
 *      Author: eduar
 */

#include "main.h"
#include "LCD_ST7.h"


#include "Save_Img.h"

 uint16_t Color_background;

Def_imag image_pix[] =
{	{0xffff, 101},
	{0x0000, 98},
	{0xffff, 2},
	{0x0000, 98},
	{0xffff, 2},
	{0x0000, 98},
	{0xffff, 2},
	{0x0000, 98},
	{0xffff, 101}

};






/**
  * @brief  Reset via Signal
  * @retval None
  */
void SIG_RESET_LCD(void)
{

	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
	HAL_Delay(4);
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
}

/**
  * @brief  Define pins for use on control LCD
  * @retval None
  */
extern void init_Pins(void)
{
	HAL_GPIO_WritePin(CS_ST7_GPIO_Port, CS_ST7_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
	HAL_Delay(6);

}

/**
  * @brief  Define pins for use on control LCD
  * @param  Start of pixel on axis x
  * @param  Start of pixel on axis y
  * @retval None
  */
void init_LCD_S7(void)
{

	SIG_RESET_LCD();
	HAL_Delay(2);
	write_Comand(1);
	HAL_Delay(3);
	write_Comand(0x11);
	HAL_Delay(3);
}


/**
  * @brief  Reset via comands
  * @retval None
  */
void Partial_Reset(void)
{
	write_Comand(Partial_off);
	HAL_Delay(3);
	write_Comand(Partial_on);
	HAL_Delay(3);
}



/**
  * @brief  Function to test new imlmentation
  * @param  Start of pixel on axis x
  * @param  Start of pixel on axis y
  * @retval None
  */
void Domi_test(void)
{
	uint32_t var;
	Set_Etart_X_Y_End(10,137, 10, 300);

	Eneble_cont_wr_mode(0x2C);
	for (var = 0; var < 907; var++)
	{

		if( Get_IdImag_typePNG(0)[var].transparent == 1)
		{
			RGB_1DAT_Pix_Num( Get_IdImag_typePNG(0)[var].RGB_color,Get_IdImag_typePNG(0)[var].num_pix);
		}
//		RGB_1DAT_Pix_Num( Get_IdImag_typeJPG(0)[var].RGB_color,Get_IdImag_typeJPG(0)[var].num_pix); 4405
		else
		{
			RGB_1DAT_Pix_Num( Color_background,Get_IdImag_typePNG(0)[var].num_pix);
		}
	}
	Disable_cont_wr_mode();
}

/**
  * @brief  use for inversion of colors
  * @retval None
  */
void Disp_Invers(void)
{
	write_Comand(Invert);
}

void Set_brightness(uint8_t brightness)
{
	uint8_t brightness_str[] =	{0x51,brightness};

	write_value_C_D(brightness_str, sizeof(brightness_str) - 1 );

}


/**
  * @brief  set the limits of x and y start, the end is the pre-defined how the last pixel of LCD .
  * @param  Start of pixel on axis x
  * @param  Start of pixel on axis y
  * @retval None
  */
void Set_X_Y(uint8_t axis_X, uint16_t axis_Y)
{
	axis_Y= axis_Y+ (uint8_t)20;

	if(axis_X < 0xF0 && axis_Y < 0x012C)
	{

		uint8_t Colum_addres1[]   =	{0x2A, 0x00, axis_X, 0x00, 0xF0};	//set the width column start on 0 and end on 240
		uint8_t Colum_addres2[]   =	{0x2B, (uint8_t)(axis_Y & 0xFF00), (uint8_t) (axis_Y), 0x01, 0x2C};	//set the width row start on 20 and end on 300

		write_value_C_D(Colum_addres1, sizeof(Colum_addres1) - 1 );
		write_value_C_D(Colum_addres2, sizeof(Colum_addres2) - 1 );
	}
}


/**
  * @brief  set the limits of x and y start and the limit of x is 240 and y is 300.
  * @param  Start of pixel on axis x
  * @param  End of pixel on axis x
  * @param  Start of pixel on axis y
  * @param  End of pixel on axis y
  * @retval None
  */
void Set_Etart_X_Y_End(uint8_t axis_X_Start, uint8_t axis_X_End,   uint16_t axis_Y_Start, uint16_t axis_Y_End )
{
	axis_Y_Start= axis_Y_Start+ (uint8_t)20;
	if(axis_X_End > 240 ) axis_X_End = 240;
	if(axis_Y_End > 300 ) axis_Y_End = 300;

	if(axis_X_Start < 0xF0 && axis_Y_Start < 0x012C)
	{

		uint8_t Colum_addres1[]   =	{0x2A, 0x00, axis_X_Start, 0x00, axis_X_End};	//set the width column start on 0 and end on 240
		uint8_t Colum_addres2[]   =	{0x2B, (uint8_t)((axis_Y_Start & 0xFF00)>>8 ), (uint8_t) (axis_Y_Start), (uint8_t)((axis_Y_End & 0xFF00)>>8 ), (uint8_t) (axis_Y_End)};	//set the width row start on 20 and end on 300

		write_value_C_D(Colum_addres1, sizeof(Colum_addres1) - 1 );
		write_value_C_D(Colum_addres2, sizeof(Colum_addres2) - 1 );
	}
}


/**
  * @brief  Fill all lcd of a specific color
  * @param  R set the value on RED
  * @param  G set the value on Green
  * @param  B set the value of Blue
  * @retval None
  */
void Set_All_LCD_RGB(uint8_t R, uint8_t G , uint8_t B)
{
	uint16_t RGB_color = RGB_8b_to_5b_(R,G,B);
	uint8_t RGB_Color[]={ (uint8_t) ((RGB_color & 0xFF00 ) >> 8), (uint8_t) (RGB_color & 0xFF)};

	Color_background = RGB_8b_to_5b_(R, G, B);
	Set_X_Y(0, 0);
	Com_Value_rep(0x2C,RGB_Color, 0x10680);
}

/**
  * @brief  Memori access control
  * @param  Acces control configurations bits
  * @retval None
  */
extern void Mem_acces_crt(uint8_t Acc_Crt)
{
	uint8_t Mem_acces[] = {0x36,Acc_Crt};
	write_value_C_D(Mem_acces, sizeof(Mem_acces) - 1 );

}


/**
  * @brief  pixel format refried to datashet
  * @param  pixel format configurations bits
  * @retval None
  */
extern void Pixel_format(Pixel_Format Format_Pix)
{
	uint8_t value_pix_frmt = (Format_Pix.RGB_IF_Col_frm << (uint8_t)4) | Format_Pix.Color_IF_Frm;
	uint8_t pix_formt[] = {0x3A,value_pix_frmt};
	write_value_C_D(pix_formt, sizeof(pix_formt) - 1 );
	HAL_Delay(5);
}

/**
  * @brief  Set the color of pixel and the number of repeticion.
  * @param  R color Red value
  * @param  G color green value
  * @param  B color Blue value
  * @param  number of repetition
  * @retval None
  */
extern void RGB_Pix_Num(uint8_t R, uint8_t G , uint8_t B, uint32_t number)
{
	uint16_t RGB_color = RGB_8b_to_5b_(R,G,B);
	uint8_t RGB_Color[]={ (uint8_t) ((RGB_color & 0xFF00 ) >> 8), (uint8_t) (RGB_color & 0xFF)};


	Com_Value_rep(0x2C,RGB_Color, number);

}



extern void RGB_1DAT_Pix_Num(uint16_t RGB_color, uint32_t number)
{

	uint8_t RGB_Color[]={ (uint8_t) ((RGB_color & 0xFF00 ) >> 8), (uint8_t) (RGB_color & 0xFF)};

	Contin_wr_pix(RGB_Color, number);

}

/**
  * @brief  Transform 8bytes to 5 bytes in one uint16.
  * @param  R color Red value
  * @param  G color green value
  * @param  B color Blue value
  * @param  number of repetition
  * @retval None
  */
static uint16_t RGB_8b_to_5b_(uint8_t R, uint8_t G , uint8_t B)
{
	uint16_t val_ret;

	R=255-R;
	G=255-G;
	B=255-B;
	R = R/(255/31);
	G = G/(255/63);
	B = B/(255/31);
	val_ret=(uint16_t) ( (R << 11) | (G <<5 ) | (B & 0x1F) );

	return val_ret;

}

extern void WR_IMAGE_type_JPG(uint8_t ID_Image_JPG)
{
	uint32_t var;
	Set_Etart_X_Y_End(10,137, 10, 300);

	Eneble_cont_wr_mode(0x2C);
	for (var = 0; var < 4405; var++)
	{
		RGB_1DAT_Pix_Num( Get_IdImag_typeJPG(ID_Image_JPG)[var].RGB_color, Get_IdImag_typeJPG(ID_Image_JPG)[var].num_pix);
	}
	Disable_cont_wr_mode();
}


extern void WR_IMAGE_type_PNG(uint8_t ID_Image_PNG)
{
	uint32_t var;
	Set_Etart_X_Y_End(10,137, 10, 300);

	Eneble_cont_wr_mode(0x2C);
	for (var = 0; var < 907; var++)
	{

		if( Get_IdImag_typePNG(ID_Image_PNG)[var].transparent == 1)
		{
			RGB_1DAT_Pix_Num( Get_IdImag_typePNG(ID_Image_PNG)[var].RGB_color,Get_IdImag_typePNG(ID_Image_PNG)[var].num_pix);
		}
		else
		{
			RGB_1DAT_Pix_Num( Color_background,Get_IdImag_typePNG(ID_Image_PNG)[var].num_pix);
		}
	}
	Disable_cont_wr_mode();
}

