#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QTimer>
#include <QThread>

#include "qcustomplot.h"
#include "bluetooth.h"

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

    QTimer dataTimer;

    Bluetooth *BT = new Bluetooth;

    void MainWindow_Resize_and_Center();

    void closeEvent(QCloseEvent *event) override;

    void MainWindow_Setup_QCustomPlot();

private slots:

signals:

};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MAINWINDOW_H
