#ifndef __EliteQuant_Strategy_StrategyFactor_H__
#define __EliteQuant_Strategy_StrategyFactor_H__

#include <memory>
#include <Common/config.h>
#include <Common/Strategy/strategybase.h>

// A factory function to create strategy
namespace EliteQuant
{
	std::unique_ptr<StrategyBase> strategyFactory(const string& _algo);
}

#endif
