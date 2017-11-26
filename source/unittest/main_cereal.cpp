#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct MyData
{
	int x, y, z;

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(x, y, z); // serialize things by passing them to the archive
	}
};

int main()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string path = "c:\\workspace\\EliteQuant\\source\\Cpp\\cerealtest\\data.xml"
#else
static const std::string path="/home/letian/workspace/EliteQuant/source/Cpp/cerealtest/data.xml";
#endif
	{

		std::ofstream os(path);
		cereal::XMLOutputArchive archive(os);

		MyData m1;
		int someInt;
		double d = 2.52;

		archive(CEREAL_NVP(m1), // Names the output the same as the variable name
			someInt,        // No NVP - cereal will automatically generate an enumerated name
			//d);
			cereal::make_nvp("this_id", d)); // specify a name of your choosing; cann't have blank
	}

	{
		std::ifstream is(path);
		cereal::XMLInputArchive archive(is);

		MyData m1;
		int someInt;
		double d;

		archive(m1, someInt, d); // NVPs not strictly necessary when loading
								 // but could be used (even out of order)

	}
    
    int t;
	std::cin >> t;
}