/**
  ******************************************************************************
  * @file           : driver_SMBUS.c
  * @brief          : SMBUS Driver functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-12 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "driver_SMBUS.h"


/* Functions --------------------------------------------------------*/
/**
* @brief get data from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @param pdata:  Pointer to data buffer.
* @param size:   Size Amount of data to be sent.
* @param register_address: Register address to read.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SMBUS_get_data(module_SMBUS_HandleTypeDef *hsmbus, uint8_t *pdata, uint16_t size, uint8_t register_address)
{
	HAL_StatusTypeDef status;
	status =  HAL_I2C_Master_Transmit(hsmbus->i2c_handler, (hsmbus->SMBUS_address & SMBUS_COMMANDE_WRITE), &register_address, sizeof(register_address), hsmbus->timeout);
	if(status != HAL_OK)
	{
		return status;
	}

	status =  HAL_I2C_Master_Receive(hsmbus->i2c_handler, (hsmbus->SMBUS_address & SMBUS_COMMANDE_READ), pdata, size, hsmbus->timeout);

	return status;
}
