#ifndef READSERIALDATA_H
#define READSERIALDATA_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWidget>
#include "config.h"

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
public slots:
    void ListPortAvailable();
    void ConvertSerialData();
private:
    QSerialPort *serial;
    QList<QSerialPortInfo> listPort;

    //model
    QString data;
};

#endif // READSERIALDATA_H
