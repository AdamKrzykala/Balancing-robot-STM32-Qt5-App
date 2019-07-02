#include "communicationwindow.h"
#include "ui_communicationwindow.h"

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CommunicationWindow::CommunicationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommunicationWindow)
{
    ui->setupUi(this);

    // CONNECT:
    connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CommunicationWindow::~CommunicationWindow()
{
    delete ui;
    delete device;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Search_clicked()
{
    this->addToLogs("Szukam urządzeń...");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for(int i = 0; i < devices.count(); i++) {

        this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
        ui->comboBox_Devices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textBrowser_Logs->append(currentDateTime + "\t" + message);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::sendMessageToDevice(QString message)
{
    if( this->device->isOpen() && this->device->isWritable() ) {

        this->addToLogs("Wysyłam informacje do urządzenia " + message);
        this->device->write(message.toStdString().c_str());
    }
    else {

        this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty!");
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Connect_clicked()
{
    if(ui->comboBox_Devices->count() == 0) {

      this->addToLogs("Nie wykryto żadnych urządzeń!");
      return;
    }

    QString portName = ui->comboBox_Devices->currentText().split("\t").first();
    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!device->isOpen()) {

        if( device->open(QSerialPort::ReadWrite) ) {

            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            this->addToLogs("Otwarto port szeregowy.");
        }
        else {

            this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    }
    else {

        this->addToLogs("Port już jest otwarty!");
        return;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Disconnect_clicked()
{
    if(this->device->isOpen()) {

        this->device->close();
        this->addToLogs("Zamknięto połączenie.");
    }
    else {

        this->addToLogs("Port nie jest otwarty!");
        return;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::readFromPort()
{
    while(this->device->canReadLine()) {

        QString line = this->device->readLine();
        //qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        //qDebug() << line.left(pos);

        this->addToLogs(line.left(pos));
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Send1_clicked()
{
    sendMessageToDevice("1");
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Send2_clicked()
{
    sendMessageToDevice("0");
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CommunicationWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowser_Logs->clear();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
