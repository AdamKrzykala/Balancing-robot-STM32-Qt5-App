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
    Show_Kalman_Filter_Roll = true; Show_Kalman_Filter_Pitch = true; Show_Kalman_Filter_Yaw = true;
    Show_Madgwick_Filter_Roll = true; Show_Madgwick_Filter_Pitch = true; Show_Madgwick_Filter_Yaw = true;

    Complementary_Filter_Graph_Run = true;
    Kalman_Filter_Graph_Run = true;
    Madgwick_Filter_Graph_Run = true;

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
    MainWindow_Setup_Complementary_Filter_Graph();
    MainWindow_Setup_Kalman_Filter_Graph();
    MainWindow_Setup_Madgwick_Filter_Graph();

    // Connection with CommunicationWindow
    connect(this, SIGNAL( Disconnect_Signal() ), CW, SLOT( Disconnect_Slot() ) );
    connect(this, SIGNAL( Send_data_Signal() ), CW, SLOT( Send_Data_to_robot_Slot() ) );

    connect(CW, SIGNAL( Connection_OK_Signal() ), this, SLOT( Connection_OK_Slot() ) );
    connect(CW, SIGNAL( Parsed_frame_OK_Signal(Data_from_Robot) ), this, SLOT( MainWindow_realtimeDataSlot(Data_from_Robot) ));

    connect(CW, SIGNAL( Timeout_Error() ), this, SLOT( on_pushButton_ConnectDisconnect_clicked() ) );

    // Setup OpenGL visualisation
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    QWidget *w = new QWidget;

    container->addWidget(GW);
    w->setLayout(container);
    mainLayout->addWidget(w);

    // Setup CommunicationWindow
    CW->exec();

    Splitter_Position = ui->splitter->sizes();
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
    ui->Complementary_Filter_Graph->yAxis->setRange(-1, 1);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Complementary_Filter_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Complementary_Filter_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Complementary_Filter_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Complementary_Filter_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Kalman_Filter_Graph()
{
    ui->Kalman_Filter_Graph->addGraph(); // red line
    ui->Kalman_Filter_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Kalman_Filter_Graph->addGraph(); // green line
    ui->Kalman_Filter_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Kalman_Filter_Graph->addGraph(); // blue line
    ui->Kalman_Filter_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Kalman_Filter_Graph->xAxis->setTicker(timeTicker);
    ui->Kalman_Filter_Graph->axisRect()->setupFullAxesBox();
    ui->Kalman_Filter_Graph->yAxis->setRange(-1, 1);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Kalman_Filter_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Kalman_Filter_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Kalman_Filter_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Kalman_Filter_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Setup_Madgwick_Filter_Graph()
{
    ui->Madgwick_Filter_Graph->addGraph(); // red line
    ui->Madgwick_Filter_Graph->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->Madgwick_Filter_Graph->addGraph(); // green line
    ui->Madgwick_Filter_Graph->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->Madgwick_Filter_Graph->addGraph(); // blue line
    ui->Madgwick_Filter_Graph->graph(2)->setPen(QPen(QColor(0, 0, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    ui->Madgwick_Filter_Graph->xAxis->setTicker(timeTicker);
    ui->Madgwick_Filter_Graph->axisRect()->setupFullAxesBox();
    ui->Madgwick_Filter_Graph->yAxis->setRange(-1, 1);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Madgwick_Filter_Graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Madgwick_Filter_Graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Madgwick_Filter_Graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Madgwick_Filter_Graph->yAxis2, SLOT(setRange(QCPRange)));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Display_IMU_data()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed() / 1000.0; // time elapsed since start of demo, in seconds

    // Fusion data
    double Complementary_Filter_Roll  = Data_from.Complementary_roll;
    double Complementary_Filter_Pitch = Data_from.Complementary_pitch;
    double Complementary_Filter_Yaw   = Data_from.Complementary_yaw;

    double Kalman_Filter_Roll  = Data_from.Kalman_roll;
    double Kalman_Filter_Pitch = Data_from.Kalman_pitch;
    double Kalman_Filter_Yaw   = Data_from.Kalman_yaw;

    double Madgwick_Filter_Roll  = Data_from.Madgwick_roll;
    double Madgwick_Filter_Pitch = Data_from.Madgwick_pitch;
    double Madgwick_Filter_Yaw   = Data_from.Madgwick_yaw;

    ui->label_Roll_View->setNum(Complementary_Filter_Roll);
    ui->label_Pitch_View->setNum(Complementary_Filter_Pitch);
    ui->label_Yaw_View->setNum(Complementary_Filter_Yaw);

    ui->label_Kalman_Roll_View->setNum(Kalman_Filter_Roll);
    ui->label_Kalman_Pitch_View->setNum(Kalman_Filter_Pitch);
    ui->label_Kalman_Yaw_View->setNum(Kalman_Filter_Yaw);

    ui->label_Madgwick_Roll_View->setNum(Madgwick_Filter_Roll);
    ui->label_Madgwick_Pitch_View->setNum(Madgwick_Filter_Pitch);
    ui->label_Madgwick_Yaw_View->setNum(Madgwick_Filter_Yaw);

    // add data to lines:
    if(Show_Complementary_Filter_Roll  == true) ui->Complementary_Filter_Graph->graph(0)->addData(key, Complementary_Filter_Roll);
    if(Show_Complementary_Filter_Pitch == true) ui->Complementary_Filter_Graph->graph(1)->addData(key, Complementary_Filter_Pitch);
    if(Show_Complementary_Filter_Yaw   == true) ui->Complementary_Filter_Graph->graph(2)->addData(key, Complementary_Filter_Yaw);

    if(Show_Kalman_Filter_Roll  == true) ui->Kalman_Filter_Graph->graph(0)->addData(key, Kalman_Filter_Roll);
    if(Show_Kalman_Filter_Pitch == true) ui->Kalman_Filter_Graph->graph(1)->addData(key, Kalman_Filter_Pitch);
    if(Show_Kalman_Filter_Yaw   == true) ui->Kalman_Filter_Graph->graph(2)->addData(key, Kalman_Filter_Yaw);

    if(Show_Madgwick_Filter_Roll  == true) ui->Madgwick_Filter_Graph->graph(0)->addData(key, Madgwick_Filter_Roll);
    if(Show_Madgwick_Filter_Pitch == true) ui->Madgwick_Filter_Graph->graph(1)->addData(key, Madgwick_Filter_Pitch);
    if(Show_Madgwick_Filter_Yaw   == true) ui->Madgwick_Filter_Graph->graph(2)->addData(key, Madgwick_Filter_Yaw);

    ui->Complementary_Filter_Graph->graph(0)->rescaleValueAxis(true);
    ui->Complementary_Filter_Graph->graph(1)->rescaleValueAxis(true);
    ui->Complementary_Filter_Graph->graph(2)->rescaleValueAxis(true);

    ui->Kalman_Filter_Graph->graph(0)->rescaleValueAxis(true);
    ui->Kalman_Filter_Graph->graph(1)->rescaleValueAxis(true);
    ui->Kalman_Filter_Graph->graph(2)->rescaleValueAxis(true);

    ui->Madgwick_Filter_Graph->graph(0)->rescaleValueAxis(true);
    ui->Madgwick_Filter_Graph->graph(1)->rescaleValueAxis(true);
    ui->Madgwick_Filter_Graph->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Complementary_Filter_Graph->xAxis->setRange(key, 60, Qt::AlignRight);

    if( Complementary_Filter_Graph_Run == true ) {

        ui->Complementary_Filter_Graph->replot();

        ui->lcdNumber_Complementary_Filter_Roll->display(Complementary_Filter_Roll);
        ui->lcdNumber_Complementary_Filter_Pitch->display(Complementary_Filter_Pitch);
        ui->lcdNumber_Complementary_Filter_Yaw->display(Complementary_Filter_Yaw);
    }

    ui->Kalman_Filter_Graph->xAxis->setRange(key, 60, Qt::AlignRight);

    if( Kalman_Filter_Graph_Run == true ) {

        ui->Kalman_Filter_Graph->replot();

        ui->lcdNumber_Kalman_Filter_Roll->display(Kalman_Filter_Roll);
        ui->lcdNumber_Kalman_Filter_Pitch->display(Kalman_Filter_Pitch);
        ui->lcdNumber_Kalman_Filter_Yaw->display(Kalman_Filter_Yaw);
    }

    ui->Madgwick_Filter_Graph->xAxis->setRange(key, 60, Qt::AlignRight);

    if( Madgwick_Filter_Graph_Run == true ) {

        ui->Madgwick_Filter_Graph->replot();

        ui->lcdNumber_Madgwick_Filter_Roll->display(Madgwick_Filter_Roll);
        ui->lcdNumber_Madgwick_Filter_Pitch->display(Madgwick_Filter_Pitch);
        ui->lcdNumber_Madgwick_Filter_Yaw->display(Madgwick_Filter_Yaw);
    }

    // OpenGL visualisation
    ui->widget_RPY_Visualisation->setXRotation(Kalman_Filter_Pitch);
    ui->widget_RPY_Visualisation->setYRotation(Kalman_Filter_Yaw);
    ui->widget_RPY_Visualisation->setZRotation(Kalman_Filter_Roll);
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
    int Variance = settings.value("Variance").toInt();
    double Madgwick_beta = settings.value("Madgwick_beta").toDouble();

    int Which_filter = settings.value("Which_filter").toInt();

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
    ui->doubleSpinBox_Kalman_filter_variance->setValue(Variance);
    ui->doubleSpinBox_Madgwick_beta->setValue(Madgwick_beta);

    if( Which_filter == 0 ) ui->radioButton_Complementary_filter->setChecked(true);
    else if( Which_filter == 1 ) ui->radioButton_Kalman_filter->setChecked(true);
    else if( Which_filter == 2 ) ui->radioButton_Madgwick_filter->setChecked(true);

    qDebug() << "Wczytano PID_Kp: " << PID_Kp;
    qDebug() << "Wczytano PID_Ki: " << PID_Ki;
    qDebug() << "Wczytano PID_Kd: " << PID_Kd;

    qDebug() << "Wczytano Speed_PID_Kp: " << Speed_PID_Kp;
    qDebug() << "Wczytano Speed_PID_Ki: " << Speed_PID_Ki;
    qDebug() << "Wczytano Speed_PID_Kd: " << Speed_PID_Kd;

    qDebug() << "Wczytano Complementary_weight: " << Complementary_weight;
    qDebug() << "Wczytano wariancje: "            << Variance;
    qDebug() << "Wczytano beta: "                 << Madgwick_beta;
    qDebug() << "Wczytano Which_filter: "         << Which_filter;
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
    int Kalman_filter_process_variance = static_cast<int>( ui->doubleSpinBox_Kalman_filter_variance->value() );
    double Madgwick_beta = ui->doubleSpinBox_Madgwick_beta->value();

    int Which_filter = 0;

    if( ui->radioButton_Complementary_filter->isChecked() ) Which_filter = 0;
    else if(ui->radioButton_Kalman_filter->isChecked() )    Which_filter = 1;
    else if(ui->radioButton_Madgwick_filter->isChecked() )  Which_filter = 2;

    settings.setValue("PID_Kp", PID_Kp);
    settings.setValue("PID_Ki", PID_Ki);
    settings.setValue("PID_Kd", PID_Kd);

    settings.setValue("Speed_PID_Kp", Speed_PID_Kp);
    settings.setValue("Speed_PID_Ki", Speed_PID_Ki);
    settings.setValue("Speed_PID_Kd", Speed_PID_Kd);

    settings.setValue("Complementary_weight", Complementary_weight);
    settings.setValue("Variance", Kalman_filter_process_variance);
    settings.setValue("Madgwick_beta", Madgwick_beta);

    settings.setValue("Which_filter", Which_filter);

    qDebug() << "Zapisano PID_Kp: "                 << PID_Kp;
    qDebug() << "Zapisano PID_Ki: "                 << PID_Ki;
    qDebug() << "Zapisano PID_Kd: "                 << PID_Kd;
    qDebug() << "Zapisano Speed_PID_Kp: "           << Speed_PID_Kp;
    qDebug() << "Zapisano Speed_PID_Ki: "           << Speed_PID_Ki;
    qDebug() << "Zapisano Speed_PID_Kd: "           << Speed_PID_Kd;
    qDebug() << "Zapisano Complementary_weight: "   << Complementary_weight;
    qDebug() << "Zapisano Variance: "               << Kalman_filter_process_variance;
    qDebug() << "Zapisano beta: "                   << Madgwick_beta;
    qDebug() << "Zapisano Which_filter: "           << Which_filter;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Default_View()
{
   if(Show_Complementary_Filter_Roll  == true) ui->checkBox_Complementary_Filter_Roll->setChecked(true);
   if(Show_Complementary_Filter_Pitch == true) ui->checkBox_Complementary_Filter_Pitch->setChecked(true);
   if(Show_Complementary_Filter_Yaw   == true) ui->checkBox_Complementary_Filter_Yaw->setChecked(true);

   if(Show_Kalman_Filter_Roll  == true) ui->checkBox_Kalman_Filter_Roll->setChecked(true);
   if(Show_Kalman_Filter_Pitch == true) ui->checkBox_Kalman_Filter_Pitch->setChecked(true);
   if(Show_Kalman_Filter_Yaw   == true) ui->checkBox_Kalman_Filter_Yaw->setChecked(true);

   if(Show_Madgwick_Filter_Roll  == true) ui->checkBox_Madgwick_Filter_Roll->setChecked(true);
   if(Show_Madgwick_Filter_Pitch == true) ui->checkBox_Madgwick_Filter_Pitch->setChecked(true);
   if(Show_Madgwick_Filter_Yaw   == true) ui->checkBox_Madgwick_Filter_Yaw->setChecked(true);

   ui->label_Voltage->setNum(0);

   ui->pushButton_EmergencyStop->setCheckable(true);

   ui->pushButton_Plots_Start_Stop->setText("Stop");
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
    QPixmap Connection(":/new/prefix1/png/Bluetooth.png");
    QPixmap Stop(":/new/prefix1/png/Stop_button.png");
    QPixmap RPY(":/new/prefix1/png/RPY.png");
    QPixmap StepperMotor(":/new/prefix1/png/StepperMotor.png");

    QPixmap RedArrowUp(":/new/prefix1/png/RedArrowUp.png");
    QPixmap RedArrowDown(":/new/prefix1/png/RedArrowDown.png");
    QPixmap RedArrowLeft(":/new/prefix1/png/RedArrowLeft.png");
    QPixmap RedArrowRight(":/new/prefix1/png/RedArrowRight.png");

    QPixmap Speed(":/new/prefix1/png/Speed.png");
    QPixmap Angle(":/new/prefix1/png/Angle.png");
    QPixmap Fusion(":/new/prefix1/png/Fusion.png");
    QPixmap Variables(":/new/prefix1/png/Variables.png");

    w = ui->label_Connection->width();
    h = ui->label_Connection->height();
    ui->label_Connection->setPixmap( Connection.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Battery->width();
    h = ui->label_Battery->height();
    ui->label_Battery->setPixmap( Battery_null.scaled(w, h, Qt::KeepAspectRatio) );

    // Complementary filter RGB dots
    w = ui->label_Complementary_Filter_Roll->width();
    h = ui->label_Complementary_Filter_Roll->height();
    ui->label_Complementary_Filter_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Complementary_Filter_Pitch->width();
    h = ui->label_Complementary_Filter_Pitch->height();
    ui->label_Complementary_Filter_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Complementary_Filter_Yaw->width();
    h = ui->label_Complementary_Filter_Yaw->height();
    ui->label_Complementary_Filter_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    // Kalman filter RGB dots
    w = ui->label_Kalman_Filter_Roll->width();
    h = ui->label_Kalman_Filter_Roll->height();
    ui->label_Kalman_Filter_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Kalman_Filter_Pitch->width();
    h = ui->label_Kalman_Filter_Pitch->height();
    ui->label_Kalman_Filter_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Kalman_Filter_Yaw->width();
    h = ui->label_Kalman_Filter_Yaw->height();
    ui->label_Kalman_Filter_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    // Madgwick filter RGB dots
    w = ui->label_Madgwick_Filter_Roll->width();
    h = ui->label_Madgwick_Filter_Roll->height();
    ui->label_Madgwick_Filter_Roll->setPixmap( Red_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Madgwick_Filter_Pitch->width();
    h = ui->label_Madgwick_Filter_Pitch->height();
    ui->label_Madgwick_Filter_Pitch->setPixmap( Green_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Madgwick_Filter_Yaw->width();
    h = ui->label_Madgwick_Filter_Yaw->height();
    ui->label_Madgwick_Filter_Yaw->setPixmap( Blue_dot.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Speed->width();
    h = ui->label_Speed->height();
    ui->label_Speed->setPixmap( Speed.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Angle->width();
    h = ui->label_Angle->height();
    ui->label_Angle->setPixmap( Angle.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Fusion->width();
    h = ui->label_Fusion->height();
    ui->label_Fusion->setPixmap( Fusion.scaled(w, h, Qt::KeepAspectRatio) );

    w = ui->label_Variables->width();
    h = ui->label_Variables->height();
    ui->label_Variables->setPixmap( Variables.scaled(w, h, Qt::KeepAspectRatio) );

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
    ui->progressBar_PID_Kd->setValue( static_cast<int>(arg1* 100) );
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
    ui->progressBar_Speed_PID_Kd->setValue( static_cast<int>(arg1* 100) );
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
    QMessageBox messageBox(QMessageBox::Question,
                           tr("BBot"),
                           tr("Czy na pewno chcesz zakończyć ? \n"),
                           QMessageBox::Yes | QMessageBox::No);

    messageBox.setButtonText(QMessageBox::Yes, tr("Tak"));
    messageBox.setButtonText(QMessageBox::No,  tr("Nie"));

    if(messageBox.exec() == QMessageBox::Yes) {

        exit(0);
    }
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

void MainWindow::on_checkBox_Kalman_Filter_Roll_clicked()
{
    if( ui->checkBox_Kalman_Filter_Roll->isChecked() ) {

        Show_Kalman_Filter_Roll = true;
    }
    else {

        Show_Kalman_Filter_Roll = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Kalman_Filter_Pitch_clicked()
{
    if( ui->checkBox_Kalman_Filter_Pitch->isChecked() ) {

        Show_Kalman_Filter_Pitch = true;
    }
    else {

        Show_Kalman_Filter_Pitch = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Kalman_Filter_Yaw_clicked()
{
    if( ui->checkBox_Kalman_Filter_Yaw->isChecked() ) {

        Show_Kalman_Filter_Yaw = true;
    }
    else {

        Show_Kalman_Filter_Yaw = false;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Plots_Center_clicked()
{
    ui->splitter->setSizes( Splitter_Position );
    ui->splitter->update();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Plots_Start_Stop_clicked()
{

    if( ui->pushButton_Plots_Start_Stop->text() == "Start" ) {

        ui->pushButton_Plots_Start_Stop->setText("Stop");
    }
    else {

        ui->pushButton_Plots_Start_Stop->setText("Start");
    }

    if(Complementary_Filter_Graph_Run == true) {

        Complementary_Filter_Graph_Run = false;
    }
    else {

        Complementary_Filter_Graph_Run = true;
    }

    if(Kalman_Filter_Graph_Run == true) {

        Kalman_Filter_Graph_Run = false;
    }
    else {

        Kalman_Filter_Graph_Run = true;
    }

    if(Madgwick_Filter_Graph_Run == true) {

        Madgwick_Filter_Graph_Run = false;
    }
    else {

        Madgwick_Filter_Graph_Run = true;
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButton_Reset_Plots_Range_clicked()
{
    ui->Complementary_Filter_Graph->clearGraphs();
    ui->Kalman_Filter_Graph->clearGraphs();
    ui->Madgwick_Filter_Graph->clearGraphs();

    MainWindow_Setup_Complementary_Filter_Graph();
    MainWindow_Setup_Kalman_Filter_Graph();
    MainWindow_Setup_Madgwick_Filter_Graph();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_radioButton_Complementary_filter_toggled(bool checked)
{
    if( checked == true ) {

        Data_to.Which_filter = 0;
    }

    saveSettings();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_radioButton_Kalman_filter_toggled(bool checked)
{
    if( checked == true ) {

        Data_to.Which_filter = 1;
    }

    saveSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_Kalman_filter_variance_valueChanged(double arg1)
{
    Data_to.Kalman_procces_variance = static_cast<int>(arg1);
    saveSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_radioButton_Madgwick_filter_toggled(bool checked)
{
    if( checked == true ) {

        Data_to.Which_filter = 2;
    }

    saveSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_doubleSpinBox_Madgwick_beta_valueChanged(double arg1)
{
    Data_to.Madgwick_filter_beta = arg1;
    saveSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Madgwick_Filter_Roll_clicked()
{
    if( ui->checkBox_Madgwick_Filter_Roll->isChecked() ) {

        Show_Madgwick_Filter_Roll = true;
    }
    else {

        Show_Madgwick_Filter_Roll = false;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Madgwick_Filter_Pitch_clicked()
{
    if( ui->checkBox_Madgwick_Filter_Pitch->isChecked() ) {

        Show_Madgwick_Filter_Pitch = true;
    }
    else {

        Show_Madgwick_Filter_Pitch = false;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_checkBox_Madgwick_Filter_Yaw_clicked()
{
    if( ui->checkBox_Madgwick_Filter_Yaw->isChecked() ) {

        Show_Madgwick_Filter_Yaw = true;
    }
    else {

        Show_Madgwick_Filter_Yaw = false;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
