#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPixmap>

#include "qcustomplot.h"
#include "bluetooth.h"
#include "glwidget.h"

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace Ui {
class MainWindow;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:

    void MainWindow_realtimeDataSlot();

private:

    Ui::MainWindow *ui;

    Bluetooth *BT = new Bluetooth;

    //GLWidget *GW = new GLWidget;

    void MainWindow_Default_View();
    void MainWindow_Setup_Icons();

    bool Show_Accelerometer_X, Show_Accelerometer_Y, Show_Accelerometer_Z;
    bool Show_Accelerometer_Roll, Show_Accelerometer_Pitch, Show_Accelerometer_Yaw;

    void MainWindow_Setup_Accelerometer_Graph();
    void MainWindow_Setup_Accelerometer_RPY_Graph();

    void MainWindow_Setup_Gyroscope_Graph();
    void MainWindow_Setup_Magnetometer_Graph();
    void MainWindow_Setup_RPY_Graph();

    void MainWindow_Display_Battery_data(int voltage);

    void closeEvent(QCloseEvent *event) override;

private slots:

    void on_checkBox_Accelerometer_X_clicked();
    void on_checkBox_Accelerometer_Y_clicked();
    void on_checkBox_Accelerometer_Z_clicked();

    void on_checkBox_Accelerometer_Roll_clicked();

    void on_checkBox_Accelerometer_Pitch_clicked();

    void on_checkBox_Accelerometer_Yaw_clicked();

signals:

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MAINWINDOW_H
