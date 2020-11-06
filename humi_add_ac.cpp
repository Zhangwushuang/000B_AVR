#include "humi_add_ac.h"

void Humi_add_ac::adjust_power_lv(bool lv_alt) {

	if (lv_alt) {//有水位警告，只能关闭加湿。
	
		this->hu_ct = 0;

	}

}

void Humi_add_ac::adjust_power(bool lv_alt,int8_t &is_heat) {

	//有警告
	if (lv_alt) { //不加热，不加湿

		this->hu_ct = 0;

		if (is_heat > 0) {
		
			is_heat = 0;
		
		}

		return;

	}

	//无警告
	if (is_heat > 0) {//加热加湿

		this->hu_ct = 127;
		return;

	}

	//不加热，随意

}

uint16_t Humi_add_ac::report_state(unsigned char* buff) {

	buff[0] = this->hu_ct;
	return 1;

}

void Humi_add_ac::exce() {

	if (this->hu_ct > 0) {//如需要加湿

		digitalWrite(HU_ADD_PIN, HIGH);

	}
	else
	{

		digitalWrite(HU_ADD_PIN, LOW);

	}

}

Humi_add_ac::Humi_add_ac() {

	this->hu_ct = 0;
	pinMode(HU_ADD_PIN, OUTPUT);
	digitalWrite(HU_ADD_PIN, LOW);

}

Humi_add_ac::~Humi_add_ac() {


}

