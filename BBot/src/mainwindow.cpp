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

    Data_to.Angle_Kd = 0; Data_to.Angle_Ki = 0; Data_to.Angle_Kp = 0;
    Data_to.Speed_Kd = 0; Data_to.Speed_Ki = 0; Data_to.Speed_Kp = 0;
    Data_to.Complementary_filter_weight = 0;
    Data_to.Left_engine_speed = 0; Data_to.Right_engine_speed = 0;
    Data_to.Emergency_stop = 1;

    m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/main_settings.ini";
    loadSettings();

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

    // Connection with BT
    //connect(BT, SIGNAL( Parsed_Frame_OK() ), this, SLOT( MainWindow_realtimeDataSlot() ));

    // Connection with CommunicationWindow
    connect(this, SIGNAL( Disconnect_Signal() ), CW, SLOT( Disconnect_Slot() ) );
    connect(this, SIGNAL( Send_data_Signal() ), CW, SLOT( Send_Data_to_robot_Slot() ) );

    connect(CW, SIGNAL( Connection_OK_Signal() ), this, SLOT( Connection_OK_Slot() ) );
    connect(CW, SIGNAL( Parsed_frame_OK_Signal(Data_from_Robot) ), this, SLOT( MainWindow_realtimeDataSlot(Data_from_Robot) ));

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
    ui->Accelerometer_Graph->yAxis->setRange(-1.5, 1.5);

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
    ui->Gyroscope_Graph->yAxis->setRange(-500, 500);

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
    double Accelerometer_X = 0;
    double Accelerometer_Y = 0;
    double Accelerometer_Z = 0;

    double Accelerometer_Roll  = 0;
    double Accelerometer_Pitch = 0;
    double Accelerometer_Yaw   = 0;

    // Gyroscope data
    double Gyroscope_X = 0;
    double Gyroscope_Y = 0;
    double Gyroscope_Z = 0;

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
    double Complementary_Filter_Roll  = Data_from.Complementary_roll;
    double Complementary_Filter_Pitch = Data_from.Complementary_pitch;
    double Complementary_Filter_Yaw   = Data_from.Complementary_yaw;

    ui->label_Roll_View->setNum(Complementary_Filter_Roll);
    ui->label_Pitch_View->setNum(Complementary_Filter_Pitch);
    ui->label_Yaw_View->setNum(Complementary_Filter_Yaw);

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
    //ui->Accelerometer_Graph->graph(0)->rescaleValueAxis();
    //ui->Accelerometer_Graph->graph(1)->rescaleValueAxis(true);

    ui->Accelerometer_RPY_Graph->graph(0)->rescaleValueAxis();
    ui->Accelerometer_RPY_Graph->graph(1)->rescaleValueAxis(true);

    //ui->Gyroscope_Graph->graph(0)->rescaleValueAxis();
    //ui->Gyroscope_Graph->graph(1)->rescaleValueAxis(true);

    ui->Gyroscope_RPY_Graph->graph(0)->rescaleValueAxis();
    ui->Gyroscope_RPY_Graph->graph(1)->rescaleValueAxis(true);

    ui->Magnetometer_Graph->graph(0)->rescaleValueAxis();
    ui->Magnetometer_Graph->graph(1)->rescaleValueAxis(true);

    ui->Magnetometer_RPY_Graph->graph(0)->rescaleValueAxis(true);
    ui->Magnetometer_RPY_Graph->graph(1)->rescaleValueAxis(true);

    ui->Complementary_Filter_Graph->graph(0)->rescaleValueAxis(true);
    ui->Complementary_Filter_Graph->graph(1)->rescaleValueAxis(true);
    ui->Complementary_Filter_Graph->graph(2)->rescaleValueAxis(true);

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
    ui->widget_RPY_Visualisation->setXRotation(Complementary_Filter_Pitch);
    ui->widget_RPY_Visualisation->setYRotation(Complementary_Filter_Yaw);
    ui->widget_RPY_Visualisation->setZRotation(Complementary_Filter_Roll);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Display_Battery_data(double voltage)
{

    QPixmap Battery_null(":/new/prefix1/png/Battery_null.png");
    QPixmap Battery_low(":/new/prefix1/png/Battery_low.png");
    QPixmap Battery_medium(":/new/prefix1/png/Battery_medium.png");
    QPixmap Battery_full(":/new/prefix1/png/Battery_full.png");

    int w = ui->label_Battery->width();
    int h = ui->label_Battery->height();

    double max_value = 12.6;
    double min_value = 10.5;
    double ratio = max_value - min_value;

    double battery_level =  ( (voltage - min_value) / ratio ) * 100;

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

        ui->label_Capacity->setNum( static_cast<int>(battery_level) );
    }
    else if(battery_level > 100) {

        ui->label_Capacity->setNum(100);
    }
    else {

        ui->label_Capacity->setNum(0);
    }

    ui->label_Voltage->setNum(voltage);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Display_Engines_data()
{
    int Left_engine_speed  = Data_from.Left_engine_speed;
    int Right_engine_speed = Data_from.Right_engine_speed;

    ui->label_Left_engine_speed_View->setNum(Left_engine_speed);
    ui->label_Right_engine_speed_View->setNum(Right_engine_speed);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::MainWindow_realtimeDataSlot(Data_from_Robot data)
{        
    Data_from = data;

    MainWindow_Display_Battery_data( data.Lipol_voltage );
    MainWindow_Display_IMU_data();
    MainWindow_Display_Engines_data();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::Connection_OK_Slot()
{
    this->showMaximized();

    ui->label_PortName->setText( CW->Get_PortName() );

    // Run communication thread
    //BT->Start_communication_thread();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::loadSettings()
{
    QSettings settings(m_sSettingsFile);

    double PID_Kp = settings.value("PID_Kp").toDouble();
    double PID_Ki = settings.value("PID_Ki").toDouble();
    double PID_Kd = settings.value("PID_Kd").toDouble();

    double Speed_PID_Kp = settings.value("Speed_PID_Kp").toDouble();
    double Speed_PID_Ki = settings.value("Speed_PID_Ki").toDouble();
    double Speed_PID_Kd = settings.value("Speed_PID_Kd").toDouble();

    double Complementary_weight = settings.value("Complementary_weight").toDouble();

    settings.setValue("PID_Kp", PID_Kp);
    settings.setValue("PID_Ki", PID_Ki);
    settings.setValue("PID_Kd", PID_Kd);

    settings.setValue("Speed_PID_Kp", Speed_PID_Kp);
    settings.setValue("Speed_PID_Ki", Speed_PID_Ki);
    settings.setValue("Speed_PID_Kd", Speed_PID_Kd);

    settings.setValue("Complementary_weight", Complementary_weight);

    ui->doubleSpinBox_PID_Kp->setValue(PID_Kp);
    ui->doubleSpinBox_PID_Ki->setValue(PID_Ki);
    ui->doubleSpinBox_PID_Kd->setValue(PID_Kd);

    ui->doubleSpinBox_Speed_PID_Kp->setValue(Speed_PID_Kp);
    ui->doubleSpinBox_Speed_PID_Ki->setValue(Speed_PID_Ki);
    ui->doubleSpinBox_Speed_PID_Kd->setValue(Speed_PID_Kd);

    ui->doubleSpinBox_Complementary_filter_weight->setValue(Complementary_weight);

    qDebug() << "Wczytano PID_Kp: " << PID_Kp;
    qDebug() << "Wczytano PID_Ki: " << PID_Ki;
    qDebug() << "Wczytano PID_Kd: " << PID_Kd;

    qDebug() << "Wczytano Speed_PID_Kp: " << Speed_PID_Kp;
    qDebug() << "Wczytano Speed_PID_Ki: " << Speed_PID_Ki;
    qDebug() << "Wczytano Speed_PID_Kd: " << Speed_PID_Kd;

    qDebug() << "Wczytano Complementary_weight: " << Complementary_weight;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::saveSettings()
{
    QSettings settings(m_sSettingsFile);

    double PID_Kp = ui->doubleSpinBox_PID_Kp->value();
    double PID_Ki = ui->doubleSpinBox_PID_Ki->value();
    double PID_Kd = ui->doubleSpinBox_PID_Kd->value();

    double Speed_PID_Kp = ui->doubleSpinBox_Speed_PID_Kp->value();
    double Speed_PID_Ki = ui->doubleSpinBox_Speed_PID_Ki->value();
    double Speed_PID_Kd = ui->doubleSpinBox_Speed_PID_Kd->value();

    double Complementary_weight = ui->doubleSpinBox_Complementary_filter_weight->value();

    settings.setValue("PID_Kp", PID_Kp);
    settings.setValue("PID_Ki", PID_Ki);
    settings.setValue("PID_Kd", PID_Kd);

    settings.setValue("Speed_PID_Kp", Speed_PID_Kp);
    settings.setValue("Speed_PID_Ki", Speed_PID_Ki);
    settings.setValue("Speed_PID_Kd", Speed_PID_Kd);

    settings.setValue("Complementary_weight", Complementary_weight);

    qDebug() << "Zapisano PID_Kp: " << PID_Kp;
    qDebug() << "Zapisano PID_Ki: " << PID_Ki;
    qDebug() << "Zapisano PID_Kd: " << PID_Kd;
    qDebug() << "Zapisano Speed_PID_Kp: " << Speed_PID_Kp;
    qDebug() << "Zapisano Speed_PID_Ki: " << Speed_PID_Ki;
    qDebug() << "Zapisano Speed_PID_Kd: " << Speed_PID_Kd;
    qDebug() << "Zapisano Complementary_weight: " << Complementary_weight;
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
    QPixmap Connection(":/new/prefix1/png/Connection.png");
    QPixmap Stop(":/new/prefix1/png/Stop_button.png");
    QPixmap RPY(":/new/prefix1/png/RPY.png");
    QPixmap StepperMotor(":/new/prefix1/png/StepperMotor.png");

    QPixmap RedArrowUp(":/new/prefix1/png/RedArrowUp.png");
    QPixmap RedArrowDown(":/new/prefix1/png/RedArrowDown.png");
    QPixmap RedArrowLeft(":/new/prefix1/png/RedArrowLeft.png");
    QPixmap RedArrowRight(":/new/prefix1/png/RedArrowRight.png");

    w = ui->label_StepperMotor->width();
    h = ui->label_StepperMotor->height();
    ui->label_StepperMotor->setPixmap( StepperMotor.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_RPY->width();
    h = ui->label_RPY->height();
    ui->label_RPY->setPixmap( RPY.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Connection->width();
    h = ui->label_Connection->height();
    ui->label_Connection->setPixmap( Connection.scaled(w, h, Qt::KeepAspectRatio) );

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

    w = ui->pushButton_EmergencyStop->width();
    h = ui->pushButton_EmergencyStop->height();

    QIcon ButtonIcon(Stop.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_EmergencyStop->setIcon(ButtonIcon);
    ui->pushButton_EmergencyStop->setIconSize(QSize(w,h));

    w = ui->pushButton_Forward->width();
    h = ui->pushButton_Forward->height();

    QIcon ForwardButtonIcon(RedArrowUp.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Forward->setIcon(ForwardButtonIcon);
    ui->pushButton_Forward->setIconSize(QSize(w,h));

    w = ui->pushButton_Backward->width();
    h = ui->pushButton_Backward->height();

    QIcon BackwardButtonIcon(RedArrowDown.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Backward->setIcon(BackwardButtonIcon);
    ui->pushButton_Backward->setIconSize(QSize(w,h));

    w = ui->pushButton_Left->width();
    h = ui->pushButton_Left->height();

    QIcon LeftButtonIcon(RedArrowLeft.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Left->setIcon(LeftButtonIcon);
    ui->pushButton_Left->setIconSize(QSize(w,h));

    w = ui->pushButton_Right->width();
    h = ui->pushButton_Right->height();

    QIcon RightButtonIcon(RedArrowRight.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Right->setIcon(RightButtonIcon);
    ui->pushButton_Right->setIconSize(QSize(w,h));
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

void MainWindow::on_pushButton_ConnectDisconnect_clicked()
{
    this->hide();
    emit Disconnect_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_PID_Default_clicked()
{
    ui->doubleSpinBox_PID_Kp->setValue(10);
    ui->doubleSpinBox_PID_Ki->setValue(100);
    ui->doubleSpinBox_PID_Kd->setValue(0.1);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_PID_Clear_clicked()
{
    ui->doubleSpinBox_PID_Kp->setValue(0);
    ui->doubleSpinBox_PID_Ki->setValue(0);
    ui->doubleSpinBox_PID_Kd->setValue(0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_PID_Kp_valueChanged(double arg1)
{
    ui->progressBar_PID_Kp->setValue( static_cast<int>(arg1) );
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_PID_Kd_valueChanged(double arg1)
{
    ui->progressBar_PID_Kd->setValue( static_cast<int>(arg1) );
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_PID_Ki_valueChanged(double arg1)
{
    ui->progressBar_PID_Ki->setValue( static_cast<int>(arg1) );
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_EmergencyStop_clicked()
{
    ui->pushButton_EmergencyStop->setCheckable(true);

    if( ui->pushButton_EmergencyStop->isChecked() ) {

        Data_to.Emergency_stop = 0;
    }
    else {

        Data_to.Emergency_stop = 1;
    }

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_Speed_PID_Kp_valueChanged(double arg1)
{
    ui->progressBar_Speed_PID_Kp->setValue( static_cast<int>(arg1) );
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_Speed_PID_Ki_valueChanged(double arg1)
{
    ui->progressBar_Speed_PID_Ki->setValue( static_cast<int>(arg1) );
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_Speed_PID_Kd_valueChanged(double arg1)
{
    ui->progressBar_Speed_PID_Kd->setValue( static_cast<int>(arg1) );
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Send_clicked()
{
    // Angle PID data
    Data_to.Angle_Kp = ui->doubleSpinBox_PID_Kp->value();
    Data_to.Angle_Ki = ui->doubleSpinBox_PID_Ki->value();
    Data_to.Angle_Kd = ui->doubleSpinBox_PID_Kd->value();

    // Speed PID data
    Data_to.Speed_Kp = ui->doubleSpinBox_Speed_PID_Kp->value();
    Data_to.Speed_Ki = ui->doubleSpinBox_Speed_PID_Ki->value();
    Data_to.Speed_Kd = ui->doubleSpinBox_Speed_PID_Kd->value();

    // Filters data
    Data_to.Complementary_filter_weight = ui->doubleSpinBox_Complementary_filter_weight->value();

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Exit_clicked()
{
    exit(0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Forward_pressed()
{
    QPixmap GreenArrowUp(":/new/prefix1/png/GreenArrowUp.png");

    int w = ui->pushButton_Forward->width();
    int h = ui->pushButton_Forward->height();

    QIcon ForwardButtonIcon(GreenArrowUp.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Forward->setIcon(ForwardButtonIcon);
    ui->pushButton_Forward->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed  = -50;
    Data_to.Right_engine_speed = -50;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Forward_released()
{
    QPixmap RedArrowUp(":/new/prefix1/png/RedArrowUp.png");

    int w = ui->pushButton_Forward->width();
    int h = ui->pushButton_Forward->height();

    QIcon ForwardButtonIcon(RedArrowUp.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Forward->setIcon(ForwardButtonIcon);
    ui->pushButton_Forward->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed = 0;
    Data_to.Right_engine_speed = 0;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Left_pressed()
{
    QPixmap GreenArrowLeft(":/new/prefix1/png/GreenArrowLeft.png");

    int w = ui->pushButton_Left->width();
    int h = ui->pushButton_Left->height();

    QIcon LeftButtonIcon(GreenArrowLeft.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Left->setIcon(LeftButtonIcon);
    ui->pushButton_Left->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed  = 50;
    Data_to.Right_engine_speed = -50;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Left_released()
{
    QPixmap RedArrowLeft(":/new/prefix1/png/RedArrowLeft.png");

    int w = ui->pushButton_Left->width();
    int h = ui->pushButton_Left->height();

    QIcon LeftButtonIcon(RedArrowLeft.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Left->setIcon(LeftButtonIcon);
    ui->pushButton_Left->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed = 0;
    Data_to.Right_engine_speed = 0;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Right_pressed()
{
    QPixmap GreenArrowRight(":/new/prefix1/png/GreenArrowRight.png");

    int w = ui->pushButton_Right->width();
    int h = ui->pushButton_Right->height();

    QIcon RightButtonIcon(GreenArrowRight.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Right->setIcon(RightButtonIcon);
    ui->pushButton_Right->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed  = -50;
    Data_to.Right_engine_speed = 50;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Right_released()
{
    QPixmap RedArrowRight(":/new/prefix1/png/RedArrowRight.png");

    int w = ui->pushButton_Right->width();
    int h = ui->pushButton_Right->height();

    QIcon RightButtonIcon(RedArrowRight.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Right->setIcon(RightButtonIcon);
    ui->pushButton_Right->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed = 0;
    Data_to.Right_engine_speed = 0;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Backward_pressed()
{
    QPixmap GreenArrowBackward(":/new/prefix1/png/GreenArrowDown.png");

    int w = ui->pushButton_Backward->width();
    int h = ui->pushButton_Backward->height();

    QIcon BackwardButtonIcon(GreenArrowBackward.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Backward->setIcon(BackwardButtonIcon);
    ui->pushButton_Backward->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed  = 50;
    Data_to.Right_engine_speed = 50;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Backward_released()
{
    QPixmap RedArrowBackward(":/new/prefix1/png/RedArrowDown.png");

    int w = ui->pushButton_Backward->width();
    int h = ui->pushButton_Backward->height();

    QIcon BackwardButtonIcon(RedArrowBackward.scaled(w, h, Qt::KeepAspectRatio));

    ui->pushButton_Backward->setIcon(BackwardButtonIcon);
    ui->pushButton_Backward->setIconSize(QSize(w,h));

    // Send data to robot
    Data_to.Left_engine_speed = 0;
    Data_to.Right_engine_speed = 0;

    CW->Fill_Data_to_robot(Data_to);

    emit Send_data_Signal();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_Complementary_filter_weight_valueChanged(double arg1)
{
    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Speed_PID_Default_clicked()
{
    ui->doubleSpinBox_Speed_PID_Kp->setValue(1);
    ui->doubleSpinBox_Speed_PID_Ki->setValue(2);
    ui->doubleSpinBox_Speed_PID_Kd->setValue(3);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Speed_PID_Clear_clicked()
{
    ui->doubleSpinBox_Speed_PID_Kp->setValue(0);
    ui->doubleSpinBox_Speed_PID_Ki->setValue(0);
    ui->doubleSpinBox_Speed_PID_Kd->setValue(0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
