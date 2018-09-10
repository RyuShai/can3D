#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QDialog>
#include <QLabel>
class WarningDialog :public QDialog
{
public:
    WarningDialog(QWidget *parent = 0);
    QLabel *message;
};

#endif // WARNINGDIALOG_H
