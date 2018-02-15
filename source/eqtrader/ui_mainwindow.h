/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEnglish;
    QAction *actionChinese;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QTableWidget *tableWidgetMarket;
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
    QTabWidget *tabWidgetAccount;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *tableWidgetLog;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableWidgetOrder;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *tableWidgetFill;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *tableWidgetPosition;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_6;
    QTableWidget *tableWidgetAccount;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *tableWidgetStrategy;
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
        MainWindow->resize(1116, 833);
        QIcon icon;
        icon.addFile(QStringLiteral("../Downloads/EliteQuant-EliteQuant_Python-master/EliteQuant_Python/source/gui/image/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionChinese = new QAction(MainWindow);
        actionChinese->setObjectName(QStringLiteral("actionChinese"));
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
        tableWidgetMarket = new QTableWidget(splitter);
        if (tableWidgetMarket->columnCount() < 15)
            tableWidgetMarket->setColumnCount(15);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetMarket->setHorizontalHeaderItem(14, __qtablewidgetitem14);
        tableWidgetMarket->setObjectName(QStringLiteral("tableWidgetMarket"));
        splitter->addWidget(tableWidgetMarket);
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
        ComboBoxContractType->addItem(QString());
        ComboBoxContractType->addItem(QString());
        ComboBoxContractType->addItem(QString());
        ComboBoxContractType->addItem(QString());
        ComboBoxContractType->setObjectName(QStringLiteral("ComboBoxContractType"));

        formLayout->setWidget(3, QFormLayout::FieldRole, ComboBoxContractType);

        Label_4 = new QLabel(formLayoutWidget);
        Label_4->setObjectName(QStringLiteral("Label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Label_4);

        ComboBoxDirection = new QComboBox(formLayoutWidget);
        ComboBoxDirection->addItem(QString());
        ComboBoxDirection->addItem(QString());
        ComboBoxDirection->setObjectName(QStringLiteral("ComboBoxDirection"));

        formLayout->setWidget(4, QFormLayout::FieldRole, ComboBoxDirection);

        Label_5 = new QLabel(formLayoutWidget);
        Label_5->setObjectName(QStringLiteral("Label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, Label_5);

        ComboBox_BuyOrSell = new QComboBox(formLayoutWidget);
        ComboBox_BuyOrSell->addItem(QString());
        ComboBox_BuyOrSell->addItem(QString());
        ComboBox_BuyOrSell->addItem(QString());
        ComboBox_BuyOrSell->addItem(QString());
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
        ComboBox_OrderType->addItem(QString());
        ComboBox_OrderType->addItem(QString());
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
        tabWidgetAccount = new QTabWidget(splitter_2);
        tabWidgetAccount->setObjectName(QStringLiteral("tabWidgetAccount"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tableWidgetLog = new QTableWidget(tab);
        if (tableWidgetLog->columnCount() < 2)
            tableWidgetLog->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetLog->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetLog->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        tableWidgetLog->setObjectName(QStringLiteral("tableWidgetLog"));

        horizontalLayout_2->addWidget(tableWidgetLog);

        tabWidgetAccount->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tableWidgetOrder = new QTableWidget(tab_2);
        if (tableWidgetOrder->columnCount() < 15)
            tableWidgetOrder->setColumnCount(15);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(4, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(5, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(6, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(7, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(8, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(9, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(10, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(11, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(12, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(13, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidgetOrder->setHorizontalHeaderItem(14, __qtablewidgetitem31);
        tableWidgetOrder->setObjectName(QStringLiteral("tableWidgetOrder"));

        horizontalLayout_3->addWidget(tableWidgetOrder);

        tabWidgetAccount->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayout_4 = new QHBoxLayout(tab_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tableWidgetFill = new QTableWidget(tab_3);
        if (tableWidgetFill->columnCount() < 13)
            tableWidgetFill->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(3, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(4, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(5, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(6, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(7, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(8, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(9, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(10, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(11, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidgetFill->setHorizontalHeaderItem(12, __qtablewidgetitem44);
        tableWidgetFill->setObjectName(QStringLiteral("tableWidgetFill"));

        horizontalLayout_4->addWidget(tableWidgetFill);

        tabWidgetAccount->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        horizontalLayout_5 = new QHBoxLayout(tab_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tableWidgetPosition = new QTableWidget(tab_4);
        if (tableWidgetPosition->columnCount() < 13)
            tableWidgetPosition->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(0, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(1, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(2, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(3, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(4, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(5, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(6, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(7, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(8, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(9, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(10, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(11, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidgetPosition->setHorizontalHeaderItem(12, __qtablewidgetitem57);
        tableWidgetPosition->setObjectName(QStringLiteral("tableWidgetPosition"));

        horizontalLayout_5->addWidget(tableWidgetPosition);

        tabWidgetAccount->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        horizontalLayout_6 = new QHBoxLayout(tab_5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        tableWidgetAccount = new QTableWidget(tab_5);
        if (tableWidgetAccount->columnCount() < 11)
            tableWidgetAccount->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(0, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(1, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(2, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(3, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(4, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(5, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(6, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(7, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(8, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(9, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tableWidgetAccount->setHorizontalHeaderItem(10, __qtablewidgetitem68);
        tableWidgetAccount->setObjectName(QStringLiteral("tableWidgetAccount"));

        horizontalLayout_6->addWidget(tableWidgetAccount);

        tabWidgetAccount->addTab(tab_5, QString());
        splitter_2->addWidget(tabWidgetAccount);
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

        tableWidgetStrategy = new QTableWidget(layoutWidget);
        if (tableWidgetStrategy->columnCount() < 7)
            tableWidgetStrategy->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(0, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(1, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(2, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(3, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(4, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(5, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tableWidgetStrategy->setHorizontalHeaderItem(6, __qtablewidgetitem75);
        tableWidgetStrategy->setObjectName(QStringLiteral("tableWidgetStrategy"));

        gridLayout->addWidget(tableWidgetStrategy, 1, 0, 1, 4);

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
        menuBar->setGeometry(QRect(0, 0, 1116, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(actionEnglish);
        menu->addAction(actionChinese);

        retranslateUi(MainWindow);

        tabWidgetAccount->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EliteQuant", nullptr));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", nullptr));
        actionChinese->setText(QApplication::translate("MainWindow", "Chinese", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMarket->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Symbol", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMarket->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMarket->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Last", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetMarket->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Volume", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetMarket->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Open Interest", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetMarket->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Bid Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetMarket->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Bid", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetMarket->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Ask", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetMarket->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Ask Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetMarket->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Yest. Close", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetMarket->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Open", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetMarket->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "High", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetMarket->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Low", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetMarket->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetMarket->horizontalHeaderItem(14);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "Source", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Discretionary", nullptr));
        Label->setText(QApplication::translate("MainWindow", "Symbol", nullptr));
        Label_2->setText(QApplication::translate("MainWindow", "Name", nullptr));
        Label_3->setText(QApplication::translate("MainWindow", "Security Type", nullptr));
        ComboBoxContractType->setItemText(0, QApplication::translate("MainWindow", "Stock", nullptr));
        ComboBoxContractType->setItemText(1, QApplication::translate("MainWindow", "Future", nullptr));
        ComboBoxContractType->setItemText(2, QApplication::translate("MainWindow", "Option", nullptr));
        ComboBoxContractType->setItemText(3, QApplication::translate("MainWindow", "Forex", nullptr));

        Label_4->setText(QApplication::translate("MainWindow", "Direction", nullptr));
        ComboBoxDirection->setItemText(0, QApplication::translate("MainWindow", "Long", nullptr));
        ComboBoxDirection->setItemText(1, QApplication::translate("MainWindow", "Short", nullptr));

        Label_5->setText(QApplication::translate("MainWindow", "Order Flag", nullptr));
        ComboBox_BuyOrSell->setItemText(0, QApplication::translate("MainWindow", "Open", nullptr));
        ComboBox_BuyOrSell->setItemText(1, QApplication::translate("MainWindow", "Close", nullptr));
        ComboBox_BuyOrSell->setItemText(2, QApplication::translate("MainWindow", "Close Yesterday", nullptr));
        ComboBox_BuyOrSell->setItemText(3, QApplication::translate("MainWindow", "Close Today", nullptr));

        Label_6->setText(QApplication::translate("MainWindow", "Price", nullptr));
        Label_7->setText(QApplication::translate("MainWindow", "Quantity", nullptr));
        Label_8->setText(QApplication::translate("MainWindow", "Order Type", nullptr));
        ComboBox_OrderType->setItemText(0, QApplication::translate("MainWindow", "Market", nullptr));
        ComboBox_OrderType->setItemText(1, QApplication::translate("MainWindow", "Limit", nullptr));

        Label_9->setText(QApplication::translate("MainWindow", "Exchange", nullptr));
        Label_10->setText(QApplication::translate("MainWindow", "Account", nullptr));
        pushButton_Order->setText(QApplication::translate("MainWindow", "Place Order", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetLog->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetLog->horizontalHeaderItem(1);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "Content", nullptr));
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tab), QApplication::translate("MainWindow", "Log", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetOrder->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "Order ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidgetOrder->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "Symbol", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidgetOrder->horizontalHeaderItem(2);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidgetOrder->horizontalHeaderItem(3);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "Security Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidgetOrder->horizontalHeaderItem(4);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "Direction", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidgetOrder->horizontalHeaderItem(5);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "Order Flag", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidgetOrder->horizontalHeaderItem(6);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidgetOrder->horizontalHeaderItem(7);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidgetOrder->horizontalHeaderItem(8);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "Filled", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidgetOrder->horizontalHeaderItem(9);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidgetOrder->horizontalHeaderItem(10);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "Order Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidgetOrder->horizontalHeaderItem(11);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "Cancel Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidgetOrder->horizontalHeaderItem(12);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "Exchange", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidgetOrder->horizontalHeaderItem(13);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "Account", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidgetOrder->horizontalHeaderItem(14);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "Source", nullptr));
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tab_2), QApplication::translate("MainWindow", "Order", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidgetFill->horizontalHeaderItem(0);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "Order ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidgetFill->horizontalHeaderItem(1);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "Fill ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidgetFill->horizontalHeaderItem(2);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "Symbol", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidgetFill->horizontalHeaderItem(3);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidgetFill->horizontalHeaderItem(4);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "Security Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidgetFill->horizontalHeaderItem(5);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "Direction", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidgetFill->horizontalHeaderItem(6);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "Order Flag", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidgetFill->horizontalHeaderItem(7);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "Fill Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidgetFill->horizontalHeaderItem(8);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "Filled", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidgetFill->horizontalHeaderItem(9);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "Fill Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidgetFill->horizontalHeaderItem(10);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "Exchange", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidgetFill->horizontalHeaderItem(11);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "Account", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidgetFill->horizontalHeaderItem(12);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "Source", nullptr));
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tab_3), QApplication::translate("MainWindow", "Fill", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidgetPosition->horizontalHeaderItem(0);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "Symbol", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidgetPosition->horizontalHeaderItem(1);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidgetPosition->horizontalHeaderItem(2);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "Security Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidgetPosition->horizontalHeaderItem(3);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "Direction", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidgetPosition->horizontalHeaderItem(4);
        ___qtablewidgetitem49->setText(QApplication::translate("MainWindow", "Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidgetPosition->horizontalHeaderItem(5);
        ___qtablewidgetitem50->setText(QApplication::translate("MainWindow", "Yest. Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidgetPosition->horizontalHeaderItem(6);
        ___qtablewidgetitem51->setText(QApplication::translate("MainWindow", "Freezed", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidgetPosition->horizontalHeaderItem(7);
        ___qtablewidgetitem52->setText(QApplication::translate("MainWindow", "Average Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidgetPosition->horizontalHeaderItem(8);
        ___qtablewidgetitem53->setText(QApplication::translate("MainWindow", "Open PnL", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidgetPosition->horizontalHeaderItem(9);
        ___qtablewidgetitem54->setText(QApplication::translate("MainWindow", "Closed PnL", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidgetPosition->horizontalHeaderItem(10);
        ___qtablewidgetitem55->setText(QApplication::translate("MainWindow", "Account", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidgetPosition->horizontalHeaderItem(11);
        ___qtablewidgetitem56->setText(QApplication::translate("MainWindow", "Source", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidgetPosition->horizontalHeaderItem(12);
        ___qtablewidgetitem57->setText(QApplication::translate("MainWindow", "Time", nullptr));
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tab_4), QApplication::translate("MainWindow", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidgetAccount->horizontalHeaderItem(0);
        ___qtablewidgetitem58->setText(QApplication::translate("MainWindow", "AccountID", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = tableWidgetAccount->horizontalHeaderItem(1);
        ___qtablewidgetitem59->setText(QApplication::translate("MainWindow", "Yest. Net", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = tableWidgetAccount->horizontalHeaderItem(2);
        ___qtablewidgetitem60->setText(QApplication::translate("MainWindow", "Net", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = tableWidgetAccount->horizontalHeaderItem(3);
        ___qtablewidgetitem61->setText(QApplication::translate("MainWindow", "Available", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = tableWidgetAccount->horizontalHeaderItem(4);
        ___qtablewidgetitem62->setText(QApplication::translate("MainWindow", "Commission", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = tableWidgetAccount->horizontalHeaderItem(5);
        ___qtablewidgetitem63->setText(QApplication::translate("MainWindow", "Margin", nullptr));
        QTableWidgetItem *___qtablewidgetitem64 = tableWidgetAccount->horizontalHeaderItem(6);
        ___qtablewidgetitem64->setText(QApplication::translate("MainWindow", "Closed PnL", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = tableWidgetAccount->horizontalHeaderItem(7);
        ___qtablewidgetitem65->setText(QApplication::translate("MainWindow", "Open PnL", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = tableWidgetAccount->horizontalHeaderItem(8);
        ___qtablewidgetitem66->setText(QApplication::translate("MainWindow", "Brokerage", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = tableWidgetAccount->horizontalHeaderItem(9);
        ___qtablewidgetitem67->setText(QApplication::translate("MainWindow", "API", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = tableWidgetAccount->horizontalHeaderItem(10);
        ___qtablewidgetitem68->setText(QApplication::translate("MainWindow", "Time", nullptr));
        tabWidgetAccount->setTabText(tabWidgetAccount->indexOf(tab_5), QApplication::translate("MainWindow", "Account", nullptr));
        label->setText(QApplication::translate("MainWindow", "Automatic", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = tableWidgetStrategy->horizontalHeaderItem(0);
        ___qtablewidgetitem69->setText(QApplication::translate("MainWindow", "SID", nullptr));
        QTableWidgetItem *___qtablewidgetitem70 = tableWidgetStrategy->horizontalHeaderItem(1);
        ___qtablewidgetitem70->setText(QApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem71 = tableWidgetStrategy->horizontalHeaderItem(2);
        ___qtablewidgetitem71->setText(QApplication::translate("MainWindow", "nHoldings", nullptr));
        QTableWidgetItem *___qtablewidgetitem72 = tableWidgetStrategy->horizontalHeaderItem(3);
        ___qtablewidgetitem72->setText(QApplication::translate("MainWindow", "nTrades", nullptr));
        QTableWidgetItem *___qtablewidgetitem73 = tableWidgetStrategy->horizontalHeaderItem(4);
        ___qtablewidgetitem73->setText(QApplication::translate("MainWindow", "Open PnL", nullptr));
        QTableWidgetItem *___qtablewidgetitem74 = tableWidgetStrategy->horizontalHeaderItem(5);
        ___qtablewidgetitem74->setText(QApplication::translate("MainWindow", "Close PnL", nullptr));
        QTableWidgetItem *___qtablewidgetitem75 = tableWidgetStrategy->horizontalHeaderItem(6);
        ___qtablewidgetitem75->setText(QApplication::translate("MainWindow", "Status", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Start Strat", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Pause Strat", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Stop Strat", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Liquidate Strat", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
