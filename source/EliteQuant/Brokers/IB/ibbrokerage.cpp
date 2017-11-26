#include <Brokers/IB/ibbrokerage.h>
#include <mutex>
#include <algorithm>
#include <Common/Data/datatype.h>
#include <Common/Data/datamanager.h>
#include <Common/Order/orderstatus.h>
#include <Common/Order/ordermanager.h>
#include <Common/Util/util.h>
#include <Common/Security/portfoliomanager.h>
#include <Common/Logger/logger.h>

using namespace std;
using namespace IBOfficial;

namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;

	IBBrokerage::IBBrokerage() :
		m_pClient(new EPosixClientSocket(this))
	{
	}

	IBBrokerage::~IBBrokerage()
	{
	}

	//********************************************************************************************//
	// Brokerage part
	void IBBrokerage::processBrokerageMessages()
	{
		if (!brokerage::heatbeat(5)) {
			disconnectFromBrokerage();
			return;
		}
		switch (_bkstate) {
		case BK_ACCOUNT:		// not used
			requestBrokerageAccountInformation(CConfig::instance().account);
			break;
		case BK_ACCOUNTACK:		// not used
			break;
		case BK_GETORDERID:
			requestNextValidOrderID();
			break;
		case BK_GETORDERIDACK:
			break;
		case BK_READYTOORDER:
			monitorClientRequest();
			break;
		case BK_PLACEORDER_ACK:
			break;
		case BK_CANCELORDER:
			cancelOrder(0); //TODO
			break;
		case BK_CANCELORDER_ACK:
			break;
		}

		// from IB source code
		// TODO: what does this do?
		if (m_pClient->fd() >= 0) {
			fd_set readSet, writeSet, errorSet;
			FD_ZERO(&readSet);
			errorSet = writeSet = readSet;

			FD_SET(m_pClient->fd(), &readSet);

			if (!m_pClient->isOutBufferEmpty())
				FD_SET(m_pClient->fd(), &writeSet);

			FD_SET(m_pClient->fd(), &errorSet);

			int ret = select(m_pClient->fd() + 1, &readSet, &writeSet, &errorSet, &(brokerage::timeout));

			if (ret == 0) { // timeout
				return;
			}

			if (ret < 0) {	// error
				printf("error\n");
				disconnectFromBrokerage();
				return;
			}

			if (m_pClient->fd() < 0) {
				printf("error\n");
				return;
			}

			if (FD_ISSET(m_pClient->fd(), &errorSet)) {
				// error on socket
				printf("error\n");
				m_pClient->onError();
			}

			if (m_pClient->fd() < 0) {
				return;
			}

			if (FD_ISSET(m_pClient->fd(), &writeSet)) {
				// socket is ready for writing
				m_pClient->onSend();
			}

			if (m_pClient->fd() < 0) {
				return;
			}

			if (FD_ISSET(m_pClient->fd(), &readSet)) {
				// socket is ready for reading
				m_pClient->onReceive();
			}
		}
	}

	bool IBBrokerage::connectToBrokerage() {
		const char* host = CConfig::instance().ib_host.c_str();
		unsigned int port = CConfig::instance().ib_port;
		int clientId = 0;

		PRINT_TO_FILE("INFO:[%s,%d][%s]Connecting to %s:%d clientId:%d.\n", __FILE__, __LINE__, __FUNCTION__, host, port, clientId);

		bool bRes = m_pClient->eConnect(host, port, clientId);

		if (bRes) {
			PRINT_TO_FILE("INFO:[%s,%d][%s]Connected to ib brokerage %s:%d clientId:%d\n", __FILE__, __LINE__, __FUNCTION__, host, port, clientId);
			_bkstate = BK_CONNECT;
			//m_pClient->setServerLogLevel(5);			// can not work on m_pClient before a loop process
			if (clientId == 0) {
				//m_pClient->reqAutoOpenOrders(true);		// associate TWS with the client
			}
			//_nServerVersion = m_pClient->serverVersion();

			// trigger updatePortfolio()
			//m_pClient->reqAccountUpdates();
		}
		else {
			PRINT_TO_FILE("ERROR:[%s,%d][%s]Cannot connect to %s:%d clientId:%d\n", __FILE__, __LINE__, __FUNCTION__, host, port, clientId);
		}
		return bRes;
	}

	void IBBrokerage::disconnectFromBrokerage() {
		// CancelMarketData
		int i = 0;
		for (auto it = CConfig::instance().securities.begin(); it != CConfig::instance().securities.end(); ++it)
		{
			m_pClient->cancelMktData(i);
			i++;
		}

		m_pClient->eDisconnect();
		_bkstate = BK_DISCONNECTED;
		PRINT_TO_FILE("INFO:[%s,%d][%s]TWS connection disconnected!\n", __FILE__, __LINE__, __FUNCTION__);
	}

	bool IBBrokerage::isConnectedToBrokerage() const
	{
		return m_pClient->isConnected();
	}

	void IBBrokerage::placeOrder(std::shared_ptr<Order> o)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Place order, id = %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)o->orderId);

		IBOfficial::Order oib;			// local stack
		Contract contract;				// local stack

		if (o->fullSymbol.empty())
		{
			PRINT_TO_FILE_AND_CONSOLE("ERROR:[%s,%d][%s]Order is not valid %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)o->orderId);
			return;
		}

		if (o->orderId == 0)
		{
			PRINT_TO_FILE_AND_CONSOLE("ERROR:[%s,%d][%s]Order is not valid %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)o->orderId);
			return;
		}

		/*if (o->orderStatus != OrderStatus::OS_NewBorn)		// in order to enable replacement order
		{
		PRINT_TO_FILE_AND_CONSOLE("ERROR:[%s,%d][%s]Not a NewBorn order %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)o->orderId);
		return;
		}*/

		SecurityFullNameToContract(o->fullSymbol, contract);
		OrderToIBOfficialOrder(o, oib);

		lock_guard<mutex> g(orderStatus_mtx);
		o->orderStatus = OrderStatus::OS_Submitted;  // TODO: similar to gotCancel, change status in OrderManager
		m_pClient->placeOrder(o->orderId, contract, oib);

		sendOrderSubmitted(o->orderId);
	}

	void IBBrokerage::requestNextValidOrderID()
	{
		static int tmp = 1;
		PRINT_TO_FILE("INFO:[%s,%d][%s]Requesting next order id, reqId = %d\n", __FILE__, __LINE__, __FUNCTION__, tmp);
		if (_bkstate < BK_GETORDERIDACK)
			_bkstate = BK_GETORDERIDACK;
		if (m_orderId == -1)
			m_pClient->reqIds(tmp++);
	}

	//1.from web/distance too long/tws cancel?
	void IBBrokerage::cancelOrder(int oid)
	{
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)m_orderId);
		m_pClient->cancelOrder(oid);
	}

	// cancel all orders for this symbol
	void IBBrokerage::cancelOrders(const string& symbol)
	{
		vector<std::shared_ptr<Order>> v = OrderManager::instance().retrieveNonFilledOrderPtr(symbol);

		for (std::shared_ptr<Order> o : v) {
			m_pClient->cancelOrder(o->orderId);
			PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order %ld\n", __FILE__, __LINE__, __FUNCTION__, (long)o->orderId);
		}
	}

	void IBBrokerage::cancelAllOrders() {}

	///https://www.interactivebrokers.com/en/software/api/apiguide/java/updateportfolio.htm
	void IBBrokerage::requestBrokerageAccountInformation(const string& account_)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Requesting brokerage account info: %s\n", __FILE__, __LINE__, __FUNCTION__, account_.c_str());
		m_pClient->reqAccountUpdates(true, account_);  // trigger updateAccountValue()
	}

	void IBBrokerage::requestOpenOrders() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Requesting open orders.\n", __FILE__, __LINE__, __FUNCTION__);
		m_pClient->reqOpenOrders();
	}

	void IBBrokerage::modifyOrder_SameT(uint64_t oid, double price, int quantity) {
		std::shared_ptr<Order> po = OrderManager::instance().retrieveOrder(oid);
		po->orderSize = quantity;
		po->limitPrice = price;

		placeOrder(po);
	}

	/*void IBBrokerage::exerciseOptions(TickerId id, const Contract &contract,
	int exerciseAction, int exerciseQuantity, const IBString &account,
	int override) {}*/

	// End of Brokerage part
	//********************************************************************************************//

	//********************************************************************************************//
	// Market data part
	bool IBBrokerage::connectToMarketDataFeed() {
		_mkstate = MK_CONNECT;
		return true;
	}

	void IBBrokerage::disconnectFromMarketDataFeed() {
		_mkstate = MK_DISCONNECTED;
	}

	bool IBBrokerage::isConnectedToMarketDataFeed() const {
		return m_pClient->isConnected();
	}

	void IBBrokerage::processMarketMessages()
	{
		if (!marketdatafeed::heatbeat(5)) {
			disconnectFromMarketDataFeed();
			return;
		}
		switch (_mkstate) {
		case MK_ACCOUNT:
			if (_bkstate == BK_READYTOORDER)			// wait for brokerage initialization
				requestMarketDataAccountInformation(CConfig::instance().account);
			break;
		case MK_ACCOUNTACK:
			break;
		case MK_REQCONTRACT:
			requestContractDetails();
			break;
		case MK_REQCONTRACT_ACK:
			break;
			//case MK_REQHISTBAR:
			//  requestHistData();
			//  break;
		case MK_REQREALTIMEDATA:
			if (_mode == TICKBAR) {
				subscribeMarketData();
			}
			else if (_mode == DEPTH) {
				subscribeMarketDepth();
			}
			break;
		case MK_REQREALTIMEDATAACK:
			break;
		case MK_STOP:
			disconnectFromMarketDataFeed();
			break;
		}
	}

	void IBBrokerage::subscribeMarketData() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Subscribing to market data.\n", __FILE__, __LINE__, __FUNCTION__);
		// 236 - shortable; 256 - inventory[error(x)]
		//static const char* gt = "100,101,104,106,165,221,225,233,236,258,411";
		static const char* gt =
			"100,101,104,105,106,107,165,221,225,233,236,258,293,294,295,318,411";
		TagValueListSPtr mktDataOptions;

		int i = 0;
		for (auto it = CConfig::instance().securities.begin(); it != CConfig::instance().securities.end(); ++it)
		{
			Contract c;
			SecurityFullNameToContract(*it, c);
			PRINT_TO_FILE("INFO:[%s,%d][%s]subscribe to %s(%d)\n", __FILE__, __LINE__, __FUNCTION__, c.localSymbol.c_str(), c.conId);
			m_pClient->reqMktData(i, c, gt, false, mktDataOptions);
			m_pClient->reqRealTimeBars(BARREQUESTSTARTINGPOINT + i, c, 5, "TRADES", true, mktDataOptions);
			i++;
		}

		_mkstate = MK_REQREALTIMEDATAACK;

		//ReqMkDepth();
	}

	void IBBrokerage::unsubscribeMarketData(TickerId reqId) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Cancel market data %d.\n", __FILE__, __LINE__, __FUNCTION__, reqId);
		m_pClient->cancelMktData(reqId);
	}

	/*TWS currently limits users to a maximum of 3 distinct market depth requests.
	This same restriction applies to API clients, however API clients may make
	multiple market depth requests for the same security.*/
	void IBBrokerage::subscribeMarketDepth() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Subscribing to market depth.\n", __FILE__, __LINE__, __FUNCTION__);

		static const int IBLIMITMKDEPTHNUM = 3;
		TagValueListSPtr mktDataOptions;

		int i = 0;
		for (auto it = CConfig::instance().securities.begin(); it != CConfig::instance().securities.end(); ++it) {
			Contract c;
			SecurityFullNameToContract(*it, c);
			c.exchange = "ISLAND";

			PRINT_TO_FILE("INFO:[%s,%d][%s]Market depth subscribed to contract %s, %s.\n", __FILE__, __LINE__, __FUNCTION__, c.symbol.c_str(), c.exchange.c_str());
			m_pClient->reqMktDepth(i + 1000, c, 10, mktDataOptions);

			if (i >= IBLIMITMKDEPTHNUM)
				break;
		}
		_mkstate = MK_REQREALTIMEDATAACK;
	}

	void IBBrokerage::unsubscribeMarketDepth(TickerId reqId) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Cancel market depth %ld.\n", __FILE__, __LINE__, __FUNCTION__, reqId);

		m_pClient->cancelMktDepth(reqId);
	}

	void IBBrokerage::subscribeRealTimeBars(TickerId id, const Security& security, int barSize, const string& whatToShow, bool useRTH) {}
	void IBBrokerage::unsubscribeRealTimeBars(TickerId tickerId) {}
	void IBBrokerage::requestContractDetails()
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Requesting contract details.\n", __FILE__, __LINE__, __FUNCTION__);

		IBOfficial::Contract c;
		SecurityFullNameToContract("SPY STK SMART", c);
		m_pClient->reqContractDetails(0, c);

		if (_mkstate < MK_REQCONTRACT_ACK) {
			_mkstate = MK_REQCONTRACT_ACK;
		}
	}

	// enddate in "yyyyMMdd HH:mm:ss"
	// duration in seconds
	// barsize in seconds
	// useRTH = "0" or "1"
	std::vector<string> histreqeuests_;				// store symbol
	void IBBrokerage::requestHistoricalData(string fullsymbol, string enddate, string duration, string barsize, string useRTH) {
		int date_format = 1;	// 1: yyyymmdd{space}{space}hh:mm:dd  // 2 long integer specifying the number of seconds since 1/1/1970 GM	
		IBOfficial::Contract contract;
		SecurityFullNameToContract(fullsymbol, contract);

		if (fullsymbol.find("STK") != string::npos)
			contract.includeExpired = false;
		else
			contract.includeExpired = true;

		int useRegularTradingHour = useRTH == "1" ? 1 : 0;

		int interval = std::stoi(barsize);
		string barSize_;
		switch (interval)
		{
		case 1:
			barSize_ = "1 secs";		// not 1 sec
			break;
		case 5:
			barSize_ = "5 secs";
			break;
		case 15:
			barSize_ = "15 secs";
			break;
		case 30:
			barSize_ = "30 secs";
			break;
		case 60:
			barSize_ = "1 min";
			break;
		case 120:
			barSize_ = "2 mins";
			break;
		case 180:
			barSize_ = "3 mins";
			break;
		case 300:
			barSize_ = "5 mins";
			break;
		case 900:
			barSize_ = "15 mins";
			break;
		case 1800:
			barSize_ = "30 mins";
			break;
		case 3600:
			barSize_ = "1 hour";
			break;
		case 86400:
			barSize_ = "1 day";
			break;
		default:
			barSize_ = "1 secs";
			break;
		}

		string durationString_ = duration + " S";			// currently only consider intraday bar, so duration <= 1day
		histreqeuests_.push_back(fullsymbol);
		IBOfficial::TagValueListSPtr charOptions_;
		m_pClient->reqHistoricalData(histreqeuests_.size() - 1, contract, enddate, durationString_, barSize_,
			"TRADES", useRegularTradingHour, date_format, charOptions_);
	}

	// See requestBrokerageAccountInformation()
	void IBBrokerage::requestMarketDataAccountInformation(const string& account) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Requesting market data account info.\n", __FILE__, __LINE__, __FUNCTION__);

		m_pClient->reqAccountUpdates(true, account);		// it doesn't trigger updatePortfolio if no position
		if (_mkstate < MK_REQCONTRACT) {		// if _mkstate < MK_ACCOUNTACK
			_mkstate = MK_REQCONTRACT;
		}
	}
	// End of Market data
	//********************************************************************************************//

	//********************************************************************************************//
	// events from EWrapper
	void IBBrokerage::tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {
		Tick k;
		k.fullsymbol_ = CConfig::instance().securities[tickerId];
		k.price_ = price;
		k.size_ = 0;			// TODO: use actual size

		time_t current_time;
		time(&current_time);
		k.time_ = tointtime(current_time);

		if (field == TickType::LAST)
		{
			k.datatype_ = DataType::DT_TradePrice;
		}
		else if (field == TickType::BID)
		{
			k.datatype_ = DataType::DT_BidPrice;
		}
		else if (field == TickType::ASK)
		{
			k.datatype_ = DataType::DT_AskPrice;
		}
		else
		{
			return;
		}

		marketdatafeed::msgq_pub_->sendmsg(k.serialize());
	}

	void IBBrokerage::tickSize(TickerId tickerId, TickType field, int size) {
		Tick k;
		k.fullsymbol_ = CConfig::instance().securities[tickerId];
		k.price_ = 0;
		k.size_ = size;

		time_t current_time;
		time(&current_time);
		k.time_ = tointtime(current_time);

		if (field == TickType::LAST_SIZE)
		{
			k.datatype_ = DataType::DT_TradeSize;
		}
		else if (field == TickType::BID_SIZE)
		{
			k.datatype_ = DataType::DT_BidSize;
		}
		else if (field == TickType::ASK_SIZE)
		{
			k.datatype_ = DataType::DT_AskSize;
		}
		else
		{
			return;
		}

		marketdatafeed::msgq_pub_->sendmsg(k.serialize());
	}

	///https://www.interactivebrokers.com/en/software/api/apiguide/java/orderstatus.htm
	// Note that TWS orders have a fixed clientId and orderId of 0 that distinguishes them from API orders.
	void IBBrokerage::orderStatus(OrderId orderId, const IBString &status, int filled,
		int remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const IBString& whyHeld)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Order status, oid = %ld.\n", __FILE__, __LINE__, __FUNCTION__, orderId);

		if (status == "Cancelled") {
			OrderManager::instance().gotCancel(orderId);
			sendOrderCancelled(orderId);
		}
	}

	void IBBrokerage::openOrder(OrderId oid, const Contract& contract,
		const IBOfficial::Order& order, const OrderState& ostat)
	{
		// Will be called at connection
		if (ostat.warningText.empty())
		{
			PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Open orders, oid = %lu, status=%s.\n", __FILE__, __LINE__, __FUNCTION__, oid, ostat.status.c_str());
		}
		else
		{
			PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Open orders, oid = %lu, status=%s, warning=%s.\n", __FILE__, __LINE__, __FUNCTION__, oid, ostat.status.c_str(), ostat.warningText.c_str());
			sendGeneralMessage(ostat.warningText);
		}

		if (ostat.status != "Submitted" && ostat.status != "Filled" && ostat.status != "PreSubmitted")
		{
			// igore other states
			return;
		}
		else
		{
			OrderManager::instance().gotOrder(oid);
			sendOrderAcknowledged(oid);
		}
	}

	void IBBrokerage::openOrderEnd()
	{
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Open orders end.\n", __FILE__, __LINE__, __FUNCTION__);
	}

	void IBBrokerage::updateAccountValue(const IBString& key, const IBString& val,
		const IBString& currency, const IBString& accountName)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Update account value: %s,%s,%s,%s.\n", __FILE__, __LINE__, __FUNCTION__, key.c_str(), val.c_str(), currency.c_str(), accountName.c_str());
		PortfolioManager::instance()._account.setvalue(key, val, currency);
	}

	// triggered by reqAccountUpdate(true, null) called in Start()
	void IBBrokerage::updatePortfolio(const Contract& contract, int position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Update portfolio: %s,%d,%3.f\n", __FILE__, __LINE__, __FUNCTION__, contract.localSymbol.c_str(), position, averageCost);

		//Note: after closing position, position is 0 
		//Don't send message when position is 0
		string symbol;
		ContractToSecurityFullName(symbol, contract);
		if (position != 0) {
			sendOpenPositionMessage(symbol, position, averageCost, unrealizedPNL, realizedPNL);
		}

		if (_mkstate < MK_REQCONTRACT) {
			_mkstate = MK_REQCONTRACT;
		}
	}

	void IBBrokerage::nextValidId(IBOfficial::OrderId orderid)
	{
		//if (orderid >= m_orderId) {		// TODO: it seems ib is connected twice
		if (orderid > m_orderId) {
			PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]client id=%d next_valid_order_id = %ld\n", __FILE__, __LINE__, __FUNCTION__, m_pClient->clientId(), orderid);
			m_orderId = orderid;
			_bkstate = BK_READYTOORDER;
		}
	}

	void IBBrokerage::contractDetails(int reqId, const ContractDetails& contractDetails)
	{
		if (_mkstate < MK_REQREALTIMEDATA) {
			_mkstate = MK_REQREALTIMEDATA;
		}
		PRINT_TO_FILE("INFO:[%s,%d][%s]reqid=%d, symbol=%s\n", __FILE__, __LINE__, __FUNCTION__, reqId, contractDetails.longName.c_str());
	}

	void IBBrokerage::contractDetailsEnd(int reqId)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Contract details end. reqid=%d\n", __FILE__, __LINE__, __FUNCTION__, reqId);
	}

	void IBBrokerage::execDetails(int reqId, const Contract& contract, const Execution& execution)
	{
		PRINT_TO_FILE("INFO:[%s,%d][%s]Execution (Fill) details. reqid=%d.\n", __FILE__, __LINE__, __FUNCTION__, reqId);

		time_t current_time;
		time(&current_time);

		Fill t;
		ContractToSecurityFullName(t.fullSymbol, contract);
		t.tradetime = tointtime(current_time);
		t.tradeId = execution.orderId;
		t.tradePrice = execution.price;
		t.tradeSize = (execution.side == "BOT" ? 1 : -1)*execution.shares;
		OrderManager::instance().gotFill(t);
		sendOrderFilled(t);		// BOT SLD
	}

	//Error Code: https://www.interactivebrokers.com/en/software/api/apiguide/tables/api_message_codes.htm
	void IBBrokerage::error(const int id, const int errorCode, const IBString errorString) {
		PRINT_TO_FILE("ERROR:[%s,%d][%s]id=%d,eCode=%d,msg:%s.\n", __FILE__, __LINE__, __FUNCTION__, id, errorCode, errorString.c_str());
		sendGeneralMessage(to_string(id) + SERIALIZATION_SEPARATOR + to_string(errorCode) + SERIALIZATION_SEPARATOR + errorString);

		/*if (errorCode == 202)			// order cancelled, moved to order status callback
		{
		OrderManager::instance().gotCancel(id);
		sendOrderCancelled(id);
		}*/
		if (id == -1 && errorCode == 1100) { // if "Connectivity between IB and TWS has been lost"
			disconnectFromBrokerage();
			disconnectFromMarketDataFeed();
		}
		else if (errorCode == 326) {
			PRINT_TO_FILE("ERROR:[%s,%d][%s]ClientId duplicated! bump up clientID and reconnect!!. Error=%s\n", __FILE__, __LINE__, __FUNCTION__, errorString.c_str());
			disconnectFromBrokerage();
			disconnectFromMarketDataFeed();
			connectToBrokerage();		// reconnect. TODO: should increase ib_client_id ?
			connectToMarketDataFeed();
			//exit(0);
		}
	}

	// TODO postion = depth
	void IBBrokerage::updateMktDepth(TickerId id, int position, int operation, int side, double price, int size) {
		const char* sidestr = (side == 1) ? "BID_PRICE" : "ASK_PRICE";	 // side 0 for ask, 1 for bid
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Update market depth: %s %d %s %d %.3f %d\n", __FILE__, __LINE__, __FUNCTION__,
			CConfig::instance().securities[id - 1000].c_str(), operation, sidestr, position, price, size);
	}

	// TODO postion = depth
	void IBBrokerage::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
		int side, double price, int size) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Update market depth L2.\n", __FILE__, __LINE__, __FUNCTION__);

		const char* sidestr = (side == 1) ? "BID_PRICE" : "ASK_PRICE";	 // side 0 for ask, 1 for bid
		printf("%s %d %s %d %.3f %d\n",
			CConfig::instance().securities[id - 1000].c_str(),
			operation, sidestr, position, price, size);
	}

	// triggered by EClientSocket::reqManagedAccts
	// feed in upon connection
	void IBBrokerage::managedAccounts(const IBString& accountsList) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]client_id=%d,the managed account is:%s.\n", __FILE__, __LINE__, __FUNCTION__, m_pClient->clientId(), accountsList.c_str());

		if (CConfig::instance().account != accountsList) {
			printf("ERROR:Config account %s does not match IB account %s!\n",
				CConfig::instance().account.c_str(), accountsList.c_str());
			disconnectFromBrokerage();
			gShutdown = true;
			//exit(1);
		}
	}

	// Intra-day bar sizes are relayed back in Local Time Zone, daily bar sizes and greater are relayed back in Exchange Time Zone.
	void IBBrokerage::historicalData(TickerId reqId, const IBString& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps) {
		try {
			string symbol = histreqeuests_[reqId];
			sendHistoricalBarMessage(symbol, date, open, high, low, close, volume, barCount, WAP);
		}
		catch (...) {
			sendGeneralMessage("Historical Data Error");
		}
	}

	void IBBrokerage::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count) {
		string symbol;
		uint64_t index = reqId - BARREQUESTSTARTINGPOINT;
		if (reqId >= BARREQUESTSTARTINGPOINT) {
			symbol = CConfig::instance().securities[index];
		}
		else {
			return;
		}

		PRINT_TO_FILE("INFO:[%s,%d][%s]%s:%.2f:%.2f:%.2f:%.2f:%.2f:%ld.\n", __FILE__, __LINE__, __FUNCTION__,
			symbol.c_str(), open, high, low, close, wap, volume);
	}
	// end of events from EWrapper
	//********************************************************************************************//

	//********************************************************************************************//
	// auxilliary functions
	//********************************************************************************************//
	// symbol sectype exchange right multiplier
	void IBBrokerage::SecurityFullNameToContract(const std::string& symbol, Contract& c)
	{
		vector<string> v = stringsplit(symbol, ' ');

		c.localSymbol = v[0];
		c.secType = v[1];
		c.exchange = v[2];
		c.currency = "USD";

		if (v.size() == 4)
		{
			c.multiplier = v[3];
		}
	}

	void IBBrokerage::ContractToSecurityFullName(std::string& symbol, const Contract& c)
	{
		char sym[128] = {};
		if ((c.multiplier == "1") || (c.multiplier == ""))
			//sprintf(sym, "%s %s %s", c.localSymbol.c_str(), c.secType.c_str(), c.exchange.c_str());
			sprintf(sym, "%s %s SMART", c.localSymbol.c_str(), c.secType.c_str());
		else
			//sprintf(sym, "%s %s %s %s", c.localSymbol.c_str(), c.secType.c_str(), c.exchange.c_str(), c.multiplier.c_str());
			sprintf(sym, "%s %s %s %s", c.localSymbol.c_str(), c.secType.c_str(), c.exchange.c_str(), c.multiplier.c_str());

		symbol = sym;
	}

	void IBBrokerage::OrderToIBOfficialOrder(std::shared_ptr<Order> o, IBOfficial::Order& oib)
	{
		oib.auxPrice = o->trailPrice != 0 ? (double)o->trailPrice : (double)o->stopPrice;
		oib.lmtPrice = (double)o->limitPrice;

		// Only MKT, LMT, STP, and STP LMT, TRAIL, TRAIL LIMIT are supported
		oib.orderType = o->orderType;

		oib.totalQuantity = std::abs(o->orderSize);
		oib.action = o->orderSize > 0 ? "BUY" : "SELL";         // SSHORT not supported here

		oib.tif = o->timeInForce;
		oib.outsideRth = true;
		//order.OrderId = (int)o.id;
		oib.transmit = true;

		oib.account = o->account.empty() ? CConfig::instance().account : o->account;
		// Set up IB order Id
		oib.orderId = o->orderId;
	}
	// end of auxilliary functions
	//********************************************************************************************//
}