#ifndef _EliteQuant_Common_PortfolioManager_H_
#define _EliteQuant_Common_PortfolioManager_H_

#include <string>
#include <assert.h>
#include <numeric>
#include <mutex>
#include <regex>
#include <atomic>
#include <map>
#include <Common/config.h>
#include <Common/Account/accountinfo.h>
#include <Common/Security/position.h>
#include <Common/Security/security.h>
#include <Common/Order/orderstatus.h>
#include <Common/Order/order.h>
#include <Common/Logger/logger.h>

using namespace std;

namespace EliteQuant {
	class DLL_EXPORT_IMPORT PortfolioManager {
	public:
		PortfolioManager();
		~PortfolioManager();
		static PortfolioManager* pinstance_;
		static mutex instancelock_;
		static PortfolioManager& instance();
		//atomic<uint64_t> _count = { 0 };
		uint64_t _count = 0;
		AccountInfo _account;

		map<string, Security> _securities;			// fullsymbol --> sec info
		map<string, Position> _positions;			// fullsymbol --> size
		double _cash;

		void reset();
		void rebuild();

		void onSecurity(Security& sec);
		void Add(Position& pos);
		double Adjust(Fill& fill);
	};
}

#endif  // _EliteQuant_Common_PortfolioManager_H_