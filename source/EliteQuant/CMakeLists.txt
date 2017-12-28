include_directories(${EliteQuantCpp_SOURCE_DIR}/EliteQuant)
set(EliteQuantCppSrc
  ./Strategy/smacross.cpp
  ./Strategy/strategyFactory.cpp
  ./Common/Util/calc.cpp
  ./Common/Util/util.cpp
  ./Common/Util/consolecontrolhandler.cpp
  ./Common/Time/timeutil.cpp
  ./Common/Time/getRealTime.cpp
  ./Common/Time/heartbeat.cpp
  ./Common/Strategy/strategymanager.cpp
  ./Common/Strategy/strategybase.cpp
  ./Common/Account/accountmanager.cpp
  ./Common/Logger/logger.cpp
  ./Common/config.cpp
  ./Common/Performance/performancemanager.cpp
  ./Common/Performance/reportmanager.cpp
  ./Common/Data/marketdatafeed.cpp
  ./Common/Data/datamanager.cpp
  ./Common/Data/tick.cpp
  ./Common/Data/barseries.cpp
  ./Common/Data/bar.cpp
  ./Common/Risk/marginmanager.cpp
  ./Common/Risk/riskmanager.cpp
  ./Common/Brokerage/brokerage.cpp
  ./Common/Brokerage/exchange.cpp
  ./Common/Order/ordermanager.cpp
  ./Common/Order/orderbook.cpp
  ./Common/Order/orderstatus.cpp
  ./Common/Security/portfoliomanager.cpp
  ./Common/Security/position.cpp
  ./Common/Msgq/msgq.cpp
  ./Services/backtestoptimizationengine.cpp
  ./Services/Strategy/strategyservice.cpp
  ./Services/Api/apiservice.cpp
  ./Services/Data/dataservice.cpp
  ./Services/elitequant_.cpp
  ./Services/Brokerage/brokerageservice.cpp
  ./Services/tradingengine.cpp
  ./Brokers/Paper/paperdatafeed.cpp
  ./Brokers/Paper/paperbrokerage.cpp
  ./Brokers/Ctp/ctpbrokerage.cpp
  ./Brokers/Ctp/ctpdatafeed.cpp
  ./Brokers/IB/OfficialLinux/EPosixClientSocket.cpp
  ./Brokers/IB/OfficialLinux/EClientSocketBase.cpp
  # ./Brokers/IB/OfficialLinux/client/EClient.cpp
  # ./Brokers/IB/OfficialLinux/client/SoftDollarTier.cpp
  # ./Brokers/IB/OfficialLinux/client/OrderCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/ContractCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/OperatorCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/EClientSocket.cpp
  # ./Brokers/IB/OfficialLinux/client/TimeCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/VolumeCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/EReader.cpp
  # ./Brokers/IB/OfficialLinux/client/MarginCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/executioncondition.cpp
  # ./Brokers/IB/OfficialLinux/client/ESocket.cpp
  # ./Brokers/IB/OfficialLinux/client/StdAfx.cpp
  # ./Brokers/IB/OfficialLinux/client/EReaderOSSignal.cpp
  # ./Brokers/IB/OfficialLinux/client/EReaderWMSignal.cpp
  # ./Brokers/IB/OfficialLinux/client/DefaultEWrapper.cpp
  # ./Brokers/IB/OfficialLinux/client/EMessage.cpp
  # ./Brokers/IB/OfficialLinux/client/PriceCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/PercentChangeCondition.cpp
  # ./Brokers/IB/OfficialLinux/client/EDecoder.cpp
  # ./Brokers/IB/OfficialLinux/client/EMutex.cpp
  ./Brokers/IB/ibbrokerage.cpp
  ./Brokers/Sina/sinadatafeed.cpp
  ./Brokers/Backtest/backtestdatafeed.cpp
  ./Brokers/Google/googledatafeed.cpp
  )
#ADD_LIBRARY(boost_python STATIC IMPORTED)
#SET_TARGET_PROPERTIES(boost_python PROPERTIES
#    IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libboost_python.a)
add_library(elitequant SHARED ${EliteQuantCppSrc})
set_target_properties(elitequant  PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(elitequant  boost_python-py35  boost_system boost_filesystem boost_date_time python3.5m yaml-cpp zmq thosttraderapi thostmduserapi zmq yaml-cpp sandbox_vs_dll nanomsg pthread dl util m)
