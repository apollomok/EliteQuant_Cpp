#ifndef STRATEGYMANAGER_H
#define STRATEGYMANAGER_H
#include "strategybase.h"
#include "clientmq.h"
#include "ctickevent.h"
#include <string>

class StrategyManager
{
public:
    StrategyManager(ClientMQ* clientmq);
    ClientMQ *clientmq;
    map<string,StrategyBase> strategies;

    void LoadStrategy(StrategyBase strategy);
    void SendOrder();
    void CancelOrder();
    void Onick(TickEvent k);
    void OnPosition(string pos);
    void OnOrder(string order);
    void OnCancel(string order);
    void OnFill(string fill);

signals:
    void OutgoingMessageSignal(string sMessage);
};

#endif // STRATEGYMANAGER_H
