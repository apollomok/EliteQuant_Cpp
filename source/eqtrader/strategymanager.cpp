#include "strategymanager.h"

StrategyManager::StrategyManager(ClientMQ* clientmq)
{
    this->clientmq=clientmq;
}

void StrategyManager::LoadStrategy(StrategyBase strategy)
{
    strategies.insert(pair<string, StrategyBase>(strategy.StrategyName, strategy));
}

void StrategyManager::SendOrder()
{
    string msg = "o|MKT";
    //clientmq.put(msg)
}

void StrategyManager::CancelOrder()
{

}
void StrategyManager::Onick(TickEvent k)
{

}
void StrategyManager::OnPosition(string pos)
{

}
void StrategyManager::OnOrder(string order)
{

}
void StrategyManager::OnCancel(string order)
{

}
void StrategyManager::OnFill(string fill)
{

}
