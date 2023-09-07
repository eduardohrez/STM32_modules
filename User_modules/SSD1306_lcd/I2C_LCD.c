/*
 * I2C_LCD.c
 *
 *  Created on: Mar 17, 2022
 *      Author: eduar
 */

#include "I2C_LCD.h"
#include "I2C_base.h"
#include "font_lcd.h"
#include "I2C_ATH10.h"
#define Address_LCD 120UL
uint8_t data=0XAE;
//static uint8_t initial_conf[]=	{0X00,0xAE,0XA8,0X3F,0XD3,0X00,0X40,
//							  	 0XA1,0XC8,0XDA,0X12,0X81,0X00,
//								 0XA4,0XA6,0XD5,0X80,0X8D,0X14,
//								 0XAF,0X21,0X00,0X7F,0X22,0X00,
//								 0X07,0X20,0X00};
static uint8_t initial_conf[]=	{0X00,0xAE,0XA8,0X3F,0XD3,0X00,0X40,
							  	 0XA0,0XC8,0XDA,0X12,0X81,0X00,
								 0XA4,0XA6,0XD5,0X80,0X8D,0X14,
								 0XAF,0X21,0X00,0X7F,0X22,0X00,
								 0X07,0X20,0X00};

static uint8_t sec_ant_1=10,sec_ant_2=10,sec_ant_3=10,sec_ant_4=10;




extern Status_LCD verify_LCD()
{
	Status_LCD inital_stat=Err_int_LCD;
	inital_stat=HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, &data, 1, 1);
	inital_stat=(~(inital_stat))&0x01;
	return inital_stat;
}



extern Status_LCD Configure_LCD(uint8_t contraste)
{
	Status_LCD value_int=Err_int_LCD;
	initial_conf[12]=contraste;
	HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, initial_conf, 28, 1);
	value_int=(~(value_int))&0x01;
	return value_int;
}

extern void fill_lcd()
{
	static uint8_t fill_lcd[]={0X40,0XFF};
	int16_t value=0;
	for ( value= 0;  value< 1024; value++) {

		HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, fill_lcd, 2, 1);
	}

}



/*clear complete the LCD*/
extern void clear_lcd()
{

	uint16_t value=0;
	uint8_t clear_v[]={0X40,0x00};
	Configure_LCD(0);
	for (value = 0; value < 1024; ++value) {
		HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, clear_v, 2, 1);
	}

	reset_value_cont();
}

/*test this function*/
extern void set_colum()
{
								 // star   end
	uint8_t set_colum[]={0X20,0X00,0x21,0x00,26,0X22,0X00,0X07};
	HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, set_colum, 8, 1);
}



extern void write_value()
{
}

/*function to test some implementation*/
extern void funct_dummy()
{
	uint16_t value=0;
	uint8_t clear_v[]={0X40,0xFF};
	for (value = 0; value < 128; ++value)
	{
		HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, clear_v, 2, 1);
	}

}

/*function to test some implementation*/
extern void funct_dummy2()
{

	uint8_t value_send_5[]={128, 226, 254, 254, 254, 254, 254, 254, 254, 254, 254, 252, 240, 224, 0, 7, 63, 127, 127, 255, 255, 255, 255, 255, 255, 255, 127, 63, 31, 7};


	uint8_t send_img[2];
	uint16_t value=0;
	send_img[0]=0x40;
	for (value = 0; value < 30; ++value)
	{
			send_img[1]=value_send_5[value];
			HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, send_img, 2, 1);
	}
}

void reset_value_cont(void)
{
	sec_ant_1	=	10;
	sec_ant_2	=	10;
	sec_ant_3	=	10;
	sec_ant_4	=	10;
}


/*set columns and cords see the pdf*/
extern void set_colum_cords(uint8_t x_start,uint8_t x_end, uint8_t y_start,uint8_t y_end)
{
									  // star_x end_x    y_star  y_end
	uint8_t set_colum[]={0X20,0X00,0x21,x_start,x_end,0X22,y_start,y_end};
	HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, set_colum, 8, 1);
}

/*send number by the colum selected*/
extern void set_number(uint8_t number)
{
	uint8_t *get_font;
	uint8_t send_img[2];
	uint16_t value=0;
	get_font =test_swicht(number);
	send_img[0]=0x40;
	for (value = 0; value < 81; ++value) {
			send_img[1]=*(get_font+ value);
			HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, send_img, 2, 1);
		}
}

//write sectors and value
extern void wr_sectors(uint8_t avalib,uint8_t sec1,uint8_t sec2,uint8_t sec3, uint8_t sec4)
{

	if( (avalib & 1<<3) && sec_ant_1 != sec1 )
	{
		set_colum_cords(0, 26, 2, 7);
		set_number(sec1);
		sec_ant_1=sec1;
	}
	if( (avalib & 1<<2) && sec_ant_2 != sec2  )
	{
		set_colum_cords(28, 54, 2, 7);
		set_number(sec2);
		sec_ant_2=sec2;
	}
	if( (avalib & 1<<1) && sec_ant_3 != sec3  )
	{
		set_colum_cords(75, 101, 2, 7);
		set_number(sec3);
		sec_ant_3=sec3;
	}
	if( (avalib & 1) &&  sec_ant_4 != sec4 )
	{
		set_colum_cords(101, 127, 2, 7);
		set_number(sec4);
		sec_ant_4 = sec4;
	}
}



extern void wr_number(uint16_t number)
{
	uint16_t val_send[4];
	uint16_t diguits=0;
	uint8_t index;
	if(number<10000)
	{
		for (index = 0; index < 4; ++index)
		{
			val_send[index]=number%10;
			number/=10;
			diguits|=1<<index;
			if(number==0)
			{
				index=5;
			}
		}

	wr_sectors(diguits, val_send[3], val_send[2], val_send[1], val_send[0]);
	}
}

extern void wr_com_poin(uint8_t set_c_p)
{
	uint8_t *str;
	static int val_ant=10;
	if(val_ant!=set_c_p)
	{
		set_colum_cords(55, 69, 2, 7);
		str= p_c_get(set_c_p);
		uint8_t send_img[2];
		uint16_t value=0;
		send_img[0]=0x40;
		for (value = 0; value < 30; ++value)
		{
				send_img[1]=*(str+value);
				HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, send_img, 2, 1);
		}
		val_ant=set_c_p;
	}

}

extern void show_h_t(uint8_t t_h)
{
	float t,h;
	Get_t_h(&t, &h);
	uint16_t temp=0,hum=0;
	wr_com_poin(0);
	if(t_h==0)
	{

		temp=(ath_tem) *100;
		wr_number(temp);
	}
	else
	{
		hum=(ath_hum) *100;
		wr_number(hum);
	}
}


extern void clear_seg_lcd(uint8_t seg_lcd)
{
	switch (seg_lcd) {
		case 1:
			set_colum_cords(0, 26, 2, 7);
			set_number(erase_sec);
			sec_ant_1=erase_sec;
			break;
		case 2:
			set_colum_cords(28, 54, 2, 7);
			set_number(erase_sec);
			sec_ant_2=erase_sec;
			break;
		case 3:
			set_colum_cords(75, 101, 2, 7);
			set_number(erase_sec);
			sec_ant_3=erase_sec;
			break;
		case 4:
			set_colum_cords(101, 127, 2, 7);
			set_number(erase_sec);
			sec_ant_4=erase_sec;
			break;
		default:
			break;
	}
}

extern void clear_all_seg_lcd()
{
	for (int Value = 1; Value < 5; ++Value)
	{
		clear_seg_lcd(Value);
	}
	wr_com_poin(erase_sec);
}

extern void write_image(uint8_t Imagen_select)
{
	uint8_t *ptc_image, var,image[2];
	uint8_t var2=0;
	set_colum_cords(0, Max_layer_x, 0, 7);

	image[0]=0x40;
	for (var = 0; var < Max_layer_y; var++)
	{
		if(Imagen_select == 0) ptc_image = Get_image(var);

		else
		{
			ptc_image = Get_image_humed(var);
		}

		for (var2 = 0; var2 < Max_layer_x; var2++)
		{
			image[1]=*(ptc_image+var2);
			HAL_I2C_Master_Transmit(&I2C_P2, Address_LCD, image, 2, 1);
		}

	}
}
