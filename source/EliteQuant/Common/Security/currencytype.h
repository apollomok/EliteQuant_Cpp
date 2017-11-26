#ifndef _EliteQuant_Common_CurrencyType_H_
#define _EliteQuant_Common_CurrencyType_H_

#include <string>

namespace EliteQuant {
	enum CurrencyType {
		USD,
		AUD,
		CAD,
		CHF,
		EUR,
		GBP,
		HKD,
		JPY,
		MXN,
		NZD,
		SEK
	};

	const std::string CurrencyTypeString[] = {
		"USD",
		"AUD",
		"CAD",
		"CHF",
		"EUR",
		"GBP",
		"HKD",
		"JPY",
		"MXN",
		"NZD",
		"SEK"
	};
}

#endif  // _EliteQuant_Common_CurrencyType_H_