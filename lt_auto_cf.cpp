#include "lt_auto_cf.h"

int8_t Lt_auto_cf::check_input(unsigned char* buff) {

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

	return 14;

}

void Lt_auto_cf::load_confi() {

	this->on_h = min(23,EEPROM.read(this->begin));
	this->on_m = min(59, EEPROM.read(this->begin + 1));
	this->off_h = min(23, EEPROM.read(this->begin + 2));
	this->off_m = min(59, EEPROM.read(this->begin + 3));

	int i = 0;

	for (i = 0; i < 4; ++i)
	{

		((unsigned char*)&(this->on_delay))[i] = EEPROM.read(i + this->begin + 4);

	}

	for (i = 0; i < 4; ++i)
	{

		((unsigned char*)&(this->off_delay))[i] = EEPROM.read(i + this->begin + 8);

	}

	this->max = EEPROM.read(this->begin + 12);//鑷姩妯″紡鏈�澶у��
	this->mode = EEPROM.read(this->begin + 13);//0涓虹櫧鐏紝1涓鸿壊鐏�

	this->on_ms = 1000 * (time2long(0, this->on_h, this->on_m, 0));
	this->off_ms = 1000 * (time2long(0, this->off_h, this->off_m, 0));

}

uint16_t Lt_auto_cf::report_config(unsigned char* buff) {

	buff[0] = this->on_h;
	buff[1] = this->on_m;
	buff[2] = this->off_h;
	buff[3] = this->off_m;

	*((uint32_t*)(buff + 4)) = this->on_delay;
	*((uint32_t*)(buff + 8)) = this->off_delay;

	buff[12] = this->max;
	buff[13] = this->mode;

	return 14;

}

void Lt_auto_cf::power_out(uint8_t &now_power, uint8_t &now_mode) {

	//妯″紡鐩存帴杈撳嚭
	now_mode = this->mode;

	if (this->on_ms == this->off_ms) {
	
		now_power = this->max;
		return;
	
	}

	//璁＄畻褰撳墠鍦ㄤ竴澶╀腑鐨勬绉掓暟
	uint32_t now_ms = Clock::now_sec * 1000 + Clock::now_ms;

	//鍒ゆ柇鐜板湪鐨勬椂闂磋惤鍦ㄥ摢涓尯闂�
	if ((this->on_ms < now_ms && now_ms < this->off_ms) || (this->off_ms < this->on_ms && this->on_ms <= now_ms)) {//(寮� 鐜� 鍏�)||(鍏� 寮� 鐜�) - 寮�
	
		now_power = this->on_power(now_ms - this->on_ms);
		return;

	}
	else if ( now_ms <= this->off_ms && this->off_ms < this->on_ms) { //(鐜� 鍏� 寮�) - 寮�

		now_power = this->on_power(86400000 - this->on_ms + now_ms);
		return;
	
	}
	else if ((this->off_ms < now_ms && now_ms < this->on_ms)||(this->on_ms < this->off_ms && this->off_ms <= now_ms)) { //(鍏� 鐜� 寮�)||(寮� 鍏� 鐜�) - 鍏�
	
		now_power = this->off_power(now_ms - this->off_ms);
		return;

	}
	else if (now_ms <= this->on_ms && this->on_ms < this->off_ms) {//(鐜� 寮� 鍏�) - 鍏�
	
		now_power = this->off_power(86400000 - this->off_ms + now_ms);
		return;
	
	}

}

uint8_t Lt_auto_cf::on_power(uint32_t oned_ms) {

	uint64_t delay_ms = 1000LL * this->on_delay;//寤惰繜姣鏁�

	if (oned_ms >= delay_ms) {
	
		return this->max;
	
	}

	//nowPow = oned * max / delay(ms)
	return (uint8_t)(((uint64_t)oned_ms) * this->max / delay_ms);

}

uint8_t Lt_auto_cf::off_power(uint32_t offed_ms) {

	uint64_t delay_ms = 1000LL * this->off_delay;//寤惰繜姣鏁�

	if (offed_ms >= delay_ms) {

		return 0;//姝ゆ椂瀹屽叏鍏抽棴

	}

	//璺濈瀹屽叏鍏抽棴鐨勬绉掓暟
	uint64_t to_off_ms = delay_ms - offed_ms;

	// nowpow = to_off_ms * max/delay_ms
	//姝ゅ鐢变簬 delay_ms 鏈�澶т负 1000鍊�  uint32 ,鎵�浠ュ啀涔樹互涓�涓� uint8 鏈�澶т篃浠呬负 鈥�3E417FFFC1BE8鈥� 涓嶄細婧㈠嚭
	return (uint8_t)(to_off_ms * this->max / delay_ms);

}

Lt_auto_cf::Lt_auto_cf(uint8_t cmd_code):Config_base(cmd_code)
{


}

Lt_auto_cf::~Lt_auto_cf() {



}


