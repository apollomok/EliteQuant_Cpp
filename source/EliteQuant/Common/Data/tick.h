#ifndef __EliteQuant_Common_Tick_H_
#define __EliteQuant_Common_Tick_H_

#include <string>
#include <Common/Data/datatype.h>
using namespace std;

namespace EliteQuant {
	struct Tick {
		Tick() {}
		Tick(const string& s) :fullsymbol_(s) {}
		~Tick() {
		}

		string fullsymbol_;
		int time_;
		DataType datatype_;
		double price_;
		int size_;
		int depth_ = 1;			// default is L1 or 1

		string serialize() const;
	};

	struct FullTick : Tick {
		FullTick() {}
		FullTick(const string& s) : Tick(s) {}
		~FullTick() {}

		// assuming base Tick class stores trade/last data
		// here it adds bid/ask data
		double bidprice_L1_;
		int bidsize_L1_;
		double askprice_L1_;
		int asksize_L1_;
	};
}

#endif  // __EliteQuant_Common_Tick_H_
