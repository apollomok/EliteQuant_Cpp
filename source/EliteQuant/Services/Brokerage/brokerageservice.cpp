#include <Common/config.h>
#include <Common/Util/util.h>
#include <Common/Time/timeutil.h>
#include <Common/Logger/logger.h>
#include <Common/Data/datatype.h>
#include <Common/Order/ordermanager.h>
#include <Common/Order/ordertype.h>
#include <Common/Brokerage/brokerage.h>
#include <Common/Security/portfoliomanager.h>
#include <Common/Data/marketdatafeed.h>
#include <Strategy/strategyFactory.h>
#ifdef _WIN32
#include <nanomsg/src/pair.h>
#include <nanomsg/src/reqrep.h>
#else
#include <nanomsg/pair.h>
#include <nanomsg/reqrep.h>
#endif

using namespace std;

namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;

	void BrokerageService(shared_ptr<brokerage> poms, int clientid=0) {
		bool conn = false;
		int count = 0;
		while (!gShutdown) {
			conn = poms->connectToBrokerage();
			if (conn && poms->isConnectedToBrokerage()) {
				clientid++;
				msleep(2000);
				//poms->requestBrokerageAccountInformation(CConfig::instance().account);
				poms->_bkstate = BK_GETORDERID;			// After connection, it sets to BK_GETORDERID
				while (!gShutdown && poms->isConnectedToBrokerage()) {
					poms->processBrokerageMessages();
					msleep(10);
				}
			}
			else {
				msleep(5000);
				count++;
				if (count % 10 == 0) {
					printf("Cannot connect to broker\n");
				}
			}
		}

		poms->cancelAllOrders();
		//while (!poms->isAllOrdersCancelled())
		{
			msleep(100);
		}
		poms->disconnectFromBrokerage();
		PRINT_TO_FILE("INFO:[%s,%d][%s]Brokerage service stopped.\n", __FILE__, __LINE__, __FUNCTION__);
	}
}
