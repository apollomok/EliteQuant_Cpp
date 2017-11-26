#ifndef _EliteQuant_Services_BrokerageService_H_
#define _EliteQuant_Services_BrokerageService_H_

#include <memory>
#include <Common/config.h>
#include <Common/Data/marketdatafeed.h>
#include <Common/Brokerage/brokerage.h>

namespace EliteQuant
{
	void BrokerageService(std::shared_ptr<brokerage> poms, int clientid=0);
}

#endif  // _EliteQuant_Services_BrokerageService_H_
