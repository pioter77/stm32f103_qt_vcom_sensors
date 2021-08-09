/*
 * bme280_lib.c
 *
 *  Created on: 2 sie 2021
 *      Author: piotr
 */

#include "bme280_lib.h"

t_bme280 bme280_1={
		.prec_temp=20,
		.prec_humi=20,
		.prec_press=20,

		.SPI=SPI2,
		.CS_PORT=MYSPI_CS_GPIO_Port,
		.CS_pin=MYSPI_CS_Pin,

		.temp_digi=0,
		.humi_digi=0,
		.press_digi=0,

		.temp_raw=0,
		.humi_raw=0,
		.press_raw=0,
};

void bme280_init(){

}
void bme280_enable(){

}

void bme280_get_id(){

}

void bme280_set_reg(){

}
void bme280_get_reg(){

}

void bme280_get_temp(){

}

void bme280_get_humi(){

}

void bme280_get_pres(){

}

void bme280_get_burst(){

}

void bme280_reset(){

}

void bme280_set_sleep(){

}

void bme280_set_normal(){

}

void bme280_set_forced(){

}
