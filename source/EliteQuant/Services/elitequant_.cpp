#include <boost/python.hpp>
#include <Services/tradingengine.h>
using namespace boost::python;
using namespace EliteQuant;

// http://www.shocksolution.com/python-basics-tutorials-and-examples/linking-python-and-c-with-boostpython/

BOOST_PYTHON_MODULE(EliteQuant)
{
	class_<tradingengine, boost::noncopyable>("tradingengine_").
		def("run", &tradingengine::run).
		def("live", &tradingengine::live);
}