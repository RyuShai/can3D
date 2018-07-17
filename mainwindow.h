#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QHeaderView>
#include "config.h"
#include "readserialdata.h"
#include "modelinteract.h"
#include "box.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void Exit();
    //triggerd when port action clicked
    //connect serial to selected port
    void onPortSelected();
    void onReceivedData(ReceivedData data);
    void onModelRecordLoaded();
    void onInserNewRecorded(ReceivedData data);
    void onModelInserted();
    void onTablemodelModified(QStandardItem* item);
    void onLog();
    void onpositionChanged(const QVector3D &position);
    void onviewCenterChanged(const QVector3D &viewCenter);
private:
    //database
    ModelInteract* model;
    ReadSerialData *serial;
    //menu
    QMenuBar *menuBar;
    QMenu *menu;
    QAction *menuExitAction;
    //port menu
    QMenu *portMenu;
    QList<QAction> listPortName;

    QBoxLayout *layout;
    QHBoxLayout *uperLayout;
    QBoxLayout *lowerLayout;
    QLayout *rootHLayout;
    QWidget *groupLeftLayout;
    QWidget *groupMidLayout;
    QWidget *groupRightLayout;
    QWidget *widget;
    QWidget *lefttWidget;
    QWidget *uperWidget;
    QTableView *lowerWidget;
    QStandardItemModel* tableModel;
    Box *box;

    //function
    void CreateMenu();
    void CreateLayout();
    void CreateGroupLeftLayout();
    void CreateGroupMidLayout();
    void CreateGroupRightLayout();
    void CreateLowerLayout();
    void CreatePortName();
    QList<QStandardItem*> CreateModelRow(ReceivedData data);
    float CalVolume(float w, float h, float d);

    void Connection();
};

#endif // MAINWINDOW_H
