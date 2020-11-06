#include "time_swich_cf.h"

int8_t Time_swich_cf::check_input(unsigned char* buff) {

	if (buff[0] > 23) {

		return -1;

	}

	if (buff[2] > 23) {

		return -1;

	}

	if (buff[1] > 59) {

		return -1;

	}

	if (buff[3] > 59) {

		return -1;

	}

	return 5;

}

void Time_swich_cf::load_confi() {

	this->on_h = min(23, EEPROM.read(this->begin));
	this->on_m = min(59, EEPROM.read(this->begin + 1));
	this->off_h = min(23, EEPROM.read(this->begin + 2));
	this->off_m = min(59, EEPROM.read(this->begin + 3));

	this->max = EEPROM.read(this->begin + 4);

	this->on_sec = time2long(0, this->on_h, this->on_m, 0);
	this->off_sec = time2long(0, this->off_h, this->off_m, 0);

}

uint16_t Time_swich_cf::report_config(unsigned char* buff) {

	buff[0] = this->on_h;
	buff[1] = this->on_m;
	buff[2] = this->off_h;
	buff[3] = this->off_m;

	buff[4] = this->max;

	return 5;

}

void Time_swich_cf::power_out(uint8_t &now_power) {

	if (this->off_sec == this->on_sec) {
	
		now_power = this->max;
		return;
	
	}

	//判断在哪个区间
	if ((this->on_sec <= Clock::now_sec && Clock::now_sec < this->off_sec) //(开 现 关)
		||(this->off_sec < this->on_sec && this->on_sec <= Clock::now_sec) //(关 开 现)
		||(Clock::now_sec < this->off_sec && this->off_sec < this->on_sec)) {//(现 关 开)
	
		now_power = this->max;
		return;

	}

	now_power = 0;

}

Time_swich_cf::Time_swich_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

}

Time_swich_cf::~Time_swich_cf() {


}


