#ifndef _EliteQuant_Common_SecurityType_H_
#define _EliteQuant_Common_SecurityType_H_

#include <string>

namespace EliteQuant {
	enum SecurityType {
		UNKNOWN = -1,
		STK,
		OPT,
		FUT,
		CFD,
		FOR,
		FOP,        // futures on options
		WAR,        // Warrant
		FOX,
		IND,        // index
		BND,
		CASH,       // forex pair
		BAG,        // combo
	};

	/// xxxTypeString is the string name of xxxType
	const std::string SecurityTypeString[] = {
		"UNKNOWN",
		"STK",
		"OPT",
		"PUT",
		"CFD",
		"FOR",
		"FOP",
		"WAR",
		"FOX",
		"IND",
		"BND",
		"CASH",
		"BAG"
	};
}

#endif  // _EliteQuant_Common_SecurityType_H_