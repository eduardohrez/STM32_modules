/*
 * Files_mng.h
 *
 *  Created on: 30 may. 2023
 *      Author: eduar
 */

#ifndef FILES_MANAGER_FILES_MNG_H_
#define FILES_MANAGER_FILES_MNG_H_

#include "main.h"


/*type defs*/
typedef struct File_Select{
	const char *const Name;
	uint32_t Initial_address;
	uint32_t Actual_address;
	uint32_t Final_Adress;
	uint32_t Size_File;
	uint16_t byte_block;
	uint8_t *Data_bock;

}strc_FILE_SELECT;

/*Export functions*/
/* check if is the correct file */
extern uint8_t Verify_File(const uint8_t *Data_File, uint8_t File_selected);
/*read the file*/
extern uint8_t Read_File(uint8_t File_Select);

#endif /* FILES_MANAGER_FILES_MNG_H_ */
