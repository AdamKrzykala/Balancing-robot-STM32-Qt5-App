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

    Show_Gyroscope_X = true; Show_Gyroscope_Y = true; Show_Gyroscope_Z = true;
    Show_Gyroscope_Roll = true; Show_Gyroscope_Pitch = true; Show_Gyroscope_Yaw = true;

    Show_Magnetometer_X = true; Show_Magnetometer_Y = true; Show_Magnetometer_Z = true;
    Show_Magnetometer_Roll = true; Show_Magnetometer_Pitch = true; Show_Magnetometer_Yaw = true;

    Show_Complementary_Filter_Roll = true; Show_Complementary_Filter_Pitch = true; Show_Complementary_Filter_Yaw = true;

    // Setup MainWindow
    this->showMaximized();

    MainWindow_Default_View();
    MainWindow_Setup_Icons();

    // Setup real time graphs
    MainWindow_Setup_Accelerometer_Graph();
    MainWindow_Setup_Accelerometer_RPY_Graph();

    MainWindow_Setup_Gyroscope_Graph();
    MainWindow_Setup_Gyroscope_RPY_Graph();

    MainWindow_Setup_Magnetometer_Graph();
    MainWindow_Setup_Magnetometer_RPY_Graph();

    MainWindow_Setup_Complementary_Filter_Graph();

    // Setup Slots and Signals
    connect(BT, SIGNAL( Parsed_Frame_OK() ), this, SLOT( MainWindow_realtimeDataSlot() ));

    // Run communication thread
    BT->Start_communication_thread();

    // Setup OpenGL visualisation
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    QWidget *w = new QWidget;

    container->addWidget(GW);
    w->setLayout(container);
    mainLayout->addWidget(w);

    // Setup CommunicationWindow
    CW->exec();
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

void MainWindow::MainWindow_Setup_Gyroscope_RPY_Graph()
{
    ui->Gyroscope_RPY_Graph->addGraph(); // red line
    ui->Gyroscope_RPY_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Gyroscope_RPY_Graph->addGraph(); // green line
    ui->Gyroscope_RPY_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Gyroscope_RPY_Graph->addGraph(); // blue line
    ui->Gyroscope_RPY_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Gyroscope_RPY_Graph->xAxis->setTicker(timeTicker);
    ui->Gyroscope_RPY_Graph->axisRect()->setupFullAxesBox();
    ui->Gyroscope_RPY_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Gyroscope_RPY_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Gyroscope_RPY_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Gyroscope_RPY_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Gyroscope_RPY_Graph->yAxis2, SLOT(setRange(QCPRange)));
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

void MainWindow::MainWindow_Setup_Magnetometer_RPY_Graph()
{
    ui->Magnetometer_RPY_Graph->addGraph(); // red line
    ui->Magnetometer_RPY_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Magnetometer_RPY_Graph->addGraph(); // green line
    ui->Magnetometer_RPY_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Magnetometer_RPY_Graph->addGraph(); // blue line
    ui->Magnetometer_RPY_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Magnetometer_RPY_Graph->xAxis->setTicker(timeTicker);
    ui->Magnetometer_RPY_Graph->axisRect()->setupFullAxesBox();
    ui->Magnetometer_RPY_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Magnetometer_RPY_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Magnetometer_RPY_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Magnetometer_RPY_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Magnetometer_RPY_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Complementary_Filter_Graph()
{
    ui->Complementary_Filter_Graph->addGraph(); // red line
    ui->Complementary_Filter_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Complementary_Filter_Graph->addGraph(); // green line
    ui->Complementary_Filter_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Complementary_Filter_Graph->addGraph(); // blue line
    ui->Complementary_Filter_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Complementary_Filter_Graph->xAxis->setTicker(timeTicker);
    ui->Complementary_Filter_Graph->axisRect()->setupFullAxesBox();
    ui->Complementary_Filter_Graph->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Complementary_Filter_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Complementary_Filter_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Complementary_Filter_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Complementary_Filter_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Display_IMU_data()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    // Accelerometer data
    double Accelerometer_X = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*1*qSin(key/0.3843);
    double Accelerometer_Y = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.5*qSin(key/0.4364);
    double Accelerometer_Z = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.8*qSin(key/0.4364);

    double Accelerometer_Roll  = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*1*qSin(key/0.3843);
    double Accelerometer_Pitch = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.5*qSin(key/0.4364);
    double Accelerometer_Yaw   = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.8*qSin(key/0.4364);

    // Gyroscope data
    double Gyroscope_X = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*1*qSin(key/0.3843);
    double Gyroscope_Y = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.5*qSin(key/0.4364);
    double Gyroscope_Z = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.8*qSin(key/0.4364);

    double Gyroscope_Roll  = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*1*qSin(key/0.3843);
    double Gyroscope_Pitch = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.5*qSin(key/0.4364);
    double Gyroscope_Yaw   = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.8*qSin(key/0.4364);

    // Magnetometer data
    double Magnetometer_X = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*1*qSin(key/0.3843);
    double Magnetometer_Y = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.5*qSin(key/0.4364);
    double Magnetometer_Z = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.8*qSin(key/0.4364);

    double Magnetometer_Roll  = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*1*qSin(key/0.3843);
    double Magnetometer_Pitch = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.5*qSin(key/0.4364);
    double Magnetometer_Yaw   = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*0.8*qSin(key/0.4364);

    // Fusion data
    double Complementary_Filter_Roll  = qSin(key)+qrand()/static_cast<double>(RAND_MAX)*10*qSin(key/0.3843);
    double Complementary_Filter_Pitch = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*2*qSin(key/0.4364);
    double Complementary_Filter_Yaw   = qCos(key)+qrand()/static_cast<double>(RAND_MAX)*4*qSin(key/0.4364);

    ui->lcdNumber_Accelerometer_X->display(Accelerometer_X);
    ui->lcdNumber_Accelerometer_Y->display(Accelerometer_Y);
    ui->lcdNumber_Accelerometer_Z->display(Accelerometer_Z);

    ui->lcdNumber_Accelerometer_Roll->display(Accelerometer_Roll);
    ui->lcdNumber_Accelerometer_Pitch->display(Accelerometer_Pitch);
    ui->lcdNumber_Accelerometer_Yaw->display(Accelerometer_Yaw);

    ui->lcdNumber_Gyroscope_X->display(Gyroscope_X);
    ui->lcdNumber_Gyroscope_Y->display(Gyroscope_Y);
    ui->lcdNumber_Gyroscope_Z->display(Gyroscope_Z);

    ui->lcdNumber_Gyroscope_Roll->display(Gyroscope_Roll);
    ui->lcdNumber_Gyroscope_Pitch->display(Gyroscope_Pitch);
    ui->lcdNumber_Gyroscope_Yaw->display(Gyroscope_Yaw);

    ui->lcdNumber_Magnetometer_X->display(Magnetometer_X);
    ui->lcdNumber_Magnetometer_Y->display(Magnetometer_Y);
    ui->lcdNumber_Magnetometer_Z->display(Magnetometer_Z);

    ui->lcdNumber_Magnetometer_Roll->display(Magnetometer_Roll);
    ui->lcdNumber_Magnetometer_Pitch->display(Magnetometer_Pitch);
    ui->lcdNumber_Magnetometer_Yaw->display(Magnetometer_Yaw);

    ui->lcdNumber_Complementary_Filter_Roll->display(Complementary_Filter_Roll);
    ui->lcdNumber_Complementary_Filter_Pitch->display(Complementary_Filter_Pitch);
    ui->lcdNumber_Complementary_Filter_Yaw->display(Complementary_Filter_Yaw);

    // add data to lines:
    if(Show_Accelerometer_X == true) ui->Accelerometer_Graph->graph(0)->addData(key, Accelerometer_X);
    if(Show_Accelerometer_Y == true) ui->Accelerometer_Graph->graph(1)->addData(key, Accelerometer_Y);
    if(Show_Accelerometer_Z == true) ui->Accelerometer_Graph->graph(2)->addData(key, Accelerometer_Z);

    if(Show_Accelerometer_Roll  == true) ui->Accelerometer_RPY_Graph->graph(0)->addData(key, Accelerometer_Roll);
    if(Show_Accelerometer_Pitch == true) ui->Accelerometer_RPY_Graph->graph(1)->addData(key, Accelerometer_Pitch);
    if(Show_Accelerometer_Yaw   == true) ui->Accelerometer_RPY_Graph->graph(2)->addData(key, Accelerometer_Yaw);

    if(Show_Gyroscope_X == true) ui->Gyroscope_Graph->graph(0)->addData(key, Gyroscope_X);
    if(Show_Gyroscope_Y == true) ui->Gyroscope_Graph->graph(1)->addData(key, Gyroscope_Y);
    if(Show_Gyroscope_Z == true) ui->Gyroscope_Graph->graph(2)->addData(key, Gyroscope_Z);

    if(Show_Gyroscope_Roll  == true) ui->Gyroscope_RPY_Graph->graph(0)->addData(key, Gyroscope_Roll);
    if(Show_Gyroscope_Pitch == true) ui->Gyroscope_RPY_Graph->graph(1)->addData(key, Gyroscope_Pitch);
    if(Show_Gyroscope_Yaw   == true) ui->Gyroscope_RPY_Graph->graph(2)->addData(key, Gyroscope_Yaw);

    if(Show_Magnetometer_X == true) ui->Magnetometer_Graph->graph(0)->addData(key, Magnetometer_X);
    if(Show_Magnetometer_Y == true) ui->Magnetometer_Graph->graph(1)->addData(key, Magnetometer_Y);
    if(Show_Magnetometer_Z == true) ui->Magnetometer_Graph->graph(2)->addData(key, Magnetometer_Z);

    if(Show_Magnetometer_Roll  == true) ui->Magnetometer_RPY_Graph->graph(0)->addData(key, Magnetometer_Roll);
    if(Show_Magnetometer_Pitch == true) ui->Magnetometer_RPY_Graph->graph(1)->addData(key, Magnetometer_Pitch);
    if(Show_Magnetometer_Yaw   == true) ui->Magnetometer_RPY_Graph->graph(2)->addData(key, Magnetometer_Yaw);

    if(Show_Complementary_Filter_Roll  == true) ui->Complementary_Filter_Graph->graph(0)->addData(key, Complementary_Filter_Roll);
    if(Show_Complementary_Filter_Pitch == true) ui->Complementary_Filter_Graph->graph(1)->addData(key, Complementary_Filter_Pitch);
    if(Show_Complementary_Filter_Yaw   == true) ui->Complementary_Filter_Graph->graph(2)->addData(key, Complementary_Filter_Yaw);

    // rescale value (vertical) axis to fit the current data:
    ui->Accelerometer_Graph->graph(0)->rescaleValueAxis();
    ui->Accelerometer_Graph->graph(1)->rescaleValueAxis(true);

    ui->Accelerometer_RPY_Graph->graph(0)->rescaleValueAxis();
    ui->Accelerometer_RPY_Graph->graph(1)->rescaleValueAxis(true);

    ui->Gyroscope_Graph->graph(0)->rescaleValueAxis();
    ui->Gyroscope_Graph->graph(1)->rescaleValueAxis(true);

    ui->Gyroscope_RPY_Graph->graph(0)->rescaleValueAxis();
    ui->Gyroscope_RPY_Graph->graph(1)->rescaleValueAxis(true);

    ui->Magnetometer_Graph->graph(0)->rescaleValueAxis();
    ui->Magnetometer_Graph->graph(1)->rescaleValueAxis(true);

    ui->Magnetometer_RPY_Graph->graph(0)->rescaleValueAxis();
    ui->Magnetometer_RPY_Graph->graph(1)->rescaleValueAxis(true);

    ui->Complementary_Filter_Graph->graph(0)->rescaleValueAxis();
    ui->Complementary_Filter_Graph->graph(1)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Accelerometer_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Accelerometer_Graph->replot();

    ui->Accelerometer_RPY_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Accelerometer_RPY_Graph->replot();

    ui->Gyroscope_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Gyroscope_Graph->replot();

    ui->Gyroscope_RPY_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Gyroscope_RPY_Graph->replot();

    ui->Magnetometer_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Magnetometer_Graph->replot();

    ui->Magnetometer_RPY_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Magnetometer_RPY_Graph->replot();

    ui->Complementary_Filter_Graph->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->Complementary_Filter_Graph->replot();

    // OpenGL visualisation
    ui->widget_RPY_Visualisation->setXRotation(Complementary_Filter_Roll);
    ui->widget_RPY_Visualisation->setYRotation(Complementary_Filter_Pitch);
    ui->widget_RPY_Visualisation->setZRotation(Complementary_Filter_Yaw);
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
    // Battery data
    int Battery_voltage = 1260;

    MainWindow_Display_Battery_data(Battery_voltage);
    MainWindow_Display_IMU_data();
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

   if(Show_Gyroscope_X == true) ui->checkBox_Gyroscope_X->setChecked(true);
   if(Show_Gyroscope_Y == true) ui->checkBox_Gyroscope_Y->setChecked(true);
   if(Show_Gyroscope_Z == true) ui->checkBox_Gyroscope_Z->setChecked(true);

   if(Show_Gyroscope_Roll  == true) ui->checkBox_Gyroscope_Roll->setChecked(true);
   if(Show_Gyroscope_Pitch == true) ui->checkBox_Gyroscope_Pitch->setChecked(true);
   if(Show_Gyroscope_Yaw   == true) ui->checkBox_Gyroscope_Yaw->setChecked(true);

   if(Show_Magnetometer_X == true) ui->checkBox_Magnetometer_X->setChecked(true);
   if(Show_Magnetometer_Y == true) ui->checkBox_Magnetometer_Y->setChecked(true);
   if(Show_Magnetometer_Z == true) ui->checkBox_Magnetometer_Z->setChecked(true);

   if(Show_Magnetometer_Roll  == true) ui->checkBox_Magnetometer_Roll->setChecked(true);
   if(Show_Magnetometer_Pitch == true) ui->checkBox_Magnetometer_Pitch->setChecked(true);
   if(Show_Magnetometer_Yaw   == true) ui->checkBox_Magnetometer_Yaw->setChecked(true);

   if(Show_Complementary_Filter_Roll  == true) ui->checkBox_Complementary_Filter_Roll->setChecked(true);
   if(Show_Complementary_Filter_Pitch == true) ui->checkBox_Complementary_Filter_Pitch->setChecked(true);
   if(Show_Complementary_Filter_Yaw   == true) ui->checkBox_Complementary_Filter_Yaw->setChecked(true);

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

    w = ui->label_Gyroscope_X->width();
    h = ui->label_Gyroscope_X->height();
    ui->label_Gyroscope_X->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Gyroscope_Y->width();
    h = ui->label_Gyroscope_Y->height();
    ui->label_Gyroscope_Y->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Gyroscope_Z->width();
    h = ui->label_Gyroscope_Z->height();
    ui->label_Gyroscope_Z->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Gyroscope_Roll->width();
    h = ui->label_Gyroscope_Roll->height();
    ui->label_Gyroscope_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Gyroscope_Pitch->width();
    h = ui->label_Gyroscope_Pitch->height();
    ui->label_Gyroscope_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Gyroscope_Yaw->width();
    h = ui->label_Gyroscope_Yaw->height();
    ui->label_Gyroscope_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Magnetometer_X->width();
    h = ui->label_Magnetometer_X->height();
    ui->label_Magnetometer_X->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Magnetometer_Y->width();
    h = ui->label_Magnetometer_Y->height();
    ui->label_Magnetometer_Y->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Magnetometer_Z->width();
    h = ui->label_Magnetometer_Z->height();
    ui->label_Magnetometer_Z->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Magnetometer_Roll->width();
    h = ui->label_Magnetometer_Roll->height();
    ui->label_Magnetometer_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Magnetometer_Pitch->width();
    h = ui->label_Magnetometer_Pitch->height();
    ui->label_Magnetometer_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Magnetometer_Yaw->width();
    h = ui->label_Magnetometer_Yaw->height();
    ui->label_Magnetometer_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Complementary_Filter_Roll->width();
    h = ui->label_Complementary_Filter_Roll->height();
    ui->label_Complementary_Filter_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Complementary_Filter_Pitch->width();
    h = ui->label_Complementary_Filter_Pitch->height();
    ui->label_Complementary_Filter_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Complementary_Filter_Yaw->width();
    h = ui->label_Complementary_Filter_Yaw->height();
    ui->label_Complementary_Filter_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );
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

void MainWindow::on_checkBox_Gyroscope_X_clicked()
{
    if( ui->checkBox_Gyroscope_X->isChecked() ) {

        Show_Gyroscope_X = true;
    }
    else {

        Show_Gyroscope_X = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Gyroscope_Y_clicked()
{
    if( ui->checkBox_Gyroscope_Y->isChecked() ) {

        Show_Gyroscope_Y = true;
    }
    else {

        Show_Gyroscope_Y = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Gyroscope_Z_clicked()
{
    if( ui->checkBox_Gyroscope_Z->isChecked() ) {

        Show_Gyroscope_Z = true;
    }
    else {

        Show_Gyroscope_Z = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Gyroscope_Roll_clicked()
{
    if( ui->checkBox_Gyroscope_Roll->isChecked() ) {

        Show_Gyroscope_Roll = true;
    }
    else {

        Show_Gyroscope_Roll = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Gyroscope_Pitch_clicked()
{
    if( ui->checkBox_Gyroscope_Pitch->isChecked() ) {

        Show_Gyroscope_Pitch = true;
    }
    else {

        Show_Gyroscope_Pitch = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Gyroscope_Yaw_clicked()
{
    if( ui->checkBox_Gyroscope_Yaw->isChecked() ) {

        Show_Gyroscope_Yaw = true;
    }
    else {

        Show_Gyroscope_Yaw = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Magnetometer_X_clicked()
{
    if( ui->checkBox_Magnetometer_X->isChecked() ) {

        Show_Magnetometer_X = true;
    }
    else {

        Show_Magnetometer_X = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Magnetometer_Y_clicked()
{
    if( ui->checkBox_Magnetometer_Y->isChecked() ) {

        Show_Magnetometer_Y = true;
    }
    else {

        Show_Magnetometer_Y = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Magnetometer_Z_clicked()
{
    if( ui->checkBox_Magnetometer_Z->isChecked() ) {

        Show_Magnetometer_Z = true;
    }
    else {

        Show_Magnetometer_Z = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Magnetometer_Roll_clicked()
{
    if( ui->checkBox_Magnetometer_Roll->isChecked() ) {

        Show_Magnetometer_Roll = true;
    }
    else {

        Show_Magnetometer_Roll = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Magnetometer_Pitch_clicked()
{
    if( ui->checkBox_Magnetometer_Pitch->isChecked() ) {

        Show_Magnetometer_Pitch = true;
    }
    else {

        Show_Magnetometer_Pitch = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Magnetometer_Yaw_clicked()
{
    if( ui->checkBox_Magnetometer_Yaw->isChecked() ) {

        Show_Magnetometer_Yaw = true;
    }
    else {

        Show_Magnetometer_Yaw = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Complementary_Filter_Roll_clicked()
{
    if( ui->checkBox_Complementary_Filter_Roll->isChecked() ) {

        Show_Complementary_Filter_Roll = true;
    }
    else {

        Show_Complementary_Filter_Roll = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Complementary_Filter_Pitch_clicked()
{
    if( ui->checkBox_Complementary_Filter_Pitch->isChecked() ) {

        Show_Complementary_Filter_Pitch = true;
    }
    else {

        Show_Complementary_Filter_Pitch = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Complementary_Filter_Yaw_clicked()
{
    if( ui->checkBox_Complementary_Filter_Yaw->isChecked() ) {

        Show_Complementary_Filter_Yaw = true;
    }
    else {

        Show_Complementary_Filter_Yaw = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
