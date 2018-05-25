#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/property_tree/json_parser.hpp>  
#include <boost/property_tree/ptree.hpp>  
#include <boost/algorithm/string/find.hpp>

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <mutex>

#include <Brokers/BtcChina/btcchinadatafeed.h>
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

	btcchinadatafeed::btcchinadatafeed() {
	}

	btcchinadatafeed::~btcchinadatafeed() {
	}

	// start http request thread
	bool btcchinadatafeed::connectToMarketDataFeed()
	{
		return true;
	}

	// stop http request thread
	void btcchinadatafeed::disconnectFromMarketDataFeed() {
	}

	// is http request thread running ?
	bool btcchinadatafeed::isConnectedToMarketDataFeed() const {
		return (!gShutdown);				// automatic disconnect when shutdown
	}

	void btcchinadatafeed::processMarketMessages() {
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

	void btcchinadatafeed::subscribeMarketData() {
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

	void btcchinadatafeed::unsubscribeMarketData(TickerId reqId) {
	}

	void btcchinadatafeed::subscribeMarketDepth() {
	}

	void btcchinadatafeed::unsubscribeMarketDepth(TickerId reqId) {
	}

	void btcchinadatafeed::subscribeRealTimeBars(TickerId id, const Security& security, int barSize, const string& whatToShow, bool useRTH) {

	}

	void btcchinadatafeed::unsubscribeRealTimeBars(TickerId tickerId) {

	}

	void btcchinadatafeed::requestContractDetails() {
	}

	void btcchinadatafeed::requestHistoricalData(string contract, string enddate, string duration, string barsize, string useRTH) {

	}

	void btcchinadatafeed::requestMarketDataAccountInformation(const string& account)
	{
		if (_mkstate <= MK_REQREALTIMEDATA)
			_mkstate = MK_REQREALTIMEDATA;
	}

	////////////////////////////////////////////////////// worker function ///////////////////////////////////////
	void btcchinadatafeed::Thread_GetQuoteLoop()
	{
		std::string res = "";

		while (!gShutdown) {
			try {
				boost::asio::io_service io_service;
				
				// Get a list of endpoints corresponding to the server name.
				tcp::resolver resolver(io_service);
				tcp::resolver::query query(_host, "http");
				tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
				tcp::resolver::iterator end;

				// Try each endpoint until we successfully establish a connection.
				tcp::socket socket(io_service);
				boost::system::error_code error = boost::asio::error::host_not_found;
				while (error && endpoint_iterator != end) {
					socket.close();
					socket.connect(*endpoint_iterator++, error);
				}

				if (error) { throw boost::system::system_error(error); }

				// Form the request. We specify the "Connection: close" header so that the server will close the socket 
				// after transmitting the response. This will allow us to treat all data up until the EOF as the content.
				boost::asio::streambuf request;
				std::ostream request_stream(&request);
				request_stream << "GET /data/pro/ticker?symbol=BTCUSD HTTP/1.1\r\n";
				request_stream << "Host: " << _host << "\r\n";
				request_stream << "Accept: */*\r\n";
				request_stream << "Connection: close\r\n\r\n";

				// Send the request.
				boost::asio::write(socket, request);

				// Read the response status line.
				boost::asio::streambuf response;
				boost::asio::read_until(socket, response, "\r\n");

				// Check that response is OK.
				std::istream response_stream(&response);

				std::string http_version;
				response_stream >> http_version;

				unsigned int status_code;
				response_stream >> status_code;

				std::string status_message;
				std::getline(response_stream, status_message);
				if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
					std::cout << "Invalid response\n";
				}
				if (status_code != 200) {
					std::cout << "Response returned with status code " << status_code << "\n";
				}

				// Read the response headers, which are terminated by a blank line.
				boost::asio::read_until(socket, response, "\r\n\r\n");

				// Write whatever content we already have to output.
				if (response.size() > 0) {
					std::ostringstream oss;
					oss << &response;
					res = oss.str();
				}
				
				//std::cout << res << std::endl;

				// Read until EOF, writing data to output as we go.
				while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
					//std::cout << &response; // don't want to print just return
					std::ostringstream oss;
					oss << &response;
					res += oss.str();
				}
				
				string result=res.substr(boost::algorithm::find_first(res, "\r\n\r\n").end()-res.begin());
				//std::cout << res << std::endl;

				if (error != boost::asio::error::eof) { throw boost::system::system_error(error); }

				std::istringstream iss;
				iss.str(result.c_str());
				boost::property_tree::ptree parser;
				boost::property_tree::json_parser::read_json(iss, parser);
				boost::property_tree::ptree ticker = parser.get_child("ticker");
				/*
				参数名				类型			描述
				BidPrice			Double			买价
				AskPrice			Double			卖价
				Open				Double			开盘价
				High				Double			最高价
				Low					Double			近24小时内最低价格
				Last				Double			最新成交价格
				LastQuantity		Double			最新成交数量
				PrevCls				Double			昨日收盘价
				Timestamp			UTCTimestamp	时间戳
				ExecutionLimitDown	Double			价格下限
				ExecutionLimitUp	Double			价格上限
				*/	
				FullTick k;
				k.bidprice_L1_=ticker.get<double>("BidPrice");
				k.askprice_L1_=ticker.get<double>("AskPrice");
				k.open_=ticker.get<double>("Open");
				k.high_=ticker.get<double>("High");
				k.low_=ticker.get<double>("Low");
				k.price_= ticker.get<double>("Last");
				k.size_= ticker.get<double>("LastQuantity");
				k.pre_close_=ticker.get<double>("PrevCls");
				k.time_=(int)(ticker.get<double>("Timestamp")/1000);
				k.lower_limit_price_=ticker.get<double>("ExecutionLimitDown");
				k.upper_limit_price_=ticker.get<double>("ExecutionLimitUp");
				msgq_pub_->sendmsg(k.serialize());
				msleep(50);
					
			}
			catch (std::exception& e) {
				std::cout << "Exception: " << e.what() << "\n";
			}

			msleep(1000);
		}
	}
}