#include <Strategy/smacross.h>

namespace EliteQuant
{
	void SmaCross::initialize() {
		order_time = -10;
		buy_sell = true;
	}
	
	void SmaCross::OnTick(Tick& k) {
		//printf("SMA strat OnTick: [%s]\n", k.fullsymbol_.c_str());
		if (hmsf2inttime(k.time_) - order_time > 1000) {
			/*auto o = std::make_shared<Order>();
			o->orderType = "LMT";
			o->fullSymbol = "IF1710";
			o->orderSize = buy_sell ? 2 : -2;
			o->limitPrice = 3868.00;

			buy_sell = !buy_sell;
			order_time = k.time_;
			SendOrder(o);*/
		}
	}

	void SmaCross::OnGeneralMessage(string& msg) {
		printf("SMA strat general msg: [%s]\n", msg.c_str());
	}
}
