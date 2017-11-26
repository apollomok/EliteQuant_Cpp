#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <Common\Util\util.h>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
	/***************   file system ************************/
	boost::filesystem::path full_path(boost::filesystem::current_path());
	std::cout << "Current path is : " << full_path << std::endl;
	full_path = boost::filesystem::system_complete("../..");
	std::cout << "Current path is : " << full_path << std::endl;
	full_path = boost::filesystem::current_path() / "log";
	std::printf("Current path is : %s\n", full_path.string().c_str());
	boost::filesystem::create_directory(full_path);
	full_path = boost::filesystem::current_path() / "log/test.txt";
	std::ifstream infile(full_path.string());
	std::string str;
	std::getline(infile, str);

	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);				 /* get current time; same as: timer = time(NULL)  */
	LOCALTIME_S(&timeinfo, &rawtime);

	char datestr[50];
	sprintf(datestr, "%d-%d-%d %d:%d:%d", timeinfo.tm_year+1900, timeinfo.tm_mon+1, timeinfo.tm_mday,
		timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
	cout << datestr << endl;

	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);
	cout << "The local date and time is: " << dt << endl;
	// convert now to tm struct for UTC
	tm *gmtm = gmtime(&now);
	dt = asctime(gmtm);
	cout << "The UTC date and time is:" << dt << endl;

	int barorderinaday_ = 0;
	int interval_ = 300;
	int time_target = barorderinaday_ * interval_;		// in seconds
	int hour = time_target / 3600;
	int second = time_target % 3600;
	int minute = second / 60;
	second = second % 60;
	long barstarttime_ = hour * 10000 + minute * 100 + second;
	barorderinaday_ = 2;
	time_target = barorderinaday_ * interval_;		// in seconds
	hour = time_target / 3600;
	second = time_target % 3600;
	minute = second / 60;
	second = second % 60;
	barstarttime_ = hour * 10000 + minute * 100 + second;

	cout << "pause" << std::endl;
	int t;
	std::cin >> t;
}