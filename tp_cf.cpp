#include "tp_cf.h"

int8_t Tp_cf::check_input(unsigned char* buff) {

	int8_t t_ht = buff[0];//设定最高温度（制冷开启温度）
	int8_t t_cst = buff[1];//制冷停止温度
	int8_t t_hst = buff[2];//加温停止温度
	int8_t t_lt = buff[3];//设定最低温度（加温开启温度）

	if (t_ht < max(t_cst, t_hst)) {
	
		return -1;

	}

	if (t_lt > min(t_cst ,t_hst)) {

		return -1;

	}

	return 5;

}

void Tp_cf::load_confi() {

	this->ht = EEPROM.read(this->begin);
	this->cst = EEPROM.read(this->begin + 1);
	this->hst = EEPROM.read(this->begin + 2);
	this->lt = EEPROM.read(this->begin + 3);
	
	uint8_t temp = EEPROM.read(this->begin + 4);
	this->ig = !!temp;
	

	if (this->ht < max(this->cst, this->hst)) {

		this->ht = max(this->cst, this->hst);

	}

	if (this->lt > min(this->cst, this->hst)) {

		this->lt = min(this->cst, this->hst);

	}

}

uint16_t Tp_cf::report_config(unsigned char* buff) {

	buff[0] = this->ht;
	buff[1] = this->cst;
	buff[2] = this->hst;
	buff[3] = this->lt;

	return 4;

}

void Tp_cf::power_out(int8_t temp, int8_t &now_power, bool &alert) {

	alert = false;

	if (this->ig) {

		now_power = 0;
		return;

	}

	if (temp >= this->ht) {
	
		now_power = -127;
		alert = true;
		return;

	}

	if (now_power < 0 && temp <= this->cst) {
	
		now_power = 0;
		return;

	}

	if (temp <= this->lt) {

		now_power = 127;
		alert = true;
		return;

	}

	if (now_power > 0 && temp >= this->hst) {

		now_power = 0;
		return;

	}

}

void Tp_cf::rpt_ig(unsigned char* buff, uint8_t mask) {

	if (this->ig) {
	
		buff[0] = buff[0] + mask;
	
	}

}

Tp_cf::Tp_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

}

Tp_cf::~Tp_cf() {


}




