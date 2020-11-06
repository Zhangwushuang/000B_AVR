#include "temp_ac.h"

void compressor::get_dl_sta() {

	if (this->is_on) {
	
		this->is_dl = false;
		return;

	}

	//只有关转开的时候执行下面
	if (millis() < this->off_ms) {

		this->off_ms = millis();

	}

	if ((millis() - this->off_ms) < this->delay_ms) {

		this->is_dl = true;

	}
	else {

		this->is_dl = false;

	}

}

bool compressor::turn_on() {

	this->get_dl_sta();

	if (!this->is_dl) {
	
		this->is_on = true;
		digitalWrite(this->pin, HIGH);
		return true;
	
	}

	digitalWrite(this->pin, LOW);
	return false;
}

bool compressor::turn_off() {

	if (this->is_on) {
	
		this->off_ms = millis();
		this->is_on = false;
	
	}

	digitalWrite(this->pin, LOW);
	return true;
}

compressor::compressor(uint8_t cp, uint16_t delay):pin(cp), delay_ms(delay * 1000L)
{

	pinMode(cp,OUTPUT);
	digitalWrite(cp,LOW);

	this->is_on = false;//压缩机是否开机
	this->off_ms = 0;//压缩机关闭的millis
	this->is_dl = false;//是否处于延时保护状态

}

compressor::~compressor() {


}


//////////////////////////////////////////////////

void Temp_ac::exce() {

	if (this->power > 0) {
	
		this->heat();
		return;

	}

	if (this->power < 0) {

		this->cool();
		return;

	}

	this->stop();

}

void Temp_ac::type_ad() {

	if (this->type == COOL_ONLY && this->power > 0) {//单冷但需要加热

		this->power = 0;
		return;
	
	}

	if (this->type == HEAT_ONLY && this->power < 0) {//单热但需要制冷

		this->power = 0;
		return;

	}


}

//加热(动作根据类型选择)
void Temp_ac::heat(){

	if (this->type == CMP_TAP) { //如果是四通阀加热型
	
		if (this->cp->turn_on()) { //打开压缩机成功
		
			digitalWrite(this->hp, HIGH);//打开四通阀

		}
		else {
		
			digitalWrite(this->hp, LOW);//关闭四通阀
			this->power = 0; //将加热回归为0

		}

		return;

	}

	//关闭压缩机,打开加热器
	this->cp->turn_off();
	digitalWrite(this->hp, HIGH);

}

void Temp_ac::cool() {//制冷(制冷时动作是一样的)

	digitalWrite(this->hp, LOW);//关闭加热器

	if (!(this->cp->turn_on())) { //打开压缩机不成功

		this->power = 0; //将出力回归为0

	}

}

void Temp_ac::stop() {//停止

	this->cp->turn_off();
	digitalWrite(this->hp, LOW);

}

Temp_ac::Temp_ac(uint8_t c_pin, uint8_t h_pin, uint8_t tp, uint16_t dl, uint8_t dl_code):
	cp(new compressor(c_pin, dl)),hp(h_pin),type(tp),dl_alt_code(dl_code)
{

	this->power = 0;
	pinMode(h_pin, OUTPUT);
	digitalWrite(h_pin,LOW);

}

Temp_ac::~Temp_ac() {

	delete this->cp;

}

