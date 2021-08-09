/*
 * bme280_lib.h
 *
 *  Created on: 2 sie 2021
 *      Author: piotr
 */

#ifndef INC_BME280_LIB_H_
#define INC_BME280_LIB_H_

#include "main.h"

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

	SPI_TypeDef *SPI;				//spi instance for the particular sensor
	GPIO_TypeDef *CS_PORT;			//cs pin port pointer
	CS_PIN_NO CS_pin;				//pin no
}t_bme280;


extern t_bme280 bme280_1;			//sensor structoure instance 1

void bme280_init();
void bme280_enable();

void bme280_get_id();

void bme280_set_reg();
void bme280_get_reg();

void bme280_get_temp();
void bme280_get_humi();
void bme280_get_pres();
void bme280_get_burst();

void bme280_reset();
void bme280_set_sleep();
void bme280_set_normal();
void bme280_set_forced();

#endif /* INC_BME280_LIB_H_ */
