#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct SensorData{
    QString time;
    double id;
    double humidity;
    double temperature;
    double pm25;
    double illumination;
    double pm10;
    double atmosphere;
    double wind_speed;
    double wind_direction;
};

struct HistoryData{
    double data1;
    double data2;
    double data3;
    double data4;
    double data5;
    double data6;
};

//enum SensorKind {

extern int refreshClock;
extern QSqlDatabase db;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    void MainWindowSwitchNode(int id);
    QSqlDatabase MainWindowConnectMysql();
    SensorData MainWindowGetSensorData(int id);
    void MainWindowGetHistoryData(int id, QString kind);
    void MainWindowRefreshRealData(SensorData myData);
    void MainWindowRefreshAllComponent();
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent* event);

private slots:
    void on_comboBox_node_activated(int index);

    void on_comboBox_data_activated(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
