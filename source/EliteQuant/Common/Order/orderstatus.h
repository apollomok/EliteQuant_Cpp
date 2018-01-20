#ifndef _EliteQuant_Common_OrderStatus_H_
#define _EliteQuant_Common_OrderStatus_H_
#include <string>

namespace EliteQuant {
	enum OrderStatus {
		OS_UNKNOWN = 0,		// Unknown
		OS_NewBorn = 1,			// NewBorn
		OS_PendingSubmit = 2,
		OS_Submitted = 3,			// submitted
		OS_Acknowledged = 4,		// acknowledged
		OS_PartiallyFilled = 5,		// PartiallyFilled
		OS_Filled = 6,				// Filled
		OS_PendingCancel = 7 ,
		OS_Canceled = 8,			// Canceled
		OS_Inactive = 9,
		OS_ApiPending = 10,
		OS_ApiCancelled = 11,
		OS_Error = 12
	};

	enum OrderFlag {			// for CTP offset flag
		OF_OpenPosition = 0,
		OF_ClosePosition = 1,
		OF_ForceClose = 2,
		OF_CloseToday = 3,
		OF_CloseYesterday = 4,
		OF_ForceOff = 5,
		OF_LocalForceClose = 6
	};

	const std::string OrderStatusString[] = {
		"NewBorn",
		"PendingSubmit",
		"Submitted",
		"Acknowledged",
		"PartiallyFilled",
		"Filled",
		"PendingCancel",
		"Canceled",
		"Inactive",
		"ApiPending",
		"ApiCancelled",
		"Error",
		"None"
	};

	//OrderStatus getOrderStatus(const std::string& status);
	std::string getOrderStatusString(OrderStatus ost);
}

#endif  // _EliteQuant_Common_OrderStatus_H_