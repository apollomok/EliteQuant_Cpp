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

		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Placing Order %ld: %s. \n", __FILE__, __LINE__, __FUNCTION__, order->serverOrderId, order->fullSymbol.c_str());

		Fill fill;
		fill.fullSymbol = order->fullSymbol;
		fill.tradetime = ymdhmsf();
		fill.serverOrderId = order->serverOrderId;
		fill.clientOrderId = order->clientOrderId;
		fill.brokerOrderId = order->brokerOrderId;
		fill.tradeId = order->brokerOrderId;
		fill.tradePrice = DataManager::instance()._latestmarkets[order->fullSymbol].price_;			// assuming this security is tracked
		fill.tradeSize = order->orderSize;
		fill.account = order->account;     // paper
		fill.api = order->api;          // paper

		OrderManager::instance().gotFill(fill);
		sendOrderFilled(fill);
		sendOrderStatus(order->serverOrderId);
	}

	void paperbrokerage::requestNextValidOrderID() {
		lock_guard<mutex> g(oid_mtx);
		m_brokerOrderId++;
		_bkstate = BK_READYTOORDER;
	}


	void paperbrokerage::reqGlobalCancel() {
	}

	// does not accept cancel order
	void paperbrokerage::cancelOrder(int oid) {
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)oid);
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

	void paperbrokerage::requestOpenOrders(const string& account_) {

	}

	void paperbrokerage::requestOpenPositions(const string& account_) {

	}
}