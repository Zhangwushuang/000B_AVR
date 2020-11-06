#include "in_fan_cf.h"

int8_t In_fan_cf::check_input(unsigned char* buff) {

	return 4;

}

void In_fan_cf::load_confi() {

	this->ht = EEPROM.read(this->begin);
	this->lt = EEPROM.read(this->begin + 1);
	this->hs = EEPROM.read(this->begin + 2);
	this->ls = EEPROM.read(this->begin + 3);

}

uint16_t In_fan_cf::report_config(unsigned char* buff) {

	buff[0] = this->ht;
	buff[1] = this->lt;
	buff[2] = this->hs;
	buff[3] = this->ls;

	return 4;

}

void In_fan_cf::power_out(int8_t temp, uint8_t &now_power) {

	int8_t tp = constrain(temp, min(this->lt, this->ht),max(this->lt, this->ht));
	now_power = map(tp, this->lt, this->ht, this->ls, this->hs);

}

In_fan_cf::In_fan_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

}

In_fan_cf::~In_fan_cf() {


}


