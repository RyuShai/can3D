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
#include <QKeyEvent>
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
    void onLog(QAction *action);
    void onpositionChanged(const QVector3D &position);
    void onviewCenterChanged(const QVector3D &viewCenter);
    void onTestBtnClicked();
    void onSendSetupCodeClicked();
    void onTableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void onEditTextEnter();
    void CreatePortName();
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
    QWidget *groupLeftWidget;
    QWidget *groupMidLayout;
    QWidget *groupRightLayout;
    QVBoxLayout *rightlayout;
    QWidget *widget;
    QWidget *lefttWidget;
    QWidget *uperWidget;
    QTableView *lowerTableView;
    QStandardItemModel* tableModel;
    Box *box;

    QLineEdit * leVolumne ;
    QLineEdit *leWeight;
    QLineEdit *leHeight;
    QLineEdit *leWidth;
    QLineEdit *leDepth;
    QLineEdit *barcodeLabel;

    QAction *connected;
    //function
    void CreateMenu();
    void CreateLayout();
    void CreateGroupLeftLayout();
    void CreateGroupMidLayout();
    void CreateGroupRightLayout();
    void CreateLowerLayout();

    QList<QStandardItem*> CreateModelRow(ReceivedData data);
    float CalVolume(float w, float h, float d);

    void Connection();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
