/*
 * I2C_ATH10.h
 *
 *  Created on: 16 mar. 2022
 *      Author: eduar
 */

#ifndef ATH10_I2C_ATH10_H_
#define ATH10_I2C_ATH10_H_

#include "stdio.h"
#include "I2C_base.h"

typedef uint8_t I2C_ATH10_Stat;
typedef uint8_t	Tools_set;

extern float ath_tem;
extern float ath_hum;

#define Err_ATH10_int  	(I2C_ATH10_Stat)(0)
#define Cor_ATH10_int	(I2C_ATH10_Stat)(1)

#define Size_get_mes	(I2C_ATH10_Stat)(1)
#define Set_time_mes	(I2C_ATH10_Stat)(1)
#define Set_del_read	(Tools_set)(10)
#define Get_size_dat	(Tools_set)(6)
//define addres for sensor
typedef uint8_t I2C_SPC_ADR;

#define I2C_AD_SEND  	(I2C_SPC_ADR)(0x70)
#define Two_exp20		1048576U


extern I2C_ATH10_Stat init_I2C_ATH10();

//static void Raw_value(uint32_t *temp, uint32_t *humed);

extern void Get_t_h(float *t,float *h);

extern I2C_ATH10_Stat verify();


#endif /* ATH10_I2C_ATH10_H_ */
