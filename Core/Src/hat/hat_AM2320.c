/**
  ******************************************************************************
  * @file           : module_loader.c
  * @brief          : AM2320 Hat functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */

#include "hat_AM2320.h"

/**
* @brief Get temperature from the AM2320 sensor
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_get_temperature(AM2320_HandleTypeDef *AM2320)
{
	// Get raw data
	HAL_StatusTypeDef status = AM2320_driver_get_data(AM2320, 0x02, 2);
	AM2320_driver_get_temperature_from_data_raw(AM2320);
	return status;
}

/**
* @brief Get humidity from the AM2320 sensor
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
HAL_StatusTypeDef AM2320_get_humidity(AM2320_HandleTypeDef *AM2320)
{
	// Get raw data
	HAL_StatusTypeDef status = AM2320_driver_get_data(AM2320, 0x00, 2);
	// Get humidity
	AM2320_driver_get_humidity_from_data_raw(AM2320);

	return status;
}

/**
* @brief Get humidity from the AM2320 sensor
* @param hAM2320: Pointer to a AM2320_HandleTypeDef structure that contains
*                informations for the specified AM2320.
* @retval HAL status
*/
int AM2320_to_string(AM2320_HandleTypeDef *AM2320)
{
	int res = sprintf(AM2320->to_string, "Temperature : %d/nHumidity : %d", (int)(AM2320->temperature /1), (int)(AM2320->humidity/1));
	return res;
}
