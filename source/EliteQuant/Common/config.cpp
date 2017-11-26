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
		string path = boost::filesystem::current_path().string() + "/config.yaml";
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
		
		const string broker = config["broker"].as<std::string>();
		if (broker == "IB")
			_broker = BROKERS::IB;
		else if (broker == "CTP")
			_broker = BROKERS::CTP;
		else if (broker == "GOOGLE")
			_broker = BROKERS::GOOGLE;
		else if (broker == "SINA")
			_broker = BROKERS::SINA;
		else
			_broker = BROKERS::PAPER;

		account = config["account"].as<std::string>();
		ib_port = config["ibport"].as<long>();
		ctp_broker_id = config["ctp_broker_id"].as<std::string>();
		ctp_user_id = config["ctp_user_id"].as<std::string>();
		ctp_password = config["ctp_password"].as<std::string>();
		ctp_data_address = config["ctp_md_address"].as<std::string>();
		ctp_broker_address = config["ctp_td_address"].as<std::string>();
		const std::vector<string> tickers = config["tickers"].as<std::vector<string>>();
		for (auto s : tickers)
		{
			securities.push_back(s);
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
