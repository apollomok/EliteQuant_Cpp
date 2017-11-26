#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <thread>

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using boost::asio::ip::tcp;

typedef boost::gregorian::date Calendar;

bool g_shutdown = false;

void msleep(uint64_t _ms) {
	if (_ms == 0) { return; }
	this_thread::sleep_for(chrono::milliseconds(_ms));
}

void httpClient() {
	string host = "hq.sinajs.cn";
	string path = "/list=sh600006,sh600007,sh600009";
	std::string res = "";

	while (!g_shutdown) {
		try {
			boost::asio::io_service io_service;

			// Get a list of endpoints corresponding to the server name.
			tcp::resolver resolver(io_service);
			tcp::resolver::query query(host, "http");
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
			request_stream << "GET " << path << " HTTP/1.0\r\n";
			request_stream << "Host: " << host << "\r\n";
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

			//std::cout << res << std::endl;

			if (error != boost::asio::error::eof) { throw boost::system::system_error(error); }

			// split string
			std::vector<string> strs;
			boost::split(strs, res, boost::is_any_of("\n"));
			//cout << "* size of the vector: " << strs.size() << endl;
			for (size_t i = 0; i < strs.size(); i++)
				if (strs[i].find("var") != std::string::npos)
				{
					std::size_t pos1 = strs[i].find("_str_");
					std::size_t pos2 = strs[i].find("=");
					std::string symbol = strs[i].substr(pos1 + 5, pos2 - pos1 - 5);

					std::vector<string> str2;
					boost::split(str2, strs[i], boost::is_any_of(","));
					string price = str2[3];
					cout << "symbol = " << symbol << " price = " << price << endl;
				}
		}
		catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << "\n";
		}

		msleep(2000);
	}
}


int main(int argc, char* argv[]) {
	//std::cout << httpClient("download.finance.yahoo.com", "/d/quotes.csv?s=aapl,aig,msft,jpm,WFC,BAC,C,GS,USB,AXP,MS,MET,BK,PNC,PRU,SPG,AFL,TRV,COF,STT,ACE,BBT,CME,SCHW&f=sl1d1t1");
	std::thread liveQuote(httpClient);

	liveQuote.join();

	int i;
	cin >> i;
	if (i == 1)
	{
		g_shutdown = true;
	}

	std::cout << "liveQuote complete.\n";
	return 0;
}