#include "mylinegraph.h"
#include <QDebug>
//class MyLineGraphData : public QSharedData
//{
//public:

//};

//MyLineGraph::MyLineGraph(QWidget *parent)
//    : QMainWindow{parent}, data(new MyLineGraphData)
//{

//}

//MyLineGraph::MyLineGraph(const MyLineGraph &rhs)
//    : data{rhs.data}
//{

//}

//MyLineGraph &MyLineGraph::operator=(const MyLineGraph &rhs)
//{
//    if (this != &rhs)
//        data.operator=(rhs.data);
//    return *this;
//}

//MyLineGraph::~MyLineGraph()
//{

//}

MyLineGraph::MyLineGraph(QWidget *parent) : QChartView(parent)
{
    series = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
    axisX1 = new QValueAxis();
    axisY1 = new QValueAxis();
    for(int i = 0; i < 6; ++i){
        series->append(0, 0);
    }
}


void MyLineGraph::RefreshLineGraph(int x[], float y[]){
    chart->removeSeries(series);
//    chart = new QChart();
    //series = new QLineSeries();
    QVector<QPointF> Points;
    for(int i = 0; i < 6; ++i){
        Points.append({qreal(x[i]), qreal(int(y[i]))});
        qDebug()<<"qreal"<<qreal(x[i])<<qreal(int(y[i]));
        series->replace(Points);
    }
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    //给ｃｈａｒｔ添加坐标轴
//    //设置ｘ轴
//    axisX1->setTitleText("时间");
////    axisX1->setLabelFormat("%i");
//    axisX1->setTickCount(1);         //多少刻度
////    axisX1->setRange(0,23);		     //刻度范围
//    chart->addAxis(axisX1,Qt::AlignBottom); //把ｘ坐标轴加到底部
//    //设置ｙ轴
//    axisY1->setTitleText("监测值");
////    axisY1->setLabelFormat("%i");
////    axisY1->setTickCount(5);
//    axisY1->setRange(0,80);
//    chart->addAxis(axisY1,Qt::AlignLeft);  //把Y坐标轴加到左侧

    chart->setTitle("6小时数据图");
//    *series << QPointF(11,2) << QPointF(15,5) << QPointF(18,4) << QPointF(19,2);
    chartView->setRenderHint(QPainter::Antialiasing);
    this->setChart(chart);//添加到界面中
    this->setRenderHint(QPainter::Antialiasing);//抗锯齿渲染
}
