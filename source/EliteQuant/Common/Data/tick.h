#ifndef __EliteQuant_Common_Tick_H_
#define __EliteQuant_Common_Tick_H_

#include <string>
#include <Common/config.h>
#include <Common/Data/datatype.h>
using namespace std;

namespace EliteQuant {
	class DLL_EXPORT_IMPORT Tick : public BaseData {
	public:
		Tick() 	: fullsymbol_("")
			, time_("")
			, price_(0.0)
			, size_(0)
			, depth_(1)		// default is L1 or 1
		{
			datatype_ = DataType::DT_Trade;
		}

		Tick(const string& s) :fullsymbol_(s) {}
		~Tick() {
		}

		string fullsymbol_;
		string time_;
		double price_;
		int size_;
		int depth_;

		virtual string serialize() const;
		virtual void deserialize(string& s);
	};

	class DLL_EXPORT_IMPORT FullTick : public Tick {
	public:
		FullTick() : Tick()
			, bidprice_L1_(0.0)
			, bidsize_L1_(0)
			, askprice_L1_(0.0)
			, asksize_L1_(0)
			, open_interest(0)
			, open_(0.0)
			, high_(0.0)
			, low_(0.0)
			, pre_close_(0.0)
			, upper_limit_price_(0.0)
			, lower_limit_price_(0.0)
		{
			datatype_ = DataType::DT_Full;
		}

		FullTick(const string& s) : Tick(s) {}
		~FullTick() {}

		// assuming base Tick class stores trade/last data
		// here it adds bid/ask data
		double bidprice_L1_;
		int bidsize_L1_;
		double askprice_L1_;
		int asksize_L1_;
		int open_interest;
		double open_;
		double high_;
		double low_;
		double pre_close_;
		double upper_limit_price_;
		double lower_limit_price_;

		virtual string serialize() const;		// overriding
		virtual void deserialize(string& s);
	};
}

#endif  // __EliteQuant_Common_Tick_H_
