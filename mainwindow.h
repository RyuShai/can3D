#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Test();
private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QList<QSerialPortInfo> list;
};

#endif // MAINWINDOW_H
