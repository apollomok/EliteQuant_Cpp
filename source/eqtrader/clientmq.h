#ifndef CLIENTMQ_H
#define CLIENTMQ_H
#include <QThread>
#include <string>
#include <queue>
#include "ctickevent.h"
using namespace std;

class ClientMQ:public QThread
{
    Q_OBJECT
private:
   string msg;
   int tick_sock;
   int msg_sock;
   queue<QString> outgoing_queue;
public:
    ClientMQ();
    ~ClientMQ();
protected:
    void run();
signals:
    void UpdateSignal(string msg);

public slots:
        void PlaceOrderSlot(QString order);
};

#endif // CLIENTMQ_H
