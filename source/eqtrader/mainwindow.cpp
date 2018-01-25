#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <util/util.h>
#include <boost/filesystem.hpp>
#include <Common/Data/datatype.h>
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

    ui->tableWidgetMarket->setEditTriggers(QAbstractItemView::NoEditTriggers);		// no edit
    ui->tableWidgetMarket->setSelectionBehavior(QAbstractItemView::SelectRows);     // select row
    ui->tableWidgetMarket->verticalHeader()->setVisible(false);
    ui->tableWidgetMarket->setAlternatingRowColors(true);
    ui->tableWidgetMarket->setSortingEnabled(false);

	ui->tableWidgetLog->setEditTriggers(QAbstractItemView::NoEditTriggers);		// no edit
	ui->tableWidgetLog->setSelectionBehavior(QAbstractItemView::SelectRows);     // select row
	ui->tableWidgetLog->verticalHeader()->setVisible(false);
	ui->tableWidgetLog->setAlternatingRowColors(true);
	ui->tableWidgetLog->setSortingEnabled(false);



    this->readConfig();

	accountManager_.reset(config_server_);

    this->InitMarket();
    setWindowState(Qt::WindowMaximized);
    clientMQ=new ClientMQ();
	// https://stackoverflow.com/questions/37057042/how-to-know-in-which-thread-qt-executes-slots
    connect(this, SIGNAL(OutgoingMessageSignal(string)),clientMQ, SLOT(OutgoingMessageSlot(string)));
    connect(clientMQ, SIGNAL(IncomingMarketSignal(string)),this, SLOT(IncomingMarketSlot(string)));
	connect(clientMQ, SIGNAL(IncomingGeneralSignal(string)), this, SLOT(IncomingGeneralSlot(string)));
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
        ui->tableWidgetMarket->setRowCount(securities.size());
        int nColumn = ui->tableWidgetMarket->columnCount()-1;
        for(int i =0;i<securities.size();i++)
        {
			QString s = securities[i];
            ui->tableWidgetMarket->setItem(i, 0, new QTableWidgetItem(s));
            for (int j = 1; j<nColumn; j++)
            {
                ui->tableWidgetMarket->setItem(i, j, new QTableWidgetItem("0.0"));
            }
        }
    }
}

void MainWindow::readConfig()
{
	string path = boost::filesystem::current_path().string() + "/config_client.yaml";
	std::cout << "Reading client config from " << path << std::endl;
	YAML::Node config_client = YAML::LoadFile(path);
	config_client_ = config_client;			// save in memory

	path = boost::filesystem::current_path().string() + "/config_server.yaml";
	std::cout << "Reading server config from " << path << std::endl;
	YAML::Node config = YAML::LoadFile(path);
	config_server_ = config;			// save in memory

    const std::vector<string> accounts = config["accounts"].as<std::vector<string>>();
    for (auto s : accounts) {
        const string api = config[s]["api"].as<std::string>();

        securities.clear();
        const std::vector<string> tickers = config[s]["tickers"].as<std::vector<string>>();
        for (auto s : tickers)
        {
            securities.push_back(s.c_str());
        }
    }
}

void MainWindow::IncomingMarketSlot(string sMessage)
{
	FullTick k;
	k.deserialize(sMessage);
	
    auto index =std::find(securities.begin(),securities.end(),QString(k.fullsymbol_.c_str()));

    if(index==securities.end())
    {
        return;
    }
    int row =index-securities.begin();

    if (k.price_ > 0.0)
    {
        ui->tableWidgetMarket->item(row,1)->setText(QString(k.fullsymbol_.c_str()));
		ui->tableWidgetMarket->item(row, 13)->setText(QString(k.time_.c_str()));


        if (k.datatype_ == DataType::DT_Bid)
        {
            ui->tableWidgetMarket->item(row,5)->setText(QString::number(k.size_));
            ui->tableWidgetMarket->item(row,6)->setText(QString::number(k.price_));
        }
        else if (k.datatype_ == DataType::DT_Ask)
        {
            ui->tableWidgetMarket->item(row,7)->setText(QString::number(k.price_));
            ui->tableWidgetMarket->item(row,8)->setText(QString::number(k.size_));
        }
        else if(k.datatype_ ==DataType::DT_Trade)
        {
            ui->tableWidgetMarket->item(row,2)->setText(QString::number(k.price_));
            ui->tableWidgetMarket->item(row,3)->setText(QString::number(k.size_));
        }
        else if (k.datatype_ == DataType::DT_Full)
        {
            ui->tableWidgetMarket->item(row,2)->setText(QString::number(k.price_));
            ui->tableWidgetMarket->item(row,3)->setText(QString::number(k.size_));
            ui->tableWidgetMarket->item(row,4)->setText(QString::number(k.open_interest));
            ui->tableWidgetMarket->item(row,5)->setText(QString::number(k.bidsize_L1_));
            ui->tableWidgetMarket->item(row,6)->setText(QString::number(k.bidprice_L1_));
            ui->tableWidgetMarket->item(row,7)->setText(QString::number(k.askprice_L1_));
            ui->tableWidgetMarket->item(row,8)->setText(QString::number(k.asksize_L1_));
            ui->tableWidgetMarket->item(row,9)->setText(QString::number(k.pre_close_));
            ui->tableWidgetMarket->item(row,10)->setText(QString::number(k.open_));
            ui->tableWidgetMarket->item(row,11)->setText(QString::number(k.high_));
            ui->tableWidgetMarket->item(row,12)->setText(QString::number(k.low_));
        }
    }
}

void MainWindow::IncomingGeneralSlot(string sMessage) {
	vector<string> v = stringsplit(sMessage, '|');
	if (v[0] == "s") {
		OrderStatusHandler(sMessage);
	}
	else if (v[0] == "f") {
		FillHandler(sMessage);
	}
	else if (v[0] == "n") {
		PositionHandler(sMessage);
	}
	else if (v[0] == "h") {
		HistoricalHandler(sMessage);
	}
	else if (v[0] == "u") {
		AccountHandler(sMessage);
	}
	else if (v[0] == "r") {
		ContractHandler(sMessage);
	}
	else if (v[0] == "m") {
		GeneralMessageHandler(sMessage);
	}
}

void MainWindow::on_pushButton_Order_clicked()
{
    QString order;
    //合约代码
    QString s=ui->LineEditCode->text();
	//s.toStdString();
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

    emit OutgoingMessageSignal(order.toStdString());
}

void MainWindow::OrderStatusHandler(string& msg) {

}

void MainWindow::FillHandler(string& msg) {

}

void MainWindow::PositionHandler(string& msg) {

}


void MainWindow::HistoricalHandler(string& msg) {

}

void MainWindow::AccountHandler(string& msg) {

}

void MainWindow::ContractHandler(string& msg) {

}

void MainWindow::GeneralMessageHandler(string& msg) {
	int nColumn = ui->tableWidgetLog->columnCount();
	ui->tableWidgetLog->insertRow(0);

	vector<string> v = stringsplit(msg, '|');

	for (int j = 0; j<nColumn; j++)
	{
		ui->tableWidgetLog->setItem(0, j, new QTableWidgetItem(v[v.size()-j-1].c_str()));
	}
}
