/*
 * I2C_base.c
 *
 *  Created on: 16 mar. 2022
 *      Author: eduar
 */
#include "I2C_base.h"

extern	I2C_P2_STAT init_I2C_P2()
{
	I2C_P2_STAT status_ret=I2C_STAT_IN;

	I2C_P2.Instance = I2C2;
	I2C_P2.Init.ClockSpeed = 400000;
	I2C_P2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2C_P2.Init.OwnAddress1 = 0;
	I2C_P2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_P2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C_P2.Init.OwnAddress2 = 0;
	I2C_P2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_P2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&I2C_P2) != HAL_OK)
	{
		status_ret=I2C_STAT_NT;
	}
	return status_ret;
}

