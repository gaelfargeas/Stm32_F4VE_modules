
/**
  ******************************************************************************
  * @file           : inc_wireless.h
  * @brief          : Define for wireless hat and drivers.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-27 gael fargeas created
  *
  */
#ifndef INC_WIRELESS_INC_WIRELESS_H_
#define INC_WIRELESS_INC_WIRELESS_H_

typedef enum
{
  WIRELESS_DEFAULT 			= 0,
  WIRELESS_E28_2G4M27S		= 1,
  WIRELESS_NRF24L01			= 2
} wireless_list_enum;


typedef struct {
	SPI_HandleTypeDef* spi_handler;
	GPIO_TypeDef* CS_GPIOx;
	uint16_t CS_GPIO_Pin;
	uint8_t payload_length;
	uint32_t timeout;
	uint8_t wireless_module_address;
	wireless_list_enum wireless_module_selected;
} module_wireless_HandleTypeDef;


#endif /* INC_WIRELESS_INC_WIRELESS_H_ */
