#include "in_fan_ac.h"

void In_fan_ac::adjust_power(int8_t temp_ctrl) {

	if (temp_ctrl != 0) { //如果正在温控状态
	
		this->power = 0xFF;

	}

}

uint16_t In_fan_ac::report_state(unsigned char* buff) {

	buff[0] = this->power;
	return 1;

}

void In_fan_ac::exce() {

	uint8_t out = 0;

	if (this->power != 0) {
	
		out = map(this->power, 0, 255, 63, 255);
	
	}

	analogWrite(IN_FAN_CP, out);

}

In_fan_ac::In_fan_ac() {

	//TCCR1B = TCCR1B & B11111000 | B00000001; //风扇 pwm 31372.55 Hz

	this->power = 0;

	pinMode(IN_FAN_CP,OUTPUT);
	digitalWrite(IN_FAN_CP,LOW);

}

In_fan_ac::~In_fan_ac() {


}


