/**
  ******************************************************************************
  * @file           : module_loader.c
  * @brief          : Header for driver_AM2320.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */

#ifndef SRC_DRIVER_DRIVER_AM2320_H_
#define SRC_DRIVER_DRIVER_AM2320_H_

#include "stm32f4xx_hal.h"
#include <string.h>

#define AM2320_READ_REGISTER_CODE 0x03
#define AM2320_ADRESSE 0xB8
#define AM2320_TOSTRING_SIZE 33 //strlen("Temperature : XXXX/nHumidity : XX")

typedef struct {
	I2C_HandleTypeDef* i2c_handle;
	uint8_t AM2320_address;
	uint8_t raw_data[8];
	uint32_t Timeout;
	float temperature;
	float humidity;
	char info[20];
	char to_string[AM2320_TOSTRING_SIZE];
} AM2320_HandleTypeDef;

/* Exported functions prototypes ---------------------------------------------*/
AM2320_HandleTypeDef AM2320_driver_init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef AM2320_driver_get_data(AM2320_HandleTypeDef  *hAM2320, uint8_t Address_to_read, uint8_t receive_data_size);
HAL_StatusTypeDef AM2320_driver_get_temperature_from_data_raw(AM2320_HandleTypeDef *hAM2320);
HAL_StatusTypeDef AM2320_driver_get_humidity_from_data_raw(AM2320_HandleTypeDef *hAM2320);
HAL_StatusTypeDef AM2320_driver_check_CRC_from_data(AM2320_HandleTypeDef *hAM2320);
#endif /* SRC_DRIVER_DRIVER_AM2320_H_ */
