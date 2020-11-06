#include "humi_cf.h"

int8_t Humi_cf::check_input(unsigned char* buff) {

	if (buff[0] > 100 || buff[0] < max(buff[1], buff[2])) {

		return -1;

	}

	if (buff[3] > min(buff[1], buff[2])) {

		return -1;

	}

	return 5;

}

void Humi_cf::load_confi() {

	this->hh  = constrain( EEPROM.read(this->begin), 0 ,100 );
	this->rsh = constrain( EEPROM.read(this->begin + 1), 0, 100 );
	this->ash = constrain( EEPROM.read(this->begin + 2), 0, 100 );
	this->lh  = constrain( EEPROM.read(this->begin + 3), 0, 100 );

	if (this->hh < max(this->rsh, this->ash)) {

		this->hh = max(this->rsh, this->ash);

	}

	if (this->lh > min(this->rsh, this->ash)) {

		this->lh = min(this->rsh, this->ash);

	}

	uint8_t temp = EEPROM.read(this->begin + 4);
	this->ig = !!temp;

}

uint16_t Humi_cf::report_config(unsigned char* buff) {

	buff[0] = this->hh;
	buff[1] = this->rsh;
	buff[2] = this->ash;
	buff[3] = this->lh;

	if (this->ig) {
	
		buff[40] = buff[40] + 4;
	}

	return 4;
}

void Humi_cf::power_out(uint8_t humi, int8_t &now_power, bool &alert) {

	alert = false;

	if (this->ig) {

		now_power = 0;
		return;

	}

	if (humi >= this->hh) {

		now_power = -127;
		alert = true;

	}

	if (now_power < 0 && humi <= this->rsh) {

		now_power = 0;

	}

	if (humi <= this->lh) {

		now_power = 127;
		alert = true;

	}

	if (now_power > 0 && humi >= this->ash) {

		now_power = 0;

	}

}

Humi_cf::Humi_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

}

Humi_cf::~Humi_cf() {


}


