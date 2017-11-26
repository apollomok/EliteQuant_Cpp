#ifndef __EliteQuant_Common_TickReader_H__
#define __EliteQuant_Common_TickReader_H__

#include <condition_variable>
#include <mutex>
#include <Common/config.h>
#include <Common/Util/util.h>
#include <Common/Time/timeutil.h>
#include <Common/Time/getRealTime.h>

using std::mutex;

//////////////////////////////////////////////////////////////////////////
// tick reader
//////////////////////////////////////////////////////////////////////////
namespace EliteQuant
{
	struct TimeAndMsg {
		uint64_t t;
		string msg;
	};

	vector<TimeAndMsg> readreplayfile(const string& filetoreplay) {
		ifstream f(filetoreplay);
		vector<TimeAndMsg> lines;
		string x;
		while (f.is_open() && f.good()) {
			getline(f, x);
			if (!x.empty()) {
				vector<string> tmp = stringsplit(x, '@');
				if (tmp.size() == 2) {
					TimeAndMsg tam = { (uint64_t)atoll(tmp[0].c_str()), tmp[1] };
					lines.push_back(tam);
				}
			}
		}
		return lines;
	}
}

#endif
