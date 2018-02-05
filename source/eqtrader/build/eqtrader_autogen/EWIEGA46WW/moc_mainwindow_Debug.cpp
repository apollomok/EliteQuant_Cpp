/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "OutgoingMessageSignal"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "string"
QT_MOC_LITERAL(4, 41, 8), // "sMessage"
QT_MOC_LITERAL(5, 50, 18), // "IncomingMarketSlot"
QT_MOC_LITERAL(6, 69, 19), // "IncomingGeneralSlot"
QT_MOC_LITERAL(7, 89, 27), // "on_pushButton_Order_clicked"
QT_MOC_LITERAL(8, 117, 22), // "SetParamsToOrderWidget"
QT_MOC_LITERAL(9, 140, 3), // "row"
QT_MOC_LITERAL(10, 144, 6), // "column"
QT_MOC_LITERAL(11, 151, 13), // "StartStrategy"
QT_MOC_LITERAL(12, 165, 13), // "PauseStrategy"
QT_MOC_LITERAL(13, 179, 12), // "StopStrategy"
QT_MOC_LITERAL(14, 192, 17), // "LiquidateStrategy"
QT_MOC_LITERAL(15, 210, 18), // "TranslateToEnglish"
QT_MOC_LITERAL(16, 229, 18) // "TranslateToChinese"

    },
    "MainWindow\0OutgoingMessageSignal\0\0"
    "string\0sMessage\0IncomingMarketSlot\0"
    "IncomingGeneralSlot\0on_pushButton_Order_clicked\0"
    "SetParamsToOrderWidget\0row\0column\0"
    "StartStrategy\0PauseStrategy\0StopStrategy\0"
    "LiquidateStrategy\0TranslateToEnglish\0"
    "TranslateToChinese"
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
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   72,    2, 0x0a /* Public */,
       6,    1,   75,    2, 0x0a /* Public */,
       7,    0,   78,    2, 0x08 /* Private */,
       8,    2,   79,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OutgoingMessageSignal((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: _t->IncomingMarketSlot((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->IncomingGeneralSlot((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_Order_clicked(); break;
        case 4: _t->SetParamsToOrderWidget((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->StartStrategy(); break;
        case 6: _t->PauseStrategy(); break;
        case 7: _t->StopStrategy(); break;
        case 8: _t->LiquidateStrategy(); break;
        case 9: _t->TranslateToEnglish(); break;
        case 10: _t->TranslateToChinese(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::OutgoingMessageSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
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

// SIGNAL 0
void MainWindow::OutgoingMessageSignal(string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
