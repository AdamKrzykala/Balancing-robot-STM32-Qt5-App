#include "mainwindow.h"
#include "ui_mainwindow.h"

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow_Resize_and_Center();

    MainWindow_Setup_QCustomPlot();

    BT->Parse_frame_thread();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::MainWindow_Resize_and_Center()
{
    // Resize Window acording to Desktop Resolution
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int32_t width  = availableSize.width();
    int32_t height = availableSize.height();
    QSize newSize( width, height );

    // Set new Geometry
    setGeometry(QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, newSize, qApp->desktop()->availableGeometry() ) );

    // Put Window to top of the screen
    this->topLevelWidget();
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

void MainWindow::MainWindow_Setup_QCustomPlot()
{
    ui->Testowy_wykres->addGraph(); // blue line
    ui->Testowy_wykres->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->Testowy_wykres->addGraph(); // red line
    ui->Testowy_wykres->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->Testowy_wykres->xAxis->setTicker(timeTicker);
    ui->Testowy_wykres->axisRect()->setupFullAxesBox();
    ui->Testowy_wykres->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->Testowy_wykres->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->Testowy_wykres->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->Testowy_wykres->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->Testowy_wykres->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
    connect(BT, SIGNAL(Parsed_Frame_OK()), this, SLOT(MainWindow_realtimeDataSlot()));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::MainWindow_realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    // add data to lines:
    ui->Testowy_wykres->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->Testowy_wykres->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    ui->Testowy_wykres->graph(0)->rescaleValueAxis();
    ui->Testowy_wykres->graph(1)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->Testowy_wykres->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->Testowy_wykres->replot();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
