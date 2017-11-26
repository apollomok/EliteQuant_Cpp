#include <Common/Order/orderstatus.h>

using namespace std;

namespace EliteQuant
{
	std::string getOrderStatusString(OrderStatus ost) {
		return OrderStatusString[(int)ost];
	}
}