/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 4), // "Exit"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 14), // "onPortSelected"
QT_MOC_LITERAL(4, 32, 14), // "onReceivedData"
QT_MOC_LITERAL(5, 47, 12), // "ReceivedData"
QT_MOC_LITERAL(6, 60, 4), // "data"
QT_MOC_LITERAL(7, 65, 19), // "onModelRecordLoaded"
QT_MOC_LITERAL(8, 85, 18), // "onInserNewRecorded"
QT_MOC_LITERAL(9, 104, 15), // "onModelInserted"
QT_MOC_LITERAL(10, 120, 20), // "onTablemodelModified"
QT_MOC_LITERAL(11, 141, 14), // "QStandardItem*"
QT_MOC_LITERAL(12, 156, 4), // "item"
QT_MOC_LITERAL(13, 161, 5), // "onLog"
QT_MOC_LITERAL(14, 167, 17), // "onpositionChanged"
QT_MOC_LITERAL(15, 185, 8), // "position"
QT_MOC_LITERAL(16, 194, 19), // "onviewCenterChanged"
QT_MOC_LITERAL(17, 214, 10), // "viewCenter"
QT_MOC_LITERAL(18, 225, 16) // "onTestBtnClicked"

    },
    "MainWindow\0Exit\0\0onPortSelected\0"
    "onReceivedData\0ReceivedData\0data\0"
    "onModelRecordLoaded\0onInserNewRecorded\0"
    "onModelInserted\0onTablemodelModified\0"
    "QStandardItem*\0item\0onLog\0onpositionChanged\0"
    "position\0onviewCenterChanged\0viewCenter\0"
    "onTestBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    1,   71,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
       9,    0,   78,    2, 0x0a /* Public */,
      10,    1,   79,    2, 0x0a /* Public */,
      13,    0,   82,    2, 0x0a /* Public */,
      14,    1,   83,    2, 0x0a /* Public */,
      16,    1,   86,    2, 0x0a /* Public */,
      18,    0,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector3D,   15,
    QMetaType::Void, QMetaType::QVector3D,   17,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Exit(); break;
        case 1: _t->onPortSelected(); break;
        case 2: _t->onReceivedData((*reinterpret_cast< ReceivedData(*)>(_a[1]))); break;
        case 3: _t->onModelRecordLoaded(); break;
        case 4: _t->onInserNewRecorded((*reinterpret_cast< ReceivedData(*)>(_a[1]))); break;
        case 5: _t->onModelInserted(); break;
        case 6: _t->onTablemodelModified((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 7: _t->onLog(); break;
        case 8: _t->onpositionChanged((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 9: _t->onviewCenterChanged((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 10: _t->onTestBtnClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
