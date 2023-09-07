/*
 * crc7_soft.c
 *
 *  Created on: 19 oct. 2022
 *      Author: eduar
 */
#include "crc7_soft.h"


#define byte_size		((uint8_t)8)
#define initial_value 	((uint8_t)0xFF)
#define False			((uint8_t)0x00)
#define True			((uint8_t)0x01)
#define bits_crc		((uint8_t)0x08)	// num bits crc
#define restan_add_bits	((uint8_t)0x07) // is one less than bits of crc
#define CRC_LAST_SZ		((uint8_t)0x07)
#define SIZE_BIT		((uint8_t)0X08)
#define CRC7_value		((uint8_t)0b10001001)


int32_t save_last_crc;
uint8_t flag_lastval=False; //create init value

//test the functions
extern void dummyfunct_crc7(void)
{
//test function
	uint32_t	value = 0xFF;
	uint8_t 	Data_in[] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
	uint16_t	index = 0;

	buld_32(&value, Data_in,&index,8);
	buld_32(&value, Data_in,&index,8);
	buld_32(&value, Data_in,&index,8);

}

extern uint8_t find_bit(uint8_t byte_found)
{
	int8_t index_found = 7;
	uint8_t byt_found = initial_value ;
	while((index_found > -1) && (byt_found == initial_value))
	{
		if( (byte_found  & (1<< index_found) ) != 0 )
		{
			byt_found = index_found;
		}
		index_found--;
	}

	return (7 - byt_found);
}

extern uint8_t build_next_compar(uint8_t num_bite ,uint8_t *Data_buffer)
{
	uint8_t value_of_crc = 0, byte1,byte2;
	uint8_t value_shify_frs = num_bite;
	uint8_t value_shify_scnd = ( bits_crc - num_bite);
	byte1 = ( *(Data_buffer) & (0xFF >> value_shify_frs ) ) ;
	byte2 = ( *(Data_buffer + 1) & (0xFF << value_shify_scnd ) );
	value_of_crc |=  (byte1 << value_shify_frs) | (byte2 >> value_shify_scnd) ;

	return value_of_crc;
}

extern uint8_t Process_crc(uint8_t init_value ,uint8_t *Data_buffer)
{
	uint8_t byte1,byte2;
	uint8_t value_shify_frs = init_value;
	uint8_t value_shify_scnd = ( bits_crc - init_value);
	*Data_buffer = ( ( (*Data_buffer)^ (CRC7_value >> value_shify_frs)) );
	*(Data_buffer + 1) =  (( (*(Data_buffer + 1) )^ (CRC7_value << value_shify_scnd)) & (0xFF << value_shify_scnd)) | (  *(Data_buffer + 1) & (0xFF >> value_shify_frs) ) ;

	return 0;
}



extern uint16_t calculate_size32(uint16_t size)
{
	uint16_t calculate_size32=0;
	calculate_size32++; // by default increment in one
	if(4 <= size )
	{
		size-=4;
		calculate_size32 += size/3;
		calculate_size32++; //increment in one because if is exact divisible in 3 need add the crc
	}

	return calculate_size32;
}

extern void build_uint32_compare_crc(uint16_t size, uint32_t *build_data, uint8_t *data_in)
{
	uint8_t size_build = ((size)>4)?4:size;
	uint8_t counter,position_in=0;
	for (counter = size_build ; counter > 0; counter--)
	{
		*(build_data) |= *(data_in + position_in) << ((counter-1)*8);
		position_in++;
	}

}


extern void Set_False_flag_value(void)
{
	flag_lastval=False;
}
extern uint16_t buld_32(uint32_t *data, uint8_t *byte_int,uint16_t *index, uint16_t size)
{
	uint8_t last_crc = (uint8_t)(data[0] & 0xFF);
	int8_t size_index = 0;
	uint8_t space_crc = False;
	int8_t index_value;
	uint8_t bits_stored;
	data[0]= 0;

	if( ((size -1 ) - *index) >= 3)
	{
		size_index = 3;
	}
	else
	{
		size_index += (size -1 ) -(*index-1);


		if(size_index >= 3)
		{
			// no is available the size
		}
		else
		{
			space_crc = True;
		}
		if(flag_lastval == True)
		{
			size_index=0;
			flag_lastval=False;
		}
	}
	bits_stored = ( (size_index + 1)  * 8);
	data[0] = last_crc << (size_index * 8);
	size_index-- ;

	for (index_value = size_index; index_value >= 0; index_value--)
	{
		data[0] |= byte_int[*index] << (index_value*8 );
		(*index)++;
	}
	if(space_crc == True)
	{
		data[0]= data[0]<< 7;
		bits_stored += 7;
	}
	if( byte_int[(*index)-1] == byte_int[size -1])
	{
		flag_lastval=True;
	}
	return bits_stored;
}


extern uint8_t get_crc(uint8_t *Data, uint16_t size)
{
	uint32_t use_process_crc[]={0,0};
	uint32_t polinom = (uint32_t)(CRC7_value);
	uint32_t initialind;
	uint16_t index_pos_in=0;
	uint16_t total_value_32 =  calculate_size32(size);

	uint8_t finalize =False;

	build_uint32_compare_crc( size, use_process_crc, Data);

	initialind = (size*8)+ CRC_LAST_SZ;
	if( initialind <= 31 )
	{
		use_process_crc[0]=use_process_crc[0] << CRC_LAST_SZ;
		index_pos_in =size;
	}
	else
	{
		initialind=32;
		index_pos_in +=4;
	}
	while(False == finalize)
	{
		for (initialind; initialind > (CRC_LAST_SZ -2); initialind--)
		{

			if( (total_value_32  > 1) & (initialind==CRC_LAST_SZ) )
			{
				initialind = buld_32(use_process_crc,Data,&index_pos_in,size);
				total_value_32--;

			}
				/*process the  crc and the xor process*/
			else if( ( ((use_process_crc[0]) & (1<< initialind)) != 0)  & (initialind > CRC_LAST_SZ-1) )
			{
				use_process_crc[0] = (use_process_crc[0] ^ (polinom << (initialind - 7)) ) ;

			}
			else if ( (initialind <= CRC_LAST_SZ) & (total_value_32 <= 1) )
			{
				finalize = True;
				initialind = CRC_LAST_SZ -2;
				flag_lastval = False;

			}

			if( initialind == ((bits_crc*2 ) -1) )
			{
				save_last_crc = use_process_crc[0];

			}
		}

	}
	return (uint8_t)(use_process_crc[0]);
}
//extern uint8_t get_crc(uint8_t *Data, uint16_t size)
//{
//	uint16_t decrease_bit= (size * bits_crc);
//	uint8_t crc_last_step[2];
//	uint8_t is_complete = False;
//	uint16_t counter_byte = 0, limit_byte = size -1;
//	uint8_t num_bit_operat, value_ant=0, posAnt=0;
//	uint8_t compare_byte,finish=0;
//	uint8_t CRC7=0;
//
//	while(is_complete == False && counter_byte <size)
//	{
//		num_bit_operat = find_bit(*(Data+counter_byte) );
//		if(num_bit_operat != initial_value && num_bit_operat < 8 )
//		{
//			value_ant= num_bit_operat - posAnt;
//			decrease_bit -=value_ant;
//			compare_byte  = Process_crc(num_bit_operat, (Data + counter_byte));
//			if(( (decrease_bit <= 8+1) ||  (counter_byte >= limit_byte)) & (finish == False))
//			{
//				crc_last_step[0] = *(Data + counter_byte + 1);
//				crc_last_step[1] = 0x00;
//				counter_byte = 0;
//				decrease_bit = 16;
//				value_ant=0;
//				posAnt=0;
//				num_bit_operat=0;
//				Data = crc_last_step;
//				finish =True;
//			}
//			else if ((finish == True)  & ((decrease_bit - num_bit_operat) < restan_add_bits ) )
//			{
//				is_complete = True;
//				CRC7 =(uint8_t) (*(Data + 1));
//
//			}
//			posAnt = num_bit_operat;
//		}
//		else
//		{
//			counter_byte++;
//			decrease_bit= (size - counter_byte)* byte_size;
//			value_ant=0;
//			posAnt=0;
//		}
//	}
//	return CRC7;
//
//}




