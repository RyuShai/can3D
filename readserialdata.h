#ifndef READSERIALDATA_H
#define READSERIALDATA_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWidget>
#include "config.h"

struct ReceivedData
{   
    float width=0;
    float height=0;
    float depth=0;
    float weight=0;
    float volume=0;
    float density=0;
    QString barcode="";
    QString date="";
    void Clear(){
        width=height=depth=weight=volume=density=0;
        barcode = date ="";
    }
    void toString()
    {
        Log("width: "<<width <<" height: "<<height<<" depth: "<<depth<<"\nvolume: "<<volume<<" density: "<<density<<"\nbarcode: "<<" date: "<<date);
    }
};

class ReadSerialData :public QObject
{
public:
    ReadSerialData();
    ~ReadSerialData();
    void DisplaySerial();
    QList<QSerialPortInfo> getListPort() const;
    void setListPort(const QList<QSerialPortInfo> &value);
    bool Connect2Port(QSerialPortInfo port, qint32 baudrate = QSerialPort::Baud9600,
                      QSerialPort::DataBits databits = QSerialPort::Data8,
                      QSerialPort::Parity parity = QSerialPort::NoParity,
                      QSerialPort::StopBits stopbits = QSerialPort::OneStop);
    bool Connect2Port(QString portName, qint32 baudrate = QSerialPort::Baud9600,
                      QSerialPort::DataBits databits = QSerialPort::Data8,
                      QSerialPort::Parity parity = QSerialPort::NoParity,
                      QSerialPort::StopBits stopbits = QSerialPort::OneStop);
    void CloseConnection();
    void ConvertSerialData(QString data);
    ReceivedData receiveData;
public slots:
    void ListPortAvailable();
    void onReceiveData();
private:
    QSerialPort *serial;
    QList<QSerialPortInfo> listPort;

    //model
    QString data;
};

#endif // READSERIALDATA_H
