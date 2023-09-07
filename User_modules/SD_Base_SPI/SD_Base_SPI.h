/*
 * SD_Base_SPI.h
 *
 *  Created on: Dec 13, 2022
 *      Author: eduar
 */

#ifndef SD_BASE_SPI_SD_BASE_SPI_H_
#define SD_BASE_SPI_SD_BASE_SPI_H_

#include "main.h"
#include "Files_mng.h"

extern void Init_SD_SPI(void);
extern void Init_Resp(void);
static void Configure_SPI(void);
extern void Dummy_funct_SD(void);
extern void SPI_initial_block(void);
static uint8_t process_Send_CMD(uint8_t command, uint8_t ACMD_CMD, uint8_t *Data_send);
static void process_Write_CMD(uint8_t comand, uint16_t lenght);
static void active_Spi_CS(void);
static void deactive_Spi_CS(void);

extern uint8_t process_Read_CMD(uint8_t Read_comand_Type,uint8_t *Data);
static uint8_t *Fix_Data_CMD(uint32_t Input_Data);
extern uint8_t Read_Block(uint32_t set_block, uint32_t lenght, uint8_t *buffer);
extern uint8_t EnDis_Pull_up(uint8_t Enable_Diable);
extern uint8_t Get_Block_Data(void);
extern uint8_t Get_initial_block(void);
extern uint8_t Get_Boot_Block(void);
extern uint8_t Get_atributes_File(strc_FILE_SELECT* File_atriv);


/* found the file */
extern uint8_t Select_File(uint8_t File_selected);


// SD process functions
extern uint8_t SPI_SD_Initialaze(void);
static uint8_t Proces_Resp_R1(uint8_t *Data_proc);
static uint8_t Proces_Resp_R2(uint8_t *Data_proc);
static uint8_t Proces_Resp_R3(uint8_t *Data_proc);
static uint8_t Proces_Resp_R7(uint8_t *Data_proc);


#endif /* SD_BASE_SPI_SD_BASE_SPI_H_ */
