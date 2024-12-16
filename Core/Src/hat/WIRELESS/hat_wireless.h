/**
  ******************************************************************************
  * @file           : hat_wireless.h
  * @brief          : Header for hat_wireless.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-27 gael fargeas created
  *
  */

#ifndef SRC_HAT_WIRELESS_HAT_WIRELESS_H_
#define SRC_HAT_WIRELESS_HAT_WIRELESS_H_

/* Includes ---------------------------------------------------------*/
#include <WIRELESS/driver_SX1280.h>
#include "stm32f4xx_hal.h"
#include "WIRELESS/driver_NRF24L01.h"
#include "WIRELESS/inc_wireless.h"

/* Functions prototypes ---------------------------------------------*/
module_wireless_HandleTypeDef hat_wireless_init(SPI_HandleTypeDef* spi_handler, wireless_list_enum wireless_module_selected,
		GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t payload_length);
HAL_StatusTypeDef hat_wireless_receive_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size);
HAL_StatusTypeDef hat_wireless_send_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size);

#endif /* SRC_HAT_WIRELESS_HAT_WIRELESS_H_ */
