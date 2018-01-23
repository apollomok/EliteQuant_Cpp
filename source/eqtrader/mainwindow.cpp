#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <util/util.h>
#include <boost/filesystem.hpp>
#include <Common/Data/datatype.h>
#include <yaml-cpp/yaml.h>
#include <QDir>
#include <iostream>
#include <algorithm>
#include <Common/config.h>
#include <common/Data/tick.h>

using namespace EliteQuant;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter_2->setStretchFactor(0,3);
    ui->splitter_2->setStretchFactor(1,1);
    ui->splitter_3->setStretchFactor(0,3);
    ui->splitter_3->setStretchFactor(1,2);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSortingEnabled(false);


    this->GetConfig();
    this->InitMarket();
    setWindowState(Qt::WindowMaximized);
    clientMQ=new ClientMQ();
    connect(this, SIGNAL(PlaceOrder(QString)),clientMQ, SLOT(PlaceOrderSlot(QString)));
    connect(clientMQ, SIGNAL(UpdateSignal(string)),this, SLOT(ShowSingal(string)));
    clientMQ->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitMarket()
{
    if(securities.size()>0)
    {
        ui->tableWidget->setRowCount(securities.size());
        int nColumn = ui->tableWidget->columnCount()-1;
        for(int i =0;i<securities.size();i++)
        {
			QString s = securities[i];
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(s));
            for (int j = 1; j<nColumn; j++)
            {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem("0.0"));
            }
        }
    }
}

void MainWindow::GetConfig()
{

    //QString path;
    //QDir dir;
    //path=dir.currentPath().append("/config_server.yaml");
	//std::cout << QDir::currentPath().toStdString() << std::endl;
	string path = boost::filesystem::current_path().string() + "/config_server.yaml";
	std::cout << "eqserver running in path " << path << std::endl;
	YAML::Node config = YAML::LoadFile(path);

    const std::vector<string> accounts = config["accounts"].as<std::vector<string>>();
    for (auto s : accounts) {
        const string api = config[s]["api"].as<std::string>();
        if (api == "IB") {

            account = s;
            ib_port = config[s]["port"].as<long>();
        }
        else if (api == "CTP") {

            ctp_broker_id = config[s]["broker"].as<std::string>();
            ctp_user_id = s;
            ctp_password = config[s]["password"].as<std::string>();
            ctp_auth_code = config[s]["auth_code"].as<std::string>();
            ctp_user_prod_info = config[s]["user_prod_info"].as<std::string>();
            ctp_data_address = config[s]["md_address"].as<std::string>();
            ctp_broker_address = config[s]["td_address"].as<std::string>();
        }


        securities.clear();
        const std::vector<string> tickers = config[s]["tickers"].as<std::vector<string>>();
        for (auto s : tickers)
        {
            securities.push_back(s.c_str());
        }
    }
}

void MainWindow::ShowSingal(string sMessage)
{
	// std::cout << sMessage << std::endl;
	vector<string> v = stringsplit(sMessage, SERIALIZATION_SEPARATOR);
	FullTick k;

    k.fullsymbol_ = v[0];
    k.time_ = v[1];
    k.datatype_ = DataType(stoi(v[2]));
	k.price_ = stof(v[3]);
	k.size_ = stoi(v[4]);
	k.depth_ = stoi(v[5]);

    if (k.datatype_ == DataType::DT_Full)
    {
		k.bidprice_L1_ = stoi(v[6]);
		k.bidsize_L1_ = stoi(v[7]);
		k.askprice_L1_ = stoi(v[8]);
		k.asksize_L1_ = stoi(v[9]);
		k.open_interest = stoi(v[10]);
		k.open_ = stoi(v[11]);
		k.high_ = stoi(v[12]);
		k.low_ = stoi(v[13]);
		k.pre_close_ = stoi(v[14]);
		k.upper_limit_price_ = stoi(v[15]);
		k.lower_limit_price_ = stoi(v[16]);
    }
	
    auto index =std::find(securities.begin(),securities.end(),QString(k.fullsymbol_.c_str()));

    if(index==securities.end())
    {
        return;
    }
    int row =index-securities.begin();

    if (k.price_ > 0.0)
    {
        ui->tableWidget->item(row,1)->setText(QString(k.fullsymbol_.c_str()));
		ui->tableWidget->item(row, 13)->setText(QString(k.time_.c_str()));


        if (k.datatype_ == DataType::DT_Bid)
        {
            ui->tableWidget->item(row,5)->setText(QString::number(k.size_));
            ui->tableWidget->item(row,6)->setText(QString::number(k.price_));
        }
        else if (k.datatype_ == DataType::DT_Ask)
        {
            ui->tableWidget->item(row,7)->setText(QString::number(k.price_));
            ui->tableWidget->item(row,8)->setText(QString::number(k.size_));
        }
        else if(k.datatype_ ==DataType::DT_Trade)
        {
            ui->tableWidget->item(row,2)->setText(QString::number(k.price_));
            ui->tableWidget->item(row,3)->setText(QString::number(k.size_));
        }
        else if (k.datatype_ == DataType::DT_Full)
        {
            ui->tableWidget->item(row,2)->setText(QString::number(k.price_));
            ui->tableWidget->item(row,3)->setText(QString::number(k.size_));
            ui->tableWidget->item(row,4)->setText(QString::number(k.open_interest));
            ui->tableWidget->item(row,5)->setText(QString::number(k.bidsize_L1_));
            ui->tableWidget->item(row,6)->setText(QString::number(k.bidprice_L1_));
            ui->tableWidget->item(row,7)->setText(QString::number(k.askprice_L1_));
            ui->tableWidget->item(row,8)->setText(QString::number(k.asksize_L1_));
            ui->tableWidget->item(row,9)->setText(QString::number(k.pre_close_));
            ui->tableWidget->item(row,10)->setText(QString::number(k.open_));
            ui->tableWidget->item(row,11)->setText(QString::number(k.high_));
            ui->tableWidget->item(row,12)->setText(QString::number(k.low_));
        }
    }
}

void MainWindow::on_pushButton_Order_clicked()
{
    QString order;
    //合约代码
    QString s=ui->LineEditCode->text();
    //方向
    int n=ui->ComboBoxDirection->currentIndex();
    //开平
    QString f =QString::number(ui->ComboBox_BuyOrSell->currentIndex(),10);
    //价格
    QString p =ui->LineEdit_Price->text();
    //数量
    QString q =ui->LineEdit_Quantity->text();
    //指令类型
    int t = ui->ComboBox_OrderType->currentIndex();
    if (t == 0)
    {
        order.append("o|MKT|");
        order.append(s);
        order.append("|");
        if(n==0)
        {
            order.append(q);
        }
        else
        {
            order.append("-");
            order.append(q);
        }
    }
    else if(t == 1)
    {
        order.append("o|LMT|");
        order.append(s);
        order.append("|");
        if(n==0)
        {
            order.append(q);
        }
        else
        {
            order.append("-");
            order.append(q);
        }
        order.append("|");
        order.append(p);
        order.append("|");
        order.append(f);
    }

    emit PlaceOrder(order);
}
