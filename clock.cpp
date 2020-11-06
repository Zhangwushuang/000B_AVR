#include "clock.h"

int64_DS3231* const Clock::rtc(new int64_DS3231());
DateTime* const Clock::now_data(new DateTime());

uint32_t Clock::now_sec = 0;
uint16_t Clock::now_ms = 0;
int64_t Clock::timestamp_2000 = 0;

uint32_t Clock::int_millis = 0;

volatile bool Clock::flag = true;//中断时设置为true,读取RTC并将ms归0后设置回false
bool Clock::rpt_flag = true;
bool Clock::pass_flag = true;

int64_t Clock::rpt_send_time = 0;

void Clock::begin() {

	Clock::rtc->begin(); //启动rtc(wire.begin已经包含在内)

	Clock::rtc->convertTemperature();//开启温度测试

	attachInterrupt( 0, Clock::set_flag, FALLING ); //设置单片机中断
	Clock::rtc->enableInterrupts(EverySecond);//开启rtc中断

}

void Clock::get_time() {//检查中断flag,若true从rtc读取时间,毫秒归0,设置flag为false,记录中断时的 millis值,计算时间戳,清除中断标记

	Clock::rpt_flag = false;
	Clock::pass_flag = false;

	if (Clock::flag) { //如果刚刚中断
	
		Clock::int_millis = millis();//记录中断时的毫秒数
		Clock::now_ms = 0;//毫秒数归0

		Clock::rtc->now(Clock::now_data); //读取时间 y m d ,h m s
		Clock::now_sec = time2long(0, Clock::now_data->hh, Clock::now_data->mm, Clock::now_data->ss);//计算今天的秒数
		Clock::timestamp_2000 = Clock::now_data->get();//计算时间戳(自2000-1-1)

		Clock::pass_flag = true;//设置pass标记为true

		int64_t rpt_distance = Clock::timestamp_2000 - Clock::rpt_send_time;

		if (rpt_distance >= RPT_SEND_SPACE || rpt_distance < 0)
		{

			Clock::rpt_send_time = Clock::timestamp_2000;//记录本次报告发送时间
			Clock::rpt_flag = true;//设置标记为true

		}

		Clock::flag = false;//设置中断flag
		Clock::rtc->clearINTStatus();//清除标记

	}else{
	
		uint32_t ms = millis();

		if (ms > Clock::int_millis) {

			//当前的毫秒数减去中断时毫秒数
			Clock::now_ms = ms - Clock::int_millis;

		}
		else
		{

			Clock::int_millis = ms;
			Clock::now_ms = 0;

		}

	}

}

uint16_t Clock::report_time(unsigned char* buff) {//输出时间到报告

	buff[0] = Clock::now_data->yOff;
	buff[1] = Clock::now_data->m;
	buff[2] = Clock::now_data->d;
	buff[3] = Clock::now_data->hh;
	buff[4] = Clock::now_data->mm;
	buff[5] = Clock::now_data->ss;

	buff[6] = Clock::now_data->wday;

	return 7;
}

void Clock::set_flag() {

	Clock::flag = true;

}

int8_t Clock::get_IC_temp() {

	return Clock::rtc->getTemperature();

}

