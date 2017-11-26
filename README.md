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
IB is the most popular broker among retail traders. A lot of retail trading platform such as quantopian, quantconnect are buit to support IB. If you don't have IB account but want to try it out, they provide demo account edemo with password demouser. Just download TWS trader workstation and log in with this demo account. Note that accound id changes everytime you log on to TWS with demo account so you have to change EliteQuant config file accordingly.

**CTP**
CTP is the de-facto brokerage for Chinese futures market, including commodity futures and financial futures. They also offer free demo account [SimNow](http://simnow.com.cn/). After registration, you will get account, password, brokerid, along with market data and trading broker address. Replace them in EliteQuant config file accordingly.

## Development Environment

Below is the environment we are using

* Visual Studio 2017 Community Edition on Windows
* CodeLite 11.0.6 on Linux

Visual C++ is a popular choice on Windows. CodeLite is a free Linux IDE, very close to Visual Studio in terms of user experience. Other choices are CLion, CMake, etc.

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

* new market order: o|MKT|AAPL STK SMART|100
* new limit order: o|LMT|AAPL STK SMART|100|170.00
* tick message: AAPL STK SMART|time|data type|price|size|depth

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

In EliteQuant, an instrument is identified by its **full symbol**, which consists of a couple fo words separated by space. The general pattern is "Local_Symbol Security_Type Exchange_Name Multiplier). For example

* Stock: SPY STK SMART
* Future: ESZ7 FUT GLOBEX 50
* FX: EUR.USD CASH IDEALPRO
* FX futures: 6BU1 FUT GLOBELX
* Option: GOOGL_140920P00535000 OPT SMART 100
* Futures Options: EWQ4_C1730 FOP GLOBEX 50

### Code Structure

![Code Structure](/resource/code_structure_en.png?raw=true "Code Structure")

## Todo List

* QT GUI: currently it is purely command line based, the plan is to add QT user interface.