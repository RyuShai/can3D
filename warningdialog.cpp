#include "warningdialog.h"
#include <QHBoxLayout>
WarningDialog::WarningDialog(QWidget *parent)
    : QDialog(parent)
{
    message = new QLabel(tr("ryu rest"));
    this->setFixedSize(QSize(100,50));
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(message);
    setLayout(layout);
    setWindowTitle("kich thuoc sai");


}
