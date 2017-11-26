#ifndef _EliteQuant_Strategy_SmaCross_H_
#define _EliteQuant_Strategy_SmaCross_H_

#include <Common/Strategy/strategybase.h>
#include <atomic>

namespace EliteQuant {
	class SmaCross : public StrategyBase {
		public:
			virtual void initialize();
			virtual void OnTick(Tick& k);
			virtual void OnGeneralMessage(string& msg);
		private:
			int order_time;
			bool buy_sell;
	};
}


#endif
