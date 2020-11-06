#include "sht_cf.h"

int8_t Sht_cf::check_input(unsigned char* buff)
{

	if (buff[0] > 2) {

		return -1;

	}

	return 5;

}

void Sht_cf::load_confi()
{

	this->mode = EEPROM.read(this->begin);//拍摄类型

	if (this->mode > 2) {
	
		this->mode = 1;//默认为开灯时拍摄
	
	}

	int i = 0;

	for (i = 0; i < 4; ++i)
	{

		((unsigned char*)&(this->space))[i] = EEPROM.read(i + this->begin + 1);

	}

}

uint16_t Sht_cf::report_config(unsigned char* buff) {

	buff[0] = this->mode;
	*((uint32_t*)(buff+1)) = this->space;
	return 5;

}

Sht_cf::Sht_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

}

Sht_cf::~Sht_cf()
{

}