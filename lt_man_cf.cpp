#include "lt_man_cf.h"

bool Lt_man_cf::power_out(uint8_t &now_power, uint8_t &now_mode, bool imme) {

	if (this->lt_tp > Clock::timestamp_2000) { //如果是拍摄临时开灯
	
		now_power = 0xFF;
		now_mode = 0;
		return true;

	}

	if (this->get_time_left(imme) == 0) {
	
		return false;
	
	}

	now_power = this->max;
	now_mode = this->mode;
	return true;

}

int8_t Lt_man_cf::check_input(unsigned char* buff) {

	*((uint32_t*)buff) = (*((uint32_t*)buff)) + Clock::timestamp_2000;
	return 6;

}

void Lt_man_cf::load_confi() {

	int i = 0;

	for (i = 0; i < 4; ++i)
	{

		((unsigned char*)&(this->tar_stamp))[i] = EEPROM.read(i + this->begin);

	}

	this->max = EEPROM.read(this->begin + 4);
	this->mode = EEPROM.read(this->begin + 5);

}

uint16_t Lt_man_cf::report_config(unsigned char* buff) {

	*((uint32_t*)buff) = this->time_left;

	buff[4] = this->max;
	buff[5] = this->mode;

	return 6;

}

uint32_t Lt_man_cf::get_time_left(bool imme) {

	if (!Clock::pass_flag && !imme) {//如果既没有flag也无需马上计算
	
		return this->time_left;
	
	}

	if (this->tar_stamp <= Clock::timestamp_2000) { //如果已经过期
	
		this->time_left = 0; //剩余时间为0,转入自动模式
		return this->time_left;

	}

	this->time_left = this->tar_stamp - Clock::timestamp_2000;//计算剩余时间
	return this->time_left;

}

void Lt_man_cf::set_shoot_tp(unsigned char* buff) {

	this->lt_tp = Clock::timestamp_2000 + (uint8_t)buff[0];

}

Lt_man_cf::Lt_man_cf(uint8_t cmd_code) :Config_base(cmd_code)
{

	this->lt_tp = 0;

}

Lt_man_cf::~Lt_man_cf() {

}


