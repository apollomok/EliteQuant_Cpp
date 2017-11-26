// pass through all the data types
// take trade price and trade size, aggregate into bars and then propogate
#ifndef _EliteQuant_Common_DataType_H_
#define _EliteQuant_Common_DataType_H_

#include <string>

namespace EliteQuant {
	enum DataType : int {
		DT_BidPrice = 0,
		DT_BidSize = 1,
		DT_AskPrice = 2,
		DT_AskSize = 3,
		DT_TradePrice = 4,
		DT_TradeSize = 5,
		DT_OpenPrice = 6,
		DT_HighPrice = 7,
		DT_LowPrice = 8,
		DT_ClosePrice = 9,
		DT_Volume = 10,
		DT_OpenInterest = 11,
		DT_Bar = 12,
		DT_Account = 13,
		DT_Position = 14
	};

	/// xxxTypeString is the string name of xxxType
	const std::string DataTypeString[] = {
		"BidSize",
		"BidPrice",
		"AskPrice",
		"AskSize",
		"TradePrice",
		"TradeSize",
		"OpenPrice",
		"HighPrice",
		"LowPrice",
		"ClosePrice",
		"Volume",
		"OpenInterest",
		"Bar",
		"Account",
		"Position",
		"OrderId"
	};
}

#endif  // _EliteQuant_Common_DataType_H_