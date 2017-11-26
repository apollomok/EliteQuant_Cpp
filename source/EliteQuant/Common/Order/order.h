#ifndef _EliteQuant_Common_Order_H_
#define _EliteQuant_Common_Order_H_

#include <string>
#include <sstream>
#include <cfloat>
#include <regex>
#include <Common/Order/orderstatus.h>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>

using std::string;

namespace EliteQuant
{
	struct Order {
		Order()
			: orderId(0)
			, clientId(0)
			, orderSize(0)
			, limitPrice(DBL_MAX)
			, stopPrice(DBL_MAX)
		{
		}

		long orderId;
		long clientId;
		time_t createTime;
		string fullSymbol;
		string account;					// TODO: support multiple accounts
		string orderType;
		OrderStatus orderStatus;				// submitted, canceled, etc
		long orderSize;					// < 0 = short, order size != trade size
		long filled = 0;
		double lastFilledPrice = { 0.0f };
		double avgFilledPrice = { 0.0f };
		double limitPrice;
		double stopPrice;
		double trailPrice;
		double trailingPercent;
		string timeInForce;
		bool outsideRegularTradingHour;
		bool hidden;
		bool allOrNone;

		template<class Archive>
		void serialize(Archive & ar) {
			ar(cereal::make_nvp("id", orderId),
				cereal::make_nvp("sym", fullSymbol),
				cereal::make_nvp("type", orderType),
				cereal::make_nvp("size", orderSize),
				cereal::make_nvp("s", orderStatus),
				cereal::make_nvp("lp", limitPrice),
				cereal::make_nvp("sp", stopPrice),
				cereal::make_nvp("tp", trailPrice),
				cereal::make_nvp("lfp", lastFilledPrice),
				cereal::make_nvp("f", filled),
				cereal::make_nvp("c", createTime)
			);
		}

		string toJson(const std::regex& p) {
			std::stringstream ss;
			{
				cereal::JSONOutputArchive oarchive(ss);
				oarchive(cereal::make_nvp("order", *this));
			}
			return regex_replace(ss.str(), p, "$1");
		}
	};

	struct MarketOrder : Order
	{
		MarketOrder() : Order()
		{
			limitPrice = 0;
			stopPrice = 0;
			trailPrice = 0;
		}
	};

	struct LimitOrder : Order
	{
		LimitOrder(double lp) : Order()
		{
			limitPrice = lp;
			stopPrice = 0;
			trailPrice = 0;
		}
	};

	struct StopOrder : Order
	{
		StopOrder(double sp) : Order()
		{
			limitPrice = 0;
			stopPrice = sp;
			trailPrice = 0;
		}
	};

	struct StopLimitOrder : Order
	{
		StopLimitOrder(double lp, double sp) : Order()
		{
			limitPrice = lp;
			stopPrice = sp;
			trailPrice = 0;
		}
	};

	struct TrailingStopOrder : Order
	{
		TrailingStopOrder(double tp) : Order()
		{
			limitPrice = 0;
			stopPrice = 0;
			trailPrice = tp;
		}
	};
}

#endif // _EliteQuant_Common_Order_H_
