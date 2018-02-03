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
#include <QTranslator>

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
    strategyManager=new StrategyManager(clientMQ);
	// https://stackoverflow.com/questions/37057042/how-to-know-in-which-thread-qt-executes-slots
    connect(ui->actionEnglish, SIGNAL(triggered()), this, SLOT(TranslateToEnglish()));
	connect(ui->actionChinese, SIGNAL(triggered()), this, SLOT(TranslateToChinese()));
    connect(this, SIGNAL(OutgoingMessageSignal(string)),clientMQ, SLOT(OutgoingMessageSlot(string)));
    connect(clientMQ, SIGNAL(IncomingMarketSignal(string)),this, SLOT(IncomingMarketSlot(string)));
	connect(clientMQ, SIGNAL(IncomingGeneralSignal(string)), this, SLOT(IncomingGeneralSlot(string)));
    connect(ui->tableWidgetMarket,SIGNAL(cellClicked(int,int)),this,SLOT(SetParamsToOrderWidget(int,int)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(StartStrategy()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(PauseStrategy()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(StopStrategy()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(LiquidateStrategy()));

    clientMQ->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetParamsToOrderWidget(int row,int column)
{
    QString symbol=ui->tableWidgetMarket->item(row,0)->text();
    ui->LineEditCode->setText(symbol);

    QString name=ui->tableWidgetMarket->item(row,1)->text();
    ui->LineEditName->setText(name);

    QString askprice=ui->tableWidgetMarket->item(row,7)->text();
    ui->LineEdit_Price->setText(askprice);

}

void MainWindow::TranslateToEnglish()
{
	QTranslator translator;
	translator.load("en.qm");
	qApp->installTranslator(&translator);
	ui->retranslateUi(this);

}
void MainWindow::TranslateToChinese()
{
    QTranslator translator;
    translator.load("cn.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);

}


void MainWindow::StartStrategy()
{
    bool focus = ui->tableWidgetStrategy->isItemSelected(ui->tableWidgetStrategy->currentItem()); // 判断是否选中一行
    if(focus)
    {
      int row1 = ui->tableWidgetStrategy->currentItem()->row(); // 当前选中行
      //todo: startStratey
    }

}
void MainWindow::PauseStrategy()
{
	bool focus = ui->tableWidgetStrategy->isItemSelected(ui->tableWidgetStrategy->currentItem()); // 判断是否选中一行
	if (focus)
	{
		int row1 = ui->tableWidgetStrategy->currentItem()->row(); // 当前选中行
																  //todo: startStratey
	}
}
void MainWindow::StopStrategy()
{
    bool focus = ui->tableWidgetStrategy->isItemSelected(ui->tableWidgetStrategy->currentItem()); // 判断是否选中一行
    if(focus)
    {
      int row1 = ui->tableWidgetStrategy->currentItem()->row(); // 当前选中行
      //todo: StopStrategy
    }

}

void MainWindow::LiquidateStrategy()
{
    bool focus = ui->tableWidgetStrategy->isItemSelected(ui->tableWidgetStrategy->currentItem()); // 判断是否选中一行
    if(focus)
    {
      int row1 = ui->tableWidgetStrategy->currentItem()->row(); // 当前选中行
      //todo: LiquidateStrategy
    }

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
    //update order status
    vector<string> v = stringsplit(msg, '|');

    auto index =std::find(orderids.begin(),orderids.end(),QString(v[1].c_str())); //broker_order_id

    if(index==orderids.end())
    {
        return;
    }
    int row =index-orderids.begin();
    ui->tableWidgetOrder->setItem(row, 9, new QTableWidgetItem(v[2].c_str()));
}

void MainWindow::FillHandler(string& msg) {
    //update fill table
    ui->tableWidgetFill->insertRow(0);

	vector<string> v = stringsplit(msg, '|');
    //m.broker_order_id = v[1]
    //m.internal_order_id = v[1]
    //m.timestamp = v[2]
    //m.fill_price = v[3]
    //m.fill_size = v[4]
    //self.setItem(0, 0, QtWidgets.QTableWidgetItem(fillevent.broker_order_id))
    //self.setItem(0, 2, QtWidgets.QTableWidgetItem(fillevent.full_symbol))
    //self.setItem(0, 7, QtWidgets.QTableWidgetItem(fillevent.fill_price))
    //self.setItem(0, 8, QtWidgets.QTableWidgetItem(fillevent.fill_size))
    //self.setItem(0, 9, QtWidgets.QTableWidgetItem(fillevent.timestamp))
    ui->tableWidgetFill->setItem(0, 0, new QTableWidgetItem(v[1].c_str()));
    ui->tableWidgetFill->setItem(0, 2, new QTableWidgetItem(v[1].c_str()));
    ui->tableWidgetFill->setItem(0, 7, new QTableWidgetItem(v[3].c_str()));
    ui->tableWidgetFill->setItem(0, 8, new QTableWidgetItem(v[4].c_str()));
    ui->tableWidgetFill->setItem(0, 9, new QTableWidgetItem(v[2].c_str()));

}

void MainWindow::PositionHandler(string& msg) {
    //update position table
    ui->tableWidgetPosition ->insertRow(0);

    vector<string> v = stringsplit(msg, '|');
    ui->tableWidgetPosition->setItem(0, 0, new QTableWidgetItem(v[1].c_str()));
    ui->tableWidgetPosition->setItem(0, 2, new QTableWidgetItem(v[1].c_str()));
    ui->tableWidgetPosition->setItem(0, 7, new QTableWidgetItem(v[3].c_str()));
    ui->tableWidgetPosition->setItem(0, 8, new QTableWidgetItem(v[4].c_str()));
    ui->tableWidgetPosition->setItem(0, 9, new QTableWidgetItem(v[2].c_str()));

}


void MainWindow::HistoricalHandler(string& msg) {

    //string msg = CConfig::instance().hist_msg
    //            + SERIALIZATION_SEPARATOR + symbol
    //            + SERIALIZATION_SEPARATOR + time
    //            + SERIALIZATION_SEPARATOR + std::to_string(open)
    //            + SERIALIZATION_SEPARATOR + std::to_string(high)
    //            + SERIALIZATION_SEPARATOR + std::to_string(low)
    //            + SERIALIZATION_SEPARATOR + std::to_string(close)
    //            + SERIALIZATION_SEPARATOR + std::to_string(volume)
    //            + SERIALIZATION_SEPARATOR + std::to_string(barcount)
    //            + SERIALIZATION_SEPARATOR + std::to_string(wap);
    vector<string> v = stringsplit(msg, '|');
    //todo: save historical data to local storage

}

void MainWindow::AccountHandler(string& msg) {
    //update position table
    ui->tableWidgetAccount ->insertRow(0);

    vector<string> v = stringsplit(msg, '|');
    for (int j = 0; j < 8 ; j++)
    {
        ui->tableWidgetAccount->setItem(0, j, new QTableWidgetItem(v[j+1].c_str()));
    }
    //timestamp
    ui->tableWidgetAccount->setItem(0, 10, new QTableWidgetItem(v[8].c_str()));

}

void MainWindow::ContractHandler(string& msg) {
    //string msg = CConfig::instance().contract_msg
    //            + SERIALIZATION_SEPARATOR + symbol
    //            + SERIALIZATION_SEPARATOR + local_name
    //            + SERIALIZATION_SEPARATOR + min_tick;
    vector<string> v = stringsplit(msg, '|');
    map<string, string>::iterator it_find;
    it_find = contracts.find(v[1]);
    if(it_find != contracts.end())
    {
        it_find->second=v[3];
    }
    else
    {
        contracts.insert(pair<string, string>(v[1], v[3]));
    }
    //todo: need to show on UI.

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
