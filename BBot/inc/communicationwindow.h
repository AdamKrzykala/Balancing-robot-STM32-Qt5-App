#ifndef COMMUNICATIONWINDOW_H
#define COMMUNICATIONWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDateTime>

namespace Ui {
class CommunicationWindow;
}

class CommunicationWindow : public QDialog
{
    Q_OBJECT

public:

    explicit CommunicationWindow(QWidget *parent = nullptr);
    ~CommunicationWindow();

private slots:

    void on_pushButton_Search_clicked();
    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();

    void readFromPort();

    void on_pushButton_Send1_clicked();

    void on_pushButton_Send2_clicked();

    void on_pushButton_Clear_clicked();

private:

    Ui::CommunicationWindow *ui;

    QSerialPort *device = new QSerialPort;

    void addToLogs(QString message);

    void sendMessageToDevice(QString message);
};

#endif // COMMUNICATIONWINDOW_H
