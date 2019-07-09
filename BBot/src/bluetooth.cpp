#include "bluetooth.h"
#include <stdio.h>
#include <stdlib.h>
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int16_t Merge_bytes(uint8_t _lower_byte, uint8_t _higher_byte) {

    int16_t uint16_byte = static_cast<int16_t>( ( _higher_byte << 8 ) + _lower_byte );

    if(uint16_byte >= 32767) {

        int16_t int_byte =  static_cast<int16_t>( uint16_byte - (2 * 32768) );
        return int_byte;
    }

    else return uint16_byte;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int8_t Divide_bytes(int16_t data, uint8_t which_byte) {

    if(which_byte == 'L') {

        return (data & 0xFF);
    }
    else if(which_byte == 'H') {

        return ( data >> 8 );
    }

    return 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bluetooth::Bluetooth()
{

}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bluetooth::~Bluetooth()
{
    delete Device;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Open_connection(QString portName)
{

    //Device = new QSerialPort;
    this->Device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if( !Device->isOpen() ) {

        if( Device->open(QSerialPort::ReadWrite) ) {

            this->Device->setBaudRate(QSerialPort::BaudRate::Baud9600);
            this->Device->setDataBits(QSerialPort::DataBits::Data8);
            this->Device->setParity(QSerialPort::Parity::NoParity);
            this->Device->setStopBits(QSerialPort::StopBits::OneStop);
            this->Device->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

            emit Serial_Interface_Signal(Open_connection_OK);
        }
        else {

            emit Serial_Interface_Signal(Open_connection_FAIL);
        }
    }
    else {

        emit Serial_Interface_Signal(Port_is_busy);

        return;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Close_connection()
{
    if(this->Device->isOpen()) {

        Device->close();

        emit Serial_Interface_Signal(Close_connection_OK);
    }
    else {

        emit Serial_Interface_Signal(Close_connection_FAIL);

        return;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Receive_frame()
{
    //qDebug() << "Odbieram ! \n";

    /*
    QByteArray line = this->Device->readAll();
    qDebug() << line;

    emit Serial_Interface_Signal();

    Received_Frame_OK();

    Parse_frame();
    */
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Parse_frame()
{
    //qDebug() << "Parsuję ! \n";

    //emit Parsed_Frame_OK();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Send_frame()
{
    // Case 1: Fill data frame
    int16_t Kp = static_cast<int16_t>(DT_Robot.Kp * 100);
    int16_t Ki = static_cast<int16_t>(DT_Robot.Ki * 100);
    int16_t Kd = static_cast<int16_t>(DT_Robot.Kd * 100);

    int8_t Data_frame[DATA_FRAME_TO_ROBOT_SIZE];

    Data_frame[0] = 'S';
    Data_frame[1] = Divide_bytes(Kp, 'L');
    Data_frame[2] = Divide_bytes(Kp, 'H');
    Data_frame[3] = Divide_bytes(Ki, 'L');
    Data_frame[4] = Divide_bytes(Ki, 'H');
    Data_frame[5] = Divide_bytes(Kd, 'L');
    Data_frame[6] = Divide_bytes(Kd, 'H');

    // Case 2: Save data frame as QString
    char Data[DATA_FRAME_TO_ROBOT_SIZE];

    for (int i = 0; i < DATA_FRAME_TO_ROBOT_SIZE; i++) {

        Data[i] = Data_frame[i];
    }

    // Case 3: Send data frame
    if( Device->isWritable() ) {

        qDebug() << "Wysyłam dane: ";
        qDebug() << "Kp_L: " << Data[1];
        qDebug() << "Kp_H: " << Data[2];
        qDebug() << "Ki_L: " << Data[3];
        qDebug() << "Ki_H: " << Data[4];
        qDebug() << "Kd_L: " << Data[5];
        qDebug() << "Kd_H: " << Data[6];

        Device->write( Data, DATA_FRAME_TO_ROBOT_SIZE);
        Device->waitForBytesWritten(10);
        Device->flush();
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Communication()
{
    while(1) {

        if( Device->isOpen() ) {

            // Receiving
            //Receive_frame();

            // Sending
            Send_frame();

            msleep(100);
        }
        else {

            break;
        }
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Start_communication_thread()
{
    f = &Bluetooth::Communication;
    this->start(Priority::NormalPriority);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Set_DT_Robot(Data_to_Robot Data)
{
    DT_Robot = Data;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
