#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include "global.h"

namespace Ui {
class newWindow;
}

class newWindow : public QWidget
{
    Q_OBJECT

public:
    explicit newWindow(QWidget *parent = nullptr);
    ~newWindow();


private slots:
    void on_ID_btn_clicked();

    void on_Face_btn_clicked();

private:
    Ui::newWindow *ui;

};

#endif // NEWWINDOW_H
