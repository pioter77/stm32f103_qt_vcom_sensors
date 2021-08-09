/*
 * bme280_lib.c
 *
 *  Created on: 2 sie 2021
 *      Author: piotr
 */

#include "bme280_lib.h"

t_bme280 bme280_2={
		.prec_temp=20,
		.prec_humi=20,
		.prec_press=20,

//		.SPI=SPI2,
//		.CS_PORT=MYSPI_CS_GPIO_Port,
//		.CS_pin=MYSPI_CS_Pin,

		.temp_digi=0,
		.humi_digi=0,
		.press_digi=0,

		.temp_raw=0,
		.humi_raw=0,
		.press_raw=0,
		.BmeSpiCtrl=&spi2
};

void bme280_init(t_bme280 *bme,BME280_PREC temp_prec,BME280_PREC humi_prec,BME280_PREC press_prec){
	spi_half_init(bme->BmeSpiCtrl);
//	while(spi2.is_receive_complete==0);	//wait for finishing
	uint8_t tmp_buf[2]={0,0};
	tmp_buf[0]=0xF2 & 0x7F;		//humi precison addr write
	tmp_buf[1]=0x02;			//gumi precicion 010 -> 17 bit
	memcpy(bme->BmeSpiCtrl->txBuff,tmp_buf,2);
	spi_half_send(bme->BmeSpiCtrl, bme->BmeSpiCtrl->txBuff,2);
	while(bme->BmeSpiCtrl->is_receive_complete==0);	//wait for finishing

	tmp_buf[0]=0xF4 & 0x7F;		//tmep prec, wakup , press precison addr write
	tmp_buf[1]=0x4B;			// todo: create macors or funcition for decding values and shifring bits
	memcpy(bme->BmeSpiCtrl->txBuff,tmp_buf,2);
	spi_half_send(bme->BmeSpiCtrl, bme->BmeSpiCtrl->txBuff,2);
}
void bme280_enable(t_bme280 *bme){

}

void bme280_get_id(t_bme280 *bme){

}

void bme280_set_reg(t_bme280 *bme){

}
void bme280_get_reg(t_bme280 *bme){

}

void bme280_get_temp(t_bme280 *bme){

}

void bme280_get_humi(t_bme280 *bme){

}

void bme280_get_pres(t_bme280 *bme){

}

void bme280_get_burst(t_bme280 *bme){
	const uint8_t temp_buf[11]={0xF7,0,0,0,0,0,0,0,0,0,0};
	while(bme->BmeSpiCtrl->is_receive_complete==0);
	memcpy(bme->BmeSpiCtrl->txBuff,temp_buf,10);
	bme->BmeSpiCtrl->is_answer_allowed=1;
	spi_half_send_n_receive(bme->BmeSpiCtrl, bme->BmeSpiCtrl->txBuff, 10, bme->BmeSpiCtrl->rxBuff, 10);
}

void bme280_reset(t_bme280 *bme){

}

void bme280_set_sleep(t_bme280 *bme){

}

void bme280_set_normal(t_bme280 *bme){

}

void bme280_set_forced(t_bme280 *bme){

}
