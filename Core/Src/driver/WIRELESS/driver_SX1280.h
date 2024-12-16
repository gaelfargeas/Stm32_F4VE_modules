/*
 * driver_E28-2G4M27S.h
 *
 *  Created on: 27 nov. 2024
 *      Author: gael fargeas
 *      https://www.tme.eu/Document/1042f35a88b6ee421559d19923804032/SX128x.pdf
 */

#ifndef SRC_DRIVER_WIRELESS_DRIVER_SX1280_H_
#define SRC_DRIVER_WIRELESS_DRIVER_SX1280_H_

#include "stm32f4xx_hal.h"
#include "WIRELESS/inc_wireless.h"
#include "stdbool.h"
#include "string.h"

#define SX1280_NOP	0x00

#define SX1280_CMD_GET_STATUS					0xC0
#define SX1280_CMD_WRITE_REGISTER  				0x18
#define SX1280_CMD_READ_REGISTER     			0x19
#define SX1280_CMD_WRITE_BUFFER 				0x1A
#define SX1280_CMD_READ_BUFFER					0x1B
#define SX1280_CMD_SET_SLEEP					0x84
#define SX1280_CMD_SET_STANDBY					0x80
#define SX1280_CMD_SET_FS						0xC1
#define SX1280_CMD_SET_TX						0x83
#define SX1280_CMD_SET_RX						0x82
#define SX1280_CMD_SET_RX_DUTY_CYCLE			0x94
#define SX1280_CMD_SET_LONG_PREAMBLE			0x9B
#define SX1280_CMD_SET_CAD						0xC5
#define SX1280_CMD_SET_TX_CONTINUOUS_WAVE		0xD1
#define SX1280_CMD_SET_TX_CONTINUOUS_PREAMBLE	0xD2
#define SX1280_CMD_SET_AUTO_TX					0x98
#define SX1280_CMD_SET_AUTO_FS					0x9E
#define SX1280_CMD_SET_PACKET_TYPE				0x8A
#define SX1280_CMD_GET_PACKET_TYPE				0x03
#define SX1280_CMD_SET_RF_FREQUENCY				0x86
#define SX1280_CMD_SET_TX_PARAMS				0x8E
#define SX1280_CMD_SET_CAD_PARAMS				0x88
#define SX1280_CMD_SET_BUFFER_BASE_ADDRESS		0x8F
#define SX1280_CMD_SET_MODULATION_PARAMS		0x8B
#define SX1280_CMD_SET_PACKET_PARAMS			0x8C
#define SX1280_CMD_SET_RX_BUFFER_STATUS			0x17
#define SX1280_CMD_GET_PACKET_STATUS			0x1D
#define SX1280_CMD_GET_RSSI_LNST				0x1F
#define SX1280_CMD_SET_DIO_IRQ_PARAMS			0x8D
#define SX1280_CMD_GET_IRQ_STATUS				0x15
#define SX1280_CMD_CLEAR_IRQ_STATUS				0x97
#define SX1280_CMD_SET_REGULATOR_MODE			0x96
#define SX1280_CMD_SET_SAVE_CONTEXT				0xD5
#define SX1280_CMD_SET_PERF_COUNTER_MODE		0x9C
#define SX1280_CMD_SET_UART_SPEED				0x9D
#define SX1280_CMD_SET_RANGING_ROLE				0xA3
#define SX1280_CMD_SET_ADVANCED_RANGING			0x9A

#define SX1280_REG_CONFIG            0x00


/* Typedef -------------------------------------------------------------*/
typedef enum
{
  SX1280_SLEEP_CONFIGS_ALL_FLUSH 				= 0b00,
  SX1280_SLEEP_CONFIGS_ONLY_RAM_RETENTION 		= 0b01,
  SX1280_SLEEP_CONFIGS_ONLY_BUFFER_RETENTION 	= 0b10,
  SX1280_SLEEP_CONFIGS_ALL_RETENTION 			= 0b11
} SX1280_SLEEP_CONFIGS;

typedef enum
{
  SX1280_STANDBY_CONFIGS_RC 		= 0,
  SX1280_STANDBY_CONFIGS_XOSC		= 1
} SX1280_STANDBY_CONFIGS;

typedef enum
{
  SX1280_TX_RX_PERIODE_BASE_15625_NS		= 0X00,
  SX1280_TX_RX_PERIODE_BASE_62500_NS		= 0X01,
  SX1280_TX_RX_PERIODE_BASE_1_MS			= 0X02,
  SX1280_TX_RX_PERIODE_BASE_4_MS			= 0X03
} SX1280_TX_RX_PERIODE_BASE;

typedef enum
{
  SX1280_PACKET_TYPE_GFSK		= 0X00,
  SX1280_PACKET_TYPE_LORA		= 0X01,
  SX1280_PACKET_TYPE_RANGING	= 0X02,
  SX1280_PACKET_TYPE_FLRC		= 0X03,
  SX1280_PACKET_TYPE_BLE		= 0X04
} SX1280_PACKET_TYPE;

typedef enum
{
  SX1280_TX_RAMP_TIME_02_US		= 0X00,
  SX1280_TX_RAMP_TIME_04_US		= 0X20,
  SX1280_TX_RAMP_TIME_06_US		= 0X40,
  SX1280_TX_RAMP_TIME_08_US		= 0X60,
  SX1280_TX_RAMP_TIME_10_US		= 0X80,
  SX1280_TX_RAMP_TIME_12_US		= 0XA0,
  SX1280_TX_RAMP_TIME_16_US		= 0XC0,
  SX1280_TX_RAMP_TIME_20_US		= 0XE0
} SX1280_TX_RAMP_TIME;

typedef enum
{
  SX1280_CAD_01_SYMBOL		= 0X00,
  SX1280_CAD_02_SYMBOLS 	= 0X20,
  SX1280_CAD_04_SYMBOLS 	= 0X40,
  SX1280_CAD_08_SYMBOLS 	= 0X60,
  SX1280_CAD_16_SYMBOLS		= 0X80
} SX1280_CAD_SYMBOL_NUMBER;

typedef enum
{
  SX1280_RANGING_ROLE_SLAVE		= 0X00,
  SX1280_RANGING_ROLE_MASTER 	= 0X01
} SX1280_RANGING_ROLE;

/* Functions prototypes ---------------------------------------------*/
HAL_StatusTypeDef driver_SX1280_cs_high(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_SX1280_cs_low(module_wireless_HandleTypeDef *hwirelessmodule);

HAL_StatusTypeDef driver_SX1280_init(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_SX1280_reset(module_wireless_HandleTypeDef *hwirelessmodule);

HAL_StatusTypeDef driver_SX1280_read_register(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t reg, uint8_t *value, uint8_t value_size);
HAL_StatusTypeDef driver_SX1280_write_register(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t reg, uint8_t *value, uint8_t value_size);

HAL_StatusTypeDef driver_SX1280_send_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *value, uint8_t value_size);
HAL_StatusTypeDef driver_SX1280_receice_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *value, uint8_t value_size);

HAL_StatusTypeDef driver_SX1280_set_sleep_mode(module_wireless_HandleTypeDef *hwirelessmodule,  SX1280_SLEEP_CONFIGS sleep_config);
HAL_StatusTypeDef driver_SX1280_set_standby_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_STANDBY_CONFIGS standby_config);
HAL_StatusTypeDef driver_SX1280_set_Tx_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_TX_RX_PERIODE_BASE period_base, uint16_t Tx_timeout);
HAL_StatusTypeDef driver_SX1280_set_Rx_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_TX_RX_PERIODE_BASE period_base, uint16_t Rx_timeout);
HAL_StatusTypeDef driver_SX1280_set_long_preamble_mode(module_wireless_HandleTypeDef *hwirelessmodule, bool enable);
HAL_StatusTypeDef driver_SX1280_(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_SX1280_set_CAD_mode(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_SX1280_set_Tx_continuous_wave_mode(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_SX1280_Tx_continuous_preamble_mode(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_SX1280_set_auto_Tx(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t time);
HAL_StatusTypeDef driver_SX1280_set_packet_type(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_PACKET_TYPE packet_type);
HAL_StatusTypeDef driver_SX1280_get_packet_type(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *packet_type);
HAL_StatusTypeDef driver_SX1280_set_RF_frequency(module_wireless_HandleTypeDef *hwirelessmodule, uint32_t frequency);
HAL_StatusTypeDef driver_SX1280_set_Tx_params(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t power, SX1280_TX_RAMP_TIME ramp_time);
HAL_StatusTypeDef driver_SX1280_set_cad_params(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_CAD_SYMBOL_NUMBER cad_symbol_number);
HAL_StatusTypeDef driver_SX1280_set_buffer_base_address(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t tx_base_adress, uint8_t rx_base_adress);
HAL_StatusTypeDef driver_SX1280_set_modulation_params(module_wireless_HandleTypeDef *hwirelessmodule,
		uint8_t modulation_Param1, uint8_t modulation_Param2, uint8_t modulation_Param3);
HAL_StatusTypeDef driver_SX1280_set_packet_params(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t packet_Param1,  uint8_t packet_Param2,
		 uint8_t packet_Param3, uint8_t packet_Param4, uint8_t packet_Param5, uint8_t packet_Param6, uint8_t packet_Param7);
HAL_StatusTypeDef driver_SX1280_get_packet_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *packet_status1, uint8_t *packet_status2,
		uint8_t *packet_status3, uint8_t *packet_status4, uint8_t *packet_status5);
HAL_StatusTypeDef driver_SX1280_get_Rx_buffer_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *Rx_payload_length, uint8_t *Rx_start_buffer_pointer);
HAL_StatusTypeDef driver_SX1280_get_rssi_inst(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *rssi_inst);
HAL_StatusTypeDef driver_SX1280_set_dio_irq_params(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t irq_mask, uint16_t dio1_mask, uint16_t dio2_mask, uint16_t dio3_mask);
HAL_StatusTypeDef driver_SX1280_get_irq_status(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t *irq_status);
HAL_StatusTypeDef driver_SX1280_clear_irq_status(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t irq_mask);
HAL_StatusTypeDef driver_SX1280_set_regulator_mode(module_wireless_HandleTypeDef *hwirelessmodule, bool regulator_mode_param);
HAL_StatusTypeDef driver_SX1280_set_perf_counter_mode(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t perf_counter_mode);
HAL_StatusTypeDef driver_SX1280_set_UART_speed(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t UART_speed);
HAL_StatusTypeDef driver_SX1280_set_ranging_role(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_RANGING_ROLE ranging_role);
HAL_StatusTypeDef driver_SX1280_set_advanced_ranging_mode(module_wireless_HandleTypeDef *hwirelessmodule, bool enable);

#endif /* SRC_DRIVER_WIRELESS_DRIVER_SX1280_H_ */
