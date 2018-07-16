#include "mainwindow.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QFontDatabase>
#include <Qt3DExtras>
#include "box.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //init
    QFontDatabase::addApplicationFont(":/fonts/font2");
    serial = new ReadSerialData();
    model = new ModelInteract;

    CreateLayout();
    CreateGroupRightLayout();
//    CreateMenu();
//    CreateGroupLeftLayout();
//    CreateGroupMidLayout();

//    CreateLowerLayout();

//     Connection();

////qDebug()<<"error ?";

//    model->setPath2db("can3D.db");
//    model->LoadRecord();


}

void MainWindow::Exit()
{
    serial->CloseConnection();
    serial = Q_NULLPTR;
    close();
}

void MainWindow::onPortSelected()
{
    QAction *action = qobject_cast<QAction*>(sender());
    qDebug()<<"i :" <<action->text();
    serial->Connect2Port(action->text(),9600);
}

void MainWindow::onReceivedData(ReceivedData data)
{
    Log("widget size: "<<groupLeftLayout->layout()->count());
    groupLeftLayout->findChild<QLineEdit *>(Config::FORM_TEXT_HEIGHT)->setText(QString::number(data.height));
    groupLeftLayout->findChild<QLineEdit *>(Config::FORM_TEXT_WIDTH)->setText(QString::number(data.width));
    groupLeftLayout->findChild<QLineEdit *>(Config::FORM_TEXT_DEPTH)->setText(QString::number(data.depth));
    groupLeftLayout->findChild<QLineEdit *>(Config::FORM_TEXT_WEIGHT)->setText(QString::number(data.weight));
    groupLeftLayout->findChild<QLabel *>(Config::FORM_TEXT_VOLUME)->setText(QString::number(CalVolume(data.width,data.height,data.depth)));

    model->InserRecord(data);
}

void MainWindow::onModelRecordLoaded()
{
    Log("");
    foreach (ReceivedData *record , model->getListRecord()) {
        tableModel->appendRow(CreateModelRow(*record));
    }

}

void MainWindow::onInserNewRecorded(ReceivedData data)
{
    data.id = model->GetlastID();
    tableModel->appendRow(CreateModelRow(data));
}

void MainWindow::onModelInserted()
{
    lowerWidget->scrollToBottom();
}

void MainWindow::onTablemodelModified(QStandardItem* item)
{
    qDebug()<<item->text();


}

void MainWindow::onLog()
{

}

void MainWindow::CreateMenu()
{
    menuBar = new QMenuBar;
    menuBar->setNativeMenuBar(false);
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

    rootHLayout->setMenuBar(menuBar);

}

void MainWindow::CreateLayout()
{
    widget = new QWidget;
    lefttWidget = new QWidget;
    lefttWidget->setFixedSize(800,600);
    rootHLayout = new QHBoxLayout();
    layout = new QVBoxLayout;

    uperWidget = new QWidget;
    uperLayout = new QHBoxLayout;
    uperLayout->setSizeConstraint(QLayout::SetMinimumSize);
    uperWidget->setLayout(uperLayout);

    lowerWidget = new QTableView;
    lowerLayout = new QHBoxLayout;
    lowerLayout->setSizeConstraint(QLayout::SetMinimumSize);
    lowerWidget->resize(500,600);
    lowerWidget->setLayout(lowerLayout);

    layout->addWidget(uperWidget);
    layout->addWidget(lowerWidget);



    lefttWidget->setLayout(layout);
    rootHLayout->addWidget(lefttWidget);
    widget->setLayout(rootHLayout);
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
    QLineEdit *leHeight = new QLineEdit();
    leHeight->setObjectName(Config::FORM_TEXT_HEIGHT);
    gridLayout->addWidget(leHeight,0,1,1,1);
    gridLayout->addWidget(new QLabel(Config::UNIT_LENGTH),0,2,1,1);

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_WIDTH));
    QLineEdit *leWidth = new QLineEdit();
    leWidth->setObjectName(Config::FORM_TEXT_WIDTH);
    gridLayout->addWidget(leWidth);
    gridLayout->addWidget(new QLabel(Config::UNIT_LENGTH));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_DEPTH));
    QLineEdit *leDepth = new QLineEdit();
    leDepth->setObjectName(Config::FORM_TEXT_DEPTH);
    gridLayout->addWidget(leDepth);
    gridLayout->addWidget(new QLabel(Config::UNIT_LENGTH));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_WEIGHT));
    QLineEdit *leWeight = new QLineEdit();
    leWeight->setObjectName(Config::FORM_TEXT_WEIGHT);
    gridLayout->addWidget(leWeight);
    gridLayout->addWidget(new QLabel(Config::UNIT_WEIGHT));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_VOLUME));
    QLabel * lblVolumne = new QLabel();
    lblVolumne->setObjectName(Config::FORM_TEXT_VOLUME);
    gridLayout->addWidget(lblVolumne);
    gridLayout->addWidget(new QLabel(Config::UNIT_VOLUME));

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_DENSITY));
    QLabel *lblDensity = new QLabel();
    lblDensity->setObjectName(Config::FORM_TEXT_DENSITY);
    gridLayout->addWidget(lblDensity);
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
    layout->addWidget(barcodeLabel,4,0,1,1);

    groupMidLayout->setLayout(layout);
    uperLayout->addWidget(groupMidLayout);

}

void MainWindow::CreateGroupRightLayout()
{
    groupRightLayout = new QWidget();
//    groupRightLayout->setFixedSize(300,600);
    QHBoxLayout *layout = new QHBoxLayout(groupRightLayout);

    //create window 3d
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    //3d camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(-16, 12, 15.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0,0, 0));


    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);


    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    qDebug()<<"start";
    Box *box = new Box(rootEntity);
    qDebug()<<"end";
    view->setRootEntity(rootEntity);

    layout->addWidget(container);
    groupRightLayout->setStyleSheet("background-color:red");
    rootHLayout->addWidget(groupRightLayout);
}

void MainWindow::CreateLowerLayout()
{
//    lowerWidget = new QTableView;
    tableModel = new QStandardItemModel;
    tableModel->setHorizontalHeaderLabels(QStringList()<<"id"<<"width"<<"height"<<"depth"<<"weight"<<"volume"<<"density"<<"barcode"<<"date");
    lowerWidget->setModel(tableModel);
    lowerWidget->verticalHeader()->hide();
//    lowerWidget->horizontalHeader()->setStretchLastSection(true);
//    lowerLayout->addWidget(lowerWidget);
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

QList<QStandardItem *> MainWindow::CreateModelRow(ReceivedData data)
{
    QList<QStandardItem*> items;
    items.append(new QStandardItem(QString::number(data.id)));
    items.append(new QStandardItem(QString::number(data.width)));
    items.append(new QStandardItem(QString::number(data.height)));
    items.append(new QStandardItem(QString::number(data.depth)));
    items.append(new QStandardItem(QString::number(data.weight)));
    items.append(new QStandardItem(QString::number(data.volume)));
    items.append(new QStandardItem(QString::number(data.density)));
    items.append(new QStandardItem(data.barcode));
    items.append(new QStandardItem(data.date));
    return items;
}

float MainWindow::CalVolume(float w, float h, float d)
{
    return w*h*d;
}

void MainWindow::Connection()
{
    connect(serial,&ReadSerialData::DataReceived,this,&MainWindow::onReceivedData);
    connect(model,&ModelInteract::LoadRecorded,this,&MainWindow::onModelRecordLoaded);
    connect(model,&ModelInteract::InsertNewRecorded,this,&MainWindow::onInserNewRecorded);
    connect(tableModel,&QStandardItemModel::rowsInserted,this,&MainWindow::onModelInserted);
    connect(tableModel,&QStandardItemModel::itemChanged,this,&MainWindow::onTablemodelModified);
}
