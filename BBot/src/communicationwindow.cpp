#include "communicationwindow.h"
#include "ui_communicationwindow.h"

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::Disconnect_Slot()
{
    this->show();
    on_pushButton_Disconnect_clicked();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::Serial_Interface_Slot(Status_Codes status)
{
    switch (status) {

        case Open_connection_OK:

            Serial_is_open = true;
            this->CommunicationWindow_addToLogs("Otwarto port szeregowy");
            ui->label_ConnectionStatus->setText("<font color='green'>Połączono</font>");
            break;

        case Open_connection_FAIL:

            this->CommunicationWindow_addToLogs("Otwarcie portu szeregowego się nie powiodło !");
            ui->label_ConnectionStatus->setText("<font color='red'>Coś poszło nie tak</font>");
            break;

        case Close_connection_OK:

            Serial_is_open = false;
            this->CommunicationWindow_addToLogs("Zamknięto port szeregowy");
            ui->label_ConnectionStatus->setText("<font color='orange'>Rozłączono</font>");
            break;

        case Close_connection_FAIL:

            this->CommunicationWindow_addToLogs("Port już jest otwarty !");
            break;

        case Port_is_busy:

            this->CommunicationWindow_addToLogs("Port już jest otwarty !");
            break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::Send_Data_to_robot_Slot()
{
    BT->Set_Send_Flag();
}

void CommunicationWindow::Parsed_frame_OK_Slot()
{
    emit Parsed_frame_OK_Signal(BT->Get_DF_Robot());
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CommunicationWindow::CommunicationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommunicationWindow)
{
    ui->setupUi(this);

    CommunicationWindow_set_default();

    // CONNECT:
    connect(BT, SIGNAL( Serial_Interface_Signal(Status_Codes) ), this, SLOT( Serial_Interface_Slot(Status_Codes) ));
    connect(BT, SIGNAL( Parsed_frame_OK_Signal() ), this, SLOT( Parsed_frame_OK_Slot() ));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CommunicationWindow::~CommunicationWindow()
{
    delete ui;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::Fill_Data_to_robot(Data_to_Robot Data)
{
    BT->Set_DT_Robot(Data);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Search_clicked()
{
    this->CommunicationWindow_addToLogs("Szukam urządzeń...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for(int i = 0; i < devices.count(); i++) {

        this->CommunicationWindow_addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
        ui->comboBox_Devices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::CommunicationWindow_addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textBrowser_Logs->append(currentDateTime + "\t" + message);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox messageBox(QMessageBox::Question,
                           tr("BBot"),
                           tr("Czy na pewno chcesz zakończyć ? \n"),
                           QMessageBox::Yes | QMessageBox::No);

    messageBox.setButtonText(QMessageBox::Yes, tr("Tak"));
    messageBox.setButtonText(QMessageBox::No,  tr("Nie"));

    if(messageBox.exec() != QMessageBox::Yes) {

        event->ignore();
    }
    else {

        exit(0);
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Connect_clicked()
{
    if(ui->comboBox_Devices->count() == 0) {

      this->CommunicationWindow_addToLogs("Nie wykryto żadnych urządzeń!");
      return;
    }

    PortName = ui->comboBox_Devices->currentText().split("\t").first();

    BT->Open_connection(PortName);
    BT->Start_communication_thread();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Disconnect_clicked()
{
    BT->Close_connection();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowser_Logs->clear();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::CommunicationWindow_set_default()
{
    Serial_is_open = false;

    on_comboBox_Baud_currentIndexChanged(2);
    on_comboBox_Bits_currentIndexChanged(3);
    on_comboBox_Parity_currentIndexChanged(0);
    on_comboBox_Stop_currentIndexChanged(0);
    on_comboBox_Control_currentIndexChanged(0);

    ui->comboBox_Baud->setCurrentIndex(2);
    ui->comboBox_Bits->setCurrentIndex(3);
    ui->comboBox_Parity->setCurrentIndex(0);
    ui->comboBox_Stop->setCurrentIndex(0);
    ui->comboBox_Control->setCurrentIndex(0);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_comboBox_Baud_currentIndexChanged(int index)
{
    switch(index) {

        case 0:
            baud = QSerialPort::Baud1200;
            break;

        case 1:
            baud = QSerialPort::Baud2400;
            break;

        case 2:
            baud = QSerialPort::Baud4800;
            break;

        case 3:
            baud = QSerialPort::Baud9600;
            break;

        case 4:
            baud = QSerialPort::Baud19200;
            break;

        case 5:
            baud = QSerialPort::Baud38400;
            break;

        case 6:
            baud = QSerialPort::Baud57600;
            break;

        case 7:
            baud = QSerialPort::Baud115200;
            break;

        case 8:
            baud = QSerialPort::UnknownBaud;
            break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_comboBox_Bits_currentIndexChanged(int index)
{
    switch(index) {

        case 0:
            bits = QSerialPort::Data5;
            break;

        case 1:
            bits = QSerialPort::Data6;
            break;

        case 2:
            bits = QSerialPort::Data7;
            break;

        case 3:
            bits = QSerialPort::Data8;
            break;

        case 4:
            bits = QSerialPort::UnknownDataBits;
            break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_comboBox_Parity_currentIndexChanged(int index)
{
    switch(index) {

        case 0:
            parity = QSerialPort::NoParity;
            break;

        case 1:
            parity = QSerialPort::EvenParity;
            break;

        case 2:
            parity = QSerialPort::OddParity;
            break;

        case 3:
            parity = QSerialPort::MarkParity;
            break;

        case 4:
            parity = QSerialPort::SpaceParity;
            break;

        case 5:
            parity = QSerialPort::UnknownParity;
            break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_comboBox_Stop_currentIndexChanged(int index)
{
    switch(index) {

        case 0:
            stop = QSerialPort::OneStop;
            break;

        case 1:
            stop = QSerialPort::TwoStop;
            break;

        case 2:
            stop = QSerialPort::StopBits::OneAndHalfStop;
            break;

        case 3:
            stop = QSerialPort::StopBits::UnknownStopBits;
            break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_comboBox_Control_currentIndexChanged(int index)
{
    switch(index) {

        case 0:
            control = QSerialPort::FlowControl::NoFlowControl;
            break;

        case 1:
            control = QSerialPort::FlowControl::HardwareControl;
            break;

        case 2:
            control = QSerialPort::FlowControl::SoftwareControl;
            break;

        case 3:
            control = QSerialPort::FlowControl::UnknownFlowControl;
            break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

QString CommunicationWindow::Get_PortName()
{
    return PortName;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Cancel_clicked()
{
    exit(0);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Continue_clicked()
{

    if( Serial_is_open == true ) {

        this->hide();
        emit Connection_OK_Signal();
    }
    else {

        QMessageBox messageBox(QMessageBox::Information,
                               tr("BBot"),
                               tr("Najpierw połącz się z urządzeniem"),
                               QMessageBox::Ok);

        messageBox.exec();
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
