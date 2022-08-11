#ifndef OILWINDOW_H
#define OILWINDOW_H

#include <QWidget>

namespace Ui {
class oilWindow;
}

class oilWindow : public QWidget
{
    Q_OBJECT

public:
    explicit oilWindow(QWidget *parent = nullptr);
    ~oilWindow();

private:
    Ui::oilWindow *ui;
};

#endif // OILWINDOW_H
