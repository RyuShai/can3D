#include "mainwindow.h"
#include <QApplication>
#include "config.h"
#include "readserialdata.h"
#include <QtCore>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontUseNativeMenuBar);
        MainWindow w;
        w.setWindowTitle(Config::MAIN_WINDOW_TITLE);
        w.resize(Config::WINDO_WIDTH,Config::WINDOW_HEIGHT);
        w.show();


    return app.exec();
}
