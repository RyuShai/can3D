#include "mainwindow.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //init
    serial = new ReadSerialData();

    CreateLayout();
    CreateMenu();
    CreateGroupLeftLayout();
    CreateGroupMidLayout();
    CreateGroupRightLayout();



}

void MainWindow::Exit()
{
    close();
}

void MainWindow::onPortSelected()
{
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug()<<"i :" <<action->text();
    serial->Connect2Port(action->text());
}

void MainWindow::CreateMenu()
{
    menuBar = new QMenuBar;
    //file
    menu = new QMenu(Config::MENU_TEXT_FILE, this);
    //add portMenu
    portMenu = menu->addMenu(Config::MENU_TEXT_PORT);
    CreatePortName();


    //exit action
    menuExitAction =menu->addAction(Config::MENU_TEXT_EXIT);
    menuBar->addMenu(menu);

    //connect signal=slot
    connect(menuExitAction,&QAction::triggered,this,&MainWindow::close);

    layout->setMenuBar(menuBar);
}

void MainWindow::CreateLayout()
{
    widget = new QWidget;
    layout = new QVBoxLayout;

    uperWidget = new QWidget;
    uperLayout = new QHBoxLayout;
    uperLayout->setSizeConstraint(QLayout::SetMinimumSize);
    uperWidget->setLayout(uperLayout);

    lowerWidget = new QWidget;
    lowerLayout = new QHBoxLayout;
    lowerWidget->setLayout(lowerLayout);

    layout->addWidget(uperWidget);
    layout->addWidget(lowerWidget);

    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::CreateGroupLeftLayout()
{
    ///left layout incluude:
    /// height,width, depth, weight
    /// It form layout
    groupLeftLayout = new QWidget;
    groupLeftLayout->setStyleSheet("background-color:yellow");
    groupLeftLayout->setFixedSize(Config::LEFT_GROUP_WIDTH,Config::LEFT_GROUP_HEIGHT);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_HEIGHT),0,0,1,1);
    gridLayout->addWidget(new QLineEdit,0,1,1,1);
    gridLayout->addWidget(new QLabel(Config::UNIT_LENGTH),0,2,1,1);

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_WIDTH));
    gridLayout->addWidget(new QLineEdit());
    gridLayout->addWidget(new QLabel(Config::UNIT_LENGTH));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_DEPTH));
    gridLayout->addWidget(new QLineEdit());
    gridLayout->addWidget(new QLabel(Config::UNIT_LENGTH));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_WEIGHT));
    gridLayout->addWidget(new QLineEdit());
    gridLayout->addWidget(new QLabel(Config::UNIT_WEIGHT));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_VOLUME));
    gridLayout->addWidget(new QLabel("volume"));
    gridLayout->addWidget(new QLabel(Config::UNIT_VOLUME));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_DENSITY));
    gridLayout->addWidget(new QLabel("density"));
    gridLayout->addWidget(new QLabel(Config::UNIT_DENSITY));


    groupLeftLayout->setLayout(gridLayout);
    uperLayout->addWidget(groupLeftLayout);

}

void MainWindow::CreateGroupMidLayout()
{
    groupMidLayout = new QWidget;
//    groupMidLayout->setFixedSize(Config::MID_GROUP_WIDTH,Config::MID_GROUP_HEIGHT);

    QGridLayout *layout = new QGridLayout;
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    //set logo
    QLabel *logo = new QLabel();
    logo->setPixmap( QPixmap(":/logo").scaled(Config::LOGO_WIDTH,Config::LOGO_HEIGHT,Qt::KeepAspectRatio));
    layout->addWidget(logo,0,0,2,1);

    //set barcode image
    QLabel *barcodeImage = new QLabel();
    barcodeImage->setPixmap(QPixmap(":/barcode").scaled(Config::BARCODE_WIDTH,Config::BARCODE_HEIGHT,Qt::KeepAspectRatio));
    layout->addWidget(barcodeImage,2,0,2,1);
    //set barcode label
    QLabel *barcodeLabel = new QLabel();
    barcodeLabel->setText("test barcode label");
    layout->addWidget(barcodeLabel,3,0,1,1);

    groupMidLayout->setLayout(layout);
    uperLayout->addWidget(groupMidLayout);

}

void MainWindow::CreateGroupRightLayout()
{
    groupRightLayout = new QWidget();

    uperLayout->addWidget(groupRightLayout);
}

void MainWindow::CreatePortName()
{
    portMenu->clear();
    serial->ListPortAvailable();
    qDebug()<<"list port size: "<<serial->getListPort().size();
    for(int i=0; i<serial->getListPort().size();i++)
    {
        QAction *action = portMenu->addAction(serial->getListPort().at(i).portName());
        connect(action,&QAction::triggered,this,&MainWindow::onPortSelected);
    }

}
