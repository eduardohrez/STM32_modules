/*
 * SD_Base_SPI.c
 *
 *  Created on: Dec 13, 2022
 *      Author: eduar
 */


#include "main.h"
#include "SD_Base_SPI.h"
#include "Files_mng.h"
#include "util.h"


// commands defines
#define  Command0  0x40
#define  Command1  0x41
#define  Command2  0x42
#define  Command3  0x43
#define  Command4  0x44
#define  Command5  0x45
#define  Command6  0x46
#define  Command7  0x47
#define  Command8  0x48
#define  Command9  0x49
#define  Command10  0x4a
#define  Command11  0x4b
#define  Command12  0x4c
#define  Command13  0x4d
#define  Command14  0x4e
#define  Command15  0x4f
#define  Command16  0x50
#define  Command17  0x51
#define  Command18  0x52
#define  Command19  0x53
#define  Command20  0x54
#define  Command21  0x55
#define  Command22  0x56
#define  Command23  0x57
#define  Command24  0x58
#define  Command25  0x59
#define  Command26  0x5a
#define  Command27  0x5b
#define  Command28  0x5c
#define  Command29  0x5d
#define  Command30  0x5e
#define  Command31  0x5f
#define  Command32  0x60
#define  Command33  0x61
#define  Command34  0x62
#define  Command35  0x63
#define  Command36  0x64
#define  Command37  0x65
#define  Command38  0x66
#define  Command39  0x67
#define  Command40  0x68
#define  Command41  0x69
#define  Command42  0x6a
#define  Command43  0x6b
#define  Command44  0x6c
#define  Command45  0x6d
#define  Command46  0x6e
#define  Command47  0x6f
#define  Command48  0x70
#define  Command49  0x71
#define  Command50  0x72
#define  Command51  0x73
#define  Command52  0x74
#define  Command53  0x75
#define  Command54  0x76
#define  Command55  0x77
#define  Command56  0x78
#define  Command57  0x79
#define  Command58  0x7a
#define  Command59  0x7b
#define  Command60  0x7c
#define  Command61  0x7d
#define  Command62  0x7e
#define  Command63  0x7f


//Length of commands
#define R1_length_bytes	((uint8_t)0x01)
#define R2_length_bytes	((uint8_t)0x02)
#define R3_length_bytes	((uint8_t)0x05)
#define R6_length_bytes	((uint8_t)0x06)
#define R7_length_bytes	((uint8_t)0x05)
#define RN_No_Response	((uint8_t)0x00)

//Response type
#define R1_Resp_Type	0x00
#define R2_Resp_Type	0x01
#define R3_Resp_Type	0x02
#define R6_Resp_Type	0x06
#define R7_Resp_Type	0x03 // FOR USE IN R_Attrib

//Response ACMD
#define ACMD6 	0x00
#define ACMD22	0x01
#define ACMD23	0x02
#define ACMD41	0x03
#define ACMD42	0x04
#define ACMD51	0x05

// command limit
#define Max_command 64
#define Max_ACMD	0X06
// bool defines
#define False	0x00
#define True	0x01

// stuff bytes
#define long_zeros	((uint32_t)0x00)
#define long_ones	((uint32_t)0xFFFFFFFF)

//General Defines
#define BYTE_SIZE	((uint8_t)8)
#define ACTIVE_ERROR		((uint8_t)1)


//SD States
#define SD_OFF				((uint8_t)0)
#define SD_INIT				((uint8_t)1)
#define SD_RUN				((uint8_t)2)
#define SD_ERR0R_CAMMAND	((uint8_t)0X03)
#define SD_ERR0R_INIT		((uint8_t)0X04)
#define SD_ERR0R			((uint8_t)0XFF)

//Block BOOT SD
#define SD_BLOCK_BOOT			((uint8_t)0X00)
#define SD_INIT_ADDRE_BIOS		((uint16_t)0x01C6)
#define SD_MAX_BLOCK_LENGHT		((uint16_t)511)
#define Max_Size_Block 			((uint16_t)513) // add 1 more for the CRC

//Defines files SD
#define SD_FILES_SELECT			((uint8_t)2)
#define SD_FILE_ATTRIB_BYTE		((uint8_t)11)
#define SD_SIZE_EXTENDED_FILE	((uint8_t)96)
#define SD_SIZE_NORMAL_FILE		((uint8_t)32)

/*Address High*/
#define SD_DIRR_FILE_HI0		((uint8_t)20)
#define SD_DIRR_FILE_HI1		((uint8_t)21)
/*Address Low*/
#define SD_DIRR_FILE_LOW0		((uint8_t)26)
#define SD_DIRR_FILE_LOW1		((uint8_t)27)
/*Ofset size file*/
#define SD_SIZE_FILE_BYTES		((uint8_t)28)

#define SD_FILE_TYPE_EXTENDED	((uint8_t)0X42)
#define SD_FILE_ATTR_ARCHIVE	((uint8_t)0X20)	/*Is file*/
#define SD_FILE_ATTR_NO_FOUND	((uint8_t)0XE5) /*File no found free space*/
// pointer byes
typedef struct R1_Resp{
	uint8_t idle_stat 	:1;
	uint8_t erase_rest	:1;
	uint8_t Ileg_cmd	:1;
	uint8_t cm_crc_err	:1;
	uint8_t eras_seq_err:1;
	uint8_t addr_err	:1;
	uint8_t parm_err	:1;
	uint8_t zeros		:1;
} strc_R1_Resp;

typedef struct R2_Resp{
	uint8_t card_lock 	:1;
	uint8_t skp_lck_f	:1;
	uint8_t error		:1;
	uint8_t CC_error	:1;
	uint8_t card_ecc_f	:1;
	uint8_t wp_violat	:1;
	uint8_t ers_param	:1;
	uint8_t out_tange	:1;
	strc_R1_Resp Resp_R1_BLOCK;
/*	uint8_t idle_state	:1;
	uint8_t erase_reset	:1;
	uint8_t illg_cmd	:1;
	uint8_t com_crc_err	:1;
	uint8_t ers_seq_err	:1;
	uint8_t addr_err	:1;
	uint8_t param_err	:1;
	uint8_t zeros		:1;*/

}strc_R2_Resp;

typedef struct R3_Resp{
	uint32_t 		OCR;
	strc_R1_Resp 	R1_Resp;
}strc_R3_Resp;

typedef struct R6_Resp{
	uint8_t end_bit 	:1;
	uint8_t CRC7		:7;
	uint8_t Card_stat[2];
	uint8_t New_Publis[2];
	uint8_t CMD_Index	:6;
	uint8_t trans_bit	:1;
	uint8_t start_bit	:1;
}strc_R6_Resp;

typedef struct R7_Resp{
	strc_R1_Resp	R1_Resp_R7;
	uint8_t			cmd_vers	:4;
	uint16_t		reserv_bits;
	uint8_t			vltg_accep	:4;
	uint8_t			check_patt;

}strc_R7_Resp;


typedef struct Response_Types{
	strc_R1_Resp *strc_R1;
	strc_R2_Resp *strc_R2;
	strc_R3_Resp *strc_R3;
	strc_R7_Resp *strc_R7;
} types_struct_Res;


typedef struct commands_attrib{
	uint8_t Command;
	uint8_t Send_length;
	uint8_t Type_response;
}CMD_Attribute;

typedef struct Resp_Attr{
	uint8_t	*Path_R;
	uint8_t	lenght_Bytes;
}Resp_Attribute;

typedef struct send_cmd8{
	uint16_t RSRV_ZEROS1;
	uint8_t voltg_sup	:4;
	uint8_t RSRV_ZEROS2 :4;
	uint8_t check_pat;

}strc_send_CMD8;

typedef struct Funct_R{
	uint8_t (*Proces_Resp_R1)(uint8_t*);
}strc_Process_Resp;


// State_SD_Struct
typedef struct SD_State_Data{
	uint8_t 	State;
	uint8_t 	State_Error_Actual;
	uint16_t	Adress_Partition;
	uint32_t	Sector_Files;
	uint8_t 	Block_Read_last[Max_Size_Block];
}SD_StateData;
/*variables for SD */
typedef struct SD_Util_Variables{
	uint32_t Sector;
	uint16_t BPB_ResvdSecCnt;
	uint8_t	 BPB_NumFATs;
	uint32_t BPB_FATSz32;
	uint8_t  BPB_SecPerClus;

}SD_Variables_U;
/*Current file*/
typedef struct SD_CurrentFile{
	uint32_t Address;
	uint8_t  State;
	uint32_t Size; /*Size on bytes*/
}SD_Current_File_atrv;

/*************************** Variables array start ***************************/
CMD_Attribute SPI_Command[] =
{
		{Command0,	0x20, R1_Resp_Type},		//Resets the SD Memory Card
		{Command1,	0x20, R1_Resp_Type},		//Sends host capacity support
		{Command2,	0x00, RN_No_Response},
		{Command3,	0x00, RN_No_Response},
		{Command4,	0x00, RN_No_Response},
		{Command5,	0x00, RN_No_Response}, 		//Reserved for I/O Mode (refer to "SDIO Card Specification")
		{Command6,	0x20, R1_Resp_Type},		//Checks switchable function
		{Command7,	0x00, RN_No_Response},
		{Command8,	0x20, R7_Resp_Type},		//Sends SD Memory Card interface condition
		{Command9, 	0x20, R1_Resp_Type},		//Asks the selected card to send its cardspecific data (CSD)
		{Command10,	0x20, R1_Resp_Type},		//Asks the selected card to send its card identification (CID)
		{Command11,	0x00, RN_No_Response},
		{Command12,	0x20, R1_Resp_Type},		//Forces the card to stop transmission in Multiple Block Read Operation
		{Command13,	0x20, R2_Resp_Type},		//Asks the selected card to send its status register.
		{Command14,	0x00, RN_No_Response},
		{Command15,	0x00, RN_No_Response},
		{Command16,	0x20, R1_Resp_Type},		//In case of SDSC Card, block length is set by this command.
		{Command17,	0x20, R1_Resp_Type},		//Reads a block of the size selected by the SET_BLOCKLEN command.
		{Command18,	0x20, R1_Resp_Type},		//Continuously transfers data blocks from card to host until interrupted by a STOP_TRANSMISSION command.
		{Command19,	0x00, RN_No_Response},
		{Command20,	0x00, RN_No_Response},
		{Command21,	0x00, RN_No_Response},
		{Command22,	0x00, RN_No_Response},
		{Command23,	0x00, RN_No_Response},
		{Command24,	0x20, R1_Resp_Type},		//Writes a block of the size selected by the SET_BLOCKLEN command.
		{Command25,	0x20, R1_Resp_Type},		//Continuously writes blocks of data until 'Stop Tran' token is sent (instead 'Start Block').
		{Command26,	0x00, RN_No_Response},
		{Command27,	0x20, R1_Resp_Type},		//Programming of the programmable bits of the CSD.
		{Command28,	0x20, R1_Resp_Type},		//If the card has write protection features, this command sets the write protection bit of the addressed group.
		{Command29,	0x20, R1_Resp_Type},		//If the card has write protection features, this command clears the write protection bit of the addressed group.
		{Command30,	0x20, R1_Resp_Type},		//If the card has write protection features, this command asks the card to send the status of the write protection bits.
		{Command31,	0x20, R1_Resp_Type},
		{Command32,	0x20, R1_Resp_Type},		//Sets the address of the first write block to be erased.
		{Command33,	0x20, R1_Resp_Type},		//Sets the address of the last write block of the continuous range to be erased.
		{Command34,	0x00, RN_No_Response},
		{Command35,	0x00, RN_No_Response},
		{Command36,	0x00, RN_No_Response},
		{Command37,	0x00, RN_No_Response},
		{Command38,	0x20, R1_Resp_Type},		//Erases all previously selected write blocks. FULE and DISCARD are not supported through SPI interface.
		{Command39,	0x00, RN_No_Response},
		{Command40,	0x00, RN_No_Response},
		{Command41,	0x00, RN_No_Response},
		{Command42,	0x20, R1_Resp_Type},		//Used to Set/Reset the Password or lock/unlock the card.
		{Command43,	0x00, RN_No_Response},
		{Command44,	0x00, RN_No_Response},
		{Command45,	0x00, RN_No_Response},
		{Command46,	0x00, RN_No_Response},
		{Command47,	0x00, RN_No_Response},
		{Command48,	0x00, RN_No_Response},
		{Command49,	0x00, RN_No_Response},
		{Command50,	0x00, RN_No_Response},
		{Command51,	0x00, RN_No_Response},
		{Command52,	0x00, RN_No_Response},
		{Command53,	0x00, RN_No_Response},
		{Command54,	0x00, RN_No_Response},
		{Command55,	0x20, R1_Resp_Type},		//Defines to the card that the next command is an application specific command rather than a standard command
		{Command56,	0x20, R1_Resp_Type},		//Used either to transfer a Data Block to the card or to get a Data Block from the card for general purpose/application specific commands.
		{Command57,	0x00, RN_No_Response},
		{Command58,	0x20, R3_Resp_Type},		//Reads the OCR register of a card. CCS bit is assigned to OCR[30].
		{Command59,	0x20, R3_Resp_Type},		//Turns the CRC option on or off. A '1' in the CRC option bit will turn the option on, a '0' will turn it off
		{Command60,	0x00, RN_No_Response},
		{Command61,	0x00, RN_No_Response},
		{Command62,	0x00, RN_No_Response},
		{Command63,	0x00, RN_No_Response}
};

CMD_Attribute SPI_ACMD[] ={
		{Command6,	0x20, R2_Resp_Type},			//Send the SD Status. The status fields are given in Table 4-44
		{Command22,	0x20, R1_Resp_Type},			//Send the numbers of the well written (without errors) blocks. Responds with 32-bit+CRC data block.
		{Command23,	0x20, R1_Resp_Type},			//Set the number of write blocks to be pre-erased before writing
		{Command41,	0x20, R1_Resp_Type},			//Sends host capacity support information and activates the card's initialization process.
		{Command42,	0x20, R1_Resp_Type},			//Connect[1]/Disconnect[0] the 50 KOhm pull-up resistor on CS (pin 1) of the card.
		{Command51,	0x20, R1_Resp_Type} 			//Reads the SD Configuration Register (SCR).
};



/*************************** End array variables ***************************/
//SPI VARIABLES
SPI_HandleTypeDef hspi_SD;
//strc Response variables
strc_R1_Resp	Res_R1;
strc_R2_Resp	Res_R2;
strc_R3_Resp	Res_R3;
strc_R7_Resp	Res_R7;

types_struct_Res strc_slc_R =
{
		&Res_R1,
		&Res_R2,
		&Res_R3,
		&Res_R7,
};
//
Resp_Attribute R_Attrib[] =
{
		{(uint8_t*)(&Res_R1), R1_length_bytes},
		{(uint8_t*)(&Res_R2), R2_length_bytes},
		{(uint8_t*)(&Res_R3), R3_length_bytes},
		{(uint8_t*)(&Res_R7), R7_length_bytes}
};
//callback

strc_Process_Resp Response_process[] =
{
		{&Proces_Resp_R1},
		{&Proces_Resp_R2},
		{&Proces_Resp_R3},
		{&Proces_Resp_R7},

};

//SD structure and init
SD_StateData SD_Device =
{
		SD_OFF,		//State
		0,			//State_Error_Actual
		0,			//Adress_Partition
		0,			//Sector_Files
	   {0}			//Block_Read
};
//Variables for Regular use into this file
uint8_t SD_Base_Buffer[10];
/*Variables of SD use to get dir*/
static SD_Variables_U SD_Variables =
{
		0,
		0,
		0,
		0,
		0
};

/*current_file_state*/
static SD_Current_File_atrv SD_CurrentFile = {
		0,
		0,
		0,
};
extern void Init_SD_SPI(void)
{
	Configure_SPI();
	HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_SET);
	Init_Resp();

}

extern void Init_Resp(void)
{
	uint8_t index;
	uint8_t Index_Strc = 0;
	uint8_t *Data_fill;
	uint8_t Num_bytes;

	for (Index_Strc = 0; Index_Strc < 4; Index_Strc++)
	{
		Data_fill = R_Attrib[Index_Strc].Path_R;
		Num_bytes = R_Attrib[Index_Strc].lenght_Bytes;
		for (index = 0; index < Num_bytes; index++)
		{
			*(Data_fill + index) = 0;
		}
	}

}

extern void SPI_initial_block(void)
{
	uint8_t times;
	uint8_t Data = 0xFF;
	for (times = 0; times < 22; times++) {

		HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi_SD, &Data, 1, 1);
		HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_SET);
	}
}
static void Configure_SPI(void)
{
	  hspi_SD.Instance = SPI3;
	  hspi_SD.Init.Mode = SPI_MODE_MASTER;
	  hspi_SD.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi_SD.Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi_SD.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi_SD.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi_SD.Init.NSS = SPI_NSS_SOFT;
	  hspi_SD.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	  hspi_SD.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi_SD.Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi_SD.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi_SD.Init.CRCPolynomial = 10;
	  if (HAL_SPI_Init(&hspi_SD) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

extern void Dummy_funct_SD(void)
{
//	(void)EnDis_Pull_up(False);
/*	Get_initial_block();

	SD_Device.State_Error_Actual = Read_Block( (uint32_t)SD_Device.Adress_Partition,
											  SD_MAX_BLOCK_LENGHT,
											  (SD_Device.Block_Read_last) );*/
	Get_Block_Data();
	Select_File(0);

}

static void active_Spi_CS(void)
{
	HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_RESET);
}

static void deactive_Spi_CS(void)
{
	HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_SET);
}

//return 4 bytes that correspond of 32 bytes of input
static uint8_t *Fix_Data_CMD(uint32_t Input_Data)
{
	int8_t index=0;

	for (index = 3; index >= 0 ; index--)
	{
		SD_Base_Buffer[3 - index ] = (uint8_t)( (Input_Data >> (index *8 ) ) & 0xFF) ;
	}
	return SD_Base_Buffer;
}

//Initialize SD
extern uint8_t SPI_SD_Initialaze(void)
{
	strc_send_CMD8  CMD8_bld;
	uint8_t Error;
	uint8_t stuff_b[] = {0x00,0x00,0x00,0x00};
	uint32_t stuff_long;
	Error = process_Send_CMD(0,0,stuff_b); //reset SD
	CMD8_bld.RSRV_ZEROS1 = 0x00;
	CMD8_bld.RSRV_ZEROS2 = 0x00;
	CMD8_bld.voltg_sup = 0x01;
	CMD8_bld.check_pat = 0x55;

	Error = process_Send_CMD(8,0,(uint8_t*)(&CMD8_bld) ); //set the actual voltage
	stuff_long = long_ones;
	Error = process_Send_CMD(58,0,(uint8_t*)(&stuff_long)); //Read the OCR

	if(Error == False)
	{

		do {
			stuff_long = long_ones;
			Error = process_Send_CMD(55,0,(uint8_t*)(&stuff_long));	//send to next ACMD
			stuff_long = long_zeros;
			stuff_long = 1<<6;
			Error = process_Send_CMD(ACMD41,1,(uint8_t*)(&stuff_long));

		} while (Res_R1.idle_stat==1);
	}

	if(Error == False)
	{
		stuff_long = long_ones;
		Error = process_Send_CMD(58,0,(uint8_t*)(&stuff_long)); //Read the OCR check version
	}

	if( ( (Res_R3.OCR & (3 << 30)) >> 30) == 3 )
	{
		Error = True;
		SD_Device.State = SD_ERR0R_INIT;
	}
	else
	{
		SD_Device.State = SD_INIT;
		Error = False;
	}

	return Error;
}



extern uint8_t process_Send_CMD(uint8_t command, uint8_t ACMD_CMD, uint8_t *Data_send)
{
	uint8_t Index;
	uint8_t Data[10];
	uint8_t number_package;
	uint8_t Error;

	if( (command < Max_command) && (ACMD_CMD==False)) // only for CMD
	{
		number_package = (uint8_t)((SPI_Command[command].Send_length)/8);
		*(Data) = SPI_Command[command].Command;
		for (Index = 0; Index < number_package; Index++)
		{
			*(Data + 1 + Index) = *(Data_send + Index);
		}
		number_package++; //increment the command
		 *(Data + Index + 1) = ( ((get_crc(Data,number_package) ) << 0x01 ) | 0x01);
		number_package++;

		HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_RESET);
		// Write the command for the SPI
		HAL_SPI_Transmit(&hspi_SD, Data, number_package, 5);

		Error = process_Read_CMD (SPI_Command[command].Type_response, Data);
	}

	else if ( (command < Max_ACMD) && (ACMD_CMD == True) )
	{
		number_package = (uint8_t)(SPI_ACMD[command].Send_length/8);

		*(Data) = SPI_ACMD[command].Command;

		for (Index = 0; Index < number_package; Index++)
		{
			*(Data + 1 + Index) = *(Data_send +Index);
		}
		number_package++;
		*(Data + Index + 1) = ( ((get_crc(Data,number_package) ) << 0x01 ) | 0x01);
		number_package++;

		HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_RESET);

		// Write the command for the SPI ACM
		HAL_SPI_Transmit(&hspi_SD, Data, number_package, 5);
		Error = process_Read_CMD (SPI_ACMD[command].Type_response, Data);
	}
	return Error;
}

extern uint8_t process_Read_CMD(uint8_t Read_comand_Type,uint8_t *Data)
{
	uint8_t Times_ret;
	uint8_t Max_bytes_Data = 4;
	uint8_t Get_data_enable = False;
	uint8_t Error = True;
	uint8_t *initial_ptr = Data;
	uint8_t stuuf_ones=0xFF;

	for (Times_ret = 0; Times_ret < Max_bytes_Data; Times_ret++)
	{
//		HAL_SPI_Receive(&hspi_SD, Data, 1, 5);
		HAL_SPI_TransmitReceive(&hspi_SD, &stuuf_ones, Data, 1, 5);
		if( ( (*(Data) & 0x80) ==  0x00) &  (Get_data_enable == False) )
		{
			Max_bytes_Data = R_Attrib[Read_comand_Type].lenght_Bytes;
			Get_data_enable = True;
			Times_ret=0;
			Data = (Data+1);
			Error = False;

		}
		else if( Get_data_enable == True)
		{
			Data = (Data+1);

		}
	}

	if(Error == False) // check the command if the response is correct
	{
		Error = Response_process[Read_comand_Type].Proces_Resp_R1(initial_ptr);
	}

	HAL_GPIO_WritePin(CS_SD_GPIO_Port, CS_SD_Pin, GPIO_PIN_SET);

	return Error;
}


//process to read RESP
static uint8_t Proces_Resp_R1(uint8_t *Data_proc)
{
	uint8_t Error = False;
	strc_R1_Resp *point_R1 = (strc_R1_Resp*)Data_proc;
	if( point_R1->Ileg_cmd || point_R1->cm_crc_err ||
			point_R1->eras_seq_err || point_R1->addr_err || point_R1->parm_err)
	{
		Error = True;
	}
	Res_R1 = *point_R1;
	return Error;
}

static uint8_t Proces_Resp_R2(uint8_t *Data_proc)
{
	uint8_t Error = False;
	strc_R2_Resp  *R2_procc = (strc_R2_Resp*)(Data_proc);
	strc_R1_Resp  *R1_procc =  &R2_procc->Resp_R1_BLOCK;

	Error = Proces_Resp_R1( (uint8_t*)(R1_procc) );
	if( Error == False)
	{
		if( R2_procc->error || R2_procc->CC_error || R2_procc->card_ecc_f ||
				R2_procc->wp_violat || R2_procc->out_tange)
		{
			Error = True;
		}
	}

	Res_R2 = *R2_procc;
	return Error;
}

static uint8_t Proces_Resp_R3(uint8_t *Data_proc)
{
	uint8_t Error = False;
	strc_R1_Resp *R1_Stand =  (strc_R1_Resp*)(Data_proc);
	Error = Proces_Resp_R1( (uint8_t*)(R1_Stand) );
	Res_R3.R1_Resp = *R1_Stand;
	if(Error == False)
	{
		Res_R3.OCR = ( ( *(Data_proc + 1)<< 24) | (*(Data_proc+2)<< 16) | (*(Data_proc + 3)<< 8) | (*(Data_proc + 4)) );
	}

	return Error;
}

static uint8_t Proces_Resp_R7(uint8_t *Data_proc)
{
	uint8_t Error = False;
	strc_R1_Resp  *R1_procc =  (strc_R1_Resp*)(Data_proc);


	Error = Proces_Resp_R1( (uint8_t*)(R1_procc) );

	if(Error == False)
	{
		Res_R7.R1_Resp_R7 =  *R1_procc;
		Res_R7.cmd_vers = ( (*(Data_proc + 1) & 0xF0)>>4);
		Res_R7.reserv_bits = (  ((*(Data_proc + 1) & 0x0F) <<12) | (*(Data_proc + 2)<< 4 ) | ( (*(Data_proc + 3) & 0xF0)>>4 ) );
		Res_R7.vltg_accep = (*(Data_proc + 3) & 0x0F);
		Res_R7.check_patt = (*(Data_proc + 4));
	}

	return Error;
}



// code for read the block of SD
extern uint8_t EnDis_Pull_up(uint8_t Enable_Diable)
{
	uint8_t Error = True;
	uint32_t stuuf_ones = long_ones;

	Enable_Diable =  Enable_Diable< 2 ? Enable_Diable : 0;

	Error = process_Send_CMD(55,False,(uint8_t*)(&stuuf_ones)); // Application command

	if( !Error )
	{
//		stuuf_ones =1 ;
		Error = process_Send_CMD(ACMD42,True,(uint8_t*)(&stuuf_ones));
	}

	return Error;
}

extern uint8_t Read_Block(uint32_t set_block, uint32_t lenght, uint8_t *buffer)
{
	uint8_t Error = True;
	uint32_t Index_Data = 0;
	uint8_t stuuf_ones = 0xFF;
	uint8_t ReadData_recived = False;

	//limit of size block
	if(lenght <= SD_MAX_BLOCK_LENGHT )
	{
		Error = process_Send_CMD(16,False,(Fix_Data_CMD(lenght) ) );
	}
	else
	{
		Error = True;
	}

	if(!Error)
	{
		Error = process_Send_CMD(17,False, Fix_Data_CMD(set_block) );

		if(!Error)
		{
			active_Spi_CS();
			//read the stuf bits
			while(ReadData_recived == False)
			{
				HAL_SPI_TransmitReceive(&hspi_SD, &stuuf_ones, (buffer), 1, 5);

				//is received the start byte or the maximum wait of data is reached
				if( ((*buffer & 0x01) == 0x00) ||  Index_Data > 150)
				{
					ReadData_recived = True;
				}

				Index_Data++;
			}

			//increment the length because we need read the CRC
			lenght +=1;

			for ( Index_Data = 0; Index_Data <= lenght; Index_Data++)
			{
				HAL_SPI_TransmitReceive(&hspi_SD, &stuuf_ones, (buffer + Index_Data), 1, 10);
			}

			deactive_Spi_CS();
		}
	}
	return Error;
}

//Read the MBR_AND_START_UP
extern uint8_t Get_initial_block(void)
{
	uint8_t index;

	SD_Device.State_Error_Actual = Read_Block(SD_BLOCK_BOOT,SD_MAX_BLOCK_LENGHT,SD_Device.Block_Read_last);

	if( SD_Device.State_Error_Actual !=  ACTIVE_ERROR)
	{
		for (index = 0; index < 2; index++)
		{
			SD_Device.Adress_Partition |= (SD_Device.Block_Read_last[ SD_INIT_ADDRE_BIOS + index ]) << (index * BYTE_SIZE );
		}
	}

	return SD_Device.State_Error_Actual;
}

/**
  * @brief  Set the Data were is the table of documents in the SD (implementation is only for fat32).
  * @retval State of the process (error true) (no error false).
  * @info	check the data sheet to see how get the index.
  */
extern uint8_t Get_Block_Data(void)
{
	uint8_t index ;
	uint8_t BPB_NumFATs;
	uint32_t BPB_FATSz32 = 0;
	uint16_t BPB_ResvSecCnt = 0;

	Get_initial_block();

	if( (SD_Device.State_Error_Actual !=  ACTIVE_ERROR) && (SD_Device.Adress_Partition != 0))
	{
		/*Read the block of 1st address partition, only we can read the 1st partition*/
		SD_Device.State_Error_Actual = Read_Block( (uint32_t)SD_Device.Adress_Partition,
												   SD_MAX_BLOCK_LENGHT,
												  (SD_Device.Block_Read_last) );
		/*Get the BPB_FATSz32*/
		for (index = 0; index < 4; index++)
		{
			BPB_FATSz32 |= ( (SD_Device.Block_Read_last[36 + index]) << (index * BYTE_SIZE) );
			SD_Variables.BPB_FATSz32 = BPB_FATSz32;

		}

		/*Get the BPB_ResvSecCnt*/
		for (index = 0; index < 2; index++)
		{
			BPB_ResvSecCnt |= ( (SD_Device.Block_Read_last[14 + index]) << (index * BYTE_SIZE) );
			SD_Variables.BPB_ResvdSecCnt = BPB_ResvSecCnt;
		}

		/*Get the BPB_NumFATs*/
		BPB_NumFATs = SD_Device.Block_Read_last[16];
		SD_Variables.BPB_NumFATs = BPB_NumFATs;

		/*Get the BPB_SecPerClus*/
		SD_Variables.BPB_SecPerClus = SD_Device.Block_Read_last[13];

		SD_Device.Sector_Files = BPB_ResvSecCnt + (BPB_NumFATs * BPB_FATSz32) + SD_Device.Adress_Partition;
		SD_Variables.Sector = SD_Device.Sector_Files;


		SD_Device.State_Error_Actual = Read_Block( (uint32_t)SD_Device.Sector_Files,
														   SD_MAX_BLOCK_LENGHT,
														  (SD_Device.Block_Read_last) );
	}

	return SD_Device.State_Error_Actual;
}



/**
  * @brief  Get the direction and the first block of the file.
  * @param  select what file need read.
  * @retval State of the process (error true) (no error false).
  * @info	check the data sheet how get the file
  */
uint8_t Select_File(uint8_t File_selected)
{
	uint16_t 	index_file = 0;
	uint8_t		File_exist = False;
	uint32_t 	Addres_File = 0;
	uint32_t 	Address_sector_Modify = SD_Device.Sector_Files;
	uint8_t		*Addres ;

	if(File_selected < SD_FILES_SELECT )
	{
		while(index_file < SD_MAX_BLOCK_LENGHT)
		{
			if(SD_Device.Block_Read_last[index_file] != SD_FILE_TYPE_EXTENDED)
			{
				if( (SD_Device.Block_Read_last[index_file + SD_FILE_ATTRIB_BYTE] == SD_FILE_ATTR_ARCHIVE) &&
						(SD_Device.Block_Read_last[index_file ] != SD_FILE_ATTR_NO_FOUND) )
				{
					/*Exit file and is the name no is extended */
					File_exist = Verify_File( (uint8_t*)(&SD_Device.Block_Read_last[index_file]), File_selected );

					if(File_exist == False) /*No is the file for the search*/
					{
						(index_file < SD_MAX_BLOCK_LENGHT) ? index_file += SD_SIZE_NORMAL_FILE : index_file;	/*Is extended file jump to next file */
					}

				}
				else
				{
					(index_file < SD_MAX_BLOCK_LENGHT) ? index_file += SD_SIZE_NORMAL_FILE : index_file;	/*No exit the file jump the next*/
				}

				if(File_exist == True)
				{
					break; /*The files was found*/
				}
				else if( 0x00 == SD_Device.Block_Read_last[index_file])
				{
					break; /*we don't have more files to analyze*/
				}
				else
				{
					/*Do nothing*/
				}

			}
			else
			{
				(index_file < SD_MAX_BLOCK_LENGHT) ? index_file += SD_SIZE_EXTENDED_FILE : index_file;	/*Is extended file jump to next file */
			}

			/*Read the entire files next sector*/
			if(index_file >= SD_MAX_BLOCK_LENGHT)
			{
				Address_sector_Modify++;

				SD_Device.State_Error_Actual = Read_Block( Address_sector_Modify,
														   SD_MAX_BLOCK_LENGHT,
														  (SD_Device.Block_Read_last) );
				if(SD_Device.State_Error_Actual == False )
				{
					index_file = 0;
				}
				else
				{
					File_exist = False;
				}
			}
		}

	}
	/*Calculate address for file*/
	if( True == File_exist)
	{
		Addres_File = ( (SD_Device.Block_Read_last[index_file + SD_DIRR_FILE_HI1] <<24) | (SD_Device.Block_Read_last[index_file + SD_DIRR_FILE_HI0] << 16) ) | ((SD_Device.Block_Read_last[index_file + SD_DIRR_FILE_LOW1] << 8) | SD_Device.Block_Read_last[index_file + SD_DIRR_FILE_LOW0] );
		Addres_File = ((Addres_File - 2) * SD_Variables.BPB_SecPerClus) + SD_Variables.Sector; //BLOCK

		SD_CurrentFile.Address = Addres_File;
		Addres = (uint8_t*)(&SD_Device.Block_Read_last) ;
		Addres += index_file + SD_SIZE_FILE_BYTES ;
		SD_CurrentFile.Size = Util_Arr_32BIND(Addres ); // check this function

	}

	return File_exist;
}

/**
  * @brief  Get the attributes of the actual file.
  * @param  Pointer where be store the information.
  * @retval fill the data was success.
  */
uint8_t Get_atributes_File(strc_FILE_SELECT* File_atriv)
{
	File_atriv->Actual_address  = 0; //addres for the file start 0
	File_atriv->Initial_address = 0; //addres for the file start 0
	File_atriv->Size_File		= SD_CurrentFile.Size;
	File_atriv->Final_Adress	= File_atriv->Size_File;
	File_atriv->Data_bock       = SD_Device.Block_Read_last;

	return SD_Device.State_Error_Actual;

}
