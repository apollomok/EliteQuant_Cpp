#ifndef _EliteQuant_Brokers_PaperBrokerage_H_
#define _EliteQuant_Brokers_PaperBrokerage_H_

#include <mutex>
#include <Common/config.h>
#include <Common/Brokerage/brokerage.h>

using std::mutex;
using std::string;
using std::list;
using std::vector;

namespace EliteQuant
{
	struct Security;

	class paperbrokerage : public brokerage {
	public:
		paperbrokerage();
		~paperbrokerage();

		virtual bool connectToBrokerage();
		virtual void disconnectFromBrokerage();
		virtual bool isConnectedToBrokerage() const;

		virtual void placeOrder(std::shared_ptr<Order> order);
		virtual void requestNextValidOrderID();

		// Cancel Order
		/*Use this function to cancel all open orders globally.
		It cancels both API and TWS open orders.
		If the order was created in TWS, it also gets canceled.
		If the order was initiated in the API, it also gets canceled.*/
		void reqGlobalCancel();
		virtual void cancelOrder(int oid);
		virtual void cancelOrders(const string& symbol);
		//cancelAllOrders is not reentrant!
		virtual void cancelAllOrders();

		//https://www.interactivebrokers.com/en/software/api/apiguide/java/reqaccountupdates.htm
		virtual void requestBrokerageAccountInformation(const string& account_);

		/*Call this function to request the open orders that were placed from this client.
		Each open order will be fed back through the openOrder() and orderStatus() functions on the EWrapper.

		Note: The client with a clientId of 0 will also receive the TWS-owned open orders.
		These orders will be associated with the client and a new orderId will be generated.
		This association will persist over multiple API and TWS sessions.*/
		virtual void requestOpenOrders();
		/*Call this function to request the open orders placed from all clients and also from TWS.
		Each open order will be fed back through the openOrder() and orderStatus() functions on the EWrapper.
		Note:  No association is made between the returned orders and the requesting client.*/
		void reqAllOpenOrders();
		/*Call this function to request that newly created TWS orders be implicitly associated with the client.
		When a new TWS order is created, the order will be associated with the client,
		and fed back through the openOrder() and orderStatus() functions on the EWrapper.
		Note:  This request can only be made from a client with clientId of 0.
		If set to TRUE, newly created TWS orders will be implicitly associated with the client.
		If set to FALSE, no association will be made.*/
		void reqAutoOpenOrders(bool);

	public:

	};
}

#endif // _EliteQuant_Brokers_PaperBrokerage_H_
