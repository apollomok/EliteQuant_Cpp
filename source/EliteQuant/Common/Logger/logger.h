#ifndef _EliteQuant_Common_Logger_H_
#define _EliteQuant_Common_Logger_H_

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <mutex>
#include <Common/Time/timeutil.h>

using std::string;
using std::mutex;

namespace EliteQuant
{
	class logger {
		static logger* pinstance_;
		static mutex instancelock_;

		FILE* logfile = nullptr;
		logger();
		~logger();

	public:
		static logger& instance();

		void Initialize();

		void Printf2File(const char *format, ...);
	};
}
#endif
