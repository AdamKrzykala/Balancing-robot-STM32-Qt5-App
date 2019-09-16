#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QPixmap>
#include <QKeyEvent>
#include <QSettings>

#include "qcustomplot.h"
#include "bluetooth.h"
#include "glwidget.h"
#include "communicationwindow.h"

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

    void MainWindow_realtimeDataSlot(Data_from_Robot data);
    void Connection_OK_Slot();

private:

    Ui::MainWindow *ui;

    GLWidget            *GW = new GLWidget;
    CommunicationWindow *CW = new CommunicationWindow;

    QString m_sSettingsFile;

    Data_to_Robot Data_to;
    Data_from_Robot Data_from;

    bool Show_Accelerometer_X, Show_Accelerometer_Y, Show_Accelerometer_Z;
    bool Show_Accelerometer_Roll, Show_Accelerometer_Pitch, Show_Accelerometer_Yaw;

    bool Show_Gyroscope_X, Show_Gyroscope_Y, Show_Gyroscope_Z;
    bool Show_Gyroscope_Roll, Show_Gyroscope_Pitch, Show_Gyroscope_Yaw;

    bool Show_Magnetometer_X, Show_Magnetometer_Y, Show_Magnetometer_Z;
    bool Show_Magnetometer_Roll, Show_Magnetometer_Pitch, Show_Magnetometer_Yaw;

    bool Show_Complementary_Filter_Roll, Show_Complementary_Filter_Pitch, Show_Complementary_Filter_Yaw;
    bool Show_Kalman_Filter_Roll, Show_Kalman_Filter_Pitch, Show_Kalman_Filter_Yaw;

    bool Complementary_Filter_Graph_Run;
    bool Kalman_Filter_Graph_Run;

    void loadSettings();
    void saveSettings();

    void MainWindow_Default_View();
    void MainWindow_Setup_Icons();

    void MainWindow_Setup_Complementary_Filter_Graph();
    void MainWindow_Setup_Kalman_Filter_Graph();

    void MainWindow_Display_IMU_data();
    void MainWindow_Display_Battery_data(double voltage);
    void MainWindow_Display_Engines_data();

    void closeEvent(QCloseEvent *event) override;

    QList<int> Splitter_Position;

private slots:

    void on_checkBox_Complementary_Filter_Roll_clicked();
    void on_checkBox_Complementary_Filter_Pitch_clicked();
    void on_checkBox_Complementary_Filter_Yaw_clicked();

    void on_pushButton_ConnectDisconnect_clicked();

    void on_pushButton_PID_Default_clicked();
    void on_pushButton_PID_Clear_clicked();

    void on_doubleSpinBox_PID_Kp_valueChanged(double arg1);
    void on_doubleSpinBox_PID_Kd_valueChanged(double arg1);
    void on_doubleSpinBox_PID_Ki_valueChanged(double arg1);

    void on_pushButton_EmergencyStop_clicked();

    void on_doubleSpinBox_Speed_PID_Kp_valueChanged(double arg1);
    void on_doubleSpinBox_Speed_PID_Ki_valueChanged(double arg1);
    void on_doubleSpinBox_Speed_PID_Kd_valueChanged(double arg1);

    void on_pushButton_Send_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Forward_pressed();
    void on_pushButton_Forward_released();

    void on_pushButton_Left_pressed();
    void on_pushButton_Left_released();

    void on_pushButton_Right_pressed();
    void on_pushButton_Right_released();

    void on_pushButton_Backward_pressed();
    void on_pushButton_Backward_released();

    void on_doubleSpinBox_Complementary_filter_weight_valueChanged(double arg1);

    void on_pushButton_Speed_PID_Default_clicked();
    void on_pushButton_Speed_PID_Clear_clicked();

    void on_checkBox_Kalman_Filter_Roll_clicked();
    void on_checkBox_Kalman_Filter_Pitch_clicked();
    void on_checkBox_Kalman_Filter_Yaw_clicked();

    void on_pushButton_Plots_Center_clicked();
    void on_pushButton_Plots_Start_Stop_clicked();

    void on_pushButton_Reset_Plots_Range_clicked();

    void on_radioButton_Complementary_filter_toggled(bool checked);

    void on_radioButton_Kalman_filter_toggled(bool checked);

    void on_doubleSpinBox_Kalman_filter_variance_valueChanged(double arg1);

    void on_radioButton_Madgwick_filter_toggled(bool checked);

signals:

    void Disconnect_Signal();
    void Send_data_Signal();
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MAINWINDOW_H
