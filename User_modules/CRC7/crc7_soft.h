/*
 * crc7_soft.h
 *
 *  Created on: 19 oct. 2022
 *      Author: eduar
 */
#include "main.h"

#ifndef CRC7_CRC7_SOFT_H_
#define CRC7_CRC7_SOFT_H_

extern void		dummyfunct_crc7(void);
extern uint8_t find_bit(uint8_t byte_found);
extern uint8_t get_crc(uint8_t *Data, uint16_t size);
extern uint8_t build_next_compar(uint8_t num_bite ,uint8_t *Data_buffer);
extern uint8_t Process_crc(uint8_t init_value ,uint8_t *Data_buffer);
extern uint16_t calculate_size32(uint16_t size);
extern uint16_t buld_32(uint32_t *data, uint8_t *byte_int, uint16_t *index, uint16_t size );
extern void build_uint32_compare_crc(uint16_t size, uint32_t *build_data, uint8_t *data_in);
extern void Set_False_flag_value(void);


#endif /* CRC7_CRC7_SOFT_H_ */
