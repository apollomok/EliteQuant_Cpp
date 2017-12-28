#ifndef _EliteQuant_Common_Brokerage_H_
#define _EliteQuant_Common_Brokerage_H_
#include <mutex>
#include <Common/config.h>
#include <Common/Time/getRealTime.h>
#include <Common/Time/heartbeat.h>
#include <Common/Order/order.h>
#include <Common/Order/fill.h>
#include <Common/Security/security.h>
#include <Common/Msgq/msgq.h>

using std::mutex;
using std::string;
using std::list;

namespace EliteQuant
{
	typedef long OrderId;				// Every order has an order id
	struct Security;

	enum BKState {				// brokerage state
		BK_DISCONNECTED,
		BK_CONNECT,
		BK_ACCOUNT,
		BK_ACCOUNTACK,
		BK_GETORDERID,
		BK_GETORDERIDACK,
		BK_READYTOORDER,
		BK_PLACEORDER_ACK,
		BK_CANCELORDER,
		BK_CANCELORDER_ACK
	};

	class brokerage : virtual public CHeartbeat {
	protected:
		struct timeval timeout;
		std::unique_ptr<CMsgq> msgq_pair_;

		// outbound messages
		void sendOrderCreated(long oid);
		void sendOrderSubmitted(long oid);
		void sendOrderAcknowledged(long oid);
		void sendOrderFilled(Fill& t);
		void sendOrderCancelled(long oid);
		void sendOrderStatus(long oid);
		void sendOpenPositionMessage(string symbol, double position, double averageCost, double unrealisedPNL, double realisedPNL);
		void sendHistoricalBarMessage(string symbol, string time, double open, double high, double low, double close, int volume, int barcount = 0, double wap = 0);
		void sendGeneralMessage(std::string gm);

		// inbound messages
		void monitorClientRequest();

	public:
		brokerage();
		~brokerage();

		BKState _bkstate;
		virtual void processBrokerageMessages();

		virtual bool connectToBrokerage() = 0;
		virtual void disconnectFromBrokerage() = 0;
		virtual bool isConnectedToBrokerage() const = 0;
		virtual void placeOrder(std::shared_ptr<Order> order) = 0;
		virtual void requestNextValidOrderID() = 0;

		// Cancel Order
		virtual void cancelOrder(int oid) = 0;
		virtual void cancelOrders(const string& symbol) = 0;
		static mutex mtx_CANCELALL;
		virtual void cancelAllOrders() = 0;
		bool isAllOrdersCancelled(); //TODO

		virtual void requestBrokerageAccountInformation(const string& account_) = 0;

		virtual void requestOpenOrders() = 0;
	};
}

#endif // _EliteQuant_Common_Brokerage_H_
