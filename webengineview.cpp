#include "webengineview.h"
#include "ui_webengineview.h"

webengineview::webengineview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::webengineview)
{
    ui->setupUi(this);

}

webengineview::~webengineview()
{
    delete ui;
}
