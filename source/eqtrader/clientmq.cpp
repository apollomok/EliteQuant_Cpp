#include "clientmq.h"
#ifdef _WIN32
#include <nanomsg/src/nn.h>
#include <nanomsg/src/pipeline.h>
#include <nanomsg/src/pubsub.h>
#include <nanomsg/src/pair.h>
#else
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <nanomsg/pubsub.h>
#include <nanomsg/pair.h>
#endif
#include <time.h>
#include <queue>
#include <QStringList>


ClientMQ::ClientMQ()
{
    msg = "";
    tick_sock=nn_socket(AF_SP,NN_SUB);
    msg_sock=nn_socket(AF_SP,NN_PAIR);

    nn_setsockopt (tick_sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
    //nn_setsockopt (msg_sock, NN_PAIR, NN_SUB_SUBSCRIBE, "", 0);

    nn_connect (tick_sock, "tcp://127.0.0.1:55555") ;
    nn_connect (msg_sock, "tcp://127.0.0.1:55558") ;
}



void ClientMQ::run()
{
    while(1)
    {

        //获取消息
        char *buf = NULL;
        int bytes = nn_recv (tick_sock, &buf, NN_MSG, 0);
        if(bytes>0)
        {
			string marketmsg= string(buf);
            //if(marketmsg.indexOf('|')>0)
            {
                emit UpdateSignal(marketmsg);
                /*
                QStringList v  = marketmsg.split('|');
                TickEvent k=new TickEvent();

                k.full_symbol = v[0];
                k.timestamp = v[1];
                k.tick_type = TickType(v[2].toInt());
                k.price = v[3].toDouble();
                k.size = v[4].toInt();
                k.depth = v[5].toInt();

                if (k.tick_type == FULL)
                {
                    k.bid_price_L1 = v[6].toDouble();
                    k.bid_size_L1 = v[7].toInt();
                    k.ask_price_L1 = v[8].toDouble();
                    k.ask_size_L1 = v[9].toInt();
                    k.open_interest = v[10].toDouble();
                    k.open = v[11].toDouble();
                    k.high = v[12].toDouble();
                    k.low = v[13].toDouble();
                    k.pre_close = v[14].toDouble();
                    k.upper_limit_price = v[15].toDouble();
                    k.lower_limit_price = v[16].toDouble();
                }
               */

            }
        }

        char *buf1 = NULL;
        int bytes1 = nn_recv (tick_sock, &buf1, NN_MSG, 0);
        if(bytes1>0)
        {
            /*

                               m = GeneralEvent()
                               m.content = msg2
                               self._event_engine.put(m)

                               v = msg2.split('|')
                               if v[0] == 's':
                                  m = OrderStatusEvent()
                                  m.broker_order_id = v[1]
                                  m.internal_order_id = v[1]
                                  m.order_status = v[2]
                                  self._event_engine.put(m)
                               elif v[0] == 'f':
                                   m = FillEvent()
                                   m.broker_order_id = v[1]
                                   m.internal_order_id = v[1]
                                   m.timestamp = v[2]
                                   m.fill_price = v[3]
                                   m.fill_size = v[4]
                                   self._event_engine.put(m)
                               else:

            emit UpdateSignal(QString(buf1));
            */

        }

        /*if(outgoing_queue.size()>0)
        {
            QString msg3 = outgoing_queue.front();
            outgoing_queue.pop();
            string msg3stdstr=msg3.toStdString();
            printf("send order msg: %s",msg3stdstr.c_str());
            nn_send(msg_sock,msg3stdstr.c_str(), msg3stdstr.size(),0);
        }*/
    }
}

void ClientMQ::PlaceOrderSlot(QString order)
{
    outgoing_queue.push(order);
}
ClientMQ::~ClientMQ()
{
    nn_shutdown (tick_sock, 0);
    nn_shutdown (msg_sock, 0);
}
