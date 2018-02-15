#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/property_tree/json_parser.hpp>  
#include <boost/property_tree/ptree.hpp>  
#include <boost/algorithm/string/find.hpp>

#include "Poco/Net/HTMLForm.h"
#include "Poco/URI.h"  
#include "Poco/Net/HTTPClientSession.h"  
#include "Poco/Net/HTTPRequest.h"  
#include "Poco/Net/HTTPResponse.h"  
#include "Poco/StreamCopier.h"  
#include "Poco/Net/NetException.h"  

#include "Poco/JSON/Object.h"  
#include "Poco/JSON/Parser.h"  
#include "Poco/Dynamic/Var.h"  

#include "Poco/Net/HTTPSClientSession.h"  
#include "Poco/Net/Context.h"  
#include "Poco/Net/SSLException.h"  

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <mutex>

#include <Brokers/OkCoin/okcoindatafeed.h>
#include <Common/Util/util.h>
#include <Common/Order/orderstatus.h>
#include <Common/Logger/logger.h>
#include <Common/Data/datamanager.h>
#include <Common/Order/ordermanager.h>

class price_;
using namespace std;
using boost::asio::ip::tcp;


namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;

	okcoindatafeed::okcoindatafeed() {
	}

	okcoindatafeed::~okcoindatafeed() {
	}

	// start http request thread
	bool okcoindatafeed::connectToMarketDataFeed()
	{
		return true;
	}

	// stop http request thread
	void okcoindatafeed::disconnectFromMarketDataFeed() {
	}

	// is http request thread running ?
	bool okcoindatafeed::isConnectedToMarketDataFeed() const {
		return (!gShutdown);				// automatic disconnect when shutdown
	}

	void okcoindatafeed::processMarketMessages() {
		if (!heatbeat(5)) {
			disconnectFromMarketDataFeed();
			return;
		}

		switch (_mkstate) {
		case MK_ACCOUNT:
			requestMarketDataAccountInformation(CConfig::instance().account);
			break;
		case MK_REQREALTIMEDATA:
			subscribeMarketData();
			break;
		case MK_REQREALTIMEDATAACK:
			Thread_GetQuoteLoop();
			break;
		}
	}

	void okcoindatafeed::subscribeMarketData() {
		ostringstream os;
		//os << "/finance/info?q=" << "SPY,AAPL,VXX";
		for (auto &s : CConfig::instance().securities)
		{
			auto sv = stringsplit(s, ' ');
			if (sv[0].substr(0, 2) == "sh")
				os << sv[0] << ",";			// TODO: it ends with ","
		}
		//_path = "/list=" + os.str();  // hard code path for now
        
		_mkstate = MK_REQREALTIMEDATAACK;
	}

	void okcoindatafeed::unsubscribeMarketData(TickerId reqId) {
	}

	void okcoindatafeed::subscribeMarketDepth() {
	}

	void okcoindatafeed::unsubscribeMarketDepth(TickerId reqId) {
	}

	void okcoindatafeed::subscribeRealTimeBars(TickerId id, const Security& security, int barSize, const string& whatToShow, bool useRTH) {

	}

	void okcoindatafeed::unsubscribeRealTimeBars(TickerId tickerId) {

	}

	void okcoindatafeed::requestContractDetails() {
	}

	void okcoindatafeed::requestHistoricalData(string contract, string enddate, string duration, string barsize, string useRTH) {

	}

	void okcoindatafeed::requestMarketDataAccountInformation(const string& account)
	{
		if (_mkstate <= MK_REQREALTIMEDATA)
			_mkstate = MK_REQREALTIMEDATA;
	}

	////////////////////////////////////////////////////// worker function ///////////////////////////////////////
	void okcoindatafeed::Thread_GetQuoteLoop()
	{
		std::string res = "";

		while (!gShutdown) {
			try {
				Poco::URI purl("https://www.okcoin.com/api/v1/ticker.do?symbol=btc_usd");
				Poco::Net::Context::Ptr context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false);
				Poco::Net::HTTPSClientSession session(context);
				session.setHost(purl.getHost());
				session.setPort(purl.getPort());
				Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, purl.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);
				std::ostream& ostr = session.sendRequest(req);
				Poco::Net::HTTPResponse res;
				std::istream& istr = session.receiveResponse(res);

				std::string temp;
				Poco::StreamCopier::copyToString(istr, temp);
				
				std::istringstream iss;
				iss.str(temp);
				boost::property_tree::ptree parser;
				boost::property_tree::json_parser::read_json(iss, parser);
				boost::property_tree::ptree ticker = parser.get_child("ticker");
				/*
				# Request
					GET https ://www.okcoin.com/api/v1/ticker.do?symbol=ltc_usd
				# Response
				{
					"date":"1410431279",
					"ticker" : {
						"buy":"33.15",
						"high" : "34.15",
						"last" : "33.15",
						"low" : "32.05",
						"sell" : "33.16",
						"vol" : "10532696.39199642"
					}
				}
				date: 返回数据时服务器时间
				buy: 买一价
				high: 最高价
				last: 最新成交价
				low: 最低价
				sell: 卖一价
				vol: 成交量(最近的24小时)
				*/
				FullTick k;
				k.bidprice_L1_=ticker.get<double>("buy");
				k.askprice_L1_=ticker.get<double>("sell");
				//k.open_=ticker.get<double>("");
				k.high_=ticker.get<double>("high");
				k.low_=ticker.get<double>("low");
				k.price_= ticker.get<double>("last");
				//k.size_= ticker.get<double>("");
				//k.pre_close_=ticker.get<double>("");
				//k.time_=parser.get<int>("date");
				//k.lower_limit_price_=ticker.get<double>("");
				//k.upper_limit_price_=ticker.get<double>("");
				msgq_pub_->sendmsg(k.serialize());
				msleep(50);
					
			}
			catch (const Poco::Net::SSLException& e)
			{
				std::cerr << e.what() << ": " << e.message() << std::endl;
			}
			catch (std::exception& e) {
				std::cout << "Exception: " << e.what() << "\n";
			}

			msleep(1000);
		}
	}
}