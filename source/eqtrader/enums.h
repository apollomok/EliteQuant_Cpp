#ifndef ENUMS_H
#define ENUMS_H

enum  TickType{
TRADE = 0,
   BID = 1,
   ASK = 2,
   FULL = 3
};
enum  OrderStatus{
    NEWBORN = 0,
    PENDING_SUBMIT = 1,
    PENDING_CANCEL = 2,
    SUBMITTED = 3,
    ACKNOWLEDGED = 4,
    CANCELED = 5,
    FILLED = 6,
    PARTIALLY_FILLED = 8,
    API_PENDING = 9,
    API_CANCELLED = 10,
    ERROR = 11,
    NONE = 12
};

enum  OrderFlag{
    OPEN = 0,
    CLOSE = 1,
    CLOSE_TODAY = 2,
    CLOSE_YESTERDAY = 3
};

#endif // ENUMS_H
