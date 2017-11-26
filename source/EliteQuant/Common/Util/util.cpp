#include <mutex>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <fcntl.h>

#include <Common/config.h>
#include <Common/Util/util.h>
#include <Common/Util/consolecontrolhandler.h>
#include <Common/Time/timeutil.h>
#include <Common/Brokerage/exchange.h>

using namespace std;

namespace EliteQuant {
	vector<string> stringsplit(const string &s, char delim)
	{
		vector<string> elems;

		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}

		return elems;
	}

	bool startwith(const string& x, const string& y) {
		return x.find(y) == 0;
	}

	bool endwith(const std::string &str, const std::string &suffix) {
		return str.size() >= suffix.size() &&
			str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	int check_gshutdown(bool force) {
		atomic_bool* g = setconsolecontrolhandler();
		while (!*g) {
			msleep(1 * 1000);
		}
		// ctrl-c
		if (force) {
			throw runtime_error("Throw an exception to trigger shutdown");
		}
		return 0;
	}
}