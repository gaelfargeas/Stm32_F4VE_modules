/**
  ******************************************************************************
  * @file           : module_loader.c
  * @brief          : AM2320 Driver functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "driver_AM2320.h"

/* Functions --------------------------------------------------------*/
/**
* @brief AM2320 Initialization
* @param hi2c: Pointer to a I2C_HandleTypeDef structure that contains
*                the configuration information for the specified I2C.
* @retval AM2320 Handler TypeDef
*/
AM2320_HandleTypeDef AM2320_driver_init(I2C_HandleTypeDef *hi2c, uint8_t AM2320_address)
{
	AM2320_HandleTypeDef hAM2320;
	hAM2320.i2c_handler = hi2c;
	hAM2320.AM2320_address = AM2320_address;
	hAM2320.Timeout = HAL_MAX_DELAY;
	hAM2320.temperature = 0;
	hAM2320.humidity = 0;
	sprintf(hAM2320.info, "AM2320 SENSOR");

	return hAM2320;
}

/**
* @brief Get data from AM2320 sensor
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @param Address_to_read: Address of the first register to read
* @param receive_data_size: Number of register to read
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_driver_get_data(AM2320_HandleTypeDef *hAM2320, uint8_t Address_to_read, uint8_t receive_data_size)
{
	HAL_StatusTypeDef status;
	uint8_t data_send[] = {AM2320_READ_REGISTER_CODE, Address_to_read, receive_data_size};

	// Send read request
	status = HAL_I2C_Master_Transmit(hAM2320->i2c_handler, hAM2320->AM2320_address, data_send, 3,  hAM2320->Timeout);
	if(status != HAL_OK)
	{
		return status;
	}

	// Received data
	status =  HAL_I2C_Master_Receive(hAM2320->i2c_handler, hAM2320->AM2320_address, hAM2320->raw_data, receive_data_size + 4,  hAM2320->Timeout);
	if(status != HAL_OK)
	{
		return status;
	}

	// Check data format
	if(hAM2320->raw_data[0] != AM2320_READ_REGISTER_CODE && hAM2320->raw_data[1] != receive_data_size)
	{
		return HAL_ERROR;
	}

	return AM2320_driver_check_CRC_from_data(hAM2320);
}

/**
* @brief send blanc request to the sensor
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_driver_get_blanc_data(AM2320_HandleTypeDef *hAM2320)
{
	return AM2320_driver_get_data(hAM2320, 0x00, 0x00);
}

/**
* @brief get temperature from AM2320 data
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_driver_get_temperature_from_data_raw(AM2320_HandleTypeDef *hAM2320)
{

	uint16_t temperature_tmp = (hAM2320->raw_data[2] << 8 | hAM2320->raw_data[3]);

	// check negative sign
	if(hAM2320->raw_data[2] && 0x80)
	{
		temperature_tmp = -(int16_t) (temperature_tmp & 0x7fff);
	}

	hAM2320->temperature = (float) temperature_tmp / 10.0;

	return HAL_OK;
}

/**
* @brief get humidity from AM2320 data
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_driver_get_humidity_from_data_raw(AM2320_HandleTypeDef *hAM2320)
{
	hAM2320->humidity = (float) (hAM2320->raw_data[2] << 8 | hAM2320->raw_data[3]) / 10.0;
	return HAL_OK;
}

/**
* @brief Check CRC from AM2320 data
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_driver_check_CRC_from_data(AM2320_HandleTypeDef *hAM2320)
{
	// no CRC send : always 0xFFFF
	return HAL_OK;

}

