#include <atomic>
#include <Services/Data/dataservice.h>
#include <Common/config.h>
#include <Common/Util/util.h>
#include <Common/Time/timeutil.h>
#include <Common/Logger/logger.h>
#include <Common/Data/datatype.h>
#include <Common/Data/datamanager.h>
#include <Common/Data/tickwriter.h>
#include <Common/Data/tickreader.h>
#include <Common/Order/ordermanager.h>
#include <Common/Order/ordertype.h>
#include <Common/Security/portfoliomanager.h>
#include <Common/Data/marketdatafeed.h>
#include <Strategy/strategyFactory.h>

using namespace std;

namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;
	atomic<uint64_t> MICRO_SERVICE_NUMBER(0);

	void MarketDataService(shared_ptr<marketdatafeed> pdata, int clientid) {
		bool conn = false;
		int count = 0;

		pdata->_mode = TICKBAR;
		while (!gShutdown) {
			conn = pdata->connectToMarketDataFeed();

			if (conn && pdata->isConnectedToMarketDataFeed()) {
				msleep(2000);
				pdata->_mkstate = MK_ACCOUNT;			// after it is connected, start with MK_ACCOUNT
				while (!gShutdown && pdata->isConnectedToMarketDataFeed()) {
					pdata->processMarketMessages();
					msleep(10);
				}
			}
			else {
				msleep(5000);
				count++;
				if (count % 10 == 0) {
					PRINT_TO_FILE_AND_CONSOLE("ERROR:[%s,%d][%s]Cannot connect to Market Data Feed\n", __FILE__, __LINE__, __FUNCTION__);
				}
			}
		}
		pdata->disconnectFromMarketDataFeed();
		PRINT_TO_FILE("INFO:[%s,%d][%s]disconnect from market data feed.\n", __FILE__, __LINE__, __FUNCTION__);
	}

	void DataBoardService() {
		try {
			std::unique_ptr<CMsgq> msgq_sub_;

			// message queue factory
			if (CConfig::instance()._msgq == MSGQ::ZMQ) {
				//msgq_sub_ = std::make_unique<CMsgqZmq>(MSGQ_PROTOCOL::SUB, CConfig::instance().MKT_DATA_PUBSUB_PORT, false);
				msgq_sub_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::SUB, CConfig::instance().MKT_DATA_PUBSUB_PORT, false);
			}
			else {
				msgq_sub_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::SUB, CConfig::instance().MKT_DATA_PUBSUB_PORT, false);
			}
	
			while (!gShutdown) {
				string msg = msgq_sub_->recmsg();

				if (!msg.empty()) {
					vector<string> vs = stringsplit(msg, SERIALIZATION_SEPARATOR);
					if (vs.size() == 6)		// Always Tick; actual contents are determined by DataType
					{
						Tick k;
						k.deserialize(msg);
						
						if (DataManager::instance()._latestmarkets.find(k.fullsymbol_) != DataManager::instance()._latestmarkets.end()) {
							DataManager::instance().SetTickValue(k);
							// PRINT_TO_FILE("ERROR:[%s,%d][%s]%s.\n", __FILE__, __LINE__, __FUNCTION__, buf);
						}
					}
					else if (vs.size() == 17)		// Always Tick; actual contents are determined by DataType
					{
						FullTick k;
						k.deserialize(msg);

						if (DataManager::instance()._latestmarkets.find(k.fullsymbol_) != DataManager::instance()._latestmarkets.end()) {
							DataManager::instance().SetTickValue(k);
							// PRINT_TO_FILE("ERROR:[%s,%d][%s]%s.\n", __FILE__, __LINE__, __FUNCTION__, buf);
						}
					}
				}
			}
		}
		catch (exception& e) {
			PRINT_TO_FILE_AND_CONSOLE("ERROR:[%s,%d][%s]%s.\n", __FILE__, __LINE__, __FUNCTION__, e.what());
		}
		catch (...) {
		}
		PRINT_TO_FILE("INFO:[%s,%d][%s]disconnect from market data feed.\n", __FILE__, __LINE__, __FUNCTION__);
	}

	void BarAggregatorServcie() {
		// TODO: separate from DataBoardService
	}

	void TickRecordingService() {
		std::unique_ptr<CMsgq> msgq_sub_;

		// message queue factory
		if (CConfig::instance()._msgq == MSGQ::ZMQ) {
			//msgq_sub_ = std::make_unique<CMsgqZmq>(MSGQ_PROTOCOL::SUB, CConfig::instance().MKT_DATA_PUBSUB_PORT, false);
			msgq_sub_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::SUB, CConfig::instance().MKT_DATA_PUBSUB_PORT, false);
		}
		else {
			msgq_sub_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::SUB, CConfig::instance().MKT_DATA_PUBSUB_PORT, false);
		}

		string ymdstr = ymd();
		string fname = CConfig::instance().dataDir() + "/marketdata-" + ymdstr + ".txt";
		FILE* fp = fopen(fname.c_str(), "a+");
		TickWriter fwriter;
		fwriter.fp = fp;

		char *buf = nullptr;
		if (fp) {
			while (!gShutdown) {
				string msg = msgq_sub_->recmsg(0);

				if (!msg.empty())
					fwriter.put(msg);
			}
		}
		//PRINT_TO_FILE("INFO:[%s,%d][%s]recording service stopped: %s\n", __FILE__, __LINE__, __FUNCTION__);
	}

	void TickReplayService(const std::string& filetoreplay)
	{
		std::unique_ptr<CMsgq> msgq_pub_;

		// message queue factory
		if (CConfig::instance()._msgq == MSGQ::ZMQ) {
			//msgq_pub_ = std::make_unique<CMsgqZmq>(MSGQ_PROTOCOL::PUB, CConfig::instance().MKT_DATA_PUBSUB_PORT);
			msgq_pub_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::PUB, CConfig::instance().MKT_DATA_PUBSUB_PORT);
		}
		else {
			msgq_pub_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::PUB, CConfig::instance().MKT_DATA_PUBSUB_PORT);
		}

		uint64_t curt = 0;
		uint64_t logt = 0;
		vector<TimeAndMsg> lines = readreplayfile(filetoreplay);
		int i = 0, sz = lines.size();
		while (!gShutdown && i++ < sz) {
			logt = lines[i].t;
			curt = getMicroTime();
			static uint64_t diff = curt - logt;      //89041208806

			while (!gShutdown && (diff + logt > curt)) {
				curt = getMicroTime();
			}
			string& msg = lines[i].msg;

			msgq_pub_->sendmsg(msg);
		}
		msleep(2000);
		PRINT_TO_FILE("INFO:[%s,%d][%s]replay service stopped: %s\n", __FILE__, __LINE__, __FUNCTION__);
	}
}
