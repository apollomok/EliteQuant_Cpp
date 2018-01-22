#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <qthread.h>
#include <QFile>
#include <QTextStream>
#include <Common/Util/util.h>
#include <Common/Time/timeutil.h>
#include <Services/tradingengine.h>

int main(int argc, char *argv[])
{
	class CTradingEngineThread : public QThread {
	protected:
		void run() {
			tradingengine engine;
			engine.run();
		}
	};

	qRegisterMetaType<string>("string");           // register std::string

    QApplication a(argc, argv);

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

	CTradingEngineThread* engine_ = new CTradingEngineThread();
	engine_->start();

    MainWindow w;
    w.show();

    return a.exec();
}
