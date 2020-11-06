#include "ctrlor.h"

void Ctrlor::adjust_lt(bool imme) {

	//判断是手动还是自动(拍照模式包含在手动内)
	if (!(Configs::lt_man->power_out(Actors::light->power, Actors::light->mode, imme))){
	
		Configs::lt_auto->power_out(Actors::light->power, Actors::light->mode);
	
	}

	Actors::light->exce();

}

void Ctrlor::adjust_all() {

	Ctrlor::adjust_co2();
	Ctrlor::adjust_ro();
	Ctrlor::adjust_spray();
	Ctrlor::adjust_wt_tp();
	Ctrlor::adjust_ar();

	if (Actors::air_temp->power != 0 || Actors::light->power != 0) {
	
		digitalWrite(TEC_PUMP, HIGH);
	
	}
	else {
	
		digitalWrite(TEC_PUMP, LOW);

	}

}

void  Ctrlor::creat_rpt(unsigned char* rpt_buff) {

	int i = 0;//设置值从0开始
	i +=  Clock::report_time(rpt_buff); // i = 7 
	i += Configs::ar_tp->report_config(rpt_buff + i); //i = 11
	i += Configs::wt_tp->report_config(rpt_buff + i); //i = 15
	i += Configs::in_fan->report_config(rpt_buff + i); //i = 19
	i += Configs::humi->report_config(rpt_buff + i);//i = 23
	i += Configs::spray->report_config(rpt_buff + i);//i = 29
	i += Configs::lt_man->report_config(rpt_buff + i);//i = 35
	i += Configs::lt_auto->report_config(rpt_buff + i);//i = 49
	i += Configs::co2->report_config(rpt_buff + i);//i = 54
	i += Configs::add_wt->report_config(rpt_buff + i);//i = 59

	//记录位段
	Configs::wt_tp->rpt_ig(rpt_buff + i, 1); //i = 59
	Configs::ar_tp->rpt_ig(rpt_buff + i, 2); //i = 59

	//------------------------------------
	i = 104;//硬件设置从104开始
	i += Configs::hdw->report_config(rpt_buff + i); // i = 111
	i += Configs::sht->report_config(rpt_buff + i); // i = 116

	//------------------------------------
	i = 125;//测量值从125开始
	i += Ab_time::report_ab(rpt_buff + i); //129
	i += Snors::in_air->report_date(rpt_buff + i);//131
	i += Snors::out_air->report_date(rpt_buff + i);//133
	i += Snors::wt_tp->report_date(rpt_buff + i);//134

	//这个三个是位运算
	i += Snors::in_tk->report_date(rpt_buff + i);//134
	i += Snors::hu_tk->report_date(rpt_buff + i);//134
	i += Snors::mn_tk->report_date(rpt_buff + i);//134

	//------------------------------------
	i = 150;//工作状态从150开始
	i += Actors::air_temp->report_state(rpt_buff + i);//151
	i += Actors::wt_temp->report_state(rpt_buff + i);//152
	i += Actors::light->report_state(rpt_buff + i);//154
	i += Actors::in_fan->report_state(rpt_buff + i);//155
	i += Actors::humi_add->report_state(rpt_buff + i);//156
	i += Actors::co2->report_state(rpt_buff + i);//157
	i += Actors::spray->report_state(rpt_buff + i);//162

	//buff已经写好了,所以后面的无需填充
}

//////////////////////////////////
void Ctrlor::adjust_co2() {

	Configs::co2->power_out(Actors::co2->need_co2);
	Actors::co2->exce();

}

void Ctrlor::adjust_ro () {

	Actors::ro->need_add = Snors::mn_tk->need_add;//主水箱水位是不是过低
	Ab_time::mn_tk_alt = Snors::mn_tk->alt;//是否发送警告
	Actors::ro->exce();

}

void Ctrlor::adjust_spray() {

	//主水箱是否有水位警告
	Actors::spray->mn_lv_alert = Snors::mn_tk->alt;

	Configs::spray->power_out(Actors::spray->get_sp_dist(), Actors::spray->need_sp);//是否需要喷淋
	Actors::spray->need_hu = Snors::hu_tk->need_add; //加湿器是否需要加水

	//判断是否在换水时间
	uint8_t add = 0;
	Configs::add_wt->power_out(add);

	if (add == 0) {//不在换水时间

		Actors::spray->need_in = Snors::in_tk->need_add;//判断缸体内部是否要加水
	
	}
	else {
	
		Actors::spray->need_in = true;//在加水时间直接加水
	
	}

	Actors::spray->exce();

}

void Ctrlor::adjust_wt_tp() {//水温调节

	Configs::wt_tp->power_out(Snors::wt_tp->temp,Actors::wt_temp->power,Ab_time::wt_tp_alt);
	Actors::wt_temp->type_ad();//根据温控器类型计算温控是否执行
	Actors::wt_temp->cp_power(Snors::in_tk->alt);
	Actors::wt_temp->exce();

}

void Ctrlor::adjust_ar() {

	//本函数流程见附录1

	Configs::ar_tp->power_out(Snors::in_air->temp,Actors::air_temp->power,Ab_time::ar_tp_alt);//根据温度设定计算是否需要调节温度
	Actors::air_temp->type_ad();//根据温控器类型计算温控是否执行
	Actors::humi_add->adjust_power(Snors::hu_tk->alt, Actors::air_temp->power);//根据水位状态调整加湿器和温控器(是否制热并强制加湿)

	Actors::air_temp->exce();//操作温控器

	if (!(Actors::air_temp->power > 0)) { //如果无需制热
	
		Configs::humi->power_out(Snors::in_air->humi, Actors::humi_add->hu_ct, Ab_time::hu_alt);//根据湿度设定计算是否需要调节湿度
		Actors::humi_add->adjust_power_lv(Snors::hu_tk->alt);//根据水位调整加湿器
	
	}
	
	Actors::humi_add->exce();

	//---------------------------//
	Configs::in_fan->power_out(Snors::in_air->temp, Actors::in_fan->power);//根据温度计算风扇出力
	Actors::in_fan->adjust_power(Actors::air_temp->power);//根据温控器状态调整风扇出力
	Actors::in_fan->exce();//操作风扇

}

