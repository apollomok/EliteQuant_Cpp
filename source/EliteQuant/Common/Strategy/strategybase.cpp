#include <Common/Strategy/strategybase.h>
#include <Common/config.h>
#include <Common/Time/timeutil.h>
#include <Common/Order/ordermanager.h>

namespace EliteQuant {
	extern std::atomic<bool> gShutdown;

	StrategyBase::StrategyBase()
	{
	}

	StrategyBase::~StrategyBase() {
	}

	void StrategyBase::initialize() {
		initialized = true;
	}

	void StrategyBase::reset() {
	}

	void StrategyBase::teardown() {
		initialized = false;
	}

	// ************  Incoming Message Handers ********************//

	// ************ End Incoming Message Handers ********************//

	// ************  Outgoing Methods ********************//
	void StrategyBase::SendOrder(std::shared_ptr<Order> o)
	{
		// TODO: send o|MKT|SPY STK SMART
		/*lock_guard<mutex> g(oid_mtx);

		o->createTime = time(nullptr);
		o->orderStatus = OrderStatus::OS_NewBorn;
		o->orderId = m_orderId;
		// increase order id
		m_orderId++; */
		//OrderManager::instance().trackOrder(o);   TODO: send order through message queue;
	}

	void StrategyBase::SendOrderCancel(long oid)
	{
		// TODO: put it into order process queue
		string msg = CConfig::instance().cancel_order_msg
			+ SERIALIZATION_SEPARATOR + std::to_string(oid);

		//sendmq(msg);
	}

	void StrategyBase::SendSubscriptionRequest()
	{

	}

	void StrategyBase::SendHistoricalBarRequest()
	{

	}

	void StrategyBase::SendGeneralInformation()
	{

	}

	void StrategyBase::SendLog()
	{

	}

	// ************  End Outgoing Methods ********************//
}