#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::Test()
{
    int count=0;
    qDebug("start");
    serial =new QSerialPort();
    serial->setBaudRate(QSerialPort::Baud9600);
    list = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, list) {
        qDebug()<<"name "<<info.portName();
    }
    serial->setPort(list.at(0));
//    serial->setPortName("ttyACM0");
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
//    serial->setStopBits(QSerialPort::OneStop);
    if(serial->open(QIODevice::ReadWrite))
            qDebug("open");
    while(serial->isOpen())
    {
        QByteArray byte = serial->readAll();
        qDebug()<<"available: "<<serial->bytesAvailable();
        if(!byte.isEmpty())
        qDebug()<<byte;
        else
        {
//            QThread::sleep(1);
            qDebug()<<"null";
            count++;
        }
        if(count==1000)
        {
            serial->close();
            qDebug()<<"serial closed";
        }


    }
}
