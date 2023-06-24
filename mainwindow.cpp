#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QTimerEvent>

int refreshClock;
QSqlDatabase db;
int linegraphnum = 6;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshClock = startTimer(3600000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::MainWindowSwitchNode(int id){
//    QSqlQuery query(db);
//    query.exec("select * from air");
//    while(query.next())
//    {
//      qDebug()<<query.value("humidity").toDouble();
////      qDebug()<<query.value("nember").toDouble();
////      qDebug()<<query.value("teacher").toDouble();
//    }

//}

QSqlDatabase MainWindow::MainWindowConnectMysql(){
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
      qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        qDebug()<<"不能连接";
      return db;
    }
    else
    {
     qDebug()<<"连接成功"<<"connect to mysql OK";
    }
    return db;
}

SensorData MainWindow::MainWindowGetSensorData(int id){
    QSqlQuery query(db);
    SensorData myData;
    QString instuct = "select * from air where id=" + QString::number(id)+" and time = (select max(time) from air where id="+QString::number(id)+")";
    query.exec(instuct);

    while(query.next())
    {
        myData.time = query.value("time").toString();
        myData.id = query.value("id").toDouble();
        myData.humidity = query.value("humidity").toDouble();
        myData.temperature = query.value("temperature").toDouble();
        myData.pm25 = query.value("pm25").toDouble();
        myData.illumination = query.value("illumination").toDouble();
        myData.pm10 = query.value("pm10").toDouble();
        myData.atmosphere = query.value("atmosphere").toDouble();
        myData.wind_speed = query.value("wind_speed").toDouble();
        myData.wind_direction = query.value("wind_direction").toDouble();
    }
    return myData;
}

void MainWindow::MainWindowRefreshRealData(SensorData myData){
//    ui->comboBox_data->
    ui->label_date_val->setText(myData.time);
    ui->label_hum_val->setText(QString::number(myData.humidity,10,2));
    ui->label_temp_val->setText(QString::number(myData.temperature,10,2));
    ui->label_pm25_val->setText(QString::number(myData.pm25,10,2));
    ui->label_ill_val->setText(QString::number(myData.illumination,10,2));
    ui->label_pm10_val->setText(QString::number(myData.pm10,10,2));
    ui->label_atm_val->setText(QString::number(myData.atmosphere,10,2));
    ui->label_speed_val->setText(QString::number(myData.wind_speed,10,2));
    ui->label_direct_val->setText(QString::number(myData.wind_direction,10,2));
}

void MainWindow::timerEvent(QTimerEvent* event){
    if(event->timerId() == refreshClock){
        MainWindowRefreshRealData(MainWindowGetSensorData(ui->comboBox_node->currentIndex()));
        on_comboBox_data_activated(ui->comboBox_data->currentIndex());
    }
}

void MainWindow::on_comboBox_node_activated(int index)
{
    MainWindowRefreshRealData(this->MainWindowGetSensorData(index+2));

}

float historyData[6];

void MainWindow::on_comboBox_data_activated(int index)
{
    qDebug()<<"index "<<index;
    switch(index){
        case 0: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "humidity");break;
        case 1: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "temperature");break;
        case 2: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "pm25");break;
        case 3: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "illumination");break;
        case 4: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "pm10");break;
        case 5: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "atmosphere");break;
        case 6: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "wind_speed");break;
        case 7: MainWindowGetHistoryData(ui->comboBox_node->currentIndex()+2, "wind_direction");break;
        default:break;

    }

    int nowtime = (ui->label_date_val->text()[11].toLatin1()-48)*10+ui->label_date_val->text()[12].toLatin1()-48;
    int x[linegraphnum];
    for(int i= linegraphnum-1; i >= 0; --i){
        x[i] = nowtime - linegraphnum + i+1;
    }
    for(int i = 0; i < linegraphnum; ++i){
        qDebug()<<"mydata "<<x[i]<<','<<historyData[i];
    }
//    delete ui->LineGraph->chart;
//    ui->LineGraph->chart = new QChart();
    ui->LineGraph->RefreshLineGraph(x,historyData);
}


void MainWindow::MainWindowGetHistoryData(int id, QString kind){
    QSqlQuery query(db);
    SensorData myData;
    QString instuct = "select * from air where id=" + QString::number(id)+" order by time limit 6";
    qDebug()<<instuct+kind;
    query.exec(instuct);

    for(int i = 0; i <linegraphnum; ++i) historyData[i] = 0;
    int i = 0;
    while(query.next() && i < linegraphnum)
    {
        historyData[i++] = query.value(kind).toDouble();
    }
}

void MainWindow::MainWindowRefreshAllComponent(){
    MainWindowRefreshRealData(MainWindowGetSensorData(ui->comboBox_node->currentIndex()));
    on_comboBox_data_activated(ui->comboBox_data->currentIndex());
}
