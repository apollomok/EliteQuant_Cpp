#ifndef _EliteQuant_Common_AccountManager_H_
#define _EliteQuant_Common_AccountManager_H_

#include <string>
#include <sstream>
#include <map>
#include <regex>
#include <mutex>
#include <yaml-cpp/yaml.h>
#include <Common/config.h>
#include <Common/Account/accountinfo.h>

using std::string;

namespace EliteQuant
{
	// multiple accounts
	class DLL_EXPORT_IMPORT AccountManager {
	public:
		AccountManager();
		~AccountManager();
		static AccountManager* pinstance_;
		static mutex instancelock_;
		static AccountManager& instance();

		std::map<string, AccountInfo> accounts_;			// AccountInfo.AccountID --> AccountInfo
		void reset(YAML::Node config);
		void gotAccount(AccountInfo& a);

	};
}

#endif // _EliteQuant_Common_AccountManager_H_