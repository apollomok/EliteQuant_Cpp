#ifndef _EliteQuant_Brokers_IBBrokerage_H_
#define _EliteQuant_Brokers_IBBrokerage_H_
#ifdef _NOT_DEFINED_ALWAYS_USE_LINUX
// Windows
#include <Brokers/IB/OfficialWindows/EWrapper.h>
#include <Brokers/IB/OfficialWindows/EPosixClientSocket.h>
#include <Brokers/IB/OfficialWindows/EPosixClientSocketPlatform.h>
#include <Brokers/IB/OfficialWindows/Contract.h>
#include <Brokers/IB/OfficialWindows/Order.h>
#include <Brokers/IB/OfficialWindows/Execution.h>
#include <Brokers/IB/OfficialWindows/OrderState.h>
#else
#include <Brokers/IB/OfficialLinux/EWrapper.h>
#include <Brokers/IB/OfficialLinux/EPosixClientSocket.h>
#include <Brokers/IB/OfficialLinux/EPosixClientSocketPlatform.h>
#include <Brokers/IB/OfficialLinux/Contract.h>
#include <Brokers/IB/OfficialLinux/Order.h>
#include <Brokers/IB/OfficialLinux/Execution.h>
#include <Brokers/IB/OfficialLinux/OrderState.h>
#endif

#include <Common/config.h>
#include <Common/Brokerage/brokerage.h>
#include <Common/Data/marketdatafeed.h>
#include <mutex>
#include <string>
#include <memory>

using std::mutex;
using std::string;
using std::list;
using std::vector;
using namespace IBOfficial;

namespace EliteQuant
{
	class IBOfficial::EPosixClientSocket;
	class brokerage;
	class marketdatafeed;
	class IBBrokerage : public IBOfficial::EWrapper, public brokerage, public marketdatafeed
	{
	public:
		IBBrokerage();
		~IBBrokerage();
		int _nServerVersion;

	public: 
		// outgoing
		//********************************************************************************//
		// brokerate part
		virtual void processBrokerageMessages();
		// let brokerage depend on marketdatafeed, that is
		// brokerage doesn't really connect; it relays to marekt data
		virtual bool connectToBrokerage();
		virtual void disconnectFromBrokerage();
		virtual bool isConnectedToBrokerage() const;

		virtual void placeOrder(std::shared_ptr<Order> o);
		virtual void requestNextValidOrderID();

		// TODO: move them to OrderManagement; only cancelOrder is necessary
		virtual void cancelOrder(int oid);
		virtual void cancelOrders(const string& symbol);
		virtual void cancelAllOrders();

		//https://www.interactivebrokers.com/en/software/api/apiguide/java/reqaccountupdates.htm
		// subscribe = true
		virtual void requestBrokerageAccountInformation(const string& account_);
		virtual void requestOpenOrders();

		/*Modifying an Order
		To modify an order using the API, resubmit the order you want to modify using the same order
		id, but with the price or quantity modified as required. Only certain fields such as price or
		quantity can be altered using this method. If you want to change the order type or action, you
		will have to cancel the order and submit a new order.
		*/
		void modifyOrder_SameT(uint64_t oid, double price, int quantity);

		//https://www.interactivebrokers.com/en/software/api/apiguide/c/exerciseoptions.htm
		/*void exerciseOptions(TickerId id, const Contract &contract,
			int exerciseAction, int exerciseQuantity, const IBString &account,
			int override);*/

		// end of brokerage part
		//********************************************************************************//

		//********************************************************************************//
		// market data part
		virtual void processMarketMessages();
		virtual bool connectToMarketDataFeed();
		virtual void disconnectFromMarketDataFeed();
		virtual bool isConnectedToMarketDataFeed() const;

		virtual void subscribeMarketData();
		virtual void unsubscribeMarketData(TickerId reqId);
		virtual void subscribeMarketDepth();
		virtual void unsubscribeMarketDepth(TickerId reqId);
		virtual void subscribeRealTimeBars(TickerId id, const Security& security, int barSize, const string& whatToShow, bool useRTH);
		virtual void unsubscribeRealTimeBars(TickerId tickerId);
		virtual void requestContractDetails();
		virtual void requestHistoricalData(string fullsymbol, string enddate, string duration, string barsize, string useRTH);
		virtual void requestMarketDataAccountInformation(const string& account);
		// end of market data part
		//********************************************************************************//

	public:
		// events from EWrapper
		void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
		void tickSize(TickerId tickerId, TickType field, int size);
		void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
			double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {}
		void tickGeneric(TickerId tickerId, TickType tickType, double value) {}
		void tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
		void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
			double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
		void orderStatus(OrderId orderId, const IBString &status, int filled,
			int remaining, double avgFillPrice, int permId, int parentId,
			double lastFillPrice, int clientId, const IBString& whyHeld);
		void openOrder(OrderId oid, const Contract& contract, const IBOfficial::Order& order, const OrderState& ostat);
		void openOrderEnd();
		void winError(const IBString &str, int lastError) {}
		void connectionClosed() {}
		void updateAccountValue(const IBString& key, const IBString& val,
			const IBString& currency, const IBString& accountName);
		void updatePortfolio(const Contract& contract, int position,
			double marketPrice, double marketValue, double averageCost,
			double unrealizedPNL, double realizedPNL, const IBString& accountName);
		void updateAccountTime(const IBString& timeStamp) {}
		void accountDownloadEnd(const IBString& accountName) {}
		void nextValidId(IBOfficial::OrderId orderId);
		void contractDetails(int reqId, const ContractDetails& contractDetails);
		void bondContractDetails(int reqId, const ContractDetails& contractDetails) {}
		void contractDetailsEnd(int reqId);
		void execDetails(int reqId, const Contract& contract, const Execution& execution);
		void execDetailsEnd(int reqId) {}
		void error(const int id, const int errorCode, const IBString errorString);
		void updateMktDepth(TickerId id, int position, int operation, int side,
			double price, int size);
		void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
			int side, double price, int size);
		void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
		void managedAccounts(const IBString& accountsList);
		void receiveFA(faDataType pFaDataType, const IBString& cxml) {}
		void historicalData(TickerId reqId, const IBString& date, double open, double high,
			double low, double close, int volume, int barCount, double WAP, int hasGaps);
		void scannerParameters(const IBString &xml) {}
		void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
			const IBString &distance, const IBString &benchmark, const IBString &projection,
			const IBString &legsStr) {}
		void scannerDataEnd(int reqId) {}
		void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
			long volume, double wap, int count);
		void currentTime(long time) {}
		void fundamentalData(TickerId reqId, const IBString& data) {}
		void deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
		void tickSnapshotEnd(int reqId) {}
		void marketDataType(TickerId reqId, int marketDataType) {}
		void commissionReport(const CommissionReport &commissionReport) {}
		void position(const IBString& account, const Contract& contract, int position, double avgCost) {}
		void positionEnd() {}
		void accountSummary(int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {}
		void accountSummaryEnd(int reqId) {}
		void verifyMessageAPI(const IBString& apiData) {}
		void verifyCompleted(bool isSuccessful, const IBString& errorText) {}
		void displayGroupList(int reqId, const IBString& groups) {}
		void displayGroupUpdated(int reqId, const IBString& contractInfo) {}

	private:
		std::unique_ptr<EPosixClientSocket> m_pClient;		// std::auto_ptr<EPosixClientSocket> m_pClient; or unique_ptr
		const int BARREQUESTSTARTINGPOINT = 1000;			// reqRealTimeBars request id starting point

		// ***********************************************************************************************
		// auxiliary functions
		// ***********************************************************************************************
		void SecurityFullNameToContract(const std::string& symbol, Contract& c);
		void ContractToSecurityFullName(std::string& symbol, const Contract& c);
		void OrderToIBOfficialOrder(std::shared_ptr<Order> o, IBOfficial::Order& oib);
	};
}

#endif // _EliteQuant_Brokers_IBBrokerage_H_
