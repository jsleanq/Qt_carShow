#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //显示当前日期时间
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(time_update()));
    timer->start(1000); //1s执行一次,定时器

    //显示图标
    ui->sig1->setPixmap(QPixmap(":/new/prefix1/img/sig1.png"));
    ui->sig1->setScaledContents(true);

    ui->sig2->setPixmap(QPixmap(":/new/prefix1/img/sig2.png"));
    ui->sig2->setScaledContents(true);

    ui->sig3->setPixmap(QPixmap(":/new/prefix1/img/sig3.png"));
    ui->sig3->setScaledContents(true);

    ui->gps->setPixmap(QPixmap(":/new/prefix1/img/gps.png"));
    ui->gps->setScaledContents(true);

    ui->cloud->setPixmap(QPixmap(":/new/prefix1/img/cloud.png"));
    ui->cloud->setScaledContents(true);

    ui->power->setPixmap(QPixmap(":/new/prefix1/img/power.png"));
    ui->power->setScaledContents(true);

    ui->driver->setPixmap(QPixmap(":/new/prefix1/img/driver.jpg"));
    ui->driver->setScaledContents(true);

    ui->backgroud->setPixmap(QPixmap(":/new/prefix1/img/white_bg.png"));
    ui->backgroud->setScaledContents(true);

    ui->driver_video->setPixmap(QPixmap(":/new/prefix1/img/driver.jpg"));
    ui->driver_video->setScaledContents(true);

    ui->mask->setPixmap(QPixmap(":/new/prefix1/img/mask.png"));
    ui->mask->setScaledContents(true);

    ui->mask_2->setPixmap(QPixmap(":/new/prefix1/img/mask.png"));
    ui->mask_2->setScaledContents(true);

    //初始状态
    map_flag=false;
    ui->oil_btn->setEnabled(false);
    ui->error_btn->setEnabled(false);
    setLED(ui->led_r_input, 0, 16);
    setLED(ui->led_g_input, 0, 16);
    setLED(ui->led_r_out, 0, 16);
    setLED(ui->led_g_out, 0, 16);
    ui->input->setEnabled(false);
    ui->output->setEnabled(false);
    ui->func->setEnabled(false);


    //当前车速
    ui->speed->setText("0 km/h");
    //目的地
    ui->dest->setText("无");
    //剩余路程
    ui->leftroutie->setText("0");
    //矿石种类
    ui->type->setText("无");
    //当前载重
    ui->load->setText("0");
    //油量
    ui->oil->setText("60%");
    //矿石
    ui->mine->setText("无");
    //废石
    ui->trash->setText("无");

    //显示地图
    ui->geo_map->load(QUrl("E:/vs2019/QT_test/html/map.html"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//显示系统时间的功能
void MainWindow::time_update() {
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->time_weather->setText(str);

    QFont ft;
    ft.setPointSize(12);
    ui->time_weather->setFont(ft);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->time_weather->setPalette(pa);
}



void MainWindow::on_log_btn_clicked() {

    if(ui->log_btn->text() == "登录"){
        newWindow *logWin = new newWindow;
        logWin->show();

        //登录
        if(login_flag){
            //工作状态
            //目的地
            ui->dest->setText("等待指令");
            //剩余路程
            ui->leftroutie->setText("等待指令");
            //矿石种类
            ui->type->setText("等待指令");
            //当前载重
            ui->load->setText("等待指令");
            //矿石
            ui->mine->setText("等待指令");
            //废石
            ui->trash->setText("等待指令");
            //司机信息
            ui->car_num->setText("10325");
            ui->driver_name->setText("张三");

            ui->oil_btn->setEnabled(true);
            ui->error_btn->setEnabled(true);
            ui->log_btn->setText("退出");

            setLED(ui->led_r_input, 1, 16);
            setLED(ui->led_r_out, 1, 16);
            ui->input->setEnabled(true);
            ui->output->setEnabled(true);
            ui->func->setEnabled(true);


            ui->mask->hide();
            ui->mask_2->hide();

        }
    }else{
        //初始状态
        login_flag = false;
        map_flag=false;
        ui->oil_btn->setEnabled(false);
        ui->error_btn->setEnabled(false);


        //当前车速
        ui->speed->setText("0 km/h");
        //目的地
        ui->dest->setText("无");
        //剩余路程
        ui->leftroutie->setText("0");
        //矿石种类
        ui->type->setText("无");
        //当前载重
        ui->load->setText("0");
        //油量
        ui->oil->setText("60%");
        //矿石
        ui->mine->setText("无");
        //废石
        ui->trash->setText("无");

        ui->log_btn->setText("登录");

        setLED(ui->led_r_input, 0, 16);
        setLED(ui->led_r_out, 0, 16);
        ui->input->setEnabled(false);
        ui->output->setEnabled(false);
        ui->func->setEnabled(false);

        ui->mask->show();
        ui->mask_2->show();
    }
}


void MainWindow::on_error_btn_clicked()
{
    errorWin *errorWindow = new errorWin;
    errorWindow->show();
}


void MainWindow::on_oil_btn_clicked()
{
    QMessageBox::information(NULL, "请求加油", "请求已发送，请稍候", QMessageBox::Yes);
}



void MainWindow::on_input_clicked() {

    input_flag = !input_flag;
    if (input_flag) {
        ui->output->setEnabled(false);
        setLED(ui->led_g_input, 2, 16);
        setLED(ui->led_r_input, 0, 16);
    }
    else{
        ui->output->setEnabled(true);
        setLED(ui->led_g_input, 0, 16);
        setLED(ui->led_r_input, 1, 16);
    }

}


void MainWindow::on_output_clicked()
{
     output_flag = !output_flag;
    if (output_flag) {
        ui->input->setEnabled(false);
        setLED(ui->led_g_out, 2, 16);
        setLED(ui->led_r_out, 0, 16);
    }
    else{
        ui->input->setEnabled(true);
        setLED(ui->led_g_out, 0, 16);
        setLED(ui->led_r_out, 1, 16);
    }
}


void MainWindow::on_func_clicked()
{
    this->func_flag = true;
    exjson();
}

void MainWindow::exjson(){
    // ---> 解包json
       QFile jsfile("E:/vs2019/QT_test/func_1.json");
       if(jsfile.open(QIODevice::ReadOnly)){
           // ---> 设置解析报错
           QJsonParseError err;
           // ---> 解释json文件
           QJsonDocument jsdoc = QJsonDocument::fromJson(jsfile.readAll(), &err);

           if(err.error!=QJsonParseError::NoError){
               // ---> 如果有报错
               qDebug("json 格式错误！");
               return;
           } else {
               // ---> 读取根目录
               QJsonObject rootObj = jsdoc.object();
               // ---> 读取 目的地 的值

               ui->dest->setText(rootObj.value("dest").toString());
               ui->leftroutie->setText(rootObj.value("leftroutie").toString());
               ui->type->setText(rootObj.value("type").toString());
               ui->load->setText(rootObj.value("load").toString());
               ui->mine->setText(rootObj.value("mine").toString());
               ui->trash->setText(rootObj.value("trash").toString());
               /*
               QJsonArray Points = rootObj.value("data").toArray();
               ui->dest->setText(Points.at(1).toString());
               */
           }
           jsfile.close();
       }
}

