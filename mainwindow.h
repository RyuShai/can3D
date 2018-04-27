#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "config.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void Exit();
private:
    QMenuBar *menuBar;
    QMenu *menu;
    QAction *menuExitAction;
    QBoxLayout *layout;
    QHBoxLayout *uperLayout;
    QBoxLayout *lowerLayout;
    QWidget *groupLeftLayout;
    QWidget *groupMidLayout;
    QGroupBox *groupRightLayout;
    QWidget *widget;
    QWidget *uperWidget;
    QWidget *lowerWidget;



    //function
    void CreateMenu();
    void CreateLayout();
    void CreateGroupLeftLayout();
    void CreateGroupMidLayout();
    void CreateGroupRightLayout();
};

#endif // MAINWINDOW_H
