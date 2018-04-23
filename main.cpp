#include "mainwindow.h"
#include <QApplication>
#include "readserialdata.h"
#include "draw3d.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Draw3D draw;
    draw.show();
//    ReadSerialData reader;
//    reader.DisplaySerial();

    return a.exec();
}
