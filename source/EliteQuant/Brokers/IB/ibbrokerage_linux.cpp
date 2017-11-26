#include <Brokers/IB/ibbrokerage.h>
#include <Brokers/IB/Official/EClientSocket.h>
#include <Brokers/IB/Official/EPosixClientSocketPlatform.h>

#include <Brokers/IB/Official/Contract.h>
#include <Brokers/IB/Official/Order.h>
#include <Brokers/IB/Official/OrderState.h>
#include <Brokers/IB/Official/Execution.h>
#include <Brokers/IB/Official/CommissionReport.h>
#include <Brokers/IB/Official/ScannerSubscription.h>
#include <Brokers/IB/Official/executioncondition.h>
#include <Brokers/IB/Official/PriceCondition.h>
#include <Brokers/IB/Official/MarginCondition.h>
#include <Brokers/IB/Official/PercentChangeCondition.h>
#include <Brokers/IB/Official/TimeCondition.h>
#include <Brokers/IB/Official/VolumeCondition.h>
#include <Brokers/IB/Official/CommonDefs.h>

#include <mutex>
#include <algorithm>
#include <Common/Data/datatype.h>
#include <Common/Data/datamanager.h>
#include <Common/Order/orderstatus.h>
#include <Common/Order/ordermanager.h>
#include <Common/Util/util.h>
#include <Common/Security/portfoliomanager.h>
#include <Common/Logger/log.h>
#include <Engine/Order/orderq.h>
#include <Engine/Interface/msgq.h>

using namespace std;
using namespace IBOfficial;

namespace EliteQuant
{
	extern std::atomic<bool> g_shutdown;

	IBBrokerage::IBBrokerage() :
        m_osSignal(2000),               //2-seconds timeout
		m_pClient(new EClientSocket(this, &m_osSignal)),
        m_pReader(0)
	{
	}
		
	IBBrokerage::~IBBrokerage()
	{
        if (m_pReader)
            delete m_pReader;
        
        delete m_pClient;
	}

	//********************************************************************************************//
	// Brokerage part
	void IBBrokerage::processBrokerageMessages()
	{
		if (!brokerage::periodic_heartbeat(5)) {
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
			Place_Monitor_Oder();
			break;
		case BK_PLACEORDER_ACK:
			break;
		case BK_CANCELORDER:
			cancelOrder(0); //TODO
			break;
		case BK_CANCELORDER_ACK:
			break;
		}
        
        m_pReader->checkClient();
        m_osSignal.waitForSignal();
        m_pReader->processMsgs();

		// from IB source code
        /*
		if (m_pClient->fd() > 0) {
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
		}*/
	}

	bool IBBrokerage::connectToBrokerage() {
		const char *host = "127.0.0.1";
		unsigned int port = CConfig::instance().IBPORT;
		int clientId = 0;

		TTPrint("[%s]Connecting to %s:%d clientId:%d\n", __FUNCTION__, host, port, clientId);
		bool bRes = m_pClient->eConnect(host, port, clientId);

		if (bRes) {
			TTPrint("Connected to ib brokerage %s:%d clientId:%d\n", host, port, clientId);
			_bkstate = BK_CONNECT;
            
            m_pReader = new EReader(m_pClient, &m_osSignal);
            m_pReader->start();
            
			//m_pClient->setServerLogLevel(5);			// can not work on m_pClient before a loop process
			if (clientId == 0) {
				//m_pClient->reqAutoOpenOrders(true);		// associate TWS with the client
			}
			//_nServerVersion = m_pClient->serverVersion();

			// trigger updatePortfolio()
			//m_pClient->reqAccountUpdates();
		}
		else {
			TTPrint("Cannot connect to %s:%d clientId:%d\n", host, port, clientId);
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
		TTPrint("[%s(%d)]TWS connection disconnected!\n", __FUNCTION__, __LINE__);
	}

	bool IBBrokerage::isConnectedToBrokerage() const
	{
		//TTPrint("[%s]Checking if connected to brokerage, status=%s\n", __FUNCTION__, m_pClient->isConnected() ? "connected" : "disconnected");
		return m_pClient->isConnected();
	}

	void IBBrokerage::placeOrder(std::shared_ptr<Order> o)
	{
		TTPrint("[%s]Place order, id = %ld\n", __FUNCTION__, (long)o->orderId);

		IBOfficial::Order oib;			// local stack
		Contract contract;				// local stack

		if (o->fullSymbol.empty())
		{
			TTPrintr("[%s]Order is not valid %ld\n", __FUNCTION__, (long)o->orderId);
			return;
		}

		if (o->orderId == 0)
		{
			TTPrintr("[%s]Order id is not valid %ld\n", __FUNCTION__, (long)o->orderId);
			return;
		}

		/*if (o->orderStatus != OrderStatus::OS_NewBorn)		// in order to enable replacement order
		{
			TTPrintr("[%s]Not a NewBorn order %ld\n", __FUNCTION__, (long)o->orderId);
			return;
		}*/

		SecurityFullNameToContract(o->fullSymbol, contract);
		OrderToIBOfficialOrder(o, oib);

		lock_guard<mutex> g(orderStatus_mtx);
		o->orderStatus = OrderStatus::OS_Submitted;
		m_pClient->placeOrder(o->orderId, contract, oib);

		brokerageMessageQ::instance().orderSubmitted(o->orderId);
	}

	void IBBrokerage::requestNextValidOrderID()
	{
		static int tmp = 1;
		TTPrint("[%s]Requesting next order id, reqId = %d\n", __FUNCTION__, tmp);
		if (_bkstate < BK_GETORDERIDACK)
			_bkstate = BK_GETORDERIDACK;
		if (m_orderId == -1)
			m_pClient->reqIds(tmp++);
	}

	//1.from web/distance too long/tws cancel?
	void IBBrokerage::cancelOrder(int oid) 
	{
		TTPrintr("[%s]Cancel Order %ld\n", __FUNCTION__, (long)m_orderId);
		m_pClient->cancelOrder(oid);
	}

	// cancel all orders for this symbol
	void IBBrokerage::cancelOrders(const string& symbol) 
	{
		vector<std::shared_ptr<Order>> v = OrderManager::instance().retrieveNonFilledOrderPtr(symbol);

		for (std::shared_ptr<Order> o: v) {
			m_pClient->cancelOrder(o->orderId);
			TTPrint("[%s]Cancel Order %ld\n", __FUNCTION__, o->orderId);	
		}
	}

	void IBBrokerage::cancelAllOrders() {}

	///https://www.interactivebrokers.com/en/software/api/apiguide/java/updateportfolio.htm
	void IBBrokerage::requestBrokerageAccountInformation(const string& account_)
	{
		TTPrint("[%s]Requesting brokerage account info: %s\n", __FUNCTION__, account_.c_str());
		m_pClient->reqAccountUpdates(true, account_);  // trigger updateAccountValue()
	}

	void IBBrokerage::requestOpenOrders() {
		TTPrint("[%s]Requesting open orders \n", __FUNCTION__);
		m_pClient->reqOpenOrders();
	}

	void IBBrokerage::modifyOrder_SameT(uint64_t oid, double price, int quantity) {
		std::shared_ptr<Order> po = OrderManager::instance().retrieveOrder(oid);
		po->orderSize = quantity;
		po->limitPrice = price;
		
		placeOrder(po);
	}

	/*void IBBrokerage::exerciseOptions(TickerId id, const Contract &contract,
		int exerciseAction, int exerciseQuantity, const std::string &account,
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
		//TTPrint("[%s]Checking if connected to market data feed, status=%s \n", __FUNCTION__, m_pClient->isConnected() ? "connected" : "disconnected");
		return m_pClient->isConnected();
	}

	void IBBrokerage::processMarketMessages()
	{
		if (!marketdatafeed::periodic_heartbeat(5)) {
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
		syncZeroPositionTOBJ();
	}

	/*2014-12-08 09:02:41.763 [mkdata::error]id=7,eCode=321,msg:Error validating request:-'vd' : cause - Incorrect
	generic tick list of 100,101,104,106,162,165,221,225,233,236,256,258,411.  Legal ones for (STK) are:
	100(Option Volume),101(Option Open Interest),105(Average Opt Volume),106(Option Implied Volatility),
	107(Close Implied Volatility),125(Bond analytic data),165(Misc. Stats),166(CScreen),225(Auction),
	232/221(Mark Price),233(RTVolume),236(inventory),258/47(Fundamentals),291(Close Implied Volatility),
	293(TradeCount),294(TradeRate),295(VolumeRate),318(LastRTHTrade),370(ParticipationMonitor),
	370(ParticipationMonitor),377(CttTickTag),377(CttTickTag),381(IB Rate),384(RfqTickRespTag),
	384(RfqTickRespTag),387(DMM),388(Issuer Fundamentals),391(IBWarrantImpVolCompeteTick),
	407(FuturesMargins),411(rthistvol),428(Monetary Close Price),439(MonitorTickTag),
	439(MonitorTickTag),456/59(IBDividends),459(RTCLOSE),460(Bond Factor Multiplier),
	499(Fee and Rebate Rate),506(midptiv),511(hvolrt10 (per-underlying)),
	512/104(hvolrt30 (per-underlying)),513(hvolrt50 (per-underlying)),
	514(hvolrt75 (per-underlying)),515(hvolrt100 (per-underlying)),
	516(hvolrt150 (per-underlying)),517(hvolrt200 (per-underlying))*/
	void IBBrokerage::subscribeMarketData() {
		TTPrint("[%s]Subscribing to market data \n", __FUNCTION__);
		// 236 - shortable; 256 - inventory[error(x)]
		//static const char* gt = "100,101,104,106,165,221,225,233,236,258,411";
		static const char* gt =
			"100,101,104,105,106,107,165,221,225,233,236,258,293,294,295,318,411";
		TagValueListSPtr mktDataOptions;
		//TTPrint("[%s]send req '%s' for %s(%d)\n", __FUNCTION__, gt.c_str(),contract.symbol.c_str(),contract.conId);
		int i = 0;
		for (auto it = CConfig::instance().securities.begin(); it != CConfig::instance().securities.end(); ++it)
		{
			Contract c;
			SecurityFullNameToContract(*it, c);
			m_pClient->reqMktData(i, c, gt, false, mktDataOptions);
			m_pClient->reqRealTimeBars(BARBASEINDEX + i, c, 5, "TRADES", true, mktDataOptions);
			i++;
		}

		/*
		for (i = OPTIONBASEINDEX;
		i < OPTIONBASEINDEX + sboard::R().getOptionSize(); ++i) {
		const Contract& c = sboard::R().getOptionContract(i - OPTIONBASEINDEX);
		m_pClient->reqMktData(i, c, gt, false);
		}*/

		_mkstate = MK_REQREALTIMEDATAACK;

		//ReqMkDepth();
	}

	void IBBrokerage::unsubscribeMarketData(TickerId reqId) {
		TTPrint("[%s]Cancel market data %d\n", __FUNCTION__, reqId);
		m_pClient->cancelMktData(reqId);
	}

	/*TWS currently limits users to a maximum of 3 distinct market depth requests.
	This same restriction applies to API clients, however API clients may make
	multiple market depth requests for the same security.*/
	void IBBrokerage::subscribeMarketDepth() {
		TTPrint("[%s]Subscribing to market depth \n", __FUNCTION__);

		static const int IBLIMITMKDEPTHNUM = 3;
		TagValueListSPtr mktDataOptions;

		int i = 0;
		for (auto it = CConfig::instance().securities.begin(); it != CConfig::instance().securities.end(); ++it) {
			Contract c;
			SecurityFullNameToContract(*it, c);
			c.exchange = "ISLAND";
			printf("[%s][%d]%s %s\n", __FUNCTION__, __LINE__, c.symbol.c_str(),
				c.exchange.c_str());
			m_pClient->reqMktDepth(i + 1000, c, 10, mktDataOptions);

			if (i >= IBLIMITMKDEPTHNUM)
				break;
		}
		_mkstate = MK_REQREALTIMEDATAACK;
	}

	void IBBrokerage::unsubscribeMarketDepth(TickerId reqId) {
		TTPrint("[%s]Cancel market depth %ld\n", __FUNCTION__, reqId);
		m_pClient->cancelMktDepth(reqId);
	}

	void IBBrokerage::subscribeRealTimeBars(TickerId id, const Security& security, int barSize, const string& whatToShow, bool useRTH) {}
	void IBBrokerage::unsubscribeRealTimeBars(TickerId tickerId) {}
	void IBBrokerage::requestContractDetails()
	{
		TTPrint("[%s]Requesting contract details\n", __FUNCTION__);
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
	void IBBrokerage::requestHistoricalData(string fullsymbol, string enddate, string duration, string barsize, string useRTH ) {
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
		TTPrint("[%s]Requesting market data account info \n", __FUNCTION__);
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

		DataManager::instance().sendmq(k.serialize());
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

		DataManager::instance().sendmq(k.serialize());
	}

	///https://www.interactivebrokers.com/en/software/api/apiguide/java/orderstatus.htm
	// Note that TWS orders have a fixed clientId and orderId of 0 that distinguishes them from API orders.
	void IBBrokerage::orderStatus(OrderId orderId, const std::string &status, double filled,
		double remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const std::string& whyHeld)
	{
		TTPrint("[%s]Order status, oid = %ld\n", __FUNCTION__, orderId);

		if (status == "Cancelled") {
			OrderManager::instance().gotCancel(orderId);
			brokerageMessageQ::instance().orderCancelled(orderId);
		}
	}

	void IBBrokerage::openOrder(OrderId oid, const IBOfficial::Contract& contract, 
		const IBOfficial::Order& order, const IBOfficial::OrderState& ostat)
	{
		// Will be called at connection
		if (ostat.warningText.empty())
		{
			TTPrintr("[%s](%d)%lu,%s\n", __FUNCTION__, __LINE__, oid, ostat.status.c_str());
		}
		else
		{
			TTPrintr("[%s](%d)%lu,%s,%s\n", __FUNCTION__, __LINE__, oid, ostat.status.c_str(), ostat.warningText.c_str());
			brokerageMessageQ::instance().generalMessage(ostat.warningText);
		}

		if (ostat.status != "Submitted" && ostat.status != "Filled" && ostat.status != "PreSubmitted")
		{
			// igore other states
			return;
		}
		else
		{
			OrderManager::instance().gotOrder(oid);
			brokerageMessageQ::instance().orderAcknowledged(oid);
		}
	}

	void IBBrokerage::openOrderEnd()
	{
		TTPrintr("[%s][%d]\n", __FUNCTION__, __LINE__);
	}

	void IBBrokerage::updateAccountValue(const std::string& key, const std::string& val,
		const std::string& currency, const std::string& accountName)
	{
		TTPrint("[%s]%s,%s,%s,%s\n", __FUNCTION__, key.c_str(), val.c_str(), currency.c_str(), accountName.c_str());
		PortfolioManager::instance()._account.setvalue(key, val, currency);
	}

	// triggered by reqAccountUpdate(true, null) called in Start()            
	void IBBrokerage::updatePortfolio(const Contract& contract, double position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const std::string& accountName)
	{
		TTPrint("[%s][%d]%s,%d,%3.f\n", __FUNCTION__, __LINE__, contract.localSymbol.c_str(), position, averageCost);

		//Note: after closing position, position is 0 
		//Don't send message when position is 0
		string symbol;
		ContractToSecurityFullName(symbol, contract);
		if (position != 0) {
			brokerageMessageQ::instance().openPositionMessage(symbol, position, averageCost, unrealizedPNL, realizedPNL);
		}

		if (_mkstate < MK_REQCONTRACT) {
			_mkstate = MK_REQCONTRACT;
		}
	}

	void IBBrokerage::nextValidId(IBOfficial::OrderId orderid)
	{
		if (orderid > m_orderId) {
			TTPrint("[client id=%d] next_valid_order_id = %ld\n", m_pClient->clientId(), orderid);
			printf("next valid order id = %ld\n", orderid);
			m_orderId = orderid;
			_bkstate = BK_READYTOORDER;
		}
	}

	void IBBrokerage::contractDetails(int reqId, const ContractDetails& contractDetails)
	{
		if (_mkstate < MK_REQREALTIMEDATA) {
			_mkstate = MK_REQREALTIMEDATA;
		}
		TTPrint("[%s]reqid=<%d>, symbol=%s\n", __FUNCTION__, reqId, contractDetails.longName.c_str());
	}

	void IBBrokerage::contractDetailsEnd(int reqId)
	{
		TTPrint("[%s]<%d>\n", __FUNCTION__, reqId);
	}

	void IBBrokerage::execDetails(int reqId, const Contract& contract, const Execution& execution)
	{
		TTPrint("[%s]Execution details \n", __FUNCTION__);
		time_t current_time;
		time(&current_time);

		Trade t;
		t.tradetime = tointtime(current_time);
		t.tradeId = execution.orderId;
		t.tradePrice = execution.price;
		t.tradeSize = (execution.side == "BOT" ? 1 : -1)*execution.shares;
		OrderManager::instance().gotFill(t);
		brokerageMessageQ::instance().orderFilled(t);		// BOT SLD
	}

	//Error Code: https://www.interactivebrokers.com/en/software/api/apiguide/tables/api_message_codes.htm
	void IBBrokerage::error(const int id, const int errorCode, const std::string errorString) {
		TTPrint("[%s]id=%d,eCode=%d,msg:%s\n", __FUNCTION__, id, errorCode, errorString.c_str());
		brokerageMessageQ::instance().generalMessage(to_string(id) + SERIALIZATION_SEPARATOR + to_string(errorCode) + SERIALIZATION_SEPARATOR + errorString);

		/*if (errorCode == 202)			// order cancelled, moved to order status callback
		{
			OrderManager::instance().gotCancel(id);
			brokerageMessageQ::instance().orderCancelled(id);
		}*/
		if (id == -1 && errorCode == 1100) { // if "Connectivity between IB and TWS has been lost"
			disconnectFromBrokerage();
			disconnectFromMarketDataFeed();
		}
		else if (errorCode == 326) {
			TTPrint("[%s(%d)]ClientId duplicated! bump up clientID and reconnect!!\n", __FUNCTION__, __LINE__);
			disconnectFromBrokerage();
			disconnectFromMarketDataFeed();
			connectToBrokerage();		// reconnect. TODO: should increase IB_CLIENT_ID ?
			connectToMarketDataFeed();
			//exit(0);
		}
	}

	// TODO postion = depth
	void IBBrokerage::updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size) {
		TTPrint("[%s]\n", __FUNCTION__);
		const char* sidestr = (side == 1) ? "BID_PRICE" : "ASK_PRICE";	 // side 0 for ask, 1 for bid
		printf("%s %d %s %d %.3f %d\n",
			CConfig::instance().securities[id - 1000].c_str(),
			operation, sidestr, position, price, size);
	}

	// TODO postion = depth
	void IBBrokerage::updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
		int side, double price, int size) {
		TTPrint("[%s]\n", __FUNCTION__);
		const char* sidestr = (side == 1) ? "BID_PRICE" : "ASK_PRICE";	 // side 0 for ask, 1 for bid
		printf("%s %d %s %d %.3f %d\n",
			CConfig::instance().securities[id - 1000].c_str(),
			operation, sidestr, position, price, size);
	}

	// triggered by EClientSocket::reqManagedAccts
	// feed in upon connection
	void IBBrokerage::managedAccounts(const std::string& accountsList) {
		TTPrint("[%s]client_id=%d,the managed account is:[%s]\n",
			__FUNCTION__, m_pClient->clientId(), accountsList.c_str());
		if (CConfig::instance().account != accountsList) {
			printf("ERROR:Config account %s does not match IB account %s!\n",
				CConfig::instance().account.c_str(), accountsList.c_str());
			disconnectFromBrokerage();
			g_shutdown = true;
			//exit(1);
		}
	}

	// Intra-day bar sizes are relayed back in Local Time Zone, daily bar sizes and greater are relayed back in Exchange Time Zone.
	void IBBrokerage::historicalData(TickerId reqId, const std::string& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps) {
		try {
			string symbol = histreqeuests_[reqId];
			brokerageMessageQ::instance().historicalBarMessage(symbol, date, open, high, low, close, volume, barCount, WAP);
		}
		catch (...) {
			brokerageMessageQ::instance().generalMessage("Historical Data Error");
		}
	}

	void IBBrokerage::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count) {
		string symbol;
		uint64_t index = reqId - BARBASEINDEX;
		if (reqId >= BARBASEINDEX) {
			symbol = CConfig::instance().securities[index];
		}
		else {
			return;
		}

		printf("%s:%.2f:%.2f:%.2f:%.2f:%.2f:%ld\n", symbol.c_str(), open, high, low, close, wap,
			volume);
	}
	// end of events from EWrapper
	//********************************************************************************************//

	//********************************************************************************************//
	// auxilliary functions
	//********************************************************************************************//
	// symbol sectype exchange right multiplier
	void IBBrokerage::SecurityFullNameToContract(const std::string& symbol, Contract& c)
	{
		vector<string> v = splitv2(symbol, ' ');

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
		if (c.multiplier == "1")
			sprintf(sym, "%s %s %s", c.localSymbol.c_str(), c.secType.c_str(), c.exchange.c_str());
		else
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

