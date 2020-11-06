#include "spray_cf.h"

int8_t Spray_cf::check_input(unsigned char* buff)
{

	return 6;

}

void Spray_cf::load_confi()//读取设置
{

	int i = 0;

	for (i = 0; i < 4; ++i)
	{

		((unsigned char*)&(this->spray_space))[i] = EEPROM.read(i + this->begin);

	}

	for (i = 0; i < 2; ++i)
	{

		((unsigned char*)&(this->spray_last))[i] = EEPROM.read(i + this->begin + 4);

	}

}

uint16_t Spray_cf::report_config(unsigned char* buff) {

	*((uint32_t*)buff) = this->spray_space;
	*((uint16_t*)(buff + 4)) = this->spray_last;

	return 6;

}

void Spray_cf::power_out(uint32_t last_spray_time, bool &now_power) {

	if (this->spray_last == 0) {

		now_power = false;
		return;
	
	}

	if (last_spray_time >= this->spray_space || last_spray_time < this->spray_last) {

		now_power = true;
	
	}
	else {
	
		now_power = false;

	}

}

Spray_cf::Spray_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

}

Spray_cf::~Spray_cf()
{
}


