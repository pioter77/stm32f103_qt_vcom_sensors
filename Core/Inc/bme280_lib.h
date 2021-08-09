/*
 * bme280_lib.h
 *
 *  Created on: 2 sie 2021
 *      Author: piotr
 */

#ifndef INC_BME280_LIB_H_
#define INC_BME280_LIB_H_

#include "main.h"
#include "spi.h"
#include <string.h>
typedef uint32_t CS_PIN_NO;

typedef struct T_bme280{
	//raw: binary from sensor before transformations
	uint32_t temp_raw;
	uint32_t humi_raw;
	uint32_t press_raw;

	//digi: digital value (physical) calculated from datasheet formulas (fixed point after multiplication to remove the dot)
	uint16_t temp_digi;
	uint16_t humi_digi;
	uint16_t press_digi;

	uint8_t dev_id;
	_Bool isSleeping;

	uint8_t prec_temp;				//for passing to init struct and controlling commands got from QT master
	uint8_t prec_humi;				//16, 17, 18, 18, 20 bit values can be possible
	uint8_t prec_press;

	t_spi_ctrl *BmeSpiCtrl;
//	SPI_TypeDef *SPI;				//spi instance for the particular sensor
//	GPIO_TypeDef *CS_PORT;			//cs pin port pointer
//	CS_PIN_NO CS_pin;				//pin no
}t_bme280;


extern t_bme280 bme280_2;			//sensor structoure instance 1

//for setting each parameter precision or disable the readout
typedef enum uint8_t{
		BME280_READOUT_DISABLED=0x80,
		BME280_READOUT_16bit=0x1,
		BME280_READOUT_17bit=0x2,
		BME280_READOUT_18bit=0x3,
		BME280_READOUT_19bit=0x4,
		BME280_READOUT_20bit=0x5,

}BME280_PREC;

void bme280_init(t_bme280 *bme,BME280_PREC temp_prec,BME280_PREC humi_prec,BME280_PREC press_prec);
void bme280_enable(t_bme280 *bme);

void bme280_get_id(t_bme280 *bme);

void bme280_set_reg(t_bme280 *bme);
void bme280_get_reg(t_bme280 *bme);

void bme280_get_temp(t_bme280 *bme);
void bme280_get_humi(t_bme280 *bme);
void bme280_get_pres(t_bme280 *bme);
void bme280_get_burst(t_bme280 *bme);

void bme280_reset(t_bme280 *bme);
void bme280_set_sleep(t_bme280 *bme);
void bme280_set_normal(t_bme280 *bme);
void bme280_set_forced(t_bme280 *bme);

#endif /* INC_BME280_LIB_H_ */
