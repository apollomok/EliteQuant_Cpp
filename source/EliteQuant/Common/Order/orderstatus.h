#ifndef _EliteQuant_Common_OrderStatus_H_
#define _EliteQuant_Common_OrderStatus_H_
#include <string>

namespace EliteQuant {
	enum OrderStatus {
		OS_NewBorn = 0,			// NewBorn
		OS_PendingSubmit = 1,
		OS_PendingCancel =2 ,
		OS_Submitted = 3,			// submitted
		OS_Acknowledged = 4,		// acknowledged
		OS_Canceled = 5,			// Canceled
		OS_Filled = 6,				// Filled
		OS_Inactive = 7,
		OS_PartiallyFilled = 8,		// PartiallyFilled
		OS_ApiPending,
		OS_ApiCancelled,
		OS_Error,
		OS_None
	};

	enum OrderFlag {			// for CTP offset flag
		OF_OpenPosition = 0,
		OF_ClosePosition = 1,
		OF_CloseToday = 2,
		OF_CloseYesterday = 3
	};

	const std::string OrderStatusString[] = {
		"NewBorn",
		"PendingSubmit",
		"PendingCancel",
		"PreSubmitted",
		"Submitted",
		"Canceled",
		"Filled",
		"Inactive",
		"PartiallyFilled",
		"ApiPending",
		"ApiCancelled",
		"Error",
		"None"
	};

	//OrderStatus getOrderStatus(const std::string& status);
	std::string getOrderStatusString(OrderStatus ost);
}

#endif  // _EliteQuant_Common_OrderStatus_H_