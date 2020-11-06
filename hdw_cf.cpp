#include "hdw_cf.h"

int8_t Hdw_cf::check_input(unsigned char* buff)
{

	if (buff[0] > 2) {
	
		return -1;
	
	}

	if (buff[1] > 4) {

		return -1;

	}

	if (buff[4] > 4) {

		return -1;

	}

	return 7;

}

void Hdw_cf::load_confi()//读取设置
{

	this->lt_type = EEPROM.read(this->begin);//灯光类型

	this->ar_con = EEPROM.read(this->begin + 1);//空调类型

	int i = 0;

	for (i = 0; i < 2; ++i)
	{

		((unsigned char*)&(this->ar_p_t))[i] = EEPROM.read(i + this->begin + 2);

	}

	this->wt_con = EEPROM.read(this->begin + 4);//水温调节器类型

	for (i = 0; i < 2; ++i)
	{

		((unsigned char*)&(this->wt_p_t))[i] = EEPROM.read(i + this->begin + 5);

	}

}

uint16_t Hdw_cf::report_config(unsigned char* buff) {

	buff[0] = this->lt_type;
	buff[1] = this->ar_con;

	*((uint16_t*)(buff + 2)) = this->ar_p_t;

	buff[4] = this->wt_con;

	*((uint16_t*)(buff + 5)) = this->wt_p_t;

	return 7;

}

Hdw_cf::Hdw_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

	this->load_confi();

}

Hdw_cf::~Hdw_cf() {


}


