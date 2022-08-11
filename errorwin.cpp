#include "errorwin.h"
#include "ui_errorwin.h"
#include <QMessageBox>

#pragma execution_character_set("utf-8")

errorWin::errorWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::errorWin)
{
    ui->setupUi(this);
}

errorWin::~errorWin()
{
    delete ui;
}

void errorWin::on_push_btn_clicked()
{
     QMessageBox::information(NULL, "故障报修", "请求已发送，请稍候", QMessageBox::Yes);
}


void errorWin::on_cancel_btn_clicked()
{
    this->close();
}

