#include <mutex>
#include <Common/Order/orderstatus.h>
#include <Common/Order/fill.h>
#include <Common/Order/ordermanager.h>
#include <Common/Data/datamanager.h>
#include <Common/Logger/logger.h>
#include <Common/Util/util.h>
#include <Brokers/Ctp/ctpbrokerage.h>

using namespace std;
namespace EliteQuant
{
	extern std::atomic<bool> gShutdown;

	ctpbrokerage::ctpbrokerage() {
		string path = CConfig::instance().logDir() + "/ctp/";
		boost::filesystem::path dir(path.c_str());
		boost::filesystem::create_directory(dir);

		///创建TraderApi
		///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
		///@return 创建出的UserApi
		this->api_ = CThostFtdcTraderApi::CreateFtdcTraderApi(path.c_str());
		///注册回调接口
		///@param pSpi 派生自回调接口类的实例
		this->api_->RegisterSpi(this);

		isConnected_ = false;
		isLogedin_ = false;
		isAuthenticated_ = false;
		requireAuthentication_ = false;
		reqId_ = 0;
		orderRef_ = 0;
		frontID_ = 0;
		sessionID_ = 0;
	}

	ctpbrokerage::~ctpbrokerage() {
		if (api_ != NULL) {
			disconnectFromBrokerage();
		}
	}

	void ctpbrokerage::processBrokerageMessages()
	{
		if (!brokerage::heatbeat(5)) {
			disconnectFromBrokerage();
			return;
		}
		switch (_bkstate) {
		case BK_ACCOUNT:		// not used
			break;
		case BK_ACCOUNTACK:		// not used
			break;
		case BK_GETORDERID:		// start from here
			requestNextValidOrderID();
			break;
		case BK_GETORDERIDACK:
			break;
		case BK_READYTOORDER:
			monitorClientRequest();
			break;
		case BK_PLACEORDER_ACK:
			break;
		case BK_CANCELORDER:
			cancelOrder(0); //TODO
			break;
		case BK_CANCELORDER_ACK:
			break;
		}
	}

	bool ctpbrokerage::connectToBrokerage() {
		if (!isConnected_) {
			//订阅共有流、私有流
			THOST_TE_RESUME_TYPE type = THOST_TERT_RESTART;		// THOST_TERT_RESUME, THOST_TERT_QUICK
			this->api_->SubscribePrivateTopic(type);
			this->api_->SubscribePublicTopic(type);

			// 注册前置机并初始化
			this->api_->RegisterFront((char*)CConfig::instance().ctp_broker_address.c_str());

			// 成功后调用 onFrontConnected
			this->api_->Init();

			PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp brokerage connection connected!\n", __FILE__, __LINE__, __FUNCTION__);
			
			sendGeneralMessage("Connected to ctp brokerage");
		}

		return true;
	}

	void ctpbrokerage::disconnectFromBrokerage() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp brokerage connection disconnected!\n", __FILE__, __LINE__, __FUNCTION__);

		this->api_->RegisterSpi(NULL);
		this->api_->Release();
		this->api_ = NULL;
		isConnected_ = false;
	}

	bool ctpbrokerage::isConnectedToBrokerage() const {
		return (isConnected_);				// automatic disconnect when shutdown
	}

	void ctpbrokerage::placeOrder(std::shared_ptr<Order> order) {
		if (order->orderStatus != OrderStatus::OS_NewBorn)
			return;

		// send order
		CThostFtdcInputOrderField orderfield = CThostFtdcInputOrderField();

		strcpy(orderfield.InstrumentID, order->fullSymbol.c_str());
		orderfield.VolumeTotalOriginal = std::abs(order->orderSize);

		// CTP的模拟交易不支持市价报单
		orderfield.OrderPriceType = order->orderType == "MKT" ? THOST_FTDC_OPT_AnyPrice : THOST_FTDC_OPT_LimitPrice;
		orderfield.LimitPrice = order->orderType == "MKT" ? 0.0 : order->limitPrice;
		orderfield.Direction = order->orderSize > 0 ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;

		switch (order->orderFlag) {
			case OrderFlag::OF_OpenPosition:
				orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_Open;	// 开仓
				break;
			case OrderFlag::OF_ClosePosition:
				orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_Close;	// 平仓
				break;
			case OrderFlag::OF_CloseToday:
				orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;	// 平今
				break;
			case OrderFlag::OF_CloseYesterday:
				orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;	// 平昨
				break;
			default:
				orderfield.CombOffsetFlag[0] = THOST_FTDC_OF_Open;	// 开仓
				break;
		}

		strcpy(orderfield.OrderRef, to_string(order->orderId).c_str());

		strcpy(orderfield.InvestorID, CConfig::instance().ctp_user_id.c_str());
		strcpy(orderfield.UserID, CConfig::instance().ctp_user_id.c_str());
		strcpy(orderfield.BrokerID, CConfig::instance().ctp_broker_id.c_str());

		orderfield.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;			// 投机单
		orderfield.ContingentCondition = THOST_FTDC_CC_Immediately;		// 立即发单
		orderfield.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;		// 非强平
		orderfield.IsAutoSuspend = 0;									// 非自动挂起
		orderfield.UserForceClose = 0;									// 非用户强平
		orderfield.TimeCondition = THOST_FTDC_TC_GFD;					// 今日有效
		orderfield.VolumeCondition = THOST_FTDC_VC_AV;					// 任意成交量
		orderfield.MinVolume = 1;										// 最小成交量为1

		// TODO: 判断FAK和FOK
		//orderfield.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		//orderfield.TimeCondition = THOST_FTDC_TC_IOC;
		//orderfield.VolumeCondition = THOST_FTDC_VC_CV;				// FAK; FOK uses THOST_FTDC_VC_AV

		int i = api_->ReqOrderInsert(&orderfield, reqId_++);

		lock_guard<mutex> g(orderStatus_mtx);

		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Placing Order orderId=%ld: fullSymbol=%s\n", __FILE__, __LINE__, __FUNCTION__, order->orderId, order->fullSymbol.c_str());

		order->orderStatus = OrderStatus::OS_Submitted;
		sendOrderSubmitted(order->orderId);
	}

	void ctpbrokerage::requestNextValidOrderID() {
		if (_bkstate < BK_GETORDERIDACK)
			_bkstate = BK_GETORDERIDACK;

		lock_guard<mutex> g(oid_mtx);
		m_orderId = 0;

		// TODO: if isAuthenticate, go to authenticate
		if (!isLogedin_) {
			requestUserLogin();
		}
	}


	void ctpbrokerage::reqGlobalCancel() {
	}

	// does not accept cancel order
	void ctpbrokerage::cancelOrder(int oid) {
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order m_orderId=%ld\n", __FILE__, __LINE__, __FUNCTION__, (long)m_orderId);

		CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
		std::shared_ptr<Order> o = OrderManager::instance().retrieveOrder(oid);
		strcpy(myreq.InstrumentID, o->fullSymbol.c_str());
		//strcpy(myreq.ExchangeID, o->.c_str());			// TODO: get exchangeID from fullSymbol, e.g. "SHFE"  IF1709 FUT CFFEX 300, where 300 is multiplier
		strcpy(myreq.OrderRef, to_string(oid).c_str());
		// myreq.OrderSysID		// TODO: what is this used for?
		myreq.FrontID = frontID_;
		myreq.SessionID = sessionID_;
		myreq.ActionFlag = THOST_FTDC_AF_Delete;

		strcpy(myreq.InvestorID, CConfig::instance().ctp_user_id.c_str());
		strcpy(myreq.BrokerID, CConfig::instance().ctp_broker_id.c_str());

		int i = this->api_->ReqOrderAction(&myreq, reqId_++);
	}

	void ctpbrokerage::cancelOrders(const string& symbol) {
		PRINT_TO_FILE_AND_CONSOLE("INFO:[%s,%d][%s]Cancel Order symbol=%s\n", __FILE__, __LINE__, __FUNCTION__, symbol.c_str());
	}

	void ctpbrokerage::cancelAllOrders() {
		lock_guard<mutex> _g(mtx_CANCELALL);
	}

	// 查询账户
	void ctpbrokerage::requestBrokerageAccountInformation(const string& account_) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker requests brokerage account information.\n", __FILE__, __LINE__, __FUNCTION__);

		CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();

		// strcpy(myreq.BrokerID, id->getBrokerID().toStdString().c_str());
		// strcpy(myreq.InvestorID, id->getInvestorID().toStdString().c_str());

		// triggers OnRspQryTradingAccount
		int i = this->api_->ReqQryTradingAccount(&myreq, reqId_++);			// return 0 = 发送投资者资金账户查询请求失败
	}

	void ctpbrokerage::requestOpenOrders() {
	}

	void ctpbrokerage::reqAllOpenOrders() {

	}

	void ctpbrokerage::reqAutoOpenOrders(bool) {

	}

	void ctpbrokerage::requestAuthenticate(string userid, string authcode, string brokerid, string userproductinfo) {
		CThostFtdcReqAuthenticateField authField;

		strcpy(authField.UserID, userid.c_str());
		strcpy(authField.BrokerID, brokerid.c_str());
		strcpy(authField.AuthCode, authcode.c_str());
		strcpy(authField.UserProductInfo, userproductinfo.c_str());

		this->api_->ReqAuthenticate(&authField, reqId_++);
	}

	///用户登录请求
	void ctpbrokerage::requestUserLogin() {
		CThostFtdcReqUserLoginField loginField = CThostFtdcReqUserLoginField();

		strcpy(loginField.BrokerID, CConfig::instance().ctp_broker_id.c_str());
		strcpy(loginField.UserID, CConfig::instance().ctp_user_id.c_str());
		strcpy(loginField.Password, CConfig::instance().ctp_password.c_str());

		int i = this->api_->ReqUserLogin(&loginField, reqId_++);
	}

	///登出请求
	void ctpbrokerage::requestUserLogout() {
		CThostFtdcUserLogoutField logoutField = CThostFtdcUserLogoutField();

		strcpy(logoutField.BrokerID, CConfig::instance().ctp_broker_id.c_str());
		strcpy(logoutField.UserID, CConfig::instance().ctp_user_id.c_str());

		int i = this->api_->ReqUserLogout(&logoutField, reqId_++);
	}

	/// 查询账户， trigger onRspQryInvestorPosition
	void ctpbrokerage::requestOpenPositions() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker requests open positions.\n", __FILE__, __LINE__, __FUNCTION__);

		CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();

		strcpy(myreq.BrokerID, CConfig::instance().ctp_broker_id.c_str());
		strcpy(myreq.InvestorID, CConfig::instance().ctp_user_id.c_str());

		int i = this->api_->ReqQryInvestorPosition(&myreq, reqId_++);		// return 0 = 发送投资者持仓查询请求失败
	}

	/// 投资者结算结果确认, trigger response onRspSettlementInfoConfirm
	void ctpbrokerage::requestSettlementInfoConfirm() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker requests settlement info comfirm.\n", __FILE__, __LINE__, __FUNCTION__);

		CThostFtdcSettlementInfoConfirmField myreq = CThostFtdcSettlementInfoConfirmField();
		strcpy(myreq.BrokerID, CConfig::instance().ctp_broker_id.c_str());
		strcpy(myreq.InvestorID, CConfig::instance().ctp_user_id.c_str());
		api_->ReqSettlementInfoConfirm(&myreq, reqId_++);			// return 0 = 发送投资者结算结果确认请求失败
	}

	////////////////////////////////////////////////////// begin callback/incoming function ///////////////////////////////////////
	// TODO: where is OnCancel confirmation ? 
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	void ctpbrokerage::OnFrontConnected() {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker connected; Continue to login.\n", __FILE__, __LINE__, __FUNCTION__);
		//_bkstate = BK_CONNECT;
		isConnected_ = true;
		reqId_ = 0;
	}

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	void ctpbrokerage::OnFrontDisconnected(int nReason) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker disconnected, nReason=%d.\n", __FILE__, __LINE__, __FUNCTION__, nReason);
		_bkstate = BK_DISCONNECTED;
		isConnected_ = false;
		isLogedin_ = false;
	}

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	void ctpbrokerage::OnHeartBeatWarning(int nTimeLapse) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp brokerage heartbeat overtime error, nTimeLapse=%d.\n", __FILE__, __LINE__, __FUNCTION__, nTimeLapse);
	}

	///客户端认证响应
	void ctpbrokerage::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		if (pRspInfo->ErrorID == 0) {
			PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker authenticated. Continue to log in.\n", __FILE__, __LINE__, __FUNCTION__);

			//TODO 一：authentification before login
		}
	}

	/// 登录请求响应
	void ctpbrokerage::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		if (pRspInfo->ErrorID == 0) {
			// 保存会话参数
			// TODO: what frontID_ and sessionID_ are used for? -- one place is in cancelOrder
			frontID_ = pRspUserLogin->FrontID;
			sessionID_ = pRspUserLogin->SessionID;

			isLogedin_ = true;
			isConnected_ = true;

			PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server user logged in, TradingDay=%s, LoginTime=%s, BrokerID=%s, UserID=%s, frontID=%d, sessionID=%d, MaxOrderRef=%s\n.",
				__FILE__, __LINE__, __FUNCTION__,
				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID, pRspUserLogin->UserID, pRspUserLogin->FrontID, pRspUserLogin->SessionID, pRspUserLogin->MaxOrderRef);

			// https://stackoverflow.com/questions/22753328/c-error-expression-must-have-integral-or-enum-type-getting-this-from-a-s
			sendGeneralMessage(string("Ctp broker server user logged in:") +
				SERIALIZATION_SEPARATOR + to_string(frontID_) + SERIALIZATION_SEPARATOR + to_string(sessionID_));

			// TODO: pRspUserLogin->MaxOrderRef used for?  
			// strcpy(order_ref, pRspUserLogin->MaxOrderRef);

			if (_bkstate <= BK_READYTOORDER)
				_bkstate = BK_READYTOORDER;

			// TODO二: 放在 _bkstate 改变后面行吗？
			requestBrokerageAccountInformation("");
			requestOpenPositions();
			requestSettlementInfoConfirm();
		}
		else {
			PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server user login failed: ErrorID=%d, ErrorMsg=%s.\n",
				__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

			sendGeneralMessage(string("CTP Trader Server OnRspUserLogin error:") +
				SERIALIZATION_SEPARATOR + to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
		}
	}

	///登出请求响应
	void ctpbrokerage::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		if (pRspInfo->ErrorID == 0) {
			PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server user logged out, BrokerID=%s, UserID=%s.\n",
				__FILE__, __LINE__, __FUNCTION__, pUserLogout->BrokerID, pUserLogout->UserID);
			isLogedin_ = false;
			isConnected_ = false;
		}
		else {
			PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server user logout failed: ErrorID=%d, ErrorMsg=%s.\n",
				__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

			sendGeneralMessage(string("CTP Trader Server OnRspUserLogout error:") +
				SERIALIZATION_SEPARATOR + to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
		}
	}

	///报单录入请求响应(参数不通过)
	void ctpbrokerage::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
		if (!bResult)
		{
			PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server OnRspOrderInsert: OrderRef=%s, InstrumentID=%s, LimitPrice=%.2f, VolumeTotalOriginal=%d, Direction=%c.\n",
				__FILE__, __LINE__, __FUNCTION__, pInputOrder->OrderRef, pInputOrder->InstrumentID, pInputOrder->LimitPrice, pInputOrder->VolumeTotalOriginal, pInputOrder->Direction);

			lock_guard<mutex> g(orderStatus_mtx);
			std::shared_ptr<Order> o = OrderManager::instance().retrieveOrder(std::stoi(pInputOrder->OrderRef));
			o->orderStatus = OS_Acknowledged;			// TODO 三：应该是rejected ?

			sendOrderStatus(std::stoi(pInputOrder->OrderRef));
			sendGeneralMessage(string("CTP Trader Server OnRspOrderInsert order acknowledged:") +
				SERIALIZATION_SEPARATOR + to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
		}
		else
		{
			PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server OnRspOrderInsert: ErrorID=%d, ErrorMsg=%s.\n",
				__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

			lock_guard<mutex> g(orderStatus_mtx);
			std::shared_ptr<Order> o = OrderManager::instance().retrieveOrder(std::stoi(pInputOrder->OrderRef));
			o->orderStatus = OS_Error;			// rejected ?

			sendOrderStatus(std::stoi(pInputOrder->OrderRef));
			sendGeneralMessage(string("CTP Trader Server OnRspOrderInsert error:") +
				SERIALIZATION_SEPARATOR + to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
		}
	}

	///报单操作请求响应(参数不通过)
	// 撤单错误（柜台）
	void ctpbrokerage::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
		if (!bResult)
		{
			PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server OnRspOrderAction: OrderRef=%s, InstrumentID=%s, ActionFlag=%c.\n",
				__FILE__, __LINE__, __FUNCTION__, pInputOrderAction->OrderRef, pInputOrderAction->InstrumentID, pInputOrderAction->ActionFlag);
		}
		else
		{
			PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server OnRspOrderAction failed: ErrorID=%d, ErrorMsg=%s.\n",
				__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

			sendGeneralMessage(to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
		}
	}

	///投资者结算结果确认响应
	void ctpbrokerage::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server OnRspSettlementInfoConfirm, ConfirmDate=%s, ConfirmTime=%s.\n",
			__FILE__, __LINE__, __FUNCTION__, pSettlementInfoConfirm->ConfirmDate, pSettlementInfoConfirm->ConfirmTime);

		// 查询合约代码, trigger response OnRspQryInstrument
		CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
		int i = this->api_->ReqQryInstrument(&myreq, reqId_++);
	}

	///请求查询投资者持仓响应 (respond to requestOpenPositions)
	void ctpbrokerage::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server OnRspQryInvestorPosition, InstrumentID=%s, InvestorID=%s, OpenAmount=%f, OpenVolume=%d, PosiDirection=%c, PositionProfit=%.2f, PositionCost=%.2f, UseMargin=%.2f, LongFrozen=%d, ShortFrozen=%d, TradingDay=%s, YdPosition=%d.\n",
			__FILE__, __LINE__, __FUNCTION__, pInvestorPosition->InstrumentID, pInvestorPosition->InvestorID, pInvestorPosition->OpenAmount, pInvestorPosition->OpenVolume,
			pInvestorPosition->PosiDirection, pInvestorPosition->PositionProfit, pInvestorPosition->PositionCost, pInvestorPosition->UseMargin,
			pInvestorPosition->LongFrozen, pInvestorPosition->ShortFrozen, pInvestorPosition->TradingDay, pInvestorPosition->YdPosition);

		// TODO: 针对上期所持仓的今昨分条返回（有昨仓、无今仓），读取昨仓数据
		// pInvestorPosition->YdPosition;
		// TODO: 汇总总仓, 计算持仓均价, 读取冻结

		sendOpenPositionMessage(pInvestorPosition->InstrumentID, (pInvestorPosition->PosiDirection == THOST_FTDC_PD_Long ? 1 : -1) * pInvestorPosition->Position,
			pInvestorPosition->PositionCost, pInvestorPosition->CloseAmount, pInvestorPosition->CloseProfit);
	}

	///请求查询资金账户响应 (respond to requestAccount)
	void ctpbrokerage::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		// 资金账户查询回报
		// TODO: send account information

		// 这里的balance和快期中的账户不确定是否一样，需要测试
		double balance = pTradingAccount->PreBalance - pTradingAccount->PreCredit - pTradingAccount->PreMortgage
			+ pTradingAccount->Mortgage - pTradingAccount->Withdraw + pTradingAccount->Deposit
			+ pTradingAccount->CloseProfit + pTradingAccount->PositionProfit + pTradingAccount->CashIn - pTradingAccount->Commission;

		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server OnRspQryTradingAccount: AccountID=%s, Available=%.2f, PreBalance=%.2f, Deposit=%.2f, Withdraw=%.2f, WithdrawQuota=%.2f, Commission=%.2f, CurrMargin=%.2f, FrozenMargin=%.2f, CloseProfit=%.2f, PositionProfit=%.2f, balance=%.2f.\n",
			__FILE__, __LINE__, __FUNCTION__, pTradingAccount->AccountID, pTradingAccount->Available, pTradingAccount->PreBalance,
			pTradingAccount->Deposit, pTradingAccount->Withdraw, pTradingAccount->WithdrawQuota, pTradingAccount->Commission,
			pTradingAccount->CurrMargin, pTradingAccount->FrozenMargin, pTradingAccount->CloseProfit, pTradingAccount->PositionProfit, balance);
	}

	///请求查询合约响应 (respond to ReqQryInstrument)
	void ctpbrokerage::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		// 合约查询回报
		// pInstrument->StrikePrice; pInstrument->EndDelivDate; pInstrument->IsTrading;
		PRINT_TO_FILE("INFO:[%s,%d][%s]Ctp broker server OnRspQryInstrument: InstrumentID=%s, InstrumentName=%s, ExchangeID=%s, ExchangeInstID=%s, VolumeMultiple=%d, PriceTick=%.2f, UnderlyingInstrID=%s, ProductClass=%c, ExpireDate=%s, LongMarginRatio=%.2f.\n",
			__FILE__, __LINE__, __FUNCTION__, pInstrument->InstrumentID, pInstrument->InstrumentName, pInstrument->ExchangeID, pInstrument->ExchangeInstID,
			pInstrument->VolumeMultiple, pInstrument->PriceTick, pInstrument->UnderlyingInstrID, pInstrument->ProductClass, pInstrument->ExpireDate, pInstrument->LongMarginRatio);

		char buffer[150];
		//sprintf(buffer, "%s,%s,%s, %s", pInstrument->InstrumentID, pInstrument->InstrumentName, pInstrument->ExchangeID, pInstrument->ExpireDate);
		//sendGeneralMessage(buffer);
	}

	///错误应答
	void ctpbrokerage::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server OnRspError: ErrorID=%d, ErrorMsg=%s.\n",
			__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		sendGeneralMessage(string("CTP Trader Server OnRspError") +
			SERIALIZATION_SEPARATOR + to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
	}

	///报单通知
	void ctpbrokerage::OnRtnOrder(CThostFtdcOrderField *pOrder) {
		// 报单回报
		// pOrder->ExchangeID		交易所编号 
		// pOrder->InstrumentID		合约代码
		// pOrder->OrderRef			报单引用
		// pOrder->Direction		买卖方向
		// pOrder->CombOffsetFlag	组合开平标志
		// pOrder->LimitPrice		价格
		// pOrder->VolumeTotalOriginal		数量
		// pOrder->VolumeTraded		今成交数量
		// pOrder->VolumeTotal		剩余数量
		// Order->OrderSysID		报单编号（判断报单是否有效）
		// pOrder->OrderStatus		报单状态
		// pOrder->InsertDate		报单日期
		// pOrder->SequenceNo		序号
		PRINT_TO_FILE("INFO:[%s,%d][%s]CTP trade server OnRtnOrder details: OrderRef=%s, InstrumentID=%s, ExchangeID=%s, InsertTime=%s, CancelTime=%s, FrontID=%d, SessionID=%d, Direction=%c, CombOffsetFlag=%s, OrderStatus=%c, OrderSubmitStatus=%c, StatusMsg=%s, LimitPrice=%f, VolumeTotalOriginal=%d, VolumeTraded=%d, OrderSysID=%s, SequenceNo=%d.\n",
			__FILE__, __LINE__, __FUNCTION__, pOrder->InstrumentID, pOrder->ExchangeID, pOrder->OrderRef, pOrder->InsertTime, pOrder->CancelTime,
			pOrder->FrontID, pOrder->SessionID, pOrder->Direction, pOrder->CombOffsetFlag, pOrder->OrderStatus, pOrder->OrderSubmitStatus, pOrder->StatusMsg,
			pOrder->LimitPrice, pOrder->VolumeTotalOriginal, pOrder->VolumeTraded, pOrder->OrderSysID, pOrder->SequenceNo);	// TODO: diff between tradeid and orderref

		// increase order_id
		int nOrderref = std::stoi(pOrder->OrderRef);
		if (m_orderId <= (nOrderref+1))
			m_orderId = nOrderref + 1;

		OrderManager::instance().gotOrder(nOrderref);
		sendOrderAcknowledged(nOrderref);
	}

	/// 成交通知
	void ctpbrokerage::OnRtnTrade(CThostFtdcTradeField *pTrade) {
		PRINT_TO_FILE("INFO:[%s,%d][%s]CTP trade server OnRtnTrade details: TradeID=%s, OrderRef=%s, InstrumentID=%s, ExchangeID=%s, TradeTime=%s, OffsetFlag=%c, Direction=%c, Price=%f, Volume=%d.\n",
			__FILE__, __LINE__, __FUNCTION__, pTrade->TradeID, pTrade->OrderRef, pTrade->InstrumentID, pTrade->ExchangeID, pTrade->TradeTime,
			pTrade->OffsetFlag, pTrade->Direction, pTrade->Price, pTrade->Volume);		// TODO: diff between tradeid and orderref

		time_t current_time;
		time(&current_time);

		Fill t;
		t.fullSymbol = pTrade->InstrumentID;
		t.tradetime = tointtime(current_time);
		t.tradeId = std::stoi(pTrade->OrderRef);
		t.tradePrice = pTrade->Price;
		t.tradeSize = (pTrade->Direction == THOST_FTDC_D_Buy ? 1 : -1)*pTrade->Volume;
		OrderManager::instance().gotFill(t);
		sendOrderFilled(t);		// BOT SLD
	}

	///报单录入错误回报
	void ctpbrokerage::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
		PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server OnErrRtnOrderInsert: ErrorID=%d, ErrorMsg=%s, OrderRef=%s, InstrumentID=%s, ExchangeID=%s, Direction=%c, CombOffsetFlag=%s, LimitPrice=%f, VolumeTotalOriginal=%d.\n",
			__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg,
			pInputOrder->OrderRef, pInputOrder->InstrumentID, pInputOrder->ExchangeID,
			pInputOrder->Direction, pInputOrder->CombOffsetFlag, pInputOrder->LimitPrice, pInputOrder->VolumeTotalOriginal);

		lock_guard<mutex> g(orderStatus_mtx);
		std::shared_ptr<Order> o = OrderManager::instance().retrieveOrder(std::stoi(pInputOrder->OrderRef));
		if (o != nullptr) {
			o->orderStatus = OS_Error;			// rejected
			sendOrderStatus(std::stoi(pInputOrder->OrderRef));
		}
	}

	///报单操作错误回报
	void ctpbrokerage::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
		PRINT_TO_FILE("ERROR:[%s,%d][%s]Ctp broker server OnErrRtnOrderAction: ErrorID=%d, ErrorMsg=%s.\n",
			__FILE__, __LINE__, __FUNCTION__, pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		sendGeneralMessage(string("CTP Trader Server OnErrRtnOrderAction") +
			SERIALIZATION_SEPARATOR + to_string(pRspInfo->ErrorID) + SERIALIZATION_SEPARATOR + pRspInfo->ErrorMsg);
	}
	////////////////////////////////////////////////////// end callback/incoming function ///////////////////////////////////////

	// https://www.cplusplus.me/1780.html          -------- Doesn't work
	/*string ctpbrokerage::UTF8ToGBK(const std::string & strUTF8) {
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	//unsigned short * wszGBK = new unsigned short[len + 1];
	LPWSTR wszGBK = new WCHAR[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);

	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
	}

	string ctpbrokerage::GBKToUTF8(const std::string & strGBK) {
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;

	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;

	return strOutUTF8;
	}*/
}