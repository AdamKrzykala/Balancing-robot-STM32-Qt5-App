/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../stm32_f103_mpu9250_lib/AHRS_Qt_App/inc/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[35];
    char stringdata0[1053];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "Disconnect_Signal"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "Send_data_Signal"
QT_MOC_LITERAL(4, 47, 27), // "MainWindow_realtimeDataSlot"
QT_MOC_LITERAL(5, 75, 15), // "Data_from_Robot"
QT_MOC_LITERAL(6, 91, 4), // "data"
QT_MOC_LITERAL(7, 96, 18), // "Connection_OK_Slot"
QT_MOC_LITERAL(8, 115, 39), // "on_pushButton_ConnectDisconne..."
QT_MOC_LITERAL(9, 155, 31), // "on_checkBox_Filter_Roll_clicked"
QT_MOC_LITERAL(10, 187, 32), // "on_checkBox_Filter_Pitch_clicked"
QT_MOC_LITERAL(11, 220, 30), // "on_checkBox_Filter_Yaw_clicked"
QT_MOC_LITERAL(12, 251, 26), // "on_pushButton_Send_clicked"
QT_MOC_LITERAL(13, 278, 26), // "on_pushButton_Exit_clicked"
QT_MOC_LITERAL(14, 305, 57), // "on_doubleSpinBox_Complementar..."
QT_MOC_LITERAL(15, 363, 4), // "arg1"
QT_MOC_LITERAL(16, 368, 34), // "on_pushButton_Plots_Center_cl..."
QT_MOC_LITERAL(17, 403, 38), // "on_pushButton_Plots_Start_Sto..."
QT_MOC_LITERAL(18, 442, 39), // "on_pushButton_Reset_Plots_Ran..."
QT_MOC_LITERAL(19, 482, 43), // "on_radioButton_Complementary_..."
QT_MOC_LITERAL(20, 526, 7), // "checked"
QT_MOC_LITERAL(21, 534, 36), // "on_radioButton_Kalman_filter_..."
QT_MOC_LITERAL(22, 571, 52), // "on_doubleSpinBox_Kalman_filte..."
QT_MOC_LITERAL(23, 624, 38), // "on_radioButton_Madgwick_filte..."
QT_MOC_LITERAL(24, 663, 43), // "on_doubleSpinBox_Madgwick_bet..."
QT_MOC_LITERAL(25, 707, 31), // "on_checkBox_Gyroscope_X_toggled"
QT_MOC_LITERAL(26, 739, 31), // "on_checkBox_Gyroscope_Y_toggled"
QT_MOC_LITERAL(27, 771, 31), // "on_checkBox_Gyroscope_Z_toggled"
QT_MOC_LITERAL(28, 803, 35), // "on_checkBox_Accelerometer_X_t..."
QT_MOC_LITERAL(29, 839, 35), // "on_checkBox_Accelerometer_Y_t..."
QT_MOC_LITERAL(30, 875, 35), // "on_checkBox_Accelerometer_Z_t..."
QT_MOC_LITERAL(31, 911, 34), // "on_checkBox_Magnetometer_X_to..."
QT_MOC_LITERAL(32, 946, 34), // "on_checkBox_Magnetometer_Y_to..."
QT_MOC_LITERAL(33, 981, 34), // "on_checkBox_Magnetometer_Z_to..."
QT_MOC_LITERAL(34, 1016, 36) // "on_radioButton_Mahony_filter_..."

    },
    "MainWindow\0Disconnect_Signal\0\0"
    "Send_data_Signal\0MainWindow_realtimeDataSlot\0"
    "Data_from_Robot\0data\0Connection_OK_Slot\0"
    "on_pushButton_ConnectDisconnect_clicked\0"
    "on_checkBox_Filter_Roll_clicked\0"
    "on_checkBox_Filter_Pitch_clicked\0"
    "on_checkBox_Filter_Yaw_clicked\0"
    "on_pushButton_Send_clicked\0"
    "on_pushButton_Exit_clicked\0"
    "on_doubleSpinBox_Complementary_filter_weight_valueChanged\0"
    "arg1\0on_pushButton_Plots_Center_clicked\0"
    "on_pushButton_Plots_Start_Stop_clicked\0"
    "on_pushButton_Reset_Plots_Range_clicked\0"
    "on_radioButton_Complementary_filter_toggled\0"
    "checked\0on_radioButton_Kalman_filter_toggled\0"
    "on_doubleSpinBox_Kalman_filter_variance_valueChanged\0"
    "on_radioButton_Madgwick_filter_toggled\0"
    "on_doubleSpinBox_Madgwick_beta_valueChanged\0"
    "on_checkBox_Gyroscope_X_toggled\0"
    "on_checkBox_Gyroscope_Y_toggled\0"
    "on_checkBox_Gyroscope_Z_toggled\0"
    "on_checkBox_Accelerometer_X_toggled\0"
    "on_checkBox_Accelerometer_Y_toggled\0"
    "on_checkBox_Accelerometer_Z_toggled\0"
    "on_checkBox_Magnetometer_X_toggled\0"
    "on_checkBox_Magnetometer_Y_toggled\0"
    "on_checkBox_Magnetometer_Z_toggled\0"
    "on_radioButton_Mahony_filter_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  159,    2, 0x06 /* Public */,
       3,    0,  160,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  161,    2, 0x0a /* Public */,
       7,    0,  164,    2, 0x0a /* Public */,
       8,    0,  165,    2, 0x0a /* Public */,
       9,    0,  166,    2, 0x08 /* Private */,
      10,    0,  167,    2, 0x08 /* Private */,
      11,    0,  168,    2, 0x08 /* Private */,
      12,    0,  169,    2, 0x08 /* Private */,
      13,    0,  170,    2, 0x08 /* Private */,
      14,    1,  171,    2, 0x08 /* Private */,
      16,    0,  174,    2, 0x08 /* Private */,
      17,    0,  175,    2, 0x08 /* Private */,
      18,    0,  176,    2, 0x08 /* Private */,
      19,    1,  177,    2, 0x08 /* Private */,
      21,    1,  180,    2, 0x08 /* Private */,
      22,    1,  183,    2, 0x08 /* Private */,
      23,    1,  186,    2, 0x08 /* Private */,
      24,    1,  189,    2, 0x08 /* Private */,
      25,    1,  192,    2, 0x08 /* Private */,
      26,    1,  195,    2, 0x08 /* Private */,
      27,    1,  198,    2, 0x08 /* Private */,
      28,    1,  201,    2, 0x08 /* Private */,
      29,    1,  204,    2, 0x08 /* Private */,
      30,    1,  207,    2, 0x08 /* Private */,
      31,    1,  210,    2, 0x08 /* Private */,
      32,    1,  213,    2, 0x08 /* Private */,
      33,    1,  216,    2, 0x08 /* Private */,
      34,    1,  219,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Disconnect_Signal(); break;
        case 1: _t->Send_data_Signal(); break;
        case 2: _t->MainWindow_realtimeDataSlot((*reinterpret_cast< Data_from_Robot(*)>(_a[1]))); break;
        case 3: _t->Connection_OK_Slot(); break;
        case 4: _t->on_pushButton_ConnectDisconnect_clicked(); break;
        case 5: _t->on_checkBox_Filter_Roll_clicked(); break;
        case 6: _t->on_checkBox_Filter_Pitch_clicked(); break;
        case 7: _t->on_checkBox_Filter_Yaw_clicked(); break;
        case 8: _t->on_pushButton_Send_clicked(); break;
        case 9: _t->on_pushButton_Exit_clicked(); break;
        case 10: _t->on_doubleSpinBox_Complementary_filter_weight_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_Plots_Center_clicked(); break;
        case 12: _t->on_pushButton_Plots_Start_Stop_clicked(); break;
        case 13: _t->on_pushButton_Reset_Plots_Range_clicked(); break;
        case 14: _t->on_radioButton_Complementary_filter_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_radioButton_Kalman_filter_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_doubleSpinBox_Kalman_filter_variance_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->on_radioButton_Madgwick_filter_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_doubleSpinBox_Madgwick_beta_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->on_checkBox_Gyroscope_X_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_checkBox_Gyroscope_Y_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_checkBox_Gyroscope_Z_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_checkBox_Accelerometer_X_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->on_checkBox_Accelerometer_Y_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_checkBox_Accelerometer_Z_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_checkBox_Magnetometer_X_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_checkBox_Magnetometer_Y_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_checkBox_Magnetometer_Z_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_radioButton_Mahony_filter_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::Disconnect_Signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::Send_data_Signal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::Disconnect_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::Send_data_Signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
