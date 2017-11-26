#ifndef _EliteQuant_Common_BarInterval_H_
#define _EliteQuant_Common_BarInterval_H_

namespace EliteQuant {
	enum BarInterval {
		BI_CustomVol = -3,
		BI_CustomTicks = -2,
		BI_CustomTime = -1,
		BI_Second = 1,
		BI_Minute = 60,
		BI_FiveMin = 300,
		BI_FifteenMin = 900,
		BI_ThirtyMin = 1800,
		BI_Hour = 3600,
		BI_Day = 86400
	};
}

#endif