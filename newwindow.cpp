#include "newwindow.h"
#include "ui_newwindow.h"
#include "global.h"
#include<QMessageBox>

#pragma execution_character_set("utf-8")

newWindow::newWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newWindow)
{
    ui->setupUi(this);
}

newWindow::~newWindow()
{
    delete ui;
}

void newWindow::on_ID_btn_clicked()
{
    QMessageBox::information(NULL, "ID卡号", "请将身份卡紧贴终端", QMessageBox::Yes);
    login_flag = true;
}


void newWindow::on_Face_btn_clicked()
{
    QMessageBox::information(NULL, "人像识别", "请正对摄像头", QMessageBox::Yes);
    login_flag = true;
}


