/****************************************************************************
** Meta object code from reading C++ file 'modelinteract.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../modelinteract.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelinteract.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelInteract_t {
    QByteArrayData data[6];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelInteract_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelInteract_t qt_meta_stringdata_ModelInteract = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ModelInteract"
QT_MOC_LITERAL(1, 14, 12), // "LoadRecorded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "InsertNewRecorded"
QT_MOC_LITERAL(4, 46, 12), // "ReceivedData"
QT_MOC_LITERAL(5, 59, 4) // "data"

    },
    "ModelInteract\0LoadRecorded\0\0"
    "InsertNewRecorded\0ReceivedData\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelInteract[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    1,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void ModelInteract::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelInteract *_t = static_cast<ModelInteract *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LoadRecorded(); break;
        case 1: _t->InsertNewRecorded((*reinterpret_cast< ReceivedData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ModelInteract::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelInteract::LoadRecorded)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ModelInteract::*_t)(ReceivedData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelInteract::InsertNewRecorded)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ModelInteract::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModelInteract.data,
      qt_meta_data_ModelInteract,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ModelInteract::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelInteract::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelInteract.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ModelInteract::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ModelInteract::LoadRecorded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ModelInteract::InsertNewRecorded(ReceivedData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
