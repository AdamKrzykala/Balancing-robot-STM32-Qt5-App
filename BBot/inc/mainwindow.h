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

    GLWidget *GW = new GLWidget;

    bool Show_Accelerometer_X, Show_Accelerometer_Y, Show_Accelerometer_Z;

    void MainWindow_Default_View();
    void MainWindow_Setup_Icons();

    void MainWindow_Setup_Accelerometer_Graph();
    void MainWindow_Setup_Gyroscope_Graph();
    void MainWindow_Setup_Magnetometer_Graph();
    void MainWindow_Setup_RPY_Graph();

    void closeEvent(QCloseEvent *event) override;

private slots:

    void on_checkBox_Accelerometer_X_clicked();

    void on_checkBox_Accelerometer_Y_clicked();

    void on_checkBox_Accelerometer_Z_clicked();

signals:

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MAINWINDOW_H
