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
				request_stream << "GET /api/v1/ticker.do?symbol=btc_usd HTTP/1.1\r\n";
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
			catch (std::exception& e) {
				std::cout << "Exception: " << e.what() << "\n";
			}

			msleep(1000);
		}
	}
}