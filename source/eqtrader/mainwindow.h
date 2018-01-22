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

#include "clientmq.h"

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
    Ui::MainWindow *ui;

    string ib_host = "127.0.0.1";
    uint64_t ib_port = 7496;
    atomic_int ib_client_id;

    string account = "DU448830";
    string filetoreplay = "";

    string ctp_broker_id = "";
    string ctp_user_id = "";
    string ctp_password = "";
    string ctp_auth_code = "";
    string ctp_user_prod_info = "";
    string ctp_data_address = "";
    string ctp_broker_address = "";

    vector<QString> securities;
    /**************************************** End of Brokeragee ******************************************/

    /******************************************* Message Queue ***********************************************/
    string MKT_DATA_PUBSUB_PORT = "55555";				// market/tick data
    string BROKERAGE_PAIR_PORT = "55556";				// brokerage order, account, etc
    string BAR_AGGREGATOR_PUBSUB_PORT = "55557";		// bar from aggregation service
    string API_PORT = "55558";							// client port
    string API_ZMQ_DATA_PORT = "55559";					// client port

    string tick_msg = "k";
    string last_price_msg = "p";
    string last_size_msg = "z";
    string bar_msg = "b";
    string new_order_msg = "o";
    string cancel_order_msg = "c";
    string order_status_msg = "s";
    string fill_msg = "f";				// including partial fill
    string close_all_msg = "a";
    string position_msg = "n";
    string account_msg = "u";		// user
    string contract_msg = "r";
    string hist_msg = "h";
    string general_msg = "m";
    string test_msg = "e";		// echo
    void GetConfig();
    void InitMarket();

signals:
    void PlaceOrder(QString order);

public slots:
    void    ShowSingal(string   sMessage);
private slots:
    void on_pushButton_Order_clicked();
};

#endif // MAINWINDOW_H
