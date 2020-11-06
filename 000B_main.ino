#include "cmd.h"

void setup()   
{

	Serial.begin(19200);//调试口
	Serial1.begin(19200);//云服务器
	Serial2.begin(19200);//内网

	TCCR1B = TCCR1B & B11111000 | B00000100;  // set timer 1 divisor to   256 for PWM frequency of   122.55 Hz ping 11,12 灯光
	TCCR2B = TCCR2B & B11111000 | B00000001; //风扇 pwm 31372.55 Hz pin 9.10

	Clock::begin();
	Configs::load_all_config();
	Snors::wt_tp->set_snor_Res();

	pinMode(TEC_PUMP, OUTPUT);

	delay(2000);

}

void loop()
{

	Clock::get_time();//读取时间
	Ctrlor::adjust_lt();//调节灯光

	if (!Clock::pass_flag) {

		return;

	}

	//读取温湿度
	if (Clock::rpt_flag) {

		Snors::load_date_report();

	}

	//读取水箱状态
	Snors::load_date_loop();

	Ctrlor::adjust_all();

	Ab_time::get_ab_time();

	if (Clock::rpt_flag) {

		Cmd::snd_rpt(&Serial1, false);//发送报告到云

	}

}

void serialEvent() {

	if (Cmd::rec_cmd(&Serial)) {

		Cmd::exec_cmd(true);
		Ab_time::get_ab_time();
		Cmd::snd_rpt(&Serial);//发送报告

	}

}

void serialEvent1() {

	if(Cmd::rec_cmd(&Serial1)){

		Cmd::exec_cmd();
		Ab_time::get_ab_time();
		Cmd::snd_rpt(&Serial1);

	}//发送报告
	
}

void serialEvent2() {

	if (Cmd::rec_cmd(&Serial2)) {
	
		Cmd::exec_cmd();
		Ab_time::get_ab_time();
		Cmd::snd_rpt(&Serial2);//发送报告
	
	}

}