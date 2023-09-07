/*
 * SPI_BASE.h
 *
 *  Created on: 7 ago. 2022
 *      Author: eduar
 */

#ifndef SPI_BASE_SPI_BASE_H_
#define SPI_BASE_SPI_BASE_H_

#include "stm32f4xx_hal.h"

/*Define functions extraneous*/
extern void Init_SPI_BASE(void);
extern void write_Comand(uint8_t ptc_data);
extern void write_Comands(uint8_t *ptc_data, uint8_t size);
extern void write_value_C_D(uint8_t *ptc_data, uint16_t size);
extern void Com_Value_rep(uint8_t comand,uint8_t* value_rep , uint32_t num_rep);
extern void Contin_wr_pix(uint8_t* value_rep , uint32_t num_rep);

extern void Eneble_cont_wr_mode(uint8_t comand);
extern void Disable_cont_wr_mode();

#endif /* SPI_BASE_SPI_BASE_H_ */
