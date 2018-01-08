#ifndef _EliteQuant_Common_Trade_H_
#define _EliteQuant_Common_Trade_H_

#include <string>
#include <sstream>
#include <cfloat>
#include <regex>
#include <Common/config.h>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>

using std::string;

namespace EliteQuant
{
	struct Fill {
		Fill()
			: orderId(0)
			, tradeId(0)
			, clientId(0)
			, tradeSize(0)
			, tradePrice(DBL_MAX)
		{
		}

		long orderId;
		long tradeId;
		long clientId;
		int tradetime;			// int time
		string fullSymbol;
		string account;
		string currency;
		double tradePrice;
		long tradeSize;					// < 0 = short, order size != trade size

		template<class Archive>
		void serialize(Archive & ar) {
			ar(cereal::make_nvp("id", tradeId),
				cereal::make_nvp("sym", fullSymbol),
				cereal::make_nvp("price", tradePrice),
				cereal::make_nvp("size", tradeSize),
				cereal::make_nvp("time", tradetime)
			);
		}

		string serialize() {
			string str = std::to_string(orderId)
				+ SERIALIZATION_SEPARATOR + std::to_string(tradeId)
				+ SERIALIZATION_SEPARATOR + std::to_string(tradetime)
				+ SERIALIZATION_SEPARATOR + std::to_string(tradePrice)
				+ SERIALIZATION_SEPARATOR + std::to_string(tradeSize);

			return str;
		}

		string toJson(const std::regex& p) {
			std::stringstream ss;
			{
				cereal::JSONOutputArchive oarchive(ss);
				oarchive(cereal::make_nvp("trade", *this));
			}
			return regex_replace(ss.str(), p, "$1");
		}
	};
}

#endif // _EliteQuant_Common_Trade_H_
