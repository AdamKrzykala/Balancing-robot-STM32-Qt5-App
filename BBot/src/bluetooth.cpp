#include "bluetooth.h"
#include <stdio.h>
#include <stdlib.h>

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

byte CRC8_SingleByte(byte CRC_prev, byte Data) {

    CRC_prev ^= Data;

    for(byte Idx = 0; Idx < 8; ++Idx) {

        if( (CRC_prev & 0x80) != 0 ) {

            CRC_prev = static_cast<byte>( (CRC_prev << 1) ^ POLYNOMIAL_9 );
        } else {

            CRC_prev = static_cast<byte>(CRC_prev << 1);
        }
    }

    return CRC_prev;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

byte CRC8_DataArray(byte *pData, byte Len) {

    byte CRC_final = static_cast<byte>(0xFF);

    for(byte Idx = 0; Idx < Len; ++Idx) {

        CRC_final = CRC8_SingleByte(CRC_final, pData[Idx]);
    }

    return CRC_final;
}

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

        return static_cast<int8_t>(data & 0xFF);
    }
    else if(which_byte == 'H') {

        return ( data >> 8 );
    }

    return 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bluetooth::Bluetooth()
{
    DT_Robot.Angle_Kd = 0;
    DT_Robot.Angle_Ki = 0;
    DT_Robot.Angle_Kp = 0;
    DT_Robot.Speed_Kd = 0;
    DT_Robot.Speed_Ki = 0;
    DT_Robot.Speed_Kp = 0;
    DT_Robot.Left_engine_speed = 0;
    DT_Robot.Right_engine_speed = 0;
    DT_Robot.Emergency_stop = 0;
    DT_Robot.Complementary_filter_weight = 0;

    Send_flag = false;
    Receive_flag = false;

    connect(Device, SIGNAL( readyRead() ), this, SLOT( Receiving_test() ));
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

    if( Device->isOpen() && Device->isReadable()) {

        // Case 1: Read all data from Serial Port
        QByteArray array = Device->readAll();

        // Case 2: Copy this data to temporary frame
        if(array[0] == 'G') {

            for(int i = 0; i < GYROSCOPE_DATA_FRAME_SIZE; i++) {

                Gyro_data_frame_received[i] = array[i];
            }

            int8_t CRC_received = Gyro_data_frame_received[GYROSCOPE_DATA_FRAME_SIZE - 1];
            int8_t CRC_actual = CRC8_DataArray(Gyro_data_frame_received, GYROSCOPE_DATA_FRAME_SIZE - 1);

            if( CRC_actual == CRC_received ) {

                Parse_gyroscope_frame();
            }
        }
        if(array[14] == 'A') {

            for(int i = 0; i < ACCELEROMETER_DATA_FRAME_SIZE; i++) {

                Acce_data_frame_received[i] = array[i];
            }

            int8_t CRC_received = Acce_data_frame_received[ACCELEROMETER_DATA_FRAME_SIZE - 1];
            int8_t CRC_actual = CRC8_DataArray(Acce_data_frame_received, ACCELEROMETER_DATA_FRAME_SIZE - 1);

            if( CRC_actual == CRC_received ) {

                Parse_accelerometer_frame();
            }
        }
    }

}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Parse_accelerometer_frame()
{
    //qDebug() << "Parsuję ! \n";

    DF_Robot.a_x = static_cast<double>( Acce_data_frame_received[1] ) / 100;
    DF_Robot.a_y = static_cast<double>( Acce_data_frame_received[2] ) / 100;
    DF_Robot.a_z = static_cast<double>( Acce_data_frame_received[3] ) / 100;

    DF_Robot.a_roll  = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Acce_data_frame_received[4]), static_cast<uint8_t>(Acce_data_frame_received[5])  ) ) / 100;
    DF_Robot.a_pitch = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Acce_data_frame_received[6]), static_cast<uint8_t>(Acce_data_frame_received[7])  ) ) / 100;
    DF_Robot.a_yaw   = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Acce_data_frame_received[8]), static_cast<uint8_t>(Acce_data_frame_received[9]) ) ) / 100;

    qDebug() << "Odbieram dane: ";
    qDebug() << "a_x: " << DF_Robot.a_x;
    qDebug() << "a_y: " << DF_Robot.a_y;
    qDebug() << "a_z: " << DF_Robot.a_z;
    qDebug() << "a_roll: "  << DF_Robot.a_roll;
    qDebug() << "a_pitch: " << DF_Robot.a_pitch;
    qDebug() << "a_yaw: "   << DF_Robot.a_yaw;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Parse_gyroscope_frame()
{

    DF_Robot.g_x = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Gyro_data_frame_received[1]), static_cast<uint8_t>(Gyro_data_frame_received[2]) ) ) / 100;
    DF_Robot.g_y = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Gyro_data_frame_received[3]), static_cast<uint8_t>(Gyro_data_frame_received[4]) ) ) / 100;
    DF_Robot.g_z = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Gyro_data_frame_received[5]), static_cast<uint8_t>(Gyro_data_frame_received[6]) ) ) / 100;

    DF_Robot.g_roll  = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Gyro_data_frame_received[7]), static_cast<uint8_t>(Gyro_data_frame_received[8])  ) ) / 100;
    DF_Robot.g_pitch = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Gyro_data_frame_received[9]), static_cast<uint8_t>(Gyro_data_frame_received[10])  ) ) / 100;
    DF_Robot.g_yaw   = static_cast<double>( Merge_bytes(static_cast<uint8_t>(Gyro_data_frame_received[11]), static_cast<uint8_t>(Gyro_data_frame_received[12]) ) ) / 100;

    qDebug() << "g_x: " << DF_Robot.g_x;
    qDebug() << "g_y: " << DF_Robot.g_y;
    qDebug() << "g_z: " << DF_Robot.g_z;
    qDebug() << "g_roll: "  << DF_Robot.g_roll;
    qDebug() << "g_pitch: " << DF_Robot.g_pitch;
    qDebug() << "g_yaw: "   << DF_Robot.g_yaw;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Send_frame()
{
    // Case 1: Fill data frame

    // Angle PID data
    int16_t Angle_Kp = static_cast<int16_t>(DT_Robot.Angle_Kp * 100);
    int16_t Angle_Ki = static_cast<int16_t>(DT_Robot.Angle_Ki * 100);
    int16_t Angle_Kd = static_cast<int16_t>(DT_Robot.Angle_Kd * 100);

    // Speed PID data
    int16_t Speed_Kp = static_cast<int16_t>(DT_Robot.Speed_Kp * 100);
    int16_t Speed_Ki = static_cast<int16_t>(DT_Robot.Speed_Ki * 100);
    int16_t Speed_Kd = static_cast<int16_t>(DT_Robot.Speed_Kd * 100);

    // Filters data
    int8_t Complementary_filter_weight = static_cast<int8_t>(DT_Robot.Complementary_filter_weight * 100);

    // Engines speed data
    int16_t Left_engine_speed  = static_cast<int16_t>(DT_Robot.Left_engine_speed);
    int16_t Right_engine_speed = static_cast<int16_t>(DT_Robot.Right_engine_speed);

    // Additional data
    int8_t Emergency_stop = static_cast<int8_t>(DT_Robot.Emergency_stop);

    int8_t Data_frame[DATA_FRAME_TO_ROBOT_SIZE];

    Data_frame[0]  = 'S';

    Data_frame[1]  = Divide_bytes(Angle_Kp, 'L');
    Data_frame[2]  = Divide_bytes(Angle_Kp, 'H');
    Data_frame[3]  = Divide_bytes(Angle_Ki, 'L');
    Data_frame[4]  = Divide_bytes(Angle_Ki, 'H');
    Data_frame[5]  = Divide_bytes(Angle_Kd, 'L');
    Data_frame[6]  = Divide_bytes(Angle_Kd, 'H');

    Data_frame[7]  = Divide_bytes(Speed_Kp, 'L');
    Data_frame[8]  = Divide_bytes(Speed_Kp, 'H');
    Data_frame[9]  = Divide_bytes(Speed_Ki, 'L');
    Data_frame[10] = Divide_bytes(Speed_Ki, 'H');
    Data_frame[11] = Divide_bytes(Speed_Kd, 'L');
    Data_frame[12] = Divide_bytes(Speed_Kd, 'H');

    Data_frame[13] = Complementary_filter_weight;

    Data_frame[14] = Divide_bytes(Left_engine_speed, 'L');
    Data_frame[15] = Divide_bytes(Left_engine_speed, 'H');
    Data_frame[16] = Divide_bytes(Right_engine_speed, 'L');
    Data_frame[17] = Divide_bytes(Right_engine_speed, 'H');

    Data_frame[18] = Emergency_stop;

    Data_frame[19] = CRC8_DataArray(Data_frame, DATA_FRAME_TO_ROBOT_SIZE - 1);

    // Case 2: Save data frame as char array
    char Data[DATA_FRAME_TO_ROBOT_SIZE];

    for (int i = 0; i < DATA_FRAME_TO_ROBOT_SIZE; i++) {

        Data[i] = Data_frame[i];
    }

    // Case 3: Send data frame
    if( Device->isWritable() ) {

        qDebug() << "Wysyłam dane: ";
        qDebug() << "Kp (wychylenie): "             << Angle_Kp;
        qDebug() << "Ki (wychylenie): "             << Angle_Ki;
        qDebug() << "Kd (wychylenie): "             << Angle_Kd;
        qDebug() << "Kp (predkosc): "               << Speed_Kp;
        qDebug() << "Ki (predkosc): "               << Speed_Ki;
        qDebug() << "Kd (predkosc): "               << Speed_Kd;
        qDebug() << "Waga filtru: "                 << Complementary_filter_weight;
        qDebug() << "Predkosc lewego silnika: "     << Left_engine_speed;
        qDebug() << "Predkosc prawego silnika: "    << Right_engine_speed;
        qDebug() << "Przycisk awaryjny: "           << Emergency_stop;


        Device->write( Data, DATA_FRAME_TO_ROBOT_SIZE);
        Device->waitForBytesWritten(20);
        Device->flush();
    }

    Send_flag = false;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Communication()
{
    while(1) {

        if( Device->isOpen() ) {

            /*
            if(Receive_flag == true) {

                // Receiving
                //Receive_frame();

                // Parsing
                //Parse_frame();

                Receive_flag = false;
            }*/

            if(Send_flag == true) {

                // Sending
                Send_frame();
            }

            emit Parsed_frame_OK_Signal();

            msleep(80);
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

Data_from_Robot Bluetooth::Get_DF_Robot()
{
    return DF_Robot;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Set_Send_Flag()
{
    Send_flag = true;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bluetooth::Receiving_test()
{
    Receive_flag = true;

    // Receiving
    Receive_frame();

    // Parsing
    //Parse_frame();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
