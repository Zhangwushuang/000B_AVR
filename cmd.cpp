#include "cmd.h"

unsigned char Cmd::cmd_buff[128];
unsigned char Cmd::rpt_buff[RPT_LEN];

uint8_t Cmd::code = 0;//代码
int8_t Cmd::from = 0;//来源

bool Cmd::rec_cmd(HardwareSerial* port) {

	int i = 0;

	while (port->available() > 0) {
	
		Cmd::cmd_buff[i] = port->read();

		delay(1);//波特率19200

		++i;
	
	}

    return (i == CMD_LEN);
	
}

void Cmd::exec_cmd(bool lc) {

	Cmd::code = Cmd::cmd_buff[0];
	Cmd::from = Cmd::cmd_buff[1];

	//参数buff的指针
	unsigned char* ag_buff = (unsigned char*)Cmd::cmd_buff + 2;

	//拍照
	if (Cmd::code == SHOOT_UPLOAD) {

		Configs::lt_man->set_shoot_tp(ag_buff);//临时开灯
		Ctrlor::adjust_lt(true);//重新计算灯光

	}

	//对时
	if (Cmd::code == CHK_TIME_CD) {

		//年
		if (ag_buff[0] > 99) {
		
			return;
		
		}

		//月
		if (ag_buff[1] > 12 || ag_buff[1] < 1) {

			return;

		}

		//日
		if (ag_buff[2] > 31 || ag_buff[2] < 1 ) {

			return;

		}

		//时
		if (ag_buff[3] > 23) {

			return;

		}

		//分
		if (ag_buff[4] > 59) {

			return;

		}

		//秒
		if (ag_buff[5] > 59) {

			return;

		}

		//星期
		if (ag_buff[6] > 7) {
		
			return;

		}

		DateTime time_rec(ag_buff[0], ag_buff[1], ag_buff[2], ag_buff[3], ag_buff[4], ag_buff[5], ag_buff[6]);

		Clock::rtc->setDateTime(&time_rec);//对时
		Clock::set_flag();//设置标记
		Clock::get_time();//重新读取时间
		Ctrlor::adjust_lt();
		Ctrlor::adjust_all();

		return;

	}

	//手动喷淋
	if (Cmd::code == SPRAY_MAN_CD) {
	
		Actors::spray->last_sp_time = 0;
		Ctrlor::adjust_spray();
	
	}
	
	//手动灯光设置(因为用得最频繁，所以放第一个)
	if (Cmd::code == MAN_LT_CF) {

		if (Configs::lt_man->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::lt_man->load_confi();//重新读取
			Ctrlor::adjust_lt(true);//重新计算

		}

		return;

	}

	//气温设置
	if (Cmd::code == AR_TP_CF) {

		if (Configs::ar_tp->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::ar_tp->load_confi();//重新读取
			Ctrlor::adjust_ar();//重新计算空调

		}

		return;

	}

	//内部风扇设置
	if (Cmd::code == IN_FAN_CF) {

		if (Configs::in_fan->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::in_fan->load_confi();//重新读取
			Ctrlor::adjust_ar();//重新计算空调

		}

		return;

	}

	//自动喷淋设置
	if (Cmd::code == SPRAY_CF) {

		if (Configs::spray->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::spray->load_confi();//重新读取
			Ctrlor::adjust_spray();//重新计算

		}

		return;

	}

	//自动灯光设置
	if (Cmd::code == AUTO_LT_CF) {

		if (Configs::lt_auto->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::lt_auto->load_confi();//重新读取
			Ctrlor::adjust_lt();//重新计算

		}

		return;

	}

	//co2设置
	if (Cmd::code == CO2_CF) {

		if (Configs::co2->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::co2->load_confi();//重新读取
			Ctrlor::adjust_co2();//重新计算

		}

		return;

	}

	//加水设置
	if (Cmd::code == WT_CIRCLE_CF) {

		if (Configs::add_wt->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::add_wt->load_confi();//重新读取
			Ctrlor::adjust_spray();//重新计算

		}

		return;

	}

	//水温设置
	if (Cmd::code == WT_TP_CF) {

		if (Configs::wt_tp->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::wt_tp->load_confi();//重新读取
			Ctrlor::adjust_wt_tp();//重新计算

		}

		return;

	}

	//湿度设置
	if (Cmd::code == HUMI_CF) {

		if (Configs::humi->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::humi->load_confi();//重新读取
			Ctrlor::adjust_ar();//重新计算

		}

		return;

	}

	//硬件设置
	if ((Cmd::code == HW_CF) && lc) {//如果是通过调试口

		if (Configs::hdw->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::hdw->load_confi();//重新读取
			Ctrlor::adjust_lt();
			Ctrlor::adjust_all();

		}

		return;

	}

	//拍照间隔设置
	if (Cmd::code == AT_ST_CF) {

		if (Configs::sht->save_confi(ag_buff))//如果保存设置成功
		{

			Configs::sht->load_confi();//重新读取

		}

		return;

	}

}

void Cmd::snd_rpt(HardwareSerial* port, bool is_cmd) {

	delay(50);//总是延时50ms，以防止连续发送

	memset(Cmd::rpt_buff,0, RPT_LEN);//清零

	if (is_cmd) {//如果是命令
	
		Cmd::rpt_buff[0] = Cmd::code;
		Cmd::rpt_buff[1] = Cmd::from;
	
	}

	//将要发送的数据cp进缓存
	Ctrlor::creat_rpt((unsigned char*)Cmd::rpt_buff + 2);
	port->write((char*)Cmd::rpt_buff, RPT_LEN);//发送数据
	
}

