#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QThread>
#include <QDebug>
#include <QSerialPort>

#include "crc.h"


#define DATA_FRAME_TO_ROBOT_SIZE    7

typedef enum {

    Open_connection_OK      =   1,
    Open_connection_FAIL    =   2,

    Close_connection_OK     =   3,
    Close_connection_FAIL   =   4,

    Port_is_busy            =   5

} Status_Codes;

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int16_t Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte);
int8_t Divide_bytes(int16_t data, uint8_t which_byte);

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Data_from_Robot
{

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Data_to_Robot
{
    double Kp, Ki, Kd;
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Bluetooth : public QThread
{
    Q_OBJECT

private:

    QSerialPort *Device = new QSerialPort;

    Data_from_Robot DF_Robot;
    Data_to_Robot   DT_Robot;

    void (Bluetooth::*f)();

    void Receive_frame();
    void Parse_frame();
    void Send_frame();

    void Communication();

public:

    Bluetooth();
    ~Bluetooth();

    void run() {

        (this->*f)();
    }

    void Open_connection(QString portName);
    void Close_connection();

    void Start_communication_thread();

    void Set_DT_Robot(Data_to_Robot Data);

private slots:

public slots:

signals:

    void Serial_Interface_Signal(Status_Codes);
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // BLUETOOTH_H
