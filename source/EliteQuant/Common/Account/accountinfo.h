// this is the format of naming the file and ifndef
// 
#ifndef _EliteQuant_Common_AccountInfo_H_
#define _EliteQuant_Common_AccountInfo_H_

#include <sstream>
#include <regex>
#include <Common/config.h>

namespace EliteQuant
{
	class AccountInfo {
	public:
		string AccountID;
		string AccountType;				//INDIVIDUAL
		
		double AvailableFunds;
		double NetLiquidation;

		double EquityWithLoanValue;
		double PreviousDayEquityWithLoanValue;

		double FullInitialMargin;
		double FullMaintainanceMargin;

		double BuyingPower;
		double CashBalance;

		double RealizedPnL;
		double UnrealizedPnL;

		template<class Archive>
		void serialize(Archive & ar) {
			ar(CEREAL_NVP(AccountID), CEREAL_NVP(AccountType),
				CEREAL_NVP(AvailableFunds), CEREAL_NVP(NetLiquidation),
				CEREAL_NVP(EquityWithLoanValue), CEREAL_NVP(PreviousDayEquityWithLoanValue),
				CEREAL_NVP(FullInitialMargin), CEREAL_NVP(FullMaintainanceMargin),
				CEREAL_NVP(BuyingPower), CEREAL_NVP(CashBalance),
				CEREAL_NVP(RealizedPnL), CEREAL_NVP(UnrealizedPnL));
		}

		string toJson(const std::regex* p) {
			std::stringstream ss;
			{
				cereal::JSONOutputArchive oarchive(ss);
				oarchive(cereal::make_nvp("accountinfo", *this));
			}
			string r = ss.str();
			if (p && !r.empty()) {
				string r = regex_replace(r, *p, "$1");
			}
			return r;
		}

		void setvalue(const string &key, const string &val, const string &currency) {
			if (currency == "USD") {
				if (key == "AccountID") {
					AccountID = val;
				}
				else if (key == "AccountType") {
					AccountType = val;
				}
				else if (key == "AvailableFunds") {
					AvailableFunds = atof(val.c_str());
				}
				else if (key == "NetLiquidation") {
					NetLiquidation = atof(val.c_str());
				}
				else if (key == "EquityWithLoanValue") {
					EquityWithLoanValue = atof(val.c_str());
				}
				else if (key == "PreviousDayEquityWithLoanValue") {
					PreviousDayEquityWithLoanValue = atof(val.c_str());
				}
				else if (key == "FullInitialMargin") {
					FullInitialMargin = atof(val.c_str());
				}
				else if (key == "FullMaintainanceMargin") {
					FullMaintainanceMargin = atof(val.c_str());
				}
				else if (key == "BuyingPower") {
					BuyingPower = atof(val.c_str());
				}
				else if (key == "CashBalance") {
					CashBalance = atof(val.c_str());
				}
				else if (key == "RealizedPnL") {
					RealizedPnL = atof(val.c_str());
				}
				else if (key == "UnrealizedPnL") {
					UnrealizedPnL = atof(val.c_str());
				}
			}
		}

	};
}

#endif // _EliteQuant_Common_AccountInfo_H_
