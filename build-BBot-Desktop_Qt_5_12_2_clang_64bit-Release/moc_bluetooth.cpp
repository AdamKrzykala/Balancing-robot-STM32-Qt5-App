/****************************************************************************
** Meta object code from reading C++ file 'bluetooth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../stm32_f103_mpu9250_lib/AHRS_Qt_App/inc/bluetooth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bluetooth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Bluetooth_t {
    QByteArrayData data[8];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bluetooth_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bluetooth_t qt_meta_stringdata_Bluetooth = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Bluetooth"
QT_MOC_LITERAL(1, 10, 23), // "Serial_Interface_Signal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "Status_Codes"
QT_MOC_LITERAL(4, 48, 22), // "Parsed_frame_OK_Signal"
QT_MOC_LITERAL(5, 71, 13), // "Receive_frame"
QT_MOC_LITERAL(6, 85, 10), // "Send_frame"
QT_MOC_LITERAL(7, 96, 12) // "Timeout_Test"

    },
    "Bluetooth\0Serial_Interface_Signal\0\0"
    "Status_Codes\0Parsed_frame_OK_Signal\0"
    "Receive_frame\0Send_frame\0Timeout_Test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bluetooth[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Bluetooth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Bluetooth *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Serial_Interface_Signal((*reinterpret_cast< Status_Codes(*)>(_a[1]))); break;
        case 1: _t->Parsed_frame_OK_Signal(); break;
        case 2: _t->Receive_frame(); break;
        case 3: _t->Send_frame(); break;
        case 4: _t->Timeout_Test(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Bluetooth::*)(Status_Codes );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Bluetooth::Serial_Interface_Signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Bluetooth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Bluetooth::Parsed_frame_OK_Signal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Bluetooth::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Bluetooth.data,
    qt_meta_data_Bluetooth,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Bluetooth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bluetooth::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Bluetooth.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Bluetooth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Bluetooth::Serial_Interface_Signal(Status_Codes _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Bluetooth::Parsed_frame_OK_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
