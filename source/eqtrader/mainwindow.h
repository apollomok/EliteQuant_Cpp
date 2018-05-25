#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <inttypes.h>
#include <cmath>
#include <mutex>
#include <atomic>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <list>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include <Common/Account/accountmanager.h>

#include "clientmq.h"
#include "strategymanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     ClientMQ *clientMQ;

private:
	//************************************** Investment Bank Managers ******************************//
	AccountManager accountManager_;
	//************************************ End of Investment Bank Managers ************************//
	YAML::Node config_client_, config_server_;

    Ui::MainWindow *ui;

    vector<QString> securities;
    vector<QString> orderids;
    map<string, string> contracts;
    StrategyManager *strategyManager;
    void readConfig();
    void InitMarket();

	void OrderStatusHandler(string& msg);
	void FillHandler(string& msg);
	void PositionHandler(string& msg);
	void HistoricalHandler(string& msg);
	void AccountHandler(string& msg);
	void ContractHandler(string& msg);
	void GeneralMessageHandler(string& msg);

signals:
    void OutgoingMessageSignal(string sMessage);

public slots:
    void    IncomingMarketSlot(string   sMessage);
	void    IncomingGeneralSlot(string   sMessage);
private slots:
    void on_pushButton_Order_clicked();
	void SetParamsToOrderWidget(int row, int column);
	void StartStrategy();
	void PauseStrategy();
	void StopStrategy();
	void LiquidateStrategy();
	void TranslateToEnglish();
	void TranslateToChinese();
};

#endif // MAINWINDOW_H
