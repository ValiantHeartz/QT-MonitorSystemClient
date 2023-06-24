#include "mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "ui_mainwindow.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include "mylinegraph.h"
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QStringList drivers = QSqlDatabase::drivers();
//    foreach(QString driver, drivers)
//        qDebug() << driver;
//    return a.exec();
//}

void connect_mysql()
{
    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("mytestbase");      //连接数据库名，与设置一致
    db.setUserName("root");          //数据库用户名，与设置一致
    db.setPassword("103220");    //数据库密码，与设置一致
    db.open();

    if(!db.open())
    {
//      qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        qDebug()<<"不能连接";
      return ;
    }
    else
    {
     qDebug()<<"连接成功"<<"connect to mysql OK";
    }
    QSqlQuery query(db);
    query.exec("select * from air");
    while(query.next())
    {
      qDebug()<<query.value("humidity").toString();
//      qDebug()<<query.value("nember").toString();
//      qDebug()<<query.value("teacher").toString();
    }
}

//QSqlDatabase db;
int num = 0;
int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    MainWindow w;
    w.MainWindowConnectMysql();
    w.MainWindowRefreshAllComponent();
//    SensorData myData = w.MainWindowGetSensorData(2);
//    w.MainWindowRefreshRealData(myData);
    w.show();
    return a.exec();
}
