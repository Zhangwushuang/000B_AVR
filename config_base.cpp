#include "config_base.h"

bool Config_base::save_confi(unsigned char* buff)
{

	int8_t len = this->check_input(buff);//获取真实长度

	if (len < 0)
	{

		return false;

	}

	for (int i = 0; i < len; ++i)
	{

		EEPROM.write(i + this->begin, buff[i]);

	}

	return true;

}

int8_t Config_base::check_input(unsigned char* buff)
{

	return 0;

}

Config_base::Config_base(uint8_t cmd_code) :begin(uint16_t(cmd_code + 1) * CMD_LEN)
{

}

Config_base::~Config_base()
{
}



