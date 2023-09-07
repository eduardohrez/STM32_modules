/*
 * I2C_P2.c
 *
 *  Created on: 16 mar. 2022
 *      Author: eduar
 */

#include "I2C_ATH10.h"

I2C_HandleTypeDef I2C_P2;
uint8_t C_mesure[1] = {0xac};
uint8_t Get_mesure[7];
float ath_tem;
float ath_hum;


extern I2C_ATH10_Stat verify()
{
	I2C_ATH10_Stat estat_ret;
	estat_ret =	HAL_I2C_Master_Transmit(&I2C_P2, I2C_AD_SEND, C_mesure, 1, Set_time_mes);
	estat_ret= (~(estat_ret))&0x01;
	return estat_ret;
}


static void Raw_value(uint32_t *temp,uint32_t *humed)
{
	uint32_t bit_temp=0,bit_hum=0;
	HAL_I2C_Master_Transmit(&I2C_P2, I2C_AD_SEND, C_mesure, Size_get_mes, Set_time_mes);
	HAL_Delay(Set_time_mes);
	HAL_I2C_Master_Receive(&I2C_P2, I2C_AD_SEND, Get_mesure, Get_size_dat, Set_time_mes);
	bit_hum=Get_mesure[1]<<12 |Get_mesure[2]<<4 | ((Get_mesure[3]& 0xF0)>>4);
	bit_temp= (Get_mesure[3]&0x0F)<<16 | Get_mesure[4]<<8| Get_mesure[5];
	*temp=bit_temp;
	*humed=bit_hum;
}

extern void Get_t_h(float *t,float *h)
{

	uint32_t temp,humed;
	Raw_value(&temp, &humed);
	ath_tem	=((temp/1048576.0)*200.0)-50;
	ath_hum =(humed/1048576.0)*100;
	*t=ath_tem;
	*h=ath_hum;

}



