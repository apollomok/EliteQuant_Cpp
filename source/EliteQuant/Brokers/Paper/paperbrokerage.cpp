#include <mutex>
#include <Common/Order/orderstatus.h>
#include <Common/Order/fill.h>
#include <Common/Order/ordermanager.h>
#include <Common/Data/datamanager.h>
#include <Common/Logger/logger.h>
#include <Common/Util/util.h>
#include <Brokers/Paper/paperbrokerage.h>

using namespace std;
namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;

	paperbrokerage::paperbrokerage() {
	}

	paperbrokerage::~paperbrokerage() {
	}

	bool paperbrokerage::connectToBrokerage() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Paper brokerage connection connected!\n", __FILE__, __LINE__, __FUNCTION__);

		sendGeneralMessage("Connected to paper brokerage");
		return true;
	}

	void paperbrokerage::disconnectFromBrokerage() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Paper brokerage connection disconnected!\n", __FILE__, __LINE__, __FUNCTION__);
	}

	bool paperbrokerage::isConnectedToBrokerage() const {
		return (!gShutdown);				// automatic disconnect when shutdown
	}

	// immediate fill market order with last price
	void paperbrokerage::placeOrder(std::shared_ptr<Order> order) {
		if (order->orderStatus != OrderStatus::OS_NewBorn)
			return;

		sendOrderSubmitted(order->orderId);

		// fill the order
		{
			lock_guard<mutex> g(orderStatus_mtx);			// lock_guard<mutex> used in gotFill as well
			PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Placing Order %ld: %s. \n", __FILE__, __LINE__, __FUNCTION__, order->orderId, order->fullSymbol.c_str());
			order->orderStatus = OrderStatus::OS_Submitted;			// NewBorn --> Submitted --> OS_Acknowledged
			order->orderStatus = OrderStatus::OS_Acknowledged;
			order->orderStatus = OrderStatus::OS_Filled;			// filled immediately
		}

		Fill fill;
		time_t rawtime;
		time(&rawtime);
		fill.tradeId = order->orderId;
		fill.tradetime = tointtime(rawtime);
		fill.fullSymbol = order->fullSymbol;
		fill.account = order->account;
		fill.tradePrice = DataManager::instance()._latestmarkets[order->fullSymbol].price_;			// TODO: assuming this security is tracked
		fill.tradeSize = order->orderSize;

		sendOrderFilled(fill);
	}

	void paperbrokerage::requestNextValidOrderID() {
		lock_guard<mutex> g(oid_mtx);
		m_orderId++;
		_bkstate = BK_READYTOORDER;
	}


	void paperbrokerage::reqGlobalCancel() {
	}

	// does not accept cancel order
	void paperbrokerage::cancelOrder(int oid) {
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)m_orderId);
	}

	void paperbrokerage::cancelOrders(const string& symbol) {
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order %s\n", __FILE__, __LINE__, __FUNCTION__, symbol.c_str());
	}

	void paperbrokerage::cancelAllOrders() {
		lock_guard<mutex> _g(mtx_CANCELALL);
	}

	// get paper account info, e.g. 1mm dollars
	void paperbrokerage::requestBrokerageAccountInformation(const string& account_) {
	}

	void paperbrokerage::requestOpenOrders() {
	}

	void paperbrokerage::reqAllOpenOrders() {

	}

	void paperbrokerage::reqAutoOpenOrders(bool) {

	}
}