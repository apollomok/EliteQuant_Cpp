#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	{
		YAML::Node node;  // starts out as null
		node["key"] = "value";  // it now is a map node
		node["seq"].push_back("first element");  // node["seq"] automatically becomes a sequence
		node["seq"].push_back("second element");

		node["mirror"] = node["seq"][0];  // this creates an alias
		node["seq"][0] = "1st element";  // this also changes node["mirror"]
		node["mirror"] = "element #1";  // and this changes node["seq"][0] - they're really the "same" node

		node["self"] = node;  // you can even create self-aliases
		node[node["mirror"]] = node["seq"];  // and strange loops :)

		//node["tickers"] = "tickers";
		node["tickers"].push_back("AAPL STK SMART");
		node["tickers"].push_back("SPY STK SMART");

		std::ofstream fout("c:\\workspace\\EliteQuant\\Source\\cerealtest\\config.yaml");
		fout << node;
	}

	{
		//YAML::Node config = YAML::LoadFile("c:\\workspace\\EliteQuant\\Source\\cerealtest\\config.yaml");
		YAML::Node config = YAML::LoadFile("c:\\workspace\\EliteQuant\\Source\\cerealtest\\sample.yaml");

		const std::string username = config["name"].as<std::string>();
		const int password = config["invoice"].as<int>();
		const std::vector<string> tickers = config["tickers"].as<std::vector<string>>();
	}
}