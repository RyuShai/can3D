#include "readserialdata.h"
#include <QList>
#include <QThread>
ReadSerialData::ReadSerialData()
{
    qDebug("start");
    serial =new QSerialPort();
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
    listPort = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo info, listPort) {
        qDebug()<<"name "<<info.portName();
    }
}

void ReadSerialData::ConvertSerialData()
{
    //convert data to readable
    data = serial->readAll().data();
    qDebug()<<"data: "<<data;
}

QList<QSerialPortInfo> ReadSerialData::getListPort() const
{
    return listPort;
}

void ReadSerialData::setListPort(const QList<QSerialPortInfo> &value)
{
    listPort = value;
}

bool ReadSerialData::Connect2Port(QSerialPortInfo port, qint32 baudrate, QSerialPort::DataBits databits, QSerialPort::Parity parity, QSerialPort::StopBits stopbits)
{
    //if port opening, close it
    if(serial->isOpen())
        serial->close();

    serial->setPort(port);
    serial->setBaudRate(baudrate);
    serial->setDataBits(databits);
    serial->setParity(parity);
    serial->setStopBits(stopbits);
    if(!serial->open(QIODevice::ReadWrite))
    {
        //connect to port failed
        return false;
    }
    connect(serial,&QSerialPort::readyRead,this,&ReadSerialData::ConvertSerialData);
}

bool ReadSerialData::Connect2Port(QString portName, qint32 baudrate, QSerialPort::DataBits databits, QSerialPort::Parity parity, QSerialPort::StopBits stopbits)
{
    Log("test");
    //if port opening, close it
    if(serial->isOpen())
        serial->close();

    serial->setPortName(portName);
    serial->setBaudRate(baudrate);
    serial->setDataBits(databits);
    serial->setParity(parity);
    serial->setStopBits(stopbits);
    if(!serial->open(QIODevice::ReadWrite))
    {
        //connect to port failed
        qDebug("connect serial fail");
        return false;
    }
    connect(serial,&QSerialPort::readyRead,this,&ReadSerialData::ConvertSerialData);
}
