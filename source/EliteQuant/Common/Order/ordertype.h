#ifndef _EliteQuant_Common_OrderType_H_
#define _EliteQuant_Common_OrderType_H_

namespace EliteQuant {
	enum OrderType {
		OT_Market = 0,				// market
		OT_MarketOnClose,
		OT_Limit = 2,				// limit
		OT_LimitOnClose,
		OT_PeggedToMarket,
		OT_Stop = 5,				// stop
		OT_StopLimit = 6,			// stop limit
		OT_TrailingStop = 7,		// traiing stop
		OT_Relative,
		OT_VolumeWeightedAveragePrice,
		OT_TrailingStopLimit,
		OT_Volatility,
		OT_None,
		OT_Empty,
		OT_Default,
		OT_Scale,
		OT_MarketIfTouched,
		OT_LimitIfTouched
	};
}

#endif  // _EliteQuant_Common_OrderType_H_