#ifndef ENUMS_H
#define ENUMS_H
enum EventType
{
    TICK = 0,
    BAR = 1,
    ORDER = 2,
    FILL = 3,
    CANCEL = 4,
    ORDERSTATUS = 5,
    ACCOUNT = 6,
    POSITION = 7,
    CONTRACT = 8,
    TIMER = 9,
    GENERAL = 10
};

enum  TickType{
TRADE = 0,
   BID = 1,
   ASK = 2,
   FULL = 3
};
#endif // ENUMS_H
