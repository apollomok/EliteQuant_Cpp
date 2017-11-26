#include <Common/config.h>
#include <Common/Data/tick.h>

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
			+ SERIALIZATION_SEPARATOR + to_string(time_)
			+ SERIALIZATION_SEPARATOR + to_string(datatype_)
			+ SERIALIZATION_SEPARATOR + to_string(price_)
			+ SERIALIZATION_SEPARATOR + to_string(size_)
			+ SERIALIZATION_SEPARATOR + to_string(depth_);
		return s;
	}
}
