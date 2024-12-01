/**
  ******************************************************************************
  * @file           : driver_NRF24L01.h
  * @brief          : Header for driver_NRF24L01.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-27 gael fargeas created
  *
  *	Documentation:
  * ================================================================
  * https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf
  */

#ifndef SRC_DRIVER_WIRELESS_DRIVER_NRF24L01_H_
#define SRC_DRIVER_WIRELESS_DRIVER_NRF24L01_H_

/* Includes ---------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "WIRELESS/inc_wireless.h"
#include "stdlib.h"
#include "stdbool.h"

/* Defines ----------------------------------------------------------*/
/* NRF24L01 Commands code */
#define NRF24L01_CMD_READ_REGISTER                  0b00000000
#define NRF24L01_CMD_WRITE_REGISTER                 0b00100000
#define NRF24L01_CMD_READ_RX_PAYLOAD                0b01100001
#define NRF24L01_CMD_WRITE_TX_PAYLOAD               0b10100000
#define NRF24L01_CMD_FLUSH_TX                    	0b11100001
#define NRF24L01_CMD_FLUSH_RX                   	0b11100010
#define NRF24L01_CMD_REUSE_TX_PL                	0b11100011
#define NRF24L01_CMD_READ_RX_PL_WID                 0b01100000
#define NRF24L01_CMD_WRITE_ACK_PAYLOAD              0b10101000
#define NRF24L01_CMD_WRITE_TX_PAYLOAD_NOACK         0b10110000
#define NRF24L01_CMD_NOP                         	0b11111111

/* NRF24L01 registers address */
#define NRF24L01_REG_CONFIG            0x00
#define NRF24L01_REG_EN_AA             0x01
#define NRF24L01_REG_EN_RXADDR         0x02
#define NRF24L01_REG_SETUP_AW          0x03
#define NRF24L01_REG_SETUP_RETR        0x04
#define NRF24L01_REG_RF_CH             0x05
#define NRF24L01_REG_RF_SETUP          0x06
#define NRF24L01_REG_STATUS            0x07
#define NRF24L01_REG_OBSERVE_TX        0x08
#define NRF24L01_REG_RPD               0x09
#define NRF24L01_REG_RX_ADDR_P0        0x0A
#define NRF24L01_REG_RX_ADDR_P1        0x0B
#define NRF24L01_REG_RX_ADDR_P2        0x0C
#define NRF24L01_REG_RX_ADDR_P3        0x0D
#define NRF24L01_REG_RX_ADDR_P4        0x0E
#define NRF24L01_REG_RX_ADDR_P5        0x0F
#define NRF24L01_REG_TX_ADDR           0x10
#define NRF24L01_REG_RX_PW_P0          0x11
#define NRF24L01_REG_RX_PW_P1          0x12
#define NRF24L01_REG_RX_PW_P2          0x13
#define NRF24L01_REG_RX_PW_P3          0x14
#define NRF24L01_REG_RX_PW_P4          0x15
#define NRF24L01_REG_RX_PW_P5          0x16
#define NRF24L01_REG_FIFO_STATUS       0x17
#define NRF24L01_REG_DYNPD             0x1C
#define NRF24L01_REG_FEATURE           0x1D

/* Typedef -------------------------------------------------------------*/
typedef enum
{
  RF24L01_TX_MODE 	= 0,
  RF24L01_RX_MODE	= 1
} NRF24L01_MODE_RX_TX;

typedef enum
{
  RF24L01_CRC_1_BYTE 	= 0,
  RF24L01_CRC_2_BYTES	= 1
} NRF24L01_CRC_LENGHT;

typedef enum
{
  RF24L01_AW_3_BYTES 	= 0b01,
  RF24L01_AW_4_BYTES	= 0b10,
  RF24L01_AW_5_BYTES	= 0b11
} NRF24L01_ADDRESS_WIDTH;

typedef enum
{
  RF24L01_RETR_250_μS 	= 0b0000,
  RF24L01_RETR_500_μS 	= 0b0001,
  RF24L01_RETR_750_μS 	= 0b0010,
  RF24L01_RETR_1000_μS 	= 0b0011,
  RF24L01_RETR_1250_μS 	= 0b0100,
  RF24L01_RETR_1500_μS 	= 0b0101,
  RF24L01_RETR_1750_μS 	= 0b0110,
  RF24L01_RETR_2000_μS 	= 0b0111,
  RF24L01_RETR_2250_μS 	= 0b1000,
  RF24L01_RETR_2500_μS 	= 0b1001,
  RF24L01_RETR_2750_μS 	= 0b1010,
  RF24L01_RETR_3000_μS 	= 0b1011,
  RF24L01_RETR_3250_μS 	= 0b1100,
  RF24L01_RETR_3500_μS 	= 0b1101,
  RF24L01_RETR_3750_μS 	= 0b1110,
  RF24L01_RETR_4000_μS 	= 0b1111
} NRF24L01_RETR_DELAY;

typedef enum
{
	  RF24L01_RETR_DISABLE 	= 0b0000,
	  RF24L01_RETR_1 		= 0b0001,
	  RF24L01_RETR_2 		= 0b0010,
	  RF24L01_RETR_3 		= 0b0011,
	  RF24L01_RETR_4 		= 0b0100,
	  RF24L01_RETR_5 		= 0b0101,
	  RF24L01_RETR_6 		= 0b0110,
	  RF24L01_RETR_7 		= 0b0111,
	  RF24L01_RETR_8 		= 0b1000,
	  RF24L01_RETR_9 		= 0b1001,
	  RF24L01_RETR_10 		= 0b1010,
	  RF24L01_RETR_11 		= 0b1011,
	  RF24L01_RETR_12 		= 0b1100,
	  RF24L01_RETR_13 		= 0b1101,
	  RF24L01_RETR_14 		= 0b1110,
	  RF24L01_RETR_15	 	= 0b1111
} NRF24L01_RETR_COUNT;

typedef enum
{
  RF24L01_RF_SETUP_DATA_RATE_1MBPS 		= 0b00,
  RF24L01_RF_SETUP_DATA_RATE_2MBPS		= 0b01,
  RF24L01_RF_SETUP_DATA_RATE_250KBPS	= 0b10
} NRF24L01_RF_SETUP_DATA_RATE;

typedef enum
{
  RF24L01_RF_SETUP_POWER_16DBM 	= 0b00,
  RF24L01_RF_SETUP_POWER_12DBM	= 0b01,
  RF24L01_RF_SETUP_POWER_6DBM	= 0b10,
  RF24L01_RF_SETUP_POWER_0DBM	= 0b11
} NRF24L01_RF_SETUP_POWER;



/* Functions prototypes ---------------------------------------------*/
HAL_StatusTypeDef driver_NRF24L01_cs_high(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_cs_low(module_wireless_HandleTypeDef *hwirelessmodule);

HAL_StatusTypeDef driver_NRF24L01_init(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_MODE_RX_TX mode, uint16_t freq_MHz,
		NRF24L01_RF_SETUP_DATA_RATE data_rate, NRF24L01_RF_SETUP_POWER power, NRF24L01_CRC_LENGHT crc_lenght,
		NRF24L01_ADDRESS_WIDTH adress_widghts, NRF24L01_RETR_COUNT retr_count, NRF24L01_RETR_DELAY retr_delay);

HAL_StatusTypeDef driver_NRF24L01_write_register(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t reg, uint8_t *value, uint8_t value_size);
HAL_StatusTypeDef driver_NRF24L01_read_register(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t reg, uint8_t *data, uint8_t data_size);

HAL_StatusTypeDef driver_NRF24L01_reset(module_wireless_HandleTypeDef *hwirelessmodule);

HAL_StatusTypeDef driver_NRF24L01_flush_rx_fifo(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_flush_tx_fifo(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_power_up(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_power_down(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_set_prx_mode(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_set_ptx_mode(module_wireless_HandleTypeDef *hwirelessmodule);

HAL_StatusTypeDef driver_NRF24L01_read_rx_fifo(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *rx_payload, uint8_t payload_size);
HAL_StatusTypeDef driver_NRF24L01_write_tx_fifo(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *tx_payload, uint8_t payload_size);

HAL_StatusTypeDef driver_NRF24L01_get_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data);
HAL_StatusTypeDef driver_NRF24L01_set_address_widths(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_ADDRESS_WIDTH address_width);
HAL_StatusTypeDef driver_NRF24L01_auto_retransmit(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_DELAY delay, NRF24L01_RETR_COUNT count);
HAL_StatusTypeDef driver_NRF24L01_set_crc_length(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_CRC_LENGHT crc_lenght);

HAL_StatusTypeDef driver_NRF24L01_auto_retransmit(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_DELAY delay, NRF24L01_RETR_COUNT count);
HAL_StatusTypeDef driver_NRF24L01_auto_retransmit_delay(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_DELAY delay);
HAL_StatusTypeDef driver_NRF24L01_auto_retransmit_count(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_COUNT count);

HAL_StatusTypeDef driver_NRF24L01_set_rf_channel(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t freq_MHz);

HAL_StatusTypeDef driver_NRF24L01_set_rf_setup(module_wireless_HandleTypeDef *hwirelessmodule, bool enable, NRF24L01_RF_SETUP_DATA_RATE data_rate, NRF24L01_RF_SETUP_POWER power);
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup_continuous_carrier (module_wireless_HandleTypeDef *hwirelessmodule, bool enable);
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup_air_data_rate(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RF_SETUP_DATA_RATE data_rate);
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup_tx_output_power(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RF_SETUP_POWER power);

HAL_StatusTypeDef driver_NRF24L01_clear_max_rt(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_clear_tx_ds(module_wireless_HandleTypeDef *hwirelessmodule);
HAL_StatusTypeDef driver_NRF24L01_clear_rx_dr(module_wireless_HandleTypeDef *hwirelessmodule);

HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_0_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes);
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_1_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes);
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_2_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes);
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_3_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes);
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_4_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes);
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_5_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes);

HAL_StatusTypeDef driver_NRF24L01_get_fifo_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *status);

HAL_StatusTypeDef driver_NRF24L01_send_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size);
HAL_StatusTypeDef driver_NRF24L01_receice_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size);


#endif /* SRC_DRIVER_WIRELESS_DRIVER_NRF24L01_H_ */
