#ifndef _EliteQuant_Common_Util_H
#define _EliteQuant_Common_Util_H

#include <sstream>
#include <iterator>
//#include <future>
#include <Common/config.h>
#include <Common/Logger/logger.h>
#include <Common/Time/getRealTime.h>

using std::string;
using std::vector;
using std::pair;

namespace EliteQuant {
	int check_gshutdown(bool force = true);

	vector<string> stringsplit(const string &s, char delim);
	bool startwith(const string&, const string&);
	bool endwith(const std::string &str, const std::string &suffix);
}

#endif   // _EliteQuant_Common_Util_H
