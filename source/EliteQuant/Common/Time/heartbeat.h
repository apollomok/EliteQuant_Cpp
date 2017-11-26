#ifndef _EliteQuant_Common_HeartBeat_H_
#define _EliteQuant_Common_HeartBeat_H_

#include <time.h>

namespace EliteQuant
{
	class CHeartbeat {
	protected:
		time_t last_time;
	public:
		// derived class overwrites heartbeat to tell if itself is still alive
		bool heatbeat(int);
	};
}
#endif
