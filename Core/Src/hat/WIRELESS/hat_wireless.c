/**
  ******************************************************************************
  * @file           : hat_wireless.c
  * @brief          : WIRELESS Hat functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-27 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "hat_wireless.h"

/* Functions --------------------------------------------------------*/

/**
* @brief Wireless module initialization.
* @param spi_handler: 				pointer to a SPI_HandleTypeDef structure that contains
*               					the configuration information for SPI module..
* @param wireless_module_selected: 	Template selected.
* @param cs_GPIOx:					GPIOx of the ChipSelect gpio.
* @param cs_GPIO_Pin:				GPIO_PIN of the ChipSelect gpio.
* @param payload_length:			Payload length.
* @retval HAL status
*/
module_wireless_HandleTypeDef hat_wireless_init(SPI_HandleTypeDef* spi_handler, wireless_list_enum wireless_module_selected,
 GPIO_TypeDef* cs_GPIOx, uint16_t cs_GPIO_Pin, uint8_t payload_length)
{
	module_wireless_HandleTypeDef hwirelessmodule =	{
			.spi_handler = spi_handler,
			.wireless_module_selected = wireless_module_selected,
			.CS_GPIOx = cs_GPIOx,
			.CS_GPIO_Pin = cs_GPIO_Pin,
			.payload_length = payload_length,
			.timeout = HAL_MAX_DELAY
	};

	switch (wireless_module_selected) {
		case WIRELESS_E28_2G4M27S:
			//driver_E28_2G4M27S_init();
			break;

		case WIRELESS_NRF24L01:
			driver_NRF24L01_init(&hwirelessmodule, RF24L01_TX_MODE, 2450, RF24L01_RF_SETUP_DATA_RATE_1MBPS,
					RF24L01_RF_SETUP_POWER_0DBM, RF24L01_CRC_1_BYTE, RF24L01_AW_3_BYTES, RF24L01_RETR_10, RF24L01_RETR_1000_μS);
			break;

		default:
			break;
	}

	return hwirelessmodule;
}


/**
* @brief receive data.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param data:	 		pointer to data buffer.
* @param data_size:		Size amount of data to be received.
* @retval HAL status
*/
HAL_StatusTypeDef hat_wireless_receive_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size)
{
	HAL_StatusTypeDef status = HAL_OK;
	switch (hwirelessmodule->wireless_module_selected) {
		case WIRELESS_E28_2G4M27S:
			//status = driver_E28_2G4M27S_receice_data();

			break;

		case WIRELESS_NRF24L01:
			status = driver_NRF24L01_receice_data(hwirelessmodule, data, data_size);

			break;

		default:
			return HAL_ERROR;
			break;
	}

	return status;
}

/**
* @brief send data.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param data:			pointer to data buffer.
* @param data_size:		Size amount of data to be send.
* @retval HAL status
*/
HAL_StatusTypeDef hat_wireless_send_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size)
{
	HAL_StatusTypeDef status = HAL_OK;
	switch (hwirelessmodule->wireless_module_selected) {
		case WIRELESS_E28_2G4M27S:
			status = driver_E28_2G4M27S_send_data(hwirelessmodule);

			break;

		case WIRELESS_NRF24L01:
			status = driver_NRF24L01_send_data(hwirelessmodule, data , data_size);

			break;

		default:
			return HAL_ERROR;
			break;
	}

	return status;
}
