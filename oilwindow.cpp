#include "oilwindow.h"
#include "ui_oilwindow.h"

oilWindow::oilWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oilWindow)
{
    ui->setupUi(this);
}

oilWindow::~oilWindow()
{
    delete ui;
}
