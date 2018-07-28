#include "readserialdata.h"
#include <QList>
#include <QThread>
#include <QDomDocument>
#include <QDate>
#include <QString>
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

void ReadSerialData::onReceiveData()
{
    //convert data to readable
    data += serial->readAll();

    if(data.contains("\n"))
    {
        qDebug()<<"rawData: "<<data;
//        Log("data: "+data);
        ConvertSerialData(data);
        data="";
    }
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
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if(!serial->open(QIODevice::ReadWrite))
    {
        //connect to port failed
//        return false;
    }
    connect(serial,&QSerialPort::readyRead,this,&ReadSerialData::onReceiveData);
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
    connect(serial,&QSerialPort::readyRead,this,&ReadSerialData::onReceiveData);
}

void ReadSerialData::CloseConnection()
{
    serial->close();
}

void ReadSerialData::ConvertSerialData(QString data)
{
    QDomDocument *doc = new QDomDocument;
    doc->setContent(data);

    QDomElement docElem = doc->documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
//        qDebug("n !Null");
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
//            qDebug("e!NULL");
//            qDebug() <<"eTag: "<<e.tagName()<<" "<<e.text(); // the node really is an elemee.nt.
            if(e.tagName()==Config::WIDTH)
            {
//                qDebug("e.WIDTH");
                receiveData.width = e.text().toFloat();
            }
            else if(e.tagName()==Config::HEIGHT)
                receiveData.height = e.text().toFloat();
            else if(e.tagName() == Config::DEPTH)
                receiveData.depth = e.text().toFloat();
            else if(e.tagName()==Config::WEIGHT)
                receiveData.weight = e.text().toFloat();
            else if(e.tagName()==Config::VOLUME)
                receiveData.volume= e.text().toFloat();
            else if(e.tagName()==Config::DENSITY)
                receiveData.density = e.text().toFloat();
            else if(e.tagName()==Config::BARCODE)
                receiveData.barcode = e.text();
        }
        n = n.nextSibling();
    }
    receiveData.date = QDate::currentDate().toString("dd-MM-yyyy");
//    receiveData.toString();
//    disconnect(serial,&QSerialPort::readyRead,this,&ReadSerialData::onReceiveData);
    qDebug("before update");
    emit DataReceived(receiveData);
}

void ReadSerialData::ConvertSerialDataText(QString data)
{
    data.remove(QString("#\n"));
    qDebug()<<"data1: "<<data;
    QStringList listData= data.split(',');
    receiveData.width = ((QString)listData.at(0)).toFloat();
    receiveData.depth = ((QString)listData.at(1)).toFloat();
    receiveData.height = ((QString)listData.at(2)).toFloat();
    receiveData.weight = ((QString)listData.at(3)).toFloat();
    receiveData.barcode = ((QString)listData.at(4));
    receiveData.date = QDate::currentDate().toString("dd-MM-yyyy");
    emit DataReceived(receiveData);
}

void ReadSerialData::SendData(QString cmd)
{

//    serial->write("*1.0,2.0,3.1,4.2,5.6,6.7,7.8,9.1#");

    serial->write(cmd.toUtf8());
}
