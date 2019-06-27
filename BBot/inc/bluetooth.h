#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QThread>
#include <QDebug>

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Data_from_Robot
{

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Data_to_Robot
{

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Bluetooth : public QThread
{
    Q_OBJECT

private:

    Data_from_Robot DF_Robot;
    Data_to_Robot   DT_Robot;

    void (Bluetooth::*f)();

    void Open_connection();
    void Close_connection();

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

    void Start_communication_thread();

private slots:

public slots:

signals:

    void Open_Connection_OK();
    void Open_Connection_FAIL();

    void Close_Connection_OK();
    void Close_Connection_FAIL();

    void Received_Frame_OK();
    void Received_Frame_FAIL();

    void Parsed_Frame_OK();
    void Parsed_Frame_FAIL();

    void Sended_Frame_OK();
    void Sended_Frame_FAIL();
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // BLUETOOTH_H
