#include "spray_ac.h"

uint32_t Spray_ac::get_sp_dist() {

	if (Clock::timestamp_2000 < this->last_sp_time || this->last_sp_time == 0) {
	
		this->last_sp_time = Clock::timestamp_2000;

	}
	
	this->sp_distance = Clock::timestamp_2000 - (this->last_sp_time);
	
	return this->sp_distance;

}

uint16_t Spray_ac::report_state(unsigned char* buff) {

	if (this->need_in) {
	
		buff[0] = Configs::add_wt->max;

	}
	else {
	
		buff[0] = 0;
	
	}

	*((uint32_t*)(buff + 1)) = this->sp_distance;

	return 5;

}

void Spray_ac::exce() {

	if (this->mn_lv_alert) {//如果主水箱水位不足

		this->close_all();//关闭所有
		this->spraying = false;
		return;

	}

	if (this->need_sp) { //喷淋最优先

		if (!(this->spraying)) { //如果此时不在喷淋要打开喷淋
			
			this->last_sp_time = Clock::timestamp_2000;
			this->sp_distance = 0;//为了发送报告时方便

		}

		this->open_spray();
		return;

	}
	else 
	{
	
		this->spraying = false;
	
	}

	if (this->need_hu) { //加湿器第二

		this->open_humi();
		return;

	}

	if (this->need_in) { //缸体内部加水第三

		this->open_in();
		return;

	}

	this->close_all();//关闭所有

}

void Spray_ac::close_all() {

	digitalWrite(SP_PUMP_PIN, LOW);

	digitalWrite(SP_TAP_PIN, LOW);
	digitalWrite(HU_TAP_PIN, LOW);
	digitalWrite(IN_TAP_PIN, LOW);

	this->spraying = false;
}

void Spray_ac::open_spray() {

	digitalWrite(SP_TAP_PIN, HIGH);
	digitalWrite(HU_TAP_PIN, LOW);
	digitalWrite(IN_TAP_PIN, LOW);

	digitalWrite(SP_PUMP_PIN, HIGH);
	this->spraying = true;
}

void Spray_ac::open_in() {

	digitalWrite(IN_TAP_PIN, HIGH);
	digitalWrite(SP_TAP_PIN, LOW);
	digitalWrite(HU_TAP_PIN, LOW);

	digitalWrite(SP_PUMP_PIN, HIGH);
	this->spraying = false;
}

void Spray_ac::open_humi() {

	digitalWrite(HU_TAP_PIN, HIGH);
	digitalWrite(SP_TAP_PIN, LOW);
	digitalWrite(IN_TAP_PIN, LOW);

	digitalWrite(SP_PUMP_PIN, HIGH);
	this->spraying = false;
}

Spray_ac::Spray_ac() 
{

	pinMode(SP_PUMP_PIN, OUTPUT);
	pinMode(IN_TAP_PIN, OUTPUT);
	pinMode(SP_TAP_PIN, OUTPUT);
	pinMode(HU_TAP_PIN, OUTPUT);

	this->close_all();//关闭所有

	this->last_sp_time = 0;//将间隔设置为最大,那么开机就会立刻喷淋

}

Spray_ac::~Spray_ac() {

}


