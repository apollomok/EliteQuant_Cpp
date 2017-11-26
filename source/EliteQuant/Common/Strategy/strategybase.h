#ifndef _EliteQuant_Common_StraegyBase_H_
#define _EliteQuant_Common_StraegyBase_H_

#include <Common/Util/util.h>
#include <Common/Data/tick.h>
#include <Common/Data/bar.h>
#include <Common/Order/order.h>
#include <Common/Order/fill.h>
#include <Common/Logger/logger.h>
#include <Common/Security/position.h>

namespace EliteQuant {
	struct Position;

	class StrategyBase {
	public:
		bool initialized = false;

		StrategyBase();
		virtual ~StrategyBase();
		virtual void initialize();
		virtual void reset();
		virtual void teardown();

		// ************  Incoming Message Handers ********************//
		virtual void OnTick(Tick& k) {}
		virtual void OnBar(Bar& k) {}
		virtual void OnOrderTicket(long oid) {}				// Order acknowledge
		virtual void OnOrderCancel(long oid) {}
		virtual void OnFill(Fill& f) {}
		virtual void OnPosition(Position& p) {}
		virtual void OnGeneralMessage(string& msg) {}
		// ************ End Incoming Message Handers ********************//

		// ************  Outgoing Methods ********************//
		void SendOrder(std::shared_ptr<Order> o);
		void SendOrderCancel(long oid);
		void SendSubscriptionRequest();
		void SendHistoricalBarRequest();
		void SendGeneralInformation();
		void SendLog();

		// ************  End Outgoing Methods ********************//
	};
}

#endif // _EliteQuant_Common_StraegyBase_H_
