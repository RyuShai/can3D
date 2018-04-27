#ifndef READSERIALDATA_H
#define READSERIALDATA_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWidget>

class ReadSerialData :public QObject
{
public:
    ReadSerialData();
    ~ReadSerialData();
    void DisplaySerial();
    public slots:
    void ListPortAvailable();
private:
    QSerialPort *serial;
    QList<QSerialPortInfo> list;
};

#endif // READSERIALDATA_H
