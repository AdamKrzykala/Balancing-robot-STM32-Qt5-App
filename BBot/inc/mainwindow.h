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
    GLWidget  *GW = new GLWidget;

    void MainWindow_Default_View();
    void MainWindow_Setup_Icons();

    bool Show_Accelerometer_X, Show_Accelerometer_Y, Show_Accelerometer_Z;
    bool Show_Accelerometer_Roll, Show_Accelerometer_Pitch, Show_Accelerometer_Yaw;

    bool Show_Gyroscope_X, Show_Gyroscope_Y, Show_Gyroscope_Z;
    bool Show_Gyroscope_Roll, Show_Gyroscope_Pitch, Show_Gyroscope_Yaw;

    bool Show_Magnetometer_X, Show_Magnetometer_Y, Show_Magnetometer_Z;
    bool Show_Magnetometer_Roll, Show_Magnetometer_Pitch, Show_Magnetometer_Yaw;

    bool Show_Complementary_Filter_Roll, Show_Complementary_Filter_Pitch, Show_Complementary_Filter_Yaw;

    void MainWindow_Setup_Accelerometer_Graph();
    void MainWindow_Setup_Accelerometer_RPY_Graph();

    void MainWindow_Setup_Gyroscope_Graph();
    void MainWindow_Setup_Gyroscope_RPY_Graph();

    void MainWindow_Setup_Magnetometer_Graph();
    void MainWindow_Setup_Magnetometer_RPY_Graph();

    void MainWindow_Setup_Complementary_Filter_Graph();

    void MainWindow_Display_IMU_data();
    void MainWindow_Display_Battery_data(int voltage);

    void closeEvent(QCloseEvent *event) override;

private slots:

    void on_checkBox_Accelerometer_X_clicked();
    void on_checkBox_Accelerometer_Y_clicked();
    void on_checkBox_Accelerometer_Z_clicked();

    void on_checkBox_Accelerometer_Roll_clicked();
    void on_checkBox_Accelerometer_Pitch_clicked();
    void on_checkBox_Accelerometer_Yaw_clicked();

    void on_checkBox_Gyroscope_X_clicked();
    void on_checkBox_Gyroscope_Y_clicked();
    void on_checkBox_Gyroscope_Z_clicked();

    void on_checkBox_Gyroscope_Roll_clicked();
    void on_checkBox_Gyroscope_Pitch_clicked();
    void on_checkBox_Gyroscope_Yaw_clicked();

    void on_checkBox_Magnetometer_X_clicked();
    void on_checkBox_Magnetometer_Y_clicked();
    void on_checkBox_Magnetometer_Z_clicked();

    void on_checkBox_Magnetometer_Roll_clicked();
    void on_checkBox_Magnetometer_Pitch_clicked();
    void on_checkBox_Magnetometer_Yaw_clicked();

    void on_checkBox_Complementary_Filter_Roll_clicked();
    void on_checkBox_Complementary_Filter_Pitch_clicked();
    void on_checkBox_Complementary_Filter_Yaw_clicked();

signals:

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MAINWINDOW_H
