/*
 * hat_AM2320.c
 *
 *  Created on: 31 oct. 2024
 *      Author: gael fargeas
 */

#include "hat_AM2320.h"

HAL_StatusTypeDef AM2320_get_temperature(AM2320_HandleTypeDef *AM2320)
{
	// Get raw data
	HAL_StatusTypeDef status = AM2320_driver_get_data(AM2320, 0x02, 2);
	AM2320_driver_get_temperature_from_data_raw(AM2320);
	return status;
}

HAL_StatusTypeDef AM2320_get_humidity(AM2320_HandleTypeDef *AM2320)
{
	// Get raw data
	HAL_StatusTypeDef status = AM2320_driver_get_data(AM2320, 0x00, 2);
	// Get humidity
	AM2320_driver_get_humidity_from_data_raw(AM2320);

	return status;
}
