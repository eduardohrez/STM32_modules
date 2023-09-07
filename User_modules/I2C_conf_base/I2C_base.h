/*
 * I2C_base.h
 *
 *  Created on: 16 mar. 2022
 *      Author: eduar
 */

#ifndef I2C_CONF_BASE_I2C_BASE_H_
#define I2C_CONF_BASE_I2C_BASE_H_

#include "stm32f4xx.h"

extern I2C_HandleTypeDef I2C_P2;

typedef uint8_t I2C_P2_STAT;
typedef uint8_t	Tools_set;

#define I2C_STAT_IN		(Tools_set)(1)
#define I2C_STAT_NT		(Tools_set)(0)

extern	I2C_P2_STAT init_I2C_P2();

#endif /* I2C_CONF_BASE_I2C_BASE_H_ */
