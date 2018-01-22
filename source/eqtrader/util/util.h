#pragma once

#include <string>
#include <sstream>
#include <vector>

using namespace std;

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