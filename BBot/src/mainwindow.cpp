#include "mainwindow.h"
#include "ui_mainwindow.h"

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Default variables values
    Show_Accelerometer_X = true; Show_Accelerometer_Y = true; Show_Accelerometer_Z = true;
    Show_Accelerometer_Roll = true; Show_Accelerometer_Pitch = true; Show_Accelerometer_Yaw = true;

    // Setup MainWindow
    this->showMaximized();

    MainWindow_Default_View();
    MainWindow_Setup_Icons();

    // Setup real time graphs
    MainWindow_Setup_Accelerometer_Graph();
    MainWindow_Setup_Accelerometer_RPY_Graph();

    MainWindow_Setup_Gyroscope_Graph();
    MainWindow_Setup_Magnetometer_Graph();
    MainWindow_Setup_RPY_Graph();

    // Setup Slots and Signals
    connect(BT, SIGNAL( Parsed_Frame_OK() ), this, SLOT( MainWindow_realtimeDataSlot() ));

    // Run communication thread
    BT->Start_communication_thread();



    //QHBoxLayout *container = new QHBoxLayout;
    //container->addWidget(GW);
    //ui->widget_3D->setLayout(container);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::closeEvent(QCloseEvent *event)
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

        event->accept();
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Accelerometer_Graph()
{
    ui->Accelerometer_Graph->addGraph(); // red line
    ui->Accelerometer_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Accelerometer_Graph->addGraph(); // green line
    ui->Accelerometer_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Accelerometer_Graph->addGraph(); // blue line
    ui->Accelerometer_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Accelerometer_Graph->xAxis->setTicker(timeTicker);
    ui->Accelerometer_Graph->axisRect()->setupFullAxesBox();
    ui->Accelerometer_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Accelerometer_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Accelerometer_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Accelerometer_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Accelerometer_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Accelerometer_RPY_Graph()
{
    ui->Accelerometer_RPY_Graph->addGraph(); // red line
    ui->Accelerometer_RPY_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Accelerometer_RPY_Graph->addGraph(); // green line
    ui->Accelerometer_RPY_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Accelerometer_RPY_Graph->addGraph(); // blue line
    ui->Accelerometer_RPY_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Accelerometer_RPY_Graph->xAxis->setTicker(timeTicker);
    ui->Accelerometer_RPY_Graph->axisRect()->setupFullAxesBox();
    ui->Accelerometer_RPY_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Accelerometer_RPY_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Accelerometer_RPY_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Accelerometer_RPY_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Accelerometer_RPY_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Gyroscope_Graph()
{
    ui->Gyroscope_Graph->addGraph(); // red line
    ui->Gyroscope_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Gyroscope_Graph->addGraph(); // green line
    ui->Gyroscope_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Gyroscope_Graph->addGraph(); // blue line
    ui->Gyroscope_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Gyroscope_Graph->xAxis->setTicker(timeTicker);
    ui->Gyroscope_Graph->axisRect()->setupFullAxesBox();
    ui->Gyroscope_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Gyroscope_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Gyroscope_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Gyroscope_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Gyroscope_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Magnetometer_Graph()
{
    ui->Magnetometer_Graph->addGraph(); // red line
    ui->Magnetometer_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Magnetometer_Graph->addGraph(); // green line
    ui->Magnetometer_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Magnetometer_Graph->addGraph(); // blue line
    ui->Magnetometer_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Magnetometer_Graph->xAxis->setTicker(timeTicker);
    ui->Magnetometer_Graph->axisRect()->setupFullAxesBox();
    ui->Magnetometer_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Magnetometer_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Magnetometer_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Magnetometer_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Magnetometer_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_RPY_Graph()
{
    ui->RPY_Graph->addGraph(); // red line
    ui->RPY_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->RPY_Graph->addGraph(); // green line
    ui->RPY_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->RPY_Graph->addGraph(); // blue line
    ui->RPY_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->RPY_Graph->xAxis->setTicker(timeTicker);
    ui->RPY_Graph->axisRect()->setupFullAxesBox();
    ui->RPY_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->RPY_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->RPY_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->RPY_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->RPY_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Display_Battery_data(int voltage)
{

    QPixmap Battery_null(":/new/prefix1/png/Battery_null.png");
    QPixmap Battery_low(":/new/prefix1/png/Battery_low.png");
    QPixmap Battery_medium(":/new/prefix1/png/Battery_medium.png");
    QPixmap Battery_full(":/new/prefix1/png/Battery_full.png");

    int w = ui->label_Battery->width();
    int h = ui->label_Battery->height();

    double max_value = 1260;
    double min_value = 1050;
    double ratio = max_value - min_value;

    int battery_level = static_cast<int>( ( (voltage - min_value) / ratio ) * 100 );

    if(battery_level >= 0 && battery_level <= 20) {

        ui->label_Battery->setPixmap( Battery_low.scaled(w, h, Qt::KeepAspectRatio) );
    }
    else if(battery_level > 20 && battery_level <= 70 ) {

        ui->label_Battery->setPixmap( Battery_medium.scaled(w, h, Qt::KeepAspectRatio) );
    }
    else if(battery_level > 70) {

        ui->label_Battery->setPixmap( Battery_full.scaled(w, h, Qt::KeepAspectRatio) );
    }

    if(battery_level >= 0) {

        ui->label_Voltage->setNum(battery_level);
    }
    else if(battery_level > 100) {

        ui->label_Voltage->setNum(100);
    }
    else {

        ui->label_Voltage->setNum(0);
    }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::MainWindow_realtimeDataSlot()
{        
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    // Accelerometer data
    double Accelerometer_X = qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843);
    double Accelerometer_Y = qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364);
    double Accelerometer_Z = qCos(key)+qrand()/(double)RAND_MAX*0.8*qSin(key/0.4364);

    double Accelerometer_Roll  = qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843);
    double Accelerometer_Pitch = qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364);
    double Accelerometer_Yaw   = qCos(key)+qrand()/(double)RAND_MAX*0.8*qSin(key/0.4364);

    // Gyroscope data
    double Gyroscope_X = qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843);
    double Gyroscope_Y = qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364);
    double Gyroscope_Z = qCos(key)+qrand()/(double)RAND_MAX*0.8*qSin(key/0.4364);

    // Magnetometer data
    double Magnetometer_X = qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843);
    double Magnetometer_Y = qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364);
    double Magnetometer_Z = qCos(key)+qrand()/(double)RAND_MAX*0.8*qSin(key/0.4364);

    // Fusion data
    double Roll = qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843);
    double Pitch = qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364);
    double Yaw = qCos(key)+qrand()/(double)RAND_MAX*0.8*qSin(key/0.4364);

    // Battery data
    int Battery_voltage = 1260;

    MainWindow_Display_Battery_data(Battery_voltage);

    ui->lcdNumber_Accelerometer_X->display(Accelerometer_X);
    ui->lcdNumber_Accelerometer_Y->display(Accelerometer_Y);
    ui->lcdNumber_Accelerometer_Z->display(Accelerometer_Z);

    ui->lcdNumber_Accelerometer_Roll->display(Accelerometer_Roll);
    ui->lcdNumber_Accelerometer_Pitch->display(Accelerometer_Pitch);
    ui->lcdNumber_Accelerometer_Yaw->display(Accelerometer_Yaw);

    ui->lcdNumber_Gyroscope_X->display(Gyroscope_X);
    ui->lcdNumber_Gyroscope_Y->display(Gyroscope_Y);
    ui->lcdNumber_Gyroscope_Z->display(Gyroscope_Z);

    ui->lcdNumber_Magnetometer_X->display(Magnetometer_X);
    ui->lcdNumber_Magnetometer_Y->display(Magnetometer_Y);
    ui->lcdNumber_Magnetometer_Z->display(Magnetometer_Z);

    ui->lcdNumber_Roll->display(Roll);
    ui->lcdNumber_Pitch->display(Pitch);
    ui->lcdNumber_Yaw->display(Yaw);

    // add data to lines:
    if(Show_Accelerometer_X == true) ui->Accelerometer_Graph->graph(0)->addData(key, Accelerometer_X);
    if(Show_Accelerometer_Y == true) ui->Accelerometer_Graph->graph(1)->addData(key, Accelerometer_Y);
    if(Show_Accelerometer_Z == true) ui->Accelerometer_Graph->graph(2)->addData(key, Accelerometer_Z);

    if(Show_Accelerometer_Roll  == true) ui->Accelerometer_RPY_Graph->graph(0)->addData(key, Accelerometer_Roll);
    if(Show_Accelerometer_Pitch == true) ui->Accelerometer_RPY_Graph->graph(1)->addData(key, Accelerometer_Pitch);
    if(Show_Accelerometer_Yaw   == true) ui->Accelerometer_RPY_Graph->graph(2)->addData(key, Accelerometer_Yaw);

    ui->Gyroscope_Graph->graph(0)->addData(key, Gyroscope_X);
    ui->Gyroscope_Graph->graph(1)->addData(key, Gyroscope_Y);
    ui->Gyroscope_Graph->graph(2)->addData(key, Gyroscope_Z);

    ui->Magnetometer_Graph->graph(0)->addData(key, Magnetometer_X);
    ui->Magnetometer_Graph->graph(1)->addData(key, Magnetometer_Y);
    ui->Magnetometer_Graph->graph(2)->addData(key, Magnetometer_Z);

    ui->RPY_Graph->graph(0)->addData(key, Roll);
    ui->RPY_Graph->graph(1)->addData(key, Pitch);
    ui->RPY_Graph->graph(2)->addData(key, Yaw);

    // rescale value (vertical) axis to fit the current data:
    ui->Accelerometer_Graph->graph(0)->rescaleValueAxis();
    ui->Accelerometer_Graph->graph(1)->rescaleValueAxis(true);

    ui->Accelerometer_RPY_Graph->graph(0)->rescaleValueAxis();
    ui->Accelerometer_RPY_Graph->graph(1)->rescaleValueAxis(true);

    ui->Gyroscope_Graph->graph(0)->rescaleValueAxis();
    ui->Gyroscope_Graph->graph(1)->rescaleValueAxis(true);

    ui->Magnetometer_Graph->graph(0)->rescaleValueAxis();
    ui->Magnetometer_Graph->graph(1)->rescaleValueAxis(true);

    ui->RPY_Graph->graph(0)->rescaleValueAxis();
    ui->RPY_Graph->graph(1)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Accelerometer_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Accelerometer_Graph->replot();

    ui->Accelerometer_RPY_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Accelerometer_RPY_Graph->replot();

    ui->Gyroscope_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Gyroscope_Graph->replot();

    ui->Magnetometer_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Magnetometer_Graph->replot();

    ui->RPY_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->RPY_Graph->replot();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Default_View()
{
   if(Show_Accelerometer_X == true) ui->checkBox_Accelerometer_X->setChecked(true);
   if(Show_Accelerometer_Y == true) ui->checkBox_Accelerometer_Y->setChecked(true);
   if(Show_Accelerometer_Z == true) ui->checkBox_Accelerometer_Z->setChecked(true);

   if(Show_Accelerometer_Roll  == true) ui->checkBox_Accelerometer_Roll->setChecked(true);
   if(Show_Accelerometer_Pitch == true) ui->checkBox_Accelerometer_Pitch->setChecked(true);
   if(Show_Accelerometer_Yaw   == true) ui->checkBox_Accelerometer_Yaw->setChecked(true);

   ui->label_Voltage->setNum(0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Icons()
{
    int w = 0;
    int h = 0;

    QPixmap Red_dot(":/new/prefix1/png/Red_dot.png");
    QPixmap Green_dot(":/new/prefix1/png/Green_dot.png");
    QPixmap Blue_dot(":/new/prefix1/png/Blue_dot.png");

    QPixmap Battery_null(":/new/prefix1/png/Battery_null.png");

    w = ui->label_Battery->width();
    h = ui->label_Battery->height();
    ui->label_Battery->setPixmap( Battery_null.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Accelerometer_X->width();
    h = ui->label_Accelerometer_X->height();
    ui->label_Accelerometer_X->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Accelerometer_Y->width();
    h = ui->label_Accelerometer_Y->height();
    ui->label_Accelerometer_Y->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Accelerometer_Z->width();
    h = ui->label_Accelerometer_Z->height();
    ui->label_Accelerometer_Z->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Accelerometer_Roll->width();
    h = ui->label_Accelerometer_Roll->height();
    ui->label_Accelerometer_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Accelerometer_Pitch->width();
    h = ui->label_Accelerometer_Pitch->height();
    ui->label_Accelerometer_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Accelerometer_Yaw->width();
    h = ui->label_Accelerometer_Yaw->height();
    ui->label_Accelerometer_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Accelerometer_X_clicked()
{
    if( ui->checkBox_Accelerometer_X->isChecked() ) {

        Show_Accelerometer_X = true;
    }
    else {

        Show_Accelerometer_X = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Accelerometer_Y_clicked()
{
    if( ui->checkBox_Accelerometer_Y->isChecked() ) {

        Show_Accelerometer_Y = true;
    }
    else {

        Show_Accelerometer_Y = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Accelerometer_Z_clicked()
{
    if( ui->checkBox_Accelerometer_Z->isChecked() ) {

        Show_Accelerometer_Z = true;
    }
    else {

        Show_Accelerometer_Z = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Accelerometer_Roll_clicked()
{
    if( ui->checkBox_Accelerometer_Roll->isChecked() ) {

        Show_Accelerometer_Roll = true;
    }
    else {

        Show_Accelerometer_Roll = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Accelerometer_Pitch_clicked()
{
    if( ui->checkBox_Accelerometer_Pitch->isChecked() ) {

        Show_Accelerometer_Pitch = true;
    }
    else {

        Show_Accelerometer_Pitch = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Accelerometer_Yaw_clicked()
{
    if( ui->checkBox_Accelerometer_Yaw->isChecked() ) {

        Show_Accelerometer_Yaw = true;
    }
    else {

        Show_Accelerometer_Yaw = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
