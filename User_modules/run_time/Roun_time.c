/*
 * Roun_time.c
 *
 *  Created on: 10 jul. 2022
 *      Author: eduar
 */

#include "../../User_modules/run_time/Roun_time.h"

#include "main.h"
#include "I2C_LCD.h"

extern void steps_routine(uint8_t tasks)
{
	switch (tasks) {
		case 0:
			write_image(0);
			break;
		case 1:
			show_h_t(0);
			break;
		case 2:
			write_image(1);
			break;
		case 3:
			show_h_t(1);
			break;
		default:
			break;
	}
}
