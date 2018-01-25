#include <Common/Account/accountmanager.h>

namespace EliteQuant {
	AccountManager* AccountManager::pinstance_ = nullptr;
	mutex AccountManager::instancelock_;

	AccountManager::AccountManager()
	{
	}

	AccountManager::~AccountManager()
	{
		// release all the orders
	}

	AccountManager& AccountManager::instance() {
		if (pinstance_ == nullptr) {
			std::lock_guard<mutex> g(instancelock_);
			if (pinstance_ == nullptr) {
				pinstance_ = new AccountManager();
			}
		}
		return *pinstance_;
	}

	void AccountManager::reset(YAML::Node config) {
		accounts_.clear();

		// initialize accounts from server_config.yaml
		const std::vector<string> accounts = config["accounts"].as<std::vector<string>>();
		for (auto s : accounts) {
			AccountInfo a;
			a.AccountID = s;
			a.api = config[s]["api"].as<std::string>();
			a.brokerage = config[s]["broker"].as<std::string>();
			accounts_[s] = a;
		}
	}

	void AccountManager::gotAccount(AccountInfo& a) {
		auto iter = accounts_.find(a.AccountID);
		if (iter != accounts_.end()) {		// account exists, update
			iter->second.PreviousDayEquityWithLoanValue = a.PreviousDayEquityWithLoanValue;
			iter->second.CashBalance = a.CashBalance;
			iter->second.AvailableFunds = a.AvailableFunds;
			iter->second.Commission = a.Commission;
			iter->second.FullInitialMargin = a.FullInitialMargin;
			iter->second.FullMaintainanceMargin = a.FullMaintainanceMargin;
			iter->second.RealizedPnL = a.RealizedPnL;
			iter->second.UnrealizedPnL = a.UnrealizedPnL;
			iter->second.timestamp = a.timestamp;
		}
		else {                  // add to the map; unknown brokerage and api
			AccountInfo a_ = a;
			accounts_[a_.AccountID] = a_;

			PRINT_TO_FILE_AND_CONSOLE("ERROR:[%s,%d][%s]Unknown account received; account id=%s\n", __FILE__, __LINE__, __FUNCTION__, a_.AccountID.c_str());
		}
	}
}

