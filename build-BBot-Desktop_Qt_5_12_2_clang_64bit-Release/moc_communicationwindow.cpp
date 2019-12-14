/****************************************************************************
** Meta object code from reading C++ file 'communicationwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../stm32_f103_mpu9250_lib/AHRS_Qt_App/inc/communicationwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'communicationwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CommunicationWindow_t {
    QByteArrayData data[25];
    char stringdata0[597];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CommunicationWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CommunicationWindow_t qt_meta_stringdata_CommunicationWindow = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CommunicationWindow"
QT_MOC_LITERAL(1, 20, 20), // "Connection_OK_Signal"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 22), // "Connection_FAIL_Signal"
QT_MOC_LITERAL(4, 65, 22), // "Parsed_frame_OK_Signal"
QT_MOC_LITERAL(5, 88, 15), // "Data_from_Robot"
QT_MOC_LITERAL(6, 104, 13), // "Timeout_Error"
QT_MOC_LITERAL(7, 118, 15), // "Disconnect_Slot"
QT_MOC_LITERAL(8, 134, 21), // "Serial_Interface_Slot"
QT_MOC_LITERAL(9, 156, 12), // "Status_Codes"
QT_MOC_LITERAL(10, 169, 6), // "status"
QT_MOC_LITERAL(11, 176, 23), // "Send_Data_to_robot_Slot"
QT_MOC_LITERAL(12, 200, 20), // "Parsed_frame_OK_Slot"
QT_MOC_LITERAL(13, 221, 28), // "on_pushButton_Search_clicked"
QT_MOC_LITERAL(14, 250, 29), // "on_pushButton_Connect_clicked"
QT_MOC_LITERAL(15, 280, 32), // "on_pushButton_Disconnect_clicked"
QT_MOC_LITERAL(16, 313, 27), // "on_pushButton_Clear_clicked"
QT_MOC_LITERAL(17, 341, 28), // "on_pushButton_Cancel_clicked"
QT_MOC_LITERAL(18, 370, 30), // "on_pushButton_Continue_clicked"
QT_MOC_LITERAL(19, 401, 36), // "on_comboBox_Baud_currentIndex..."
QT_MOC_LITERAL(20, 438, 5), // "index"
QT_MOC_LITERAL(21, 444, 36), // "on_comboBox_Bits_currentIndex..."
QT_MOC_LITERAL(22, 481, 38), // "on_comboBox_Parity_currentInd..."
QT_MOC_LITERAL(23, 520, 36), // "on_comboBox_Stop_currentIndex..."
QT_MOC_LITERAL(24, 557, 39) // "on_comboBox_Control_currentIn..."

    },
    "CommunicationWindow\0Connection_OK_Signal\0"
    "\0Connection_FAIL_Signal\0Parsed_frame_OK_Signal\0"
    "Data_from_Robot\0Timeout_Error\0"
    "Disconnect_Slot\0Serial_Interface_Slot\0"
    "Status_Codes\0status\0Send_Data_to_robot_Slot\0"
    "Parsed_frame_OK_Slot\0on_pushButton_Search_clicked\0"
    "on_pushButton_Connect_clicked\0"
    "on_pushButton_Disconnect_clicked\0"
    "on_pushButton_Clear_clicked\0"
    "on_pushButton_Cancel_clicked\0"
    "on_pushButton_Continue_clicked\0"
    "on_comboBox_Baud_currentIndexChanged\0"
    "index\0on_comboBox_Bits_currentIndexChanged\0"
    "on_comboBox_Parity_currentIndexChanged\0"
    "on_comboBox_Stop_currentIndexChanged\0"
    "on_comboBox_Control_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CommunicationWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    1,  111,    2, 0x06 /* Public */,
       6,    0,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  115,    2, 0x0a /* Public */,
       8,    1,  116,    2, 0x0a /* Public */,
      11,    0,  119,    2, 0x0a /* Public */,
      12,    0,  120,    2, 0x0a /* Public */,
      13,    0,  121,    2, 0x08 /* Private */,
      14,    0,  122,    2, 0x08 /* Private */,
      15,    0,  123,    2, 0x08 /* Private */,
      16,    0,  124,    2, 0x08 /* Private */,
      17,    0,  125,    2, 0x08 /* Private */,
      18,    0,  126,    2, 0x08 /* Private */,
      19,    1,  127,    2, 0x08 /* Private */,
      21,    1,  130,    2, 0x08 /* Private */,
      22,    1,  133,    2, 0x08 /* Private */,
      23,    1,  136,    2, 0x08 /* Private */,
      24,    1,  139,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,

       0        // eod
};

void CommunicationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommunicationWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Connection_OK_Signal(); break;
        case 1: _t->Connection_FAIL_Signal(); break;
        case 2: _t->Parsed_frame_OK_Signal((*reinterpret_cast< Data_from_Robot(*)>(_a[1]))); break;
        case 3: _t->Timeout_Error(); break;
        case 4: _t->Disconnect_Slot(); break;
        case 5: _t->Serial_Interface_Slot((*reinterpret_cast< Status_Codes(*)>(_a[1]))); break;
        case 6: _t->Send_Data_to_robot_Slot(); break;
        case 7: _t->Parsed_frame_OK_Slot(); break;
        case 8: _t->on_pushButton_Search_clicked(); break;
        case 9: _t->on_pushButton_Connect_clicked(); break;
        case 10: _t->on_pushButton_Disconnect_clicked(); break;
        case 11: _t->on_pushButton_Clear_clicked(); break;
        case 12: _t->on_pushButton_Cancel_clicked(); break;
        case 13: _t->on_pushButton_Continue_clicked(); break;
        case 14: _t->on_comboBox_Baud_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_comboBox_Bits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_comboBox_Parity_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_comboBox_Stop_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_comboBox_Control_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CommunicationWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommunicationWindow::Connection_OK_Signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CommunicationWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommunicationWindow::Connection_FAIL_Signal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CommunicationWindow::*)(Data_from_Robot );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommunicationWindow::Parsed_frame_OK_Signal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CommunicationWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommunicationWindow::Timeout_Error)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CommunicationWindow::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_CommunicationWindow.data,
    qt_meta_data_CommunicationWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CommunicationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommunicationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommunicationWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CommunicationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void CommunicationWindow::Connection_OK_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CommunicationWindow::Connection_FAIL_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CommunicationWindow::Parsed_frame_OK_Signal(Data_from_Robot _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CommunicationWindow::Timeout_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
