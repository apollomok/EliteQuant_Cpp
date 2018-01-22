#include <fstream>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <Common/config.h>
//#include <Common/Util/util.h>
#include <yaml-cpp/yaml.h>

namespace bpt = boost::property_tree;
namespace bpo = boost::program_options;
namespace fs = boost::filesystem;

namespace EliteQuant {
	CConfig* CConfig::pinstance_ = nullptr;
	mutex CConfig::instancelock_;

	CConfig::CConfig() {
		readConfig();
	}

	CConfig& CConfig::instance() {
		if (pinstance_ == nullptr) {
			std::lock_guard<mutex> g(instancelock_);
			if (pinstance_ == nullptr) {
				pinstance_ = new CConfig();
			}
		}
		return *pinstance_;
	}

	void CConfig::readConfig()
	{
#ifdef _DEBUG
		std::printf("Current path is : %s\n", boost::filesystem::current_path().string().c_str());
#endif
		string path = boost::filesystem::current_path().string() + "/config_server.yaml";
		YAML::Node config = YAML::LoadFile(path);

		_config_dir = boost::filesystem::current_path().string();
		_log_dir = config["log_dir"].as<std::string>();
		_data_dir = config["data_dir"].as<std::string>();
		boost::filesystem::path log_path(logDir());
		boost::filesystem::create_directory(log_path);
		boost::filesystem::path data_path(dataDir());
		boost::filesystem::create_directory(data_path);


		const string msgq = config["msgq"].as<std::string>();
		if (msgq == "zmq")
			_msgq = MSGQ::ZMQ;
		else if (msgq == "kafka")
			_msgq = MSGQ::KAFKA;
		else
			_msgq = MSGQ::NANOMSG;
		
		// TODO: support multiple accounts; currently only the last account loop counts
		const std::vector<string> accounts = config["accounts"].as<std::vector<string>>();
		for (auto s : accounts) {
			const string api = config[s]["api"].as<std::string>();
			if (api == "IB") {
				_broker = BROKERS::IB;
				account = s;
				ib_port = config[s]["port"].as<long>();
			}
			else if (api == "CTP") {
				_broker = BROKERS::CTP;
				ctp_broker_id = config[s]["broker"].as<std::string>();
				ctp_user_id = s;
				ctp_password = config[s]["password"].as<std::string>();
				ctp_auth_code = config[s]["auth_code"].as<std::string>();
				ctp_user_prod_info = config[s]["user_prod_info"].as<std::string>();
				ctp_data_address = config[s]["md_address"].as<std::string>();
				ctp_broker_address = config[s]["td_address"].as<std::string>();
			}
			else if (api == "SINA")
				_broker = BROKERS::SINA;
			else
				_broker = BROKERS::PAPER;


			securities.clear();
			const std::vector<string> tickers = config[s]["tickers"].as<std::vector<string>>();
			for (auto s : tickers)
			{
				securities.push_back(s);
			}
		}
	}

	string CConfig::configDir()
	{
		//return boost::filesystem::current_path().string();
		return _config_dir;
	}

	string CConfig::logDir()
	{
		//boost::filesystem::path full_path = boost::filesystem::current_path() / "log";
		//return full_path.string();
		return _log_dir;
	}

	string CConfig::dataDir()
	{
		//boost::filesystem::path full_path = boost::filesystem::current_path() / "data";
		//return full_path.string();
		return _data_dir;
	}
}
