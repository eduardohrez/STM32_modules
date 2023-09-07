/*
 * files_mng.c
 *
 *  Created on: 30 may. 2023
 *      Author: eduar
 */
#include "main.h"
#include "Files_mng.h"
#include "SD_Base_SPI.h"


/*Defines*/
// bool defines
#define False	0x00
#define True	0x01
/*end Defines*/

/*Types def structures */

typedef struct files_sd{
	char File_Name[11];
	uint8_t size_name;
}strc_SD_FILES;



/*End defines structures*/

/*Defines the constants*/
const strc_SD_FILES Files_select[] =
{
		{"ARCHIVO TXT",	10},
		{"img_1...TXT",	10}
};
strc_FILE_SELECT Files_work[] =
{
		{NULL, 0, 0, 0, 0, NULL},
		{NULL, 0, 0, 0, 0, NULL}
};
/*End define constant*/


/**
  * @brief  Get the direction and the first block of the file.
  * @param  select what file need read.
  * @retval State of the process (error true) (no error false).
  * @info	check the data sheet how get the file
  */
uint8_t Verify_File(const uint8_t *Data_File, uint8_t File_selected)
{
	uint8_t Status_return = False;
	uint8_t text_index;
	uint8_t check_file = 1;

	if(Data_File != NULL)
	{
		for (text_index = 0; text_index < Files_select[File_selected].size_name; text_index++)
		{
			if( Files_select[File_selected].File_Name[text_index] != (char)Data_File[text_index] )
			{
				check_file = 0;
			}
		}
		if(check_file == True)
		{
			Status_return = True;
		}
	}

	return Status_return;
}

/**
  * @brief  Read the file of the current select file and store a buffer.
  * @param  what file be read.
  */
extern uint8_t Read_File(uint8_t File_Select)
{

}
