/*
 * util.c
 *
 *  Created on: 22 ago. 2023
 *      Author: eduar
 */

#include "util.h"
#include "main.h"

extern uint32_t Util_Arr_32BIND(uint8_t *Arr_inp )
{
	uint32_t ret_val = 0;
	ret_val = (Arr_inp[0]) |  (Arr_inp[1] << 8) | (Arr_inp[2] << 16) | (Arr_inp[3]<<24 );

	return ret_val;
}

