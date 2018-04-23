#include "readserialdata.h"
#include <QList>
#include <QThread>
ReadSerialData::ReadSerialData()
{
    qDebug("start");
    serial =new QSerialPort();
    serial->setBaudRate(QSerialPort::Baud9600);
    ListPortAvailable();
    serial->setPort(list.at(0));
//    serial->setPortName("ttyACM0");
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);
    if(serial->isOpen())
            qDebug("open");
    connect(serial,&QSerialPort::readyRead,this,&ReadSerialData::DisplaySerial);
}

ReadSerialData::~ReadSerialData()
{
    qDebug()<<"closed";
    serial->close();
}

void ReadSerialData::DisplaySerial()
{
    qDebug()<<serial->readAll();
}

void ReadSerialData::ListPortAvailable()
{
    list = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, list) {
        qDebug()<<"name "<<info.portName();
    }
}
