#include <Common/config.h>
#include <Common/Data/tick.h>
#include <Common/Util/util.h>

namespace EliteQuant
{
	string Tick::serialize() const
	{
		// TODO: which one is more efficient?
		//char msg[128] = {};
		//sprintf(msg, "%s|%d|%.2f", fullsymbol_.c_str(), datatype_, price_, size_, depth_);
		//return msg;

		string s;
		s = fullsymbol_ 
			+ SERIALIZATION_SEPARATOR + time_
			+ SERIALIZATION_SEPARATOR + to_string(datatype_)
			+ SERIALIZATION_SEPARATOR + to_string(price_)
			+ SERIALIZATION_SEPARATOR + to_string(size_)
			+ SERIALIZATION_SEPARATOR + to_string(depth_);
		return s;
	}

	void Tick::deserialize(string& msg) {
		vector<string> vs = stringsplit(msg, SERIALIZATION_SEPARATOR);

		fullsymbol_ = vs[0];
		time_ = vs[1];					//atoi(vs[1].c_str());
		datatype_ = (DataType)(atoi(vs[2].c_str()));
		price_ = atof(vs[3].c_str());
		size_ = atoi(vs[4].c_str());
		depth_ = atoi(vs[5].c_str());
	}

	string FullTick::serialize() const
	{
		// TODO: which one is more efficient?
		//char msg[128] = {};
		//sprintf(msg, "%s|%d|%.2f", fullsymbol_.c_str(), datatype_, price_, size_, depth_);
		//return msg;

		string s;
		s = fullsymbol_
			+ SERIALIZATION_SEPARATOR + time_
			+ SERIALIZATION_SEPARATOR + to_string(DataType::DT_Full)
			+ SERIALIZATION_SEPARATOR + to_string(price_)
			+ SERIALIZATION_SEPARATOR + to_string(size_)
			+ SERIALIZATION_SEPARATOR + to_string(depth_)
			+ SERIALIZATION_SEPARATOR + to_string(bidprice_L1_)
			+ SERIALIZATION_SEPARATOR + to_string(bidsize_L1_)
			+ SERIALIZATION_SEPARATOR + to_string(askprice_L1_)
			+ SERIALIZATION_SEPARATOR + to_string(asksize_L1_)
			+ SERIALIZATION_SEPARATOR + to_string(open_interest)
			+ SERIALIZATION_SEPARATOR + to_string(open_)
			+ SERIALIZATION_SEPARATOR + to_string(high_)
			+ SERIALIZATION_SEPARATOR + to_string(low_)
			+ SERIALIZATION_SEPARATOR + to_string(pre_close_)
			+ SERIALIZATION_SEPARATOR + to_string(upper_limit_price_)
			+ SERIALIZATION_SEPARATOR + to_string(lower_limit_price_);

		return s;
	}

	void FullTick::deserialize(string& msg) {
		vector<string> v = stringsplit(msg, SERIALIZATION_SEPARATOR);

		fullsymbol_ = v[0];
		time_ = v[1];
		datatype_ = (DataType)(atoi(v[2].c_str()));
		price_ = atof(v[3].c_str());
		size_ = atoi(v[4].c_str());
		depth_ = atoi(v[5].c_str());

		if (datatype_ == DataType::DT_Full)			// check it is not DataType::Trade
		{
			bidprice_L1_ = stoi(v[6]);
			bidsize_L1_ = stoi(v[7]);
			askprice_L1_ = stoi(v[8]);
			asksize_L1_ = stoi(v[9]);
			open_interest = stoi(v[10]);
			open_ = stoi(v[11]);
			high_ = stoi(v[12]);
			low_ = stoi(v[13]);
			pre_close_ = stoi(v[14]);
			upper_limit_price_ = stoi(v[15]);
			lower_limit_price_ = stoi(v[16]);
		}
	}
}
