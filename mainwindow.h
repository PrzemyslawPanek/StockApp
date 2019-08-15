#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <vector>
#include <map>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool uncheckRestButtons();

    QVector<double>getTimeForPlot();
    double getStartTime();
    auto getVolumePosBar();
    auto getVolumeNegBar();
    static void swapTimeIntervalValue (int swapValueForButton);
    int getTimeIntervalForButton();
    bool drawPlot();
    bool init_ploting();
    void showPointToolTip(QMouseEvent *event);




private slots:







    void on_threeYearsButton_clicked(bool checked);


    void on_twoYearsButton_clicked(bool checked);

    void on_oneYearButton_clicked(bool checked);

    void on_sixMonthButton_clicked(bool checked);

    void on_threeMonthsButton_clicked(bool checked);

    void on_oneMonthButton_clicked(bool checked);

    void on_oneWeekButton_clicked(bool checked);





private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
