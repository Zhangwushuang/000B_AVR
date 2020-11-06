#include "cmd.h"

void setup()   
{

	Serial.begin(19200);//���Կ�
	Serial1.begin(19200);//�Ʒ�����
	Serial2.begin(19200);//����

	TCCR1B = TCCR1B & B11111000 | B00000100;  // set timer 1 divisor to   256 for PWM frequency of   122.55 Hz ping 11,12 �ƹ�
	TCCR2B = TCCR2B & B11111000 | B00000001; //���� pwm 31372.55 Hz pin 9.10

	Clock::begin();
	Configs::load_all_config();
	Snors::wt_tp->set_snor_Res();

	pinMode(TEC_PUMP, OUTPUT);

	delay(2000);

}

void loop()
{

	Clock::get_time();//��ȡʱ��
	Ctrlor::adjust_lt();//���ڵƹ�

	if (!Clock::pass_flag) {

		return;

	}

	//��ȡ��ʪ��
	if (Clock::rpt_flag) {

		Snors::load_date_report();

	}

	//��ȡˮ��״̬
	Snors::load_date_loop();

	Ctrlor::adjust_all();

	Ab_time::get_ab_time();

	if (Clock::rpt_flag) {

		Cmd::snd_rpt(&Serial1, false);//���ͱ��浽��

	}

}

void serialEvent() {

	if (Cmd::rec_cmd(&Serial)) {

		Cmd::exec_cmd(true);
		Ab_time::get_ab_time();
		Cmd::snd_rpt(&Serial);//���ͱ���

	}

}

void serialEvent1() {

	if(Cmd::rec_cmd(&Serial1)){

		Cmd::exec_cmd();
		Ab_time::get_ab_time();
		Cmd::snd_rpt(&Serial1);

	}//���ͱ���
	
}

void serialEvent2() {

	if (Cmd::rec_cmd(&Serial2)) {
	
		Cmd::exec_cmd();
		Ab_time::get_ab_time();
		Cmd::snd_rpt(&Serial2);//���ͱ���
	
	}

}