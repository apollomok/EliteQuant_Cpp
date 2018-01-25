/****************************************************************************
** Meta object code from reading C++ file 'clientmq.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clientmq.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientmq.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH

struct qt_meta_stringdata_ClientMQ_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientMQ_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientMQ_t qt_meta_stringdata_ClientMQ = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ClientMQ"
QT_MOC_LITERAL(1, 9, 20), // "IncomingMarketSignal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "string"
QT_MOC_LITERAL(4, 38, 3), // "msg"
QT_MOC_LITERAL(5, 42, 21), // "IncomingGeneralSignal"
QT_MOC_LITERAL(6, 64, 19) // "OutgoingMessageSlot"

    },
    "ClientMQ\0IncomingMarketSignal\0\0string\0"
    "msg\0IncomingGeneralSignal\0OutgoingMessageSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientMQ[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void ClientMQ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientMQ *_t = static_cast<ClientMQ *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IncomingMarketSignal((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: _t->IncomingGeneralSignal((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->OutgoingMessageSlot((*reinterpret_cast< string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ClientMQ::*_t)(string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientMQ::IncomingMarketSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ClientMQ::*_t)(string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientMQ::IncomingGeneralSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ClientMQ::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClientMQ.data,
      qt_meta_data_ClientMQ,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientMQ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientMQ::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientMQ.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ClientMQ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ClientMQ::IncomingMarketSignal(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientMQ::IncomingGeneralSignal(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
