/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QTableWidget *tableWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *Label;
    QLineEdit *LineEditCode;
    QLabel *Label_2;
    QLineEdit *LineEditName;
    QLabel *Label_3;
    QComboBox *ComboBoxContractType;
    QLabel *Label_4;
    QComboBox *ComboBoxDirection;
    QLabel *Label_5;
    QComboBox *ComboBox_BuyOrSell;
    QLabel *Label_6;
    QLineEdit *LineEdit_Price;
    QLabel *Label_7;
    QLineEdit *LineEdit_Quantity;
    QLabel *Label_8;
    QComboBox *ComboBox_OrderType;
    QLabel *Label_9;
    QComboBox *ComboBox_Market;
    QLabel *Label_10;
    QComboBox *ComboBox_Account;
    QPushButton *pushButton_Order;
    QSplitter *splitter_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QTextBrowser *textBrowser_2;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_4;
    QTextBrowser *textBrowser_3;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_5;
    QTextBrowser *textBrowser_4;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_6;
    QTextBrowser *textBrowser_5;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral("../Downloads/EliteQuant-EliteQuant_Python-master/EliteQuant_Python/source/gui/image/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_3->sizePolicy().hasHeightForWidth());
        splitter_3->setSizePolicy(sizePolicy);
        splitter_3->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setMinimumSize(QSize(100, 100));
        splitter->setFrameShape(QFrame::StyledPanel);
        splitter->setOrientation(Qt::Horizontal);
        tableWidget = new QTableWidget(splitter);
        if (tableWidget->columnCount() < 15)
            tableWidget->setColumnCount(15);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(14, __qtablewidgetitem14);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        splitter->addWidget(tableWidget);
        formLayoutWidget = new QWidget(splitter);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        Label = new QLabel(formLayoutWidget);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label);

        LineEditCode = new QLineEdit(formLayoutWidget);
        LineEditCode->setObjectName(QStringLiteral("LineEditCode"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LineEditCode);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QStringLiteral("Label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, Label_2);

        LineEditName = new QLineEdit(formLayoutWidget);
        LineEditName->setObjectName(QStringLiteral("LineEditName"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LineEditName);

        Label_3 = new QLabel(formLayoutWidget);
        Label_3->setObjectName(QStringLiteral("Label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, Label_3);

        ComboBoxContractType = new QComboBox(formLayoutWidget);
        ComboBoxContractType->setObjectName(QStringLiteral("ComboBoxContractType"));

        formLayout->setWidget(3, QFormLayout::FieldRole, ComboBoxContractType);

        Label_4 = new QLabel(formLayoutWidget);
        Label_4->setObjectName(QStringLiteral("Label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Label_4);

        ComboBoxDirection = new QComboBox(formLayoutWidget);
        ComboBoxDirection->setObjectName(QStringLiteral("ComboBoxDirection"));

        formLayout->setWidget(4, QFormLayout::FieldRole, ComboBoxDirection);

        Label_5 = new QLabel(formLayoutWidget);
        Label_5->setObjectName(QStringLiteral("Label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, Label_5);

        ComboBox_BuyOrSell = new QComboBox(formLayoutWidget);
        ComboBox_BuyOrSell->setObjectName(QStringLiteral("ComboBox_BuyOrSell"));

        formLayout->setWidget(5, QFormLayout::FieldRole, ComboBox_BuyOrSell);

        Label_6 = new QLabel(formLayoutWidget);
        Label_6->setObjectName(QStringLiteral("Label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, Label_6);

        LineEdit_Price = new QLineEdit(formLayoutWidget);
        LineEdit_Price->setObjectName(QStringLiteral("LineEdit_Price"));

        formLayout->setWidget(6, QFormLayout::FieldRole, LineEdit_Price);

        Label_7 = new QLabel(formLayoutWidget);
        Label_7->setObjectName(QStringLiteral("Label_7"));

        formLayout->setWidget(7, QFormLayout::LabelRole, Label_7);

        LineEdit_Quantity = new QLineEdit(formLayoutWidget);
        LineEdit_Quantity->setObjectName(QStringLiteral("LineEdit_Quantity"));

        formLayout->setWidget(7, QFormLayout::FieldRole, LineEdit_Quantity);

        Label_8 = new QLabel(formLayoutWidget);
        Label_8->setObjectName(QStringLiteral("Label_8"));

        formLayout->setWidget(8, QFormLayout::LabelRole, Label_8);

        ComboBox_OrderType = new QComboBox(formLayoutWidget);
        ComboBox_OrderType->setObjectName(QStringLiteral("ComboBox_OrderType"));

        formLayout->setWidget(8, QFormLayout::FieldRole, ComboBox_OrderType);

        Label_9 = new QLabel(formLayoutWidget);
        Label_9->setObjectName(QStringLiteral("Label_9"));

        formLayout->setWidget(9, QFormLayout::LabelRole, Label_9);

        ComboBox_Market = new QComboBox(formLayoutWidget);
        ComboBox_Market->setObjectName(QStringLiteral("ComboBox_Market"));

        formLayout->setWidget(9, QFormLayout::FieldRole, ComboBox_Market);

        Label_10 = new QLabel(formLayoutWidget);
        Label_10->setObjectName(QStringLiteral("Label_10"));

        formLayout->setWidget(10, QFormLayout::LabelRole, Label_10);

        ComboBox_Account = new QComboBox(formLayoutWidget);
        ComboBox_Account->setObjectName(QStringLiteral("ComboBox_Account"));

        formLayout->setWidget(10, QFormLayout::FieldRole, ComboBox_Account);

        pushButton_Order = new QPushButton(formLayoutWidget);
        pushButton_Order->setObjectName(QStringLiteral("pushButton_Order"));

        formLayout->setWidget(11, QFormLayout::FieldRole, pushButton_Order);

        splitter->addWidget(formLayoutWidget);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        sizePolicy1.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy1);
        splitter_2->setMinimumSize(QSize(100, 100));
        splitter_2->setFrameShape(QFrame::StyledPanel);
        splitter_2->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(textBrowser);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        textBrowser_2 = new QTextBrowser(tab_2);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));

        horizontalLayout_3->addWidget(textBrowser_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayout_4 = new QHBoxLayout(tab_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        textBrowser_3 = new QTextBrowser(tab_3);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));

        horizontalLayout_4->addWidget(textBrowser_3);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        horizontalLayout_5 = new QHBoxLayout(tab_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        textBrowser_4 = new QTextBrowser(tab_4);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));

        horizontalLayout_5->addWidget(textBrowser_4);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        horizontalLayout_6 = new QHBoxLayout(tab_5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        textBrowser_5 = new QTextBrowser(tab_5);
        textBrowser_5->setObjectName(QStringLiteral("textBrowser_5"));

        horizontalLayout_6->addWidget(textBrowser_5);

        tabWidget->addTab(tab_5, QString());
        splitter_2->addWidget(tabWidget);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tableWidget_2 = new QTableWidget(layoutWidget);
        if (tableWidget_2->columnCount() < 7)
            tableWidget_2->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem21);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));

        gridLayout->addWidget(tableWidget_2, 1, 0, 1, 4);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 2, 1, 1);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 2, 3, 1, 1);

        splitter_2->addWidget(layoutWidget);
        splitter_3->addWidget(splitter_2);

        horizontalLayout->addWidget(splitter_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EliteQuant", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Symbol", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Last", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Volume", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Open Interest", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Bid Size", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Bid", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Ask", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Ask Size", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Yest. Close", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Open", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "High", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Low", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Time", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(14);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "Source", 0));
        label_2->setText(QApplication::translate("MainWindow", "Discretionary", 0));
        Label->setText(QApplication::translate("MainWindow", "Symbol", 0));
        Label_2->setText(QApplication::translate("MainWindow", "Name", 0));
        Label_3->setText(QApplication::translate("MainWindow", "Security Type", 0));
        ComboBoxContractType->clear();
        ComboBoxContractType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Stock", 0)
         << QApplication::translate("MainWindow", "Future", 0)
         << QApplication::translate("MainWindow", "Option", 0)
         << QApplication::translate("MainWindow", "Forex", 0)
        );
        Label_4->setText(QApplication::translate("MainWindow", "Direction", 0));
        ComboBoxDirection->clear();
        ComboBoxDirection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Long", 0)
         << QApplication::translate("MainWindow", "Short", 0)
        );
        Label_5->setText(QApplication::translate("MainWindow", "Order Flag", 0));
        ComboBox_BuyOrSell->clear();
        ComboBox_BuyOrSell->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Open", 0)
         << QApplication::translate("MainWindow", "Close", 0)
         << QApplication::translate("MainWindow", "Close Yesterday", 0)
         << QApplication::translate("MainWindow", "Close Today", 0)
        );
        Label_6->setText(QApplication::translate("MainWindow", "Price", 0));
        Label_7->setText(QApplication::translate("MainWindow", "Quantity", 0));
        Label_8->setText(QApplication::translate("MainWindow", "Order Type", 0));
        ComboBox_OrderType->clear();
        ComboBox_OrderType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Market", 0)
         << QApplication::translate("MainWindow", "Limit", 0)
        );
        Label_9->setText(QApplication::translate("MainWindow", "Exchange", 0));
        Label_10->setText(QApplication::translate("MainWindow", "Account", 0));
        pushButton_Order->setText(QApplication::translate("MainWindow", "Place Order", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Log", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Order", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Fill", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Position", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Account", 0));
        label->setText(QApplication::translate("MainWindow", "Automatic", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "SID", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "nHoldings", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "nTrades", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "Open PnL", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "Close PnL", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "Status", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Start Strat", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Pause Strat", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Stop Strat", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Liquidate Strat", 0));
        menu->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
