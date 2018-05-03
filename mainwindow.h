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
#include "config.h"
#include "readserialdata.h"
#include "modelinteract.h"
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
    QWidget *groupLeftLayout;
    QWidget *groupMidLayout;
    QWidget *groupRightLayout;
    QWidget *widget;
    QWidget *uperWidget;
    QWidget *lowerWidget;



    //function
    void CreateMenu();
    void CreateLayout();
    void CreateGroupLeftLayout();
    void CreateGroupMidLayout();
    void CreateGroupRightLayout();
    void CreatePortName();
    float CalVolume(float w, float h, float d);

    void Connection();
};

#endif // MAINWINDOW_H
