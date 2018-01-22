# EliteQuant_Cpp
C/C++ High frequency quantitative trading and investment platform

* [Platform Introduction](#platform-introduction)
* [Project Summary](#project-summary)
* [Participation](#participation)
* [Installation](#installation)
* [Development Environment](#development-environment)
* [Architecture Diagram](#architecture-diagram)
* [Todo List](#todo-list)

---

## Platform Introduction

EliteQuant is an open source forever free unified quant trading platform built by quant traders, for quant traders. It is dual listed on both [github](https://github.com/EliteQuant) and [gitee](https://gitee.com/EliteQuant).

The word unified carries two features.
- First it’s unified across backtesting and live trading. Just switch the data source to play with real money.
- Second it’s consistent across platforms written in their native langugages. It becomes easy to communicate with peer traders on strategies, ideas, and replicate performances, sparing language details.

Related projects include
- [A list of online resources on quantitative modeling, trading, and investment](https://github.com/EliteQuant/EliteQuant)
- [C++](https://github.com/EliteQuant/EliteQuant_Cpp)
- [Python](https://github.com/EliteQuant/EliteQuant_Python)
- [Matlab](https://github.com/EliteQuant/EliteQuant_Matlab)
- [R]()
- [C#]()
- [Excel](https://github.com/EliteQuant/EliteQuant_Excel)
- [Java]()
- [Scala]()
- [Go]()
- [Julia]()

## Project Summary

EliteQuant_Cpp is C/C++ 11 based multi-threading, concurrent high-frequency trading platform. It follows modern design patterns such as event-driven, server/client architect, dependency injection and loosely-coupled robust distributed system. It is self-contained and can be used out of box. At the same time, it serves as server side for other EliteQuant projects.

## Participation

Please feel free to report issues, fork the branch, and create pull requests. Any kind of contributions are welcomed and appreciated. Through shared code architecture, it also helps traders using other languges.

## Installation

No installation is needed, it's ready for use out of box. Just download the code and enjoy. 

The easiest way is to download and uzip compiled.zip from the project root directory. Then run the program called eqsever.exe.Before you run this executable, there are a couple of config settings you need to modify. By default, the program reads config.xml from the same directory. Therefore open the config file
1. If you want to use interactive broker, open IB trader workstation (TWS), go to its menu File/Global Configuration/API/Settings, check "Enable ActiveX and Socket Client", uncheck "Read-Only API"
2. In the config file, change the account id to yours; IB account id usually can be found on the top right of the TWS window.
3. If you use CTP, change your brokerage account information and ctp addresses accordingly.
4. create folder for log_dir and data_dir respectively. The former records runtime logs, while the later saves tick data.

**Interactive Brokers**
is the most popular broker among retail traders. A lot of retail trading platform such as quantopian, quantconnect are built to support IB. If you don't have IB account but want to try it out, they provide demo account edemo with password demouser. Just download TWS trader workstation and log in with this demo account. Note that accound id changes everytime you log on to TWS with demo account so you have to change EliteQuant config file accordingly.

**CTP**
is the de-facto brokerage for Chinese futures market, including commodity futures and financial futures. They also offer free demo account [SimNow](http://simnow.com.cn/). After registration, you will get account, password, brokerid, along with market data and trading broker address. Replace them in EliteQuant config file accordingly.

![Live Demo](/resource/ib_demo.gif?raw=true "Live Demo")

## Development Environment

Below is the environment we are using

* Visual Studio 2017 Community Edition on Windows
* Qt Creator 4.5.0 Commuity

Visual C++ is a popular choice on Windows. Qt Creator builds cross-plaform Qt user interface. Other choices are CLion, CMake, etc.

### Development on Ubuntu 16.04 64 bit System

You can follow below steps to install necessary third party libraries and build this project with cmake on newest 64 bit Ubuntu system. Assume you have [xcode](https://developer.apple.com/xcode/) and [Homebrew](https://brew.sh/) installed, open a command terminal and execute the following.

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install aptitude git cmake 
sudo aptitude install zlib1g-dev rapidjson-dev python3-dev libboost-all-dev libsodium-dev \
                      libyaml-cpp-dev libwebsocketpp-dev libnanomsg-dev libzmq3-dev

# Download SimNow tradeapi for Linux
cd ~          # or directory of your choice 
wget http://simnow.sfit.com.cn/download/api/v6.3.5_20150803_tradeapi_linux64.tar
tar xvf v6.3.5_20150803_tradeapi_linux64.tar
cd v6.3.5_20150803_api_tradeapi_linux64/
sudo cp thostmduserapi.so /usr/lib/libthostmduserapi.so
sudo cp thosttraderapi.so /usr/lib/libthosttraderapi.so
cd ~        # or directory of your choice        
git clone https://github.com/EliteQuant/EliteQuant_Cpp.git
cd EliteQuant_Cpp/source
mkdir build
cd build
cmake ..
make -j2

# run the program
cd eqserver
cp ../../eqserver/config.yaml .
mkdir log data
./eqserver             # change config.yaml first
```

On Linux, you might encounter the **double free or corruption (!prev)** error when you terminate the eqserver by pressing Ctrl+C. One way to suppress this warning is to add **MALLOC_CHECK_=0** variable to your environment.
```bash
sudo vim ~/.bashrc          # edit system config
export MALLOC_CHECK_=0      # append this to the end of the file
source ~/.bashrc            # source the configuration file into effect
```

### Development on macOS
You can follow below steps to install necessary third party libraries and build this project with cmake on clean macOS system.

```bash
brew --version
brew update

brew install git cmake
brew install zlib1g-dev rapidjson-dev python3-dev libboost-all-dev libsodium-dev \
                      libyaml-cpp-dev libwebsocketpp-dev libnanomsg-dev libzmq3-dev
```

## Architecture Diagram

### Micro-Services

| Service        | Protocol     | Port  | Binding |
| ------------- |:-------------:| -----:| -----:|
| MarketData      | PUB | 55555 | Y |
| Brokerage      | PAIR | 55556 | Y |
| DataManager/BarAggregator      | PUB | 55557 | Y |
| TickRecording      | SUB      |   55555 | N |
| DataBoard | SUB      |   55555 | N |
| ApiServer | PAIR      |   55556 | N |
| ApiServer | SUB      |   55557 | N |
| ApiServer | PAIR      |   55558 | Y |

### Message Protocol

Messages are sperated by character '|'. For example

* new market order: o|account|api|client order id|MKT|AAPL STK SMART|100[|order_flag]
* new limit order: o|account|api|client order id|LMT|AAPL STK SMART|100|170.00[|order_flag]
* order status: s|account|api|server order id|client order id|broker order id|order status
* fill: f|account|api|server order id|client order id|broker order id|trade id|trade time|symbol|trade price|tradesize
* cancel: c|account|api|server order id|client order id|broker order id
* tick message: AAPL STK SMART|time|data type|price|size|depth
* full tick message: AAPL STK SMART|time|3|price|size|1|bid|bid size|ask|ask size|open interest|open|high|low|pre close|upper limit|lower limit

The following are message types:

* k: tick msg
* p: last price
* z: last size
* o: new order
* c: cancel order
* s: order status
* n: position query
* m: general message
* b: bar
* h: historical data
* e: test message

### Ticker Symbol

In EliteQuant, an instrument is identified by its **full symbol**, which consists of a couple fo words separated by space. The general pattern is "Local_Symbol Security_Type Exchange_Name Currency Multiplier“. For example

* Stock: SPY STK SMART
* Future: ESZ7 FUT GLOBEX 50
* FX: EUR.USD CASH IDEALPRO
* FX futures: 6BU1 FUT GLOBELX
* Option: GOOGL_140920P00535000 OPT SMART 100
* Futures Options: EWQ4_C1730 FOP GLOBEX 50

### order status
``` cpp
enum OrderStatus {
		OS_NewBorn = 0,			// NewBorn
		OS_PendingSubmit = 1,
		OS_PendingCancel =2 ,
		OS_Submitted = 3,			// submitted
		OS_Acknowledged = 4,		// acknowledged
		OS_Canceled = 5,			// Canceled
		OS_Filled = 6,				// Filled
		OS_Inactive = 7,
		OS_PartiallyFilled = 8		// PartiallyFilled
	};

	enum OrderFlag {			// for CTP offset flag
		OF_OpenPosition = 0,
		OF_ClosePosition = 1,
		OF_CloseToday = 2,
		OF_CloseYesterday = 3
	};
```

### Code Structure

![Code Structure](/resource/code_structure_en.png?raw=true "Code Structure")

## Todo List