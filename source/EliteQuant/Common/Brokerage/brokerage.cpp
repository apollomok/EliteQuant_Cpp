#include <mutex>
#include <Common/Brokerage/brokerage.h>
#include <Common/Order/orderstatus.h>
#include <Common/Order/ordermanager.h>
#include <Common/Logger/logger.h>
#include <Common/Security/portfoliomanager.h>

using namespace std;
namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;

	mutex brokerage::mtx_CANCELALL;

	brokerage::brokerage() :
		_bkstate(BK_DISCONNECTED) {
		timeout.tv_sec = 0;
		timeout.tv_usec = 500 * 1000;

		// message queue PUB factory
		if (CConfig::instance()._msgq == MSGQ::ZMQ) {
			//msgq_pair_ = std::make_unique<CMsgqZmq>(MSGQ_PROTOCOL::PAIR, CConfig::instance().BROKERAGE_PAIR_PORT);
			msgq_pair_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::PAIR, CConfig::instance().BROKERAGE_PAIR_PORT);
		}
		else {
			msgq_pair_ = std::make_unique<CMsgqNanomsg>(MSGQ_PROTOCOL::PAIR, CConfig::instance().BROKERAGE_PAIR_PORT);
		}
	}

	brokerage::~brokerage() {
	}

	void brokerage::processBrokerageMessages() {
		if (!heatbeat(5)) {
			disconnectFromBrokerage();
			return;
		}
		switch (_bkstate) {
		case BK_GETORDERID:
			requestNextValidOrderID();
			break;
		case BK_ACCOUNT:
			requestBrokerageAccountInformation(CConfig::instance().account);
			break;
		case BK_ACCOUNTACK:
			break;
		case BK_READYTOORDER:
			monitorClientRequest();
			break;
		case BK_PLACEORDER_ACK:
			break;
		case BK_CANCELORDER:
			cancelOrder(0); //TODO
			break;
		case BK_CANCELORDER_ACK:
			break;
		}
	}

	//Keep calling this function from brokerage::processMessages()
	void brokerage::monitorClientRequest() {
		string msg = msgq_pair_->recmsg();

		if (msg.empty())
		{
			return;
		}

		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]msg received: %s\n", __FILE__, __LINE__, __FUNCTION__, msg.c_str());

		if (startwith(msg, CConfig::instance().close_all_msg)) {  // close all positions
			lock_guard<mutex> g(oid_mtx);
			PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Close all positions.\n", __FILE__, __LINE__, __FUNCTION__);

			for (auto iterator = PortfolioManager::instance()._positions.begin(); iterator != PortfolioManager::instance()._positions.end(); iterator++)
			{
				std::shared_ptr<Order> o = make_shared<Order>();
				o->fullSymbol = iterator->first;
				o->orderId = m_orderId;
				o->createTime = time(nullptr);
				o->orderSize = (-1) * iterator->second->_size;
				o->orderType = "MKT";
				o->orderStatus = OrderStatus::OS_NewBorn;
				m_orderId++;

				OrderManager::instance().trackOrder(o);
				placeOrder(o);
			}
		}
		else if (startwith(msg, CConfig::instance().new_order_msg)) {
			vector<string> v = stringsplit(msg, SERIALIZATION_SEPARATOR);

			if (v[1] == "MKT")
			{
				if (v.size() >= 4)				// o|mkt|IBM|-500[|OrderFlag]
				{
					PRINT_TO_FILE_AND_CONSOLE("INFO[%s,%d][%s]receive market order: %s\n", __FILE__, __LINE__, __FUNCTION__, msg.c_str());
					std::shared_ptr<Order> o = make_shared<Order>();

					lock_guard<mutex> g(oid_mtx);
					assert(m_orderId >= 0);			// start with 0
					//string oid = to_string(long(m_orderId));
					
					o->fullSymbol = v[2];
					o->orderId = m_orderId;
					o->createTime = time(nullptr);
					o->orderSize = stoi(v[3]);
					o->orderType = "MKT";
					o->orderStatus = OrderStatus::OS_NewBorn;
					
					if (v.size() == 5) {
						o->orderFlag = static_cast<OrderFlag>(stoi(v[4]));
					}
					else {
						o->orderFlag = OrderFlag::OF_OpenPosition;
					}

					m_orderId++;

					OrderManager::instance().trackOrder(o);
					placeOrder(o);
				}
				else
				{
					PRINT_TO_FILE("ERROR:[%s,%d][%s]market order bad format.\n", __FILE__, __LINE__, __FUNCTION__);
				}
			}
			// TODO: assign order id here
			else if (v[1] == "LMT")			//o|lmt|IBM|-500|125.5[|OrderFlag]
			{
				if (v.size() >= 5)
				{
					//lock_guard<mutex> g(oid_mtx);
					PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]recieved limit order: %s.\n", __FILE__, __LINE__, __FUNCTION__, msg.c_str());

					lock_guard<mutex> g(oid_mtx);
					assert(m_orderId >= 0);			// start with 0

					std::shared_ptr<Order> o = make_shared<Order>();
					o->fullSymbol = v[2];
					o->orderId = m_orderId;
					o->createTime = time(nullptr);
					o->orderSize = stoi(v[3]);
					o->orderType = "LMT";
					o->limitPrice = stof(v[4]);
					o->orderStatus = OrderStatus::OS_NewBorn;
					if (v.size() == 6) {
						o->orderFlag = static_cast<OrderFlag>(stoi(v[5]));
					}
					else {
						o->orderFlag = OrderFlag::OF_OpenPosition;
					}

					m_orderId++;

					OrderManager::instance().trackOrder(o);
					placeOrder(o);
				}
				else {
					PRINT_TO_FILE("ERROR:[%s,%d][%s]limit order bad format.\n", __FILE__, __LINE__, __FUNCTION__);
				}
			}
			else {
				PRINT_TO_FILE("ERROR:[%s,%d][%s]unrecognized order type: %s %s\n", __FILE__, __LINE__, __FUNCTION__);
			}
		}	// endif new order
		else if (startwith(msg, CConfig::instance().cancel_order_msg)) {		// c|oid
			vector<string> v = stringsplit(msg, SERIALIZATION_SEPARATOR);
			if (v.size() == 2) {
				cancelOrder(atoi(v[1].c_str()));
			}
			else {
				PRINT_TO_FILE("ERROR:[%s,%d][%s]cancel order bad format.\n", __FILE__, __LINE__, __FUNCTION__);
			}
		} // endif cancel order
		// TODO: should this go to data thread?
		else if (startwith(msg, CConfig::instance().hist_msg)) {
			vector<string> v = stringsplit(msg, SERIALIZATION_SEPARATOR);
			if (v.size() == 6) {
				//shared_ptr<IBBrokerage> ib = std::static_pointer_cast<IBBrokerage>(poms);
				//ib->requestHistoricalData(v[1], v[2], v[3], v[4], v[5]);
			}
			else {
				PRINT_TO_FILE("ERROR:[%s,%d][%s]historical data request bad format.\n", __FILE__, __LINE__, __FUNCTION__);
			}
		}	// endif historical data request
		else if (startwith(msg, CConfig::instance().test_msg)) {
			static int count = 0;
			vector<string> v = stringsplit(msg, SERIALIZATION_SEPARATOR);
			PRINT_TO_FILE("INFO:[%s,%d][%s]TEST :%d,%s\n", __FILE__, __LINE__, __FUNCTION__, ++count, msg.c_str());
			if (v.size()>1) {
				string reverse(v[1].rbegin(), v[1].rend());
				msgq_pair_->sendmsg(CConfig::instance().test_msg + SERIALIZATION_SEPARATOR + reverse);
			}
		}
	}

	bool brokerage::isAllOrdersCancelled() {
		return OrderManager::instance().retrieveNonFilledOrderPtr().empty();
	}

	//******************************** Message serialization ***********************//
	void brokerage::sendOrderCreated(long oid) {
		string msg = CConfig::instance().order_status_msg
			+ SERIALIZATION_SEPARATOR + std::to_string(int(OrderStatus::OS_NewBorn))
			+ SERIALIZATION_SEPARATOR + std::to_string(oid);

		msgq_pair_->sendmsg(msg);
	}

	void brokerage::sendOrderSubmitted(long oid) {
		string msg = CConfig::instance().order_status_msg
			+ SERIALIZATION_SEPARATOR + std::to_string(int(OrderStatus::OS_Submitted))
			+ SERIALIZATION_SEPARATOR + std::to_string(oid);

		msgq_pair_->sendmsg(msg);
	}

	void brokerage::sendOrderAcknowledged(long oid) {
		string msg = CConfig::instance().order_status_msg
			+ SERIALIZATION_SEPARATOR + std::to_string(int(OrderStatus::OS_Acknowledged))
			+ SERIALIZATION_SEPARATOR + std::to_string(oid);

		msgq_pair_->sendmsg(msg);
	}

	void brokerage::sendOrderFilled(Fill& t) {
		string msg = CConfig::instance().order_status_msg
			+ SERIALIZATION_SEPARATOR + std::to_string(int(OrderStatus::OS_Filled))
			+ SERIALIZATION_SEPARATOR + t.serialize();

		msgq_pair_->sendmsg(msg);
	}

	void brokerage::sendOrderCancelled(long oid) {
		string msg = CConfig::instance().order_status_msg
			+ SERIALIZATION_SEPARATOR + std::to_string(int(OrderStatus::OS_Canceled))
			+ SERIALIZATION_SEPARATOR + std::to_string(oid);

		msgq_pair_->sendmsg(msg);
	}

	void brokerage::sendOrderStatus(long oid) {
		std::shared_ptr<Order> o = nullptr;
		/*do {
		o = OrderManager::instance().retrieveOrder(oid);
		msleep(50);
		} while (o == nullptr);*/
		o = OrderManager::instance().retrieveOrder(oid);

		if (o != nullptr)
		{
			string msg = CConfig::instance().order_status_msg
				+ SERIALIZATION_SEPARATOR + std::to_string(oid)
				+ SERIALIZATION_SEPARATOR + std::to_string(int(o ? o->orderStatus : -1));

			msgq_pair_->sendmsg(msg);
		}
		else
		{
			sendGeneralMessage("order status request with invalid order id = " + std::to_string(oid));
		}
	}

	void brokerage::sendOpenPositionMessage(string symbol, int position, double averageCost, double unrealisedPNL, double realisedPNL) {
		//char str[512];
		//sprintf(str, "%d,%.4f,%.4f,%.4f", position, averageCost, unrealisedPNL, realisedPNL);
		//push(string(str));
		string msg = CConfig::instance().position_msg
			+ SERIALIZATION_SEPARATOR + symbol
			+ SERIALIZATION_SEPARATOR + std::to_string(position)
			+ SERIALIZATION_SEPARATOR + std::to_string(averageCost)
			+ SERIALIZATION_SEPARATOR + std::to_string(unrealisedPNL)
			+ SERIALIZATION_SEPARATOR + std::to_string(realisedPNL);

		msgq_pair_->sendmsg(msg);
	}

	void brokerage::sendHistoricalBarMessage(string symbol, string time, double open, double high, double low, double close, int volume, int barcount, double wap)
	{
		string msg = CConfig::instance().hist_msg
			+ SERIALIZATION_SEPARATOR + symbol
			+ SERIALIZATION_SEPARATOR + time
			+ SERIALIZATION_SEPARATOR + std::to_string(open)
			+ SERIALIZATION_SEPARATOR + std::to_string(high)
			+ SERIALIZATION_SEPARATOR + std::to_string(low)
			+ SERIALIZATION_SEPARATOR + std::to_string(close)
			+ SERIALIZATION_SEPARATOR + std::to_string(volume)
			+ SERIALIZATION_SEPARATOR + std::to_string(barcount)
			+ SERIALIZATION_SEPARATOR + std::to_string(wap);

		msgq_pair_->sendmsg(msg);
	}

	// comma separated general msg
	void brokerage::sendGeneralMessage(std::string gm) {
		string msg = CConfig::instance().general_msg + SERIALIZATION_SEPARATOR + gm;

		msgq_pair_->sendmsg(msg);
	}

	//************************* End of message serialization ***********************//
}
