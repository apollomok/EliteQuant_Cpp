#ifndef _EliteQuant_Services_DataService_H_
#define _EliteQuant_Services_DataService_H_

#include <memory>
#include <Common/config.h>
#include <Common/Data/marketdatafeed.h>

namespace EliteQuant
{

	void MarketDataService(std::shared_ptr<marketdatafeed>, int);
	void DataBoardService();
	void BarAggregatorServcie();
	void TickRecordingService();
	void TickReplayService(const std::string& filetoreplay);
}

#endif
