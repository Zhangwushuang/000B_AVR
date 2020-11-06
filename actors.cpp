#include "actors.h"

Co2_ac* const Actors::co2 (new Co2_ac());
Humi_add_ac* const Actors::humi_add(new Humi_add_ac());
In_fan_ac* const Actors::in_fan(new In_fan_ac());
Light_ac* const Actors::light(new Light_ac(Configs::hdw->lt_type));

Ro_ac* const Actors::ro(new Ro_ac());
Spray_ac* const Actors::spray(new Spray_ac());
Wt_temp_ac* const Actors::wt_temp(new Wt_temp_ac(Configs::hdw->wt_con, Configs::hdw->wt_p_t));
Air_temp_ac* const Actors::air_temp(new Air_temp_ac(Configs::hdw->ar_con, Configs::hdw->ar_p_t));

