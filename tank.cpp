#include "tank.h"

void Tank::get_date() {

	this->alt = false;

	if (digitalRead(lp) == LOW) { //未达低水位
	
		this->alt = true;//警告为true
		this->need_add = true;//报需要加水
	
	}

	if ((digitalRead(hp) == HIGH)) { //达到了高水位
	
		this->need_add = false;//报无需加水
	
	}
}

uint16_t Tank::report_date(unsigned char* buff) {

	if (this->alt) {
	
		buff[0] = buff[0] + this->alt_code;
	
	}

	return 0;

}

Tank::Tank(uint8_t code, uint8_t h_pin, uint8_t l_pin) :alt_code(code),hp(h_pin),lp(l_pin)
{

	//设为输入并内部上拉
	pinMode(h_pin, INPUT_PULLUP);
	pinMode(l_pin, INPUT_PULLUP);

}

Tank::~Tank() {


}


