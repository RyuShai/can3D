#include "mainwindow.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QFontDatabase>
#include <Qt3DExtras>
#include <QBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //init
    QFontDatabase::addApplicationFont(":/fonts/font2");
    serial = new ReadSerialData();
    model = new ModelInteract;

    CreateLayout();
    CreateGroupRightLayout();
    CreateMenu();
    CreateGroupLeftLayout();
    CreateGroupMidLayout();

    CreateLowerLayout();

     Connection();

//qDebug()<<"error ?";

    model->setPath2db("can3D.db");
    model->LoadRecord();


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
    data.toString();
    Log("widget size: "<<groupLeftWidget->layout()->count());
    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_HEIGHT)->setText(QString::number(data.height));
    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_WIDTH)->setText(QString::number(data.width));
    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_DEPTH)->setText(QString::number(data.depth));
//    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_WEIGHT)->setText(QString::number(data.weight));
//    groupLeftWidget->findChild<QLabel *>(Config::FORM_TEXT_VOLUME)->setText(QString::number(CalVolume(data.width,data.height,data.depth)));

    model->InserRecord(data);
    if(data.height !=box->cuboid->yExtent())
        box->cuboid->setYExtent(data.height);
    if(data.width !=box->cuboid->xExtent())
        box->cuboid->setXExtent(data.width);
    if(data.depth !=box->cuboid->zExtent())
        box->cuboid->setZExtent(data.depth);
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
    lowerTableView->scrollToBottom();
}

void MainWindow::onTablemodelModified(QStandardItem* item)
{
    qDebug()<<item->text();


}

void MainWindow::onLog()
{

}

void MainWindow::onpositionChanged(const QVector3D &position)
{
    qDebug()<<"position: "<<position;
}

void MainWindow::onviewCenterChanged(const QVector3D &viewCenter)
{
    qDebug()<<"viewcenter: "<<viewCenter;
}

void MainWindow::onTestBtnClicked()
{
    qDebug()<<Q_FUNC_INFO<<endl;
    serial->SendData();
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

    lowerTableView = new QTableView;
    lowerLayout = new QHBoxLayout;
    lowerLayout->setSizeConstraint(QLayout::SetMinimumSize);
    lowerTableView->resize(500,400);
    lowerTableView->setLayout(lowerLayout);

    layout->addWidget(uperWidget);
    layout->addWidget(lowerTableView);



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
    groupLeftWidget = new QWidget;
//    groupLeftWidget-
    groupLeftWidget->setFixedSize(Config::LEFT_GROUP_WIDTH,Config::LEFT_GROUP_HEIGHT);
    groupLeftWidget->setStyleSheet("QWidget#QWidget border: 1px solid black");
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

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_VOLUME),0,3,1,1);
    QLineEdit * lblVolumne = new QLineEdit();
    lblVolumne->setObjectName(Config::FORM_TEXT_VOLUME);
    gridLayout->addWidget(lblVolumne,0,4,1,1);
    gridLayout->addWidget(new QLabel(Config::UNIT_VOLUME),0,6,1,1);

    gridLayout->addWidget(new QLabel(Config::FORM_TEXT_DENSITY),2,3,1,1);
    QLineEdit *lblDensity = new QLineEdit();
    lblDensity->setObjectName(Config::FORM_TEXT_DENSITY);
    gridLayout->addWidget(lblDensity,2,4,1,1);
    gridLayout->addWidget(new QLabel(Config::UNIT_DENSITY),2,5,1,1);

    QPushButton *btn = new QPushButton("test");
    connect(btn,&QPushButton::clicked,this,&MainWindow::onTestBtnClicked);
    gridLayout->addWidget(btn,3,4,1,1);
    //update 26/7/18
    QWidget *rootLeftWidget = new QWidget;
    QHBoxLayout *rootLeftWidgetLayout = new QHBoxLayout;

    groupLeftWidget->setLayout(gridLayout);
    uperLayout->addWidget(groupLeftWidget);




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
    rightlayout->insertWidget(0,groupMidLayout);

}

void MainWindow::CreateGroupRightLayout()
{
    groupRightLayout = new QWidget();
//    groupRightLayout->setFixedSize(300,600);
    rightlayout = new QVBoxLayout(groupRightLayout);

    //create window 3d
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    //3d camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(16.3298, 14.8403, 18.8122));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0.828393, 1.60774, -0.308398));

    ///////////////////////
    /// \brief camController
    connect(cameraEntity,&Qt3DRender::QCamera::positionChanged,this,&MainWindow::onpositionChanged);
    connect(cameraEntity,&Qt3DRender::QCamera::viewCenterChanged,this,&MainWindow::onviewCenterChanged);
    //////////////////////////
    ///

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
    box = new Box(rootEntity);
    qDebug()<<"end";
    view->setRootEntity(rootEntity);

    rightlayout->addWidget(container);
    container->setStyleSheet(" border: 1px solid white");
    rootHLayout->addWidget(groupRightLayout);
}

void MainWindow::CreateLowerLayout()
{
//    lowerWidget = new QTableView;
    tableModel = new QStandardItemModel;
    tableModel->setHorizontalHeaderLabels(QStringList()<<"id"<<"width"<<"height"<<"depth"<<"weight"<<"volume"<<"density"<<"barcode"<<"date");
    lowerTableView->setModel(tableModel);
    lowerTableView->verticalHeader()->hide();
    lowerTableView->setFixedHeight(400);
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
