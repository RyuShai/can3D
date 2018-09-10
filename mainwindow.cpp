#include "mainwindow.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QFontDatabase>
#include <Qt3DExtras>
#include <QBoxLayout>
#include <QPushButton>
#include "warningdialog.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //init
    QString db = QCoreApplication::applicationDirPath().append("/can3D.db");
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

    model->setPath2db(db);
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
    if(serial->Connect2Port(action->text(),9600))
    {
       connected->setIcon(QIcon(QPixmap(":/greendot.png")));
    }
    else{
        connected->setIcon(QIcon(QPixmap(":/dot.png")));
    }
}

void MainWindow::onReceivedData(ReceivedData data)
{
    data.toString();
    if(data.width==0 || data.height ==0 ||data.depth ==0 ||data.weight==0)
    {

        qDebug("wrong data number");
        QString msg = Config::DIALOG_ERROR_MESSAGE;
        if(data.width==0)
        {
            msg += "width ";
        }
        if(data.height == 0)
        {
            msg += "height ";
        }
        if(data.depth == 0)
        {
            msg += "depth ";
        }
        if(data.weight == 0)
        {
            msg += "weight ";
        }
        msg+= "cant not be negative or zero";
        WarningDialog *dialog = new WarningDialog(this);
        dialog->setFixedSize(QSize(350,50));
        dialog->setWindowModality(Qt::ApplicationModal);
        dialog->message->setText(msg);
        dialog->show();
        return;
    }
    qDebug("not return");
    //    Log("widget size: "<<groupLeftWidget->layout()->count());
    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_HEIGHT)->setText(QString::number(data.height));
    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_WIDTH)->setText(QString::number(data.width));
    groupLeftWidget->findChild<QLineEdit *>(Config::FORM_TEXT_DEPTH)->setText(QString::number(data.depth));
    leWeight->setText(QString::number(data.weight));
    leVolumne->setText(QString::number(data.density));
    barcodeLabel->setText(data.barcode);
    model->InserRecord(data);
    if(data.height/10 !=box->cuboid->yExtent())
        box->cuboid->setYExtent(data.height/10);
    if(data.width/10 !=box->cuboid->xExtent())
        box->cuboid->setXExtent(data.width/10);
    if(data.depth/10 !=box->cuboid->zExtent())
        box->cuboid->setZExtent(data.depth/10);
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

void MainWindow::onLog(QAction *action)
{
    qDebug()<<"log"<<endl;
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
    serial->SendData("*1.0,2.0,3.1,4.2,5.6,6.7,7.8,9.1#");
}

void MainWindow::onSendSetupCodeClicked()
{
    serial->SendData(Config::SETUP_CODE);
}

void MainWindow::onTableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    qDebug()<<"tl: "<<topLeft.row()<<" "<<topLeft.column()<<" br: "<<bottomRight.column()<<" roles: "<<roles;

    float width = tableModel->data(tableModel->index(topLeft.row(),1)).toFloat();
    float height =tableModel->data(tableModel->index(topLeft.row(),2)).toFloat();
    float depth=tableModel->data(tableModel->index(topLeft.row(),3)).toFloat();
    float weight=tableModel->data(tableModel->index(topLeft.row(),4)).toFloat();
    float volume=tableModel->data(tableModel->index(topLeft.row(),5)).toFloat();
    QString barcode=tableModel->data(tableModel->index(topLeft.row(),6)).toString();
    int id =tableModel->data(tableModel->index(topLeft.row(),0)).toInt();
    model->UpdateRecord(width,height,depth,weight,volume,0,barcode,id);
}

void MainWindow::onEditTextEnter()
{
    QLineEdit* editer = static_cast<QLineEdit*>(sender());
    if(editer == leWeight)
    {
        qDebug("leWeight");
        tableModel->setData(tableModel->index(tableModel->rowCount()-1,4),QVariant(leWeight->text()));
    }
    else if(editer == leHeight)
    {
        qDebug("leHeight");
        tableModel->setData(tableModel->index(tableModel->rowCount()-1,2),QVariant(leHeight->text()));
    }
    else if(editer == leWidth)
    {
        qDebug("leWidth");
        tableModel->setData(tableModel->index(tableModel->rowCount()-1,1),QVariant(leWidth->text()));
    }
    else if(editer == leVolumne)
    {
        qDebug("leVolumne");
        tableModel->setData(tableModel->index(tableModel->rowCount()-1,5),QVariant(leVolumne->text()));
    }
    else if(editer == leDepth)
    {
        qDebug("leDepth");
        tableModel->setData(tableModel->index(tableModel->rowCount()-1,3),QVariant(leDepth->text()));
    }
    else if(editer == barcodeLabel)
    {
        qDebug("leDepth");
        tableModel->setData(tableModel->index(tableModel->rowCount()-1,6),QVariant(barcodeLabel->text()));
    }
    tableModel->setData(tableModel->index(tableModel->rowCount()-1,7),QVariant(QDate::currentDate().toString("dd-MM-yyyy")));
}

void MainWindow::CreateMenu()
{
    menuBar = new QMenuBar;

    menuBar->setNativeMenuBar(false);
    //file
    menu = new QMenu(Config::MENU_TEXT_FILE, this);
    menu->installEventFilter(this);
    //add portMenu
    portMenu = menu->addMenu(Config::MENU_TEXT_PORT);
//    CreatePortName();
    //send setup code action
    QAction * sendSetupCode = menu->addAction(Config::MENU_TEXT_SEND_SETUP);
    //exit action
    menuExitAction =menu->addAction(Config::MENU_TEXT_EXIT);

    //add connection icon
    connected = new QAction;
    QIcon icon(QPixmap(":/dot.png"));

    connected->setIcon(icon);

    menuBar->addMenu(menu);
    menuBar->addAction(connected);
    //connect signal=slot
    connect(menuExitAction,&QAction::triggered,this,&MainWindow::close);
    connect(sendSetupCode,&QAction::triggered,this,&MainWindow::onSendSetupCodeClicked);

    rootHLayout->setMenuBar(menuBar);
}

void MainWindow::CreateLayout()
{
    widget = new QWidget;
    widget->installEventFilter(this);
    //    widget->setStyleSheet("background-color: yellow");
    lefttWidget = new QWidget;
    rootHLayout = new QHBoxLayout();
    layout = new QVBoxLayout;

    uperWidget = new QWidget;
    uperWidget->setStyleSheet("background-color: white");
    uperLayout = new QHBoxLayout;
    uperWidget->setFixedWidth(Config::ROOT_LEFT_GROUP_WIDTH);
    uperLayout->setSizeConstraint(QLayout::SetMinimumSize);
    uperWidget->setLayout(uperLayout);
    uperLayout->setContentsMargins(0,0,0,0);
    uperLayout->setSpacing(0);
    //test
    //    lefttWidget->setStyleSheet("background-color : yellow");
    //

    lowerTableView = new QTableView;
    lowerLayout = new QHBoxLayout;
    lowerLayout->setSizeConstraint(QLayout::SetMinimumSize);
    //    lowerTableView->resize(500,200);
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
    QWidget *rootLeftWidget = new QWidget();
    rootLeftWidget->setFixedWidth(Config::ROOT_LEFT_GROUP_WIDTH);

    QHBoxLayout *rootLeftWidgetLayout = new QHBoxLayout(rootLeftWidget);

    QFont font;
    font.setBold(false);
    font.setPointSize(Config::LABEL_FONT_SIZE);

    QFont fontEdit;
    fontEdit.setBold(true);
    fontEdit.setPointSize(Config::EDIT_FONT_SIZE);

    groupLeftWidget = new QWidget;
    //    groupLeftWidget-
    groupLeftWidget->setFixedSize(Config::LEFT_GROUP_WIDTH,Config::LEFT_GROUP_HEIGHT);
    groupLeftWidget->setObjectName("groupLeftWidget");
    groupLeftWidget->setStyleSheet("#groupLeftWidget{ border: 1px solid black}");
    QGridLayout *gridLayout = new QGridLayout;
    //    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
    QLabel *lblHeight = new QLabel(Config::FORM_TEXT_HEIGHT);
    lblHeight->setFont(font);
    gridLayout->addWidget(lblHeight,0,0,1,1);
    leHeight = new QLineEdit();
    //    leHeight->installEventFilter(this);
    leHeight->setFont(fontEdit);
    leHeight->setAlignment(Qt::AlignCenter);
    leHeight->setObjectName(Config::FORM_TEXT_HEIGHT);
    leHeight->setFixedHeight(Config::LINE_EDIT_WIDTH);
    gridLayout->addWidget(leHeight,0,1,1,1);
    QLabel *lblULength = new QLabel(Config::UNIT_LENGTH);
    lblULength->setFont(font);
    gridLayout->addWidget(lblULength,0,2,1,1);

    QLabel *lblWidth =new QLabel(Config::FORM_TEXT_WIDTH);
    lblWidth->setFont(font);
    gridLayout->addWidget(lblWidth);
    leWidth = new QLineEdit();
    //    leWidth->installEventFilter(this);
    leWidth->setAlignment(Qt::AlignCenter);
    leWidth->setFont(fontEdit);
    leWidth->setObjectName(Config::FORM_TEXT_WIDTH);
    leWidth->setFixedHeight(Config::LINE_EDIT_WIDTH);
    gridLayout->addWidget(leWidth);
    QLabel *lblULengthw = new QLabel(Config::UNIT_LENGTH);
    lblULengthw->setFont(font);
    gridLayout->addWidget(lblULengthw);

    QLabel *lblDepth =new QLabel(Config::FORM_TEXT_DEPTH);
    lblDepth->setFont(font);
    gridLayout->addWidget(lblDepth);
    leDepth = new QLineEdit();
    //    leDepth->installEventFilter(this);
    leDepth->setFont(fontEdit);
    leDepth->setAlignment(Qt::AlignCenter);
    leDepth->setObjectName(Config::FORM_TEXT_DEPTH);
    leDepth->setFixedHeight(Config::LINE_EDIT_WIDTH);
    gridLayout->addWidget(leDepth);
    QLabel *lblULengthd = new QLabel(Config::UNIT_LENGTH);
    lblULengthd->setFont(font);
    gridLayout->addWidget(lblULengthd);



    QWidget *weightBoxWidget = new QWidget;
    weightBoxWidget->setObjectName("weightBoxWidget");
    weightBoxWidget->setStyleSheet("#weightBoxWidget{border: 1px solid black}");
    QGridLayout *weigthBoxWidgetLayout = new QGridLayout(weightBoxWidget);
    QLabel *lblWeight = new QLabel(Config::FORM_TEXT_WEIGHT);
    lblWeight->setFont(font);
    weigthBoxWidgetLayout->addWidget(lblWeight,0,0,1,1);
    leWeight = new QLineEdit();
    //    leWeight->installEventFilter(this);
    leWeight->setAlignment(Qt::AlignCenter);
    leWeight->setFont(fontEdit);
    leWeight->setObjectName(Config::FORM_TEXT_WEIGHT);
    leWeight->setFixedHeight(Config::LINE_EDIT_WIDTH);
    weigthBoxWidgetLayout->addWidget(leWeight,1,0,1,1);
    QLabel *lblUWeight = new QLabel(Config::UNIT_WEIGHT);
    lblUWeight->setFont(font);
    weigthBoxWidgetLayout->addWidget(lblUWeight,1,1,1,1);



    QWidget *volumeWieghtBoxWidget = new QWidget;
    volumeWieghtBoxWidget->setObjectName("volumeWieghtBoxWidget");
    volumeWieghtBoxWidget->setStyleSheet("#volumeWieghtBoxWidget{border: 1px solid black}");
    QGridLayout *volumeWeigthBoxWidgetLayout = new QGridLayout(volumeWieghtBoxWidget);
    QLabel *lblVW = new QLabel(Config::FORM_TEXT_VOLUME);
    lblVW->setFont(font);
    volumeWeigthBoxWidgetLayout->addWidget(lblVW,0,0,1,1);
    leVolumne= new QLineEdit();
    //    leVolumne->installEventFilter(this);
    leVolumne->setAlignment(Qt::AlignCenter);
    leVolumne->setFont(fontEdit);
    leVolumne->setObjectName(Config::FORM_TEXT_VOLUME);
    leVolumne->setFixedHeight(Config::LINE_EDIT_WIDTH);
    volumeWeigthBoxWidgetLayout->addWidget(leVolumne,1,0,1,1);
    QLabel *lblUWeight2 = new QLabel(Config::UNIT_WEIGHT);
    lblUWeight2->setFont(font);
    volumeWeigthBoxWidgetLayout->addWidget(lblUWeight2,1,1,1,1);

    QWidget *topRightWidget = new QWidget;
    topRightWidget->setFixedSize(Config::LEFT_GROUP_WIDTH,370);
    QVBoxLayout *topRightWidgetLayout = new QVBoxLayout(topRightWidget);
    //    topRightWidgetLayout->setSpacing(10);
    topRightWidgetLayout->addWidget(weightBoxWidget);
    topRightWidgetLayout->addWidget(volumeWieghtBoxWidget);


    //    QPushButton *btn = new QPushButton("test");
    //    connect(btn,&QPushButton::clicked,this,&MainWindow::onTestBtnClicked);
    //    gridLayout->addWidget(btn,3,4,1,1);
    //update 26/7/18


    groupLeftWidget->setLayout(gridLayout);
    rootLeftWidgetLayout->addWidget(groupLeftWidget,Qt::AlignLeft);
    rootLeftWidgetLayout->addWidget(topRightWidget,Qt::AlignRight);
    uperLayout->addWidget(rootLeftWidget,Qt::AlignLeft);

    //update 29/7/18
    connect(leWeight,&QLineEdit::returnPressed,this,&MainWindow::onEditTextEnter);
    connect(leDepth,&QLineEdit::returnPressed,this,&MainWindow::onEditTextEnter);
    connect(leHeight,&QLineEdit::returnPressed,this,&MainWindow::onEditTextEnter);
    connect(leWidth,&QLineEdit::returnPressed,this,&MainWindow::onEditTextEnter);
    connect(leVolumne,&QLineEdit::returnPressed,this,&MainWindow::onEditTextEnter);

}

void MainWindow::CreateGroupMidLayout()
{
    groupMidLayout = new QWidget;
    groupMidLayout->setFixedHeight(200);

    QVBoxLayout *layout = new QVBoxLayout;
    //    layout->setSizeConstraint(QLayout::SetMinimumSize);
    //set logo
    QLabel *logo = new QLabel();
    logo->setPixmap( QPixmap(":/logo").scaled(Config::LOGO_WIDTH,Config::LOGO_HEIGHT,Qt::KeepAspectRatio));
    layout->addWidget(logo);

    //set barcode image
    QLabel *barcodeImage = new QLabel();
    barcodeImage->setPixmap(QPixmap(":/barcode").scaled(Config::BARCODE_WIDTH,Config::BARCODE_HEIGHT,Qt::KeepAspectRatio));
    layout->addWidget(barcodeImage);
    //set barcode label
    barcodeLabel = new QLineEdit();
    barcodeLabel->setFixedHeight(60);
    QFont font;
    font.setBold(true);
    font.setPointSize(Config::EDIT_FONT_SIZE);
    barcodeLabel->setFont(font);
    layout->addWidget(barcodeLabel);

    groupMidLayout->setLayout(layout);
    rightlayout->insertWidget(0,groupMidLayout);
    connect(barcodeLabel,&QLineEdit::returnPressed,this,&MainWindow::onEditTextEnter);
}

void MainWindow::CreateGroupRightLayout()
{
    groupRightLayout = new QWidget();
    groupRightLayout->setStyleSheet("background-color: white");
    groupRightLayout->setFixedSize(250,600);
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

    box = new Box(rootEntity);
    view->setRootEntity(rootEntity);

    rightlayout->addWidget(container);
    container->setStyleSheet(" border: 1px solid white");
    rootHLayout->addWidget(groupRightLayout);
}

void MainWindow::CreateLowerLayout()
{
    //    lowerWidget = new QTableView;
    tableModel = new QStandardItemModel;
    tableModel->setHorizontalHeaderLabels(QStringList()<<"id"<<"width"<<"height"<<"Length"<<"weight"<<"Volume-Weight"<<"barcode"<<"date");
    lowerTableView->setModel(tableModel);
    lowerTableView->verticalHeader()->hide();
    lowerTableView->setFixedHeight(200);
    lowerTableView->setFixedWidth(Config::ROOT_LEFT_GROUP_WIDTH);
    lowerTableView->setColumnWidth(0,30);
    for(int i=0; i<tableModel->columnCount();i++)
    {
        if(i==0)
            lowerTableView->setColumnWidth(i,30);
        else if(i==7 || i==6)
            lowerTableView->setColumnWidth(i,92);
        else
            lowerTableView->setColumnWidth(i,80);
    }
    connect(tableModel,&QStandardItemModel::dataChanged,this,&MainWindow::onTableDataChanged);
    //    lowerTableView->horizontalHeader()->setStretchLastSection(true);
    //    lowerLayout->addWidget(lowerWidget);
}

void MainWindow::CreatePortName()
{
    Log("");
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
    //    items.append(new QStandardItem(QString::number(data.density)));
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

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        Qt::Key key = static_cast<Qt::Key>(keyEvent->key());
        if(key ==Qt::Key_Space)
        {
            Log("key enter pressed");
            serial->SendData("\r");
        }
        else if(key == Qt::Key_Return)
        {

        }

    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(obj == menu)
        {
            Log("mouse press");
            CreatePortName();
        }
    }
}
