#include "parser.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// generate variables/instances for plot
#define binSize 3600*24 // bin data in 1 day intervals
static int timeInterval=50; // global varible for change plot interval

QCPBars *volumePos;
QCPBars *volumeNeg;
QCPFinancial *candlesticks;
int day,month,year;

QVector<double> MainWindow::getTimeForPlot()
{
    QVector<double> timeForPlot(parser::getSizeOfPlot()), value1(parser::getSizeOfPlot()), value2(parser::getSizeOfPlot());
    return timeForPlot;
}

double MainWindow::getStartTime()
{

    QDateTime start = QDateTime(QDate(year, month, day+2));
    double startTime = start.toTime_t();
    start.setTimeSpec(Qt::UTC);
    return startTime;
}
// two functions, first for put timeInterval into plot, second for swap timeInterval by buttons
int MainWindow::getTimeIntervalForButton()
{
    return timeInterval;
}

void MainWindow::swapTimeIntervalValue(int swapValueForButton)
{
    timeInterval=swapValueForButton;
}
// make buttons unchecked
bool MainWindow::uncheckRestButtons()
{
    if (true)
    {
        ui->threeYearsButton->setChecked(false);
        ui->twoYearsButton->setChecked(false);
        ui->oneYearButton->setChecked(false);
        ui->sixMonthButton->setChecked(false);
        ui->threeMonthsButton->setChecked(false);
        ui->oneMonthButton->setChecked(false);
        ui->oneWeekButton->setChecked(false);
    }
    return false;
}
// actions for buttons
void MainWindow::on_threeYearsButton_clicked(bool checked)
{
    uncheckRestButtons();
    ui->threeYearsButton->setChecked(true);
    if(parser::getSizeOfPlot()>1095)
    {
        swapTimeIntervalValue(1095);
    }
    else
    {
        swapTimeIntervalValue(500);
    }
    drawPlot();
    ui->plotWindow->replot();
}

void MainWindow::on_twoYearsButton_clicked(bool checked)
{
    uncheckRestButtons();
    ui->twoYearsButton->setChecked(true);
    if(parser::getSizeOfPlot()>730)
    {
        swapTimeIntervalValue(730);
    }
    else
    {
        swapTimeIntervalValue(400);
    }
    drawPlot();
    ui->plotWindow->replot();
}

void MainWindow::on_oneYearButton_clicked(bool checked)
{
    uncheckRestButtons();
     ui->oneYearButton->setChecked(true);
     if(parser::getSizeOfPlot()>365)
     {
         swapTimeIntervalValue(365);
     }
     else
     {
         swapTimeIntervalValue(parser::getSizeOfPlot());
     }
     drawPlot();
     ui->plotWindow->replot();
}

void MainWindow::on_sixMonthButton_clicked(bool checked)
{
    uncheckRestButtons();
    ui->sixMonthButton->setChecked(true);
    if(parser::getSizeOfPlot()>180)
    {
        swapTimeIntervalValue(180);
    }
    else
    {
        swapTimeIntervalValue(parser::getSizeOfPlot());
    }
    drawPlot();
    ui->plotWindow->replot();
}

void MainWindow::on_threeMonthsButton_clicked(bool checked)
{
    uncheckRestButtons();
    ui->threeMonthsButton->setChecked(true);
    swapTimeIntervalValue(90);
    drawPlot();
    ui->plotWindow->replot();
}

void MainWindow::on_oneMonthButton_clicked(bool checked)
{
    uncheckRestButtons();
    ui->oneMonthButton->setChecked(true);
    swapTimeIntervalValue(30);
    drawPlot();
    ui->plotWindow->replot();

}

void MainWindow::on_oneWeekButton_clicked(bool checked)
{
    uncheckRestButtons();
    ui->oneWeekButton->setChecked(true);
    swapTimeIntervalValue(7);
    drawPlot();
    ui->plotWindow->replot();
}

bool MainWindow::drawPlot()
{
    QVector <parser::quoteValues> vectorOfMapForPlot =parser::getVctQuoteValues();
    int interval = getTimeIntervalForButton();
    double startTime = getStartTime();

    candlesticks->data()->clear();
    for(int i=0;i<=parser::getSizeOfPlot();i++)
    {
        if (i >= interval)
        {
            break;
        }
        auto it = &vectorOfMapForPlot[i];
        candlesticks->addData(startTime + (binSize*i), it->open,it->higest, it->lowest, it->close);
    }

    volumeNeg->data()->clear();
    volumePos->data()->clear();
    for(int i=0;i<=parser::getSizeOfPlot();i++)
    {
        if (i >= interval)
        {
            break;
        }
        auto it = &vectorOfMapForPlot[i];
        if(it->open <= it->close)
        {
            volumeNeg->addData(startTime + (binSize*i),it->close);
        }
        else
        {
            volumePos->addData(startTime + (binSize*i),it->close);
        }
    }
    ui->plotWindow->rescaleAxes();
    ui->plotWindow->xAxis->scaleRange(1.025, ui->plotWindow->xAxis->range().center());
    ui->plotWindow->yAxis->scaleRange(0.9, ui->plotWindow->yAxis->range().center());
    return false;
}

// core app method
bool MainWindow::init_ploting()
{
    if(true)
    {
        // clear previous plot
        ui->plotWindow->clearPlottables();
        // assign containers for plot
        map<string, vector<parser::quoteValues>> mapQuoteValuesForPlot;
        QVector <parser::quoteValues> vectorOfMapForPlot = parser::getVctQuoteValues();
        QVector<double> timeForPlot = getTimeForPlot();

         // we dont need a legend
         ui->plotWindow->legend->setVisible(false);
         // colors
         QColor pen_color(56, 75, 107);
         QColor axis_color(107,126,158);
         // background color
         ui->plotWindow->setBackground(QBrush(QColor("#20334d")));
         // set grid color and layer
         QCPGrid *volumeCandlesickX = new QCPGrid(ui->plotWindow->xAxis);
         QCPGrid *volumeCandlesickY = new QCPGrid(ui->plotWindow->yAxis);
         volumeCandlesickX->setPen(pen_color);
         volumeCandlesickY->setPen(pen_color);
         volumeCandlesickX->setLayer("belowmain");

         // we dont need status bar
         ui->statusBar->hide();
         // create bottom axis rect for volume bar chart and set grid
         QCPAxisRect *volumeAxisRect = new QCPAxisRect(ui->plotWindow);
         QCPGrid *volumeGridBottom = new QCPGrid (volumeAxisRect->axis(QCPAxis::atBottom));
         QCPGrid *volumeGridLeft = new QCPGrid (volumeAxisRect->axis(QCPAxis::atLeft));
         volumeGridLeft->setPen(pen_color);
         volumeGridBottom->setPen(pen_color);
         ui->plotWindow->plotLayout()->addElement(1, 0, volumeAxisRect);
         volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 130));
         volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
         volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
         // colors for bot
         volumeAxisRect->axis(QCPAxis::atBottom)->setBasePen(pen_color);
         volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelColor(axis_color);
         volumeAxisRect->axis(QCPAxis::atBottom)->setSubTickPen(pen_color);
         volumeAxisRect->axis(QCPAxis::atBottom)->setTickPen(pen_color);
         //colors for left
         volumeAxisRect->axis(QCPAxis::atLeft)->setBasePen(pen_color);
         volumeAxisRect->axis(QCPAxis::atLeft)->setTickLabelColor(axis_color);
         volumeAxisRect->axis(QCPAxis::atLeft)->setSubTickPen(pen_color);
         volumeAxisRect->axis(QCPAxis::atLeft)->setTickPen(pen_color);
         // bring bottom and main axis rect closer together:
         ui->plotWindow->plotLayout()->setRowSpacing(10);
         volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
         volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
         // create and fill two bar plottables, for positive and negative volume bars:
         ui->plotWindow->setAutoAddPlottableToLegend(false);
         volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
         volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));

         // clolors/width for volume positive and negative
         volumePos->setWidth(binSize*0.7);
         volumePos->setPen(QColor(43,103,112));
         volumePos->setBrush(QColor(40, 90, 103));
         volumeNeg->setWidth(binSize*0.7);
         volumeNeg->setPen(QColor(102,53,71));
         volumeNeg->setBrush(QColor(100, 50, 69));
         // interconnect x axis ranges of main and bottom axis rects
         connect(ui->plotWindow->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
         connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), ui->plotWindow->xAxis, SLOT(setRange(QCPRange)));
         // configure axes of both main and bottom axis rect
         QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
         dateTimeTicker->setDateTimeSpec(Qt::UTC);
         dateTimeTicker->setDateTimeFormat("dd. mm. yy");
         dateTimeTicker->dateTimeToKey(QDate(2018, 11, 16));
         ui->plotWindow->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDate(2013, 11, 16)), QCPAxisTickerDateTime::dateTimeToKey(QDate(2015, 5, 2)));
         volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
         volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
         // colors/scale for xAxis and yAxis
         ui->plotWindow->xAxis->setBasePen(Qt::NoPen);
         ui->plotWindow->yAxis->setBasePen(QColor(pen_color));
         ui->plotWindow->yAxis->setTickPen(QColor(pen_color));
         ui->plotWindow->xAxis->setTickPen(QColor(pen_color));
         ui->plotWindow->yAxis->setSubTickPen(pen_color);
         ui->plotWindow->xAxis->setSubTickPen(pen_color);
         ui->plotWindow->xAxis->setTickLabelColor(axis_color);
         ui->plotWindow->yAxis->setTickLabelColor(axis_color);
         ui->plotWindow->xAxis->setTickLabels(false);
         ui->plotWindow->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
         ui->plotWindow->xAxis->setTicker(dateTimeTicker);
         ui->plotWindow->rescaleAxes();
         ui->plotWindow->xAxis->scaleRange(1.025, ui->plotWindow->xAxis->range().center());
         ui->plotWindow->yAxis->scaleRange(0.9, ui->plotWindow->yAxis->range().center());
         // make axis rects left side line up
         QCPMarginGroup *group = new QCPMarginGroup(ui->plotWindow);
         ui->plotWindow->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
         volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);
         // margin for buttons
         ui->plotWindow->axisRect()->setMinimumMargins(QMargins(0,60,0,0));
         // style for pushButtons
         qApp->setStyleSheet("QPushButton:hover:!pressed {font-weight:bold; font-size:12px; font-family:Arial; background-color:#2b405b; color:#9DABB5;}"
                             "QPushButton:unchecked {font-weight:bold; font-size:12px; font-family:Arial; border: 0px; background-color:red; color:#9DABB5;}"
                             "QPushButton:enabled {font-weight:bold; font-size:12px; font-family:Arial; border: 0px; background-color:#20334d; color:#9DABB5;}"
                             "QPushButton:checked {font-weight:bold; font-size:12px; font-family:Arial; background-color:#31496A; color:#9DABB5;}"
                             "QPushButton:checked:hover {font-weight:bold; font-size:12px; font-family:Arial; background-color:#31496A; color:#9DABB5;}"
                             "QPushButton:pressed {font-weight:bold; font-size:12px; font-family:Arial; background-color:#2c425e; color:#9DABB5;}"
                            );
         //Very bad code because i dont have time
         if (QMainWindow::isFullScreen()==true)
         {
             ui->threeYearsButton->resize(61,46);
             ui->twoYearsButton->resize(61,46);
             ui->twoYearsButton->move(81,0);
             ui->oneYearButton->resize(61,46);
             ui->oneYearButton->move(142,0);
             ui->sixMonthButton->resize(61,46);
             ui->sixMonthButton->move(203,0);
             ui->threeMonthsButton->resize(61,46);
             ui->threeMonthsButton->move(264,0);
             ui->oneMonthButton->resize(61,46);
             ui->oneMonthButton->move(325,0);
             ui->oneWeekButton->resize(61,46);
             ui->oneWeekButton->move(386,0);
             QFont f("Arial",10);
             ui->plotWindow->yAxis->setTickLabelFont(f);
             ui->plotWindow->xAxis->setTickLabelFont(f);
             volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelFont(f);
             volumeAxisRect->axis(QCPAxis::atLeft)->setTickLabelFont(f);
             qApp->setStyleSheet("QPushButton:hover:!pressed {font-weight:bold; font-size:16px; font-family:Arial; background-color:#2b405b; color:#9DABB5;}"
                                 "QPushButton:unchecked {font-weight:bold; font-size:16px; font-family:Arial; border: 0px; background-color:red; color:#9DABB5;}"
                                 "QPushButton:enabled {font-weight:bold; font-size:16px; font-family:Arial; border: 0px; background-color:#20334d; color:#9DABB5;}"
                                 "QPushButton:checked {font-weight:bold; font-size:16px; font-family:Arial; background-color:#31496A; color:#9DABB5;}"
                                 "QPushButton:checked:hover {font-weight:bold; font-size:16px; font-family:Arial; background-color:#31496A; color:#9DABB5;}"
                                 "QPushButton:pressed {font-weight:bold; font-size:16px; font-family:Arial; background-color:#2c425e; color:#9DABB5;}"
                                );
         }
    }
    // create and configure candlesticks
    candlesticks = new QCPFinancial(ui->plotWindow->xAxis, ui->plotWindow->yAxis);
    candlesticks->setWidth(binSize*0.7);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(62, 202, 177));
    candlesticks->setBrushNegative(QColor(254, 71, 97));
    candlesticks->setPenPositive(QPen(QColor(62, 202, 177)));
    candlesticks->setPenNegative(QPen(QColor(254, 71, 97)));
    candlesticks->setLayer("abovemain");
    candlesticks->setName("Candlestick");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    ui->plotWindow->replot();
    return false;
}


void MainWindow::showPointToolTip(QMouseEvent *event)
{
    int x = ui->plotWindow->xAxis->pixelToCoord(event->pos().x());
    int y = ui->plotWindow->yAxis->pixelToCoord(event->pos().y());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //common actions
    ui->setupUi(this);
    QMainWindow::showFullScreen();
    parser ob;
    ob.loadFromFile();
    //layers priority
    ui->plotWindow->addLayer("abovemain", ui->plotWindow->layer("main"), QCustomPlot::limAbove);
    ui->plotWindow->addLayer("belowmain", ui->plotWindow->layer("main"), QCustomPlot::limBelow);
    QVBoxLayout *fullScreenLayout = new QVBoxLayout;
    fullScreenLayout->setContentsMargins(0, 0, 0, 0);
    this->centralWidget()->setLayout(fullScreenLayout);
    fullScreenLayout->addWidget(ui->plotWindow);
    //make drag and zoom
    ui->plotWindow->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    init_ploting();
    drawPlot();
    //
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));

}
MainWindow::~MainWindow()
{
    delete ui;
}




