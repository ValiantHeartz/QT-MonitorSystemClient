#ifndef MYLINEGRAPH_H
#define MYLINEGRAPH_H

//#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>




//class MyLineGraph : public QMainWindow
//{
//    Q_OBJECT
//public:
//    explicit MyLineGraph(QWidget *parent = nullptr);
//    MyLineGraph(const MyLineGraph &);
//    MyLineGraph &operator=(const MyLineGraph &);
//    ~MyLineGraph();

//signals:


//private:
//    QSharedDataPointer<MyLineGraphData> data;
//};

QT_CHARTS_USE_NAMESPACE
class MyLineGraph : public QChartView
{
    Q_OBJECT
public:
    explicit MyLineGraph(QWidget *parent = nullptr);
    void RefreshLineGraph(int x[], float y[]);
    static int x;
signals:

public slots:
public:
     QLineSeries *series;
     QChart *chart;
     QChartView *chartView;
     QValueAxis *axisX1;
     QValueAxis *axisY1;

};

#endif // MYLINEGRAPH_H
