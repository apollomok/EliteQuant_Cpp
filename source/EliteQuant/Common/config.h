#ifndef __EliteQuant_Common_Config__
#define __EliteQuant_Common_Config__

#include <inttypes.h>
#include <cmath>
#include <mutex>
#include <atomic>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <list>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <cereal/include/cereal/types/unordered_map.hpp>
#include <cereal/include/cereal/types/memory.hpp>
#include <cereal/include/cereal/archives/json.hpp>
#include <cereal/include/cereal/types/vector.hpp>
#include <cereal/include/cereal/types/string.hpp>
#include <cereal/include/cereal/types/map.hpp>
#include <Common/Logger/logger.h>

#if defined(_WIN32) || defined(_WIN64)
#ifdef DLL_EXPORT
#define DLL_EXPORT_IMPORT  __declspec(dllexport)   // export DLL information
#else
#define DLL_EXPORT_IMPORT  __declspec(dllimport)   // import DLL information
#endif
#else
#define DLL_EXPORT_IMPORT
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include<WinSock2.h>
#else
#include <unistd.h>
#endif

using std::vector;
using std::string;
using std::set;
using std::mutex;
using std::map;
using std::atomic_int;

//http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

namespace EliteQuant {

#define SERIALIZATION_SEPARATOR '|'

#define PRINT_TO_FILE logger::instance().Printf2File

#define PRINT_TO__CONSOLE(...) do{\
printf("%s ",ymdhmsf().c_str());printf(__VA_ARGS__);\
}while (0)

#define PRINT_TO_FILE_AND_CONSOLE(...) do{\
logger::instance().Printf2File(__VA_ARGS__);\
printf("%s ",ymdhmsf().c_str());printf(__VA_ARGS__);\
}while (0)

#define PRINT_SHUTDOWN_MESSAGE printf("\n Thank you for using EliteQuant http://www.elitequant.com. Goodbye! \n");

	enum class RUN_MODE :uint8_t {
		TRADE_MODE = 0, RECORD_MODE, REPLAY_MODE
	};

	enum class BROKERS : uint8_t {
		IB = 0, CTP, GOOGLE, SINA, PAPER
	};

	enum class MSGQ : uint8_t {
		NANOMSG = 0, ZMQ, KAFKA, WEBSOCKET
	};

	enum class MSGQ_PROTOCOL : uint8_t {
		PAIR = 0, REQ, REP, PUB, SUB, PIPELINE
	};

	class CConfig {
		static CConfig* pinstance_;
		static mutex instancelock_;

		CConfig();
	public:
		RUN_MODE _mode = RUN_MODE::TRADE_MODE;
		BROKERS _broker = BROKERS::IB;
		MSGQ _msgq = MSGQ::NANOMSG;

		static CConfig& instance();

		void readConfig();

		string _config_dir;
		string _log_dir;
		string _data_dir;
		string configDir();
		string logDir();
		string dataDir();

		/******************************************* Brokerage ***********************************************/
		// TODO: move to brokerage
		string ib_host = "127.0.0.1";
		uint64_t ib_port = 7496;
		atomic_int ib_client_id;

		string account = "DU448830";
		string filetoreplay = "";

		string ctp_broker_id = "";
		string ctp_user_id = "";
		string ctp_password = "";
		string ctp_auth_code = "";
		string ctp_user_prod_info = "";
		string ctp_data_address = "";
		string ctp_broker_address = "";

		vector<string> securities;
		/**************************************** End of Brokeragee ******************************************/

		/******************************************* Message Queue ***********************************************/
		string MKT_DATA_PUBSUB_PORT = "55555";				// market/tick data
		string BROKERAGE_PAIR_PORT = "55556";				// brokerage order, account, etc
		string BAR_AGGREGATOR_PUBSUB_PORT = "55557";		// bar from aggregation service
		string API_PORT = "55558";							// client port
		string API_ZMQ_DATA_PORT = "55559";					// client port
				
		string tick_msg = "k";
		string last_price_msg = "p";
		string last_size_msg = "z";
		string bar_msg = "b";
		string new_order_msg = "o";
		string cancel_order_msg = "c";
		string order_status_msg = "s";
		string fill_msg = "f";				// including partial fill
		string close_all_msg = "a";
		string position_msg = "n";
		string account_msg = "u";		// user
		string contract_msg = "r";
		string hist_msg = "h";
		string general_msg = "m";
		string test_msg = "e";		// echo

		/**************************************** End of Message Queue ******************************************/
	};
}

#endif	// __EliteQuant_Common_Config__
