/*
 * SPI_BASE.c
 *
 *  Created on: 7 ago. 2022
 *      Author: eduar
 */

#ifndef SPI_BASE_SPI_BASE_C_
#define SPI_BASE_SPI_BASE_C_

#include "stm32f4xx_hal.h"
#include "main.h"


SPI_HandleTypeDef hspi_Base;


void Init_SPI_BASE(void)
{

	hspi_Base.Instance = SPI2;
	hspi_Base.Init.Mode = SPI_MODE_MASTER;
	hspi_Base.Init.Direction = SPI_DIRECTION_2LINES;
	hspi_Base.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi_Base.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi_Base.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi_Base.Init.NSS = SPI_NSS_SOFT;
	hspi_Base.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi_Base.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi_Base.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi_Base.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi_Base.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi_Base) != HAL_OK)
	{
		Error_Handler();
	}
}


extern void write_Comand(uint8_t ptc_data)
{

	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);

	HAL_SPI_Transmit(&hspi_Base, &ptc_data, 1, 0);

	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);
	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
}

void write_Comands(uint8_t *ptc_data, uint8_t size)
{
	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);

	HAL_SPI_Transmit(&hspi_Base, ptc_data, size, 0);

	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);
	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
}

extern void write_value_C_D(uint8_t *ptc_data, uint16_t size)
{
	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);

	HAL_SPI_Transmit(&hspi_Base, ptc_data, 1, 0);

	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);


	HAL_SPI_Transmit(&hspi_Base, ptc_data + 1, size, 1);

	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
}

void Com_Value_rep(uint8_t comand,uint8_t* value_rep , uint32_t num_rep)
{
	uint32_t var;
	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);

	HAL_SPI_Transmit(&hspi_Base, &comand, 1, 0);

	HAL_GPIO_TogglePin(DC_GPIO_Port, DC_Pin);

	for (var = 0; var < num_rep; ++var)
	{
		HAL_SPI_Transmit(&hspi_Base, value_rep ,2, 1);
//		HAL_SPI_Transmit_DMA(&hspi_Base, &value_rep, 1);
//		HAL_SPI_Transmit_IT(&hspi_Base, &value_rep, 1);
	}

	HAL_GPIO_TogglePin(CS_ST7_GPIO_Port, CS_ST7_Pin);
}


extern void Eneble_cont_wr_mode(uint8_t comand)
{
	HAL_GPIO_WritePin(CS_ST7_GPIO_Port, CS_ST7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_Base, &comand, 1, 0);
	HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET);
}


/**
  * @brief  Transform 8bytes to 5 bytes in one uint16.
  * @param  command comand to send
  * @param  value_rep buffer
  * @param  num_rep quantity of values
  * @retval None
  */
void Contin_wr_pix(uint8_t* value_rep , uint32_t num_rep)
{
	uint32_t var;

	for (var = 0; var < num_rep; ++var)
	{
		HAL_SPI_Transmit(&hspi_Base, value_rep ,2, 1);
	}
}

extern void Disable_cont_wr_mode()
{
	HAL_GPIO_WritePin(CS_ST7_GPIO_Port, CS_ST7_Pin, GPIO_PIN_SET);
}

#endif /* SPI_BASE_SPI_BASE_C_ */
