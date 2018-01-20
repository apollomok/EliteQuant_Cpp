#ifndef CTICKEVENT_H
#define CTICKEVENT_H

#include <QString>
#include <Common/Data/datatype.h>

using namespace EliteQuant;

class TickEvent
{

public:
    TickEvent();
    ~TickEvent();
public:
    DataType tick_type;
    QString timestamp;
    QString full_symbol;
    double price;
    int size;
    int depth;
    double bid_price_L1;
    double bid_size_L1;
    double ask_price_L1;
    double ask_size_L1;
    double open_interest;
    double open;
    double high;
    double low;
    double pre_close;
    double upper_limit_price;
    double lower_limit_price;
};


#endif // CTICKEVENT_H
