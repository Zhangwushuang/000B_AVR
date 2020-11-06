#include "light_ac.h"

uint16_t Light_ac::report_state(unsigned char* buff) {

	buff[0] = this->power;
	buff[1] = this->mode;

	return 2;

}

void Light_ac::exce() {

	if (0 == this->power) {
	
		this->off();
	
	}
	else {

		this->on();
	
	}

}

void Light_ac::off() {

	digitalWrite(LT_PWM_PIN, LOW);
	digitalWrite(LT_EN_PIN, LOW);
	digitalWrite(LT_MODE_PIN, LOW);

}

void Light_ac::on() {

	digitalWrite(LT_EN_PIN, HIGH); //打开模块及散热器

	if (this->mode) {
	
		digitalWrite(LT_MODE_PIN, HIGH);

	}
	else {
	
		digitalWrite(LT_MODE_PIN, LOW);

	}

	analogWrite(LT_PWM_PIN,(0xFF - this->power));

}

Light_ac::Light_ac(uint8_t ac_tp) :type(ac_tp)
{

	//TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
	//TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
	//TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
	//TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
	//TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
	//TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
	//TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

	pinMode(LT_PWM_PIN,OUTPUT);
	pinMode(LT_EN_PIN, OUTPUT);
	pinMode(LT_MODE_PIN, OUTPUT);

	this->power = 0;

	this->off();

}

Light_ac::~Light_ac() {



}


