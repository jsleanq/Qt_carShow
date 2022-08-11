#ifndef ERRORWIN_H
#define ERRORWIN_H

#include <QWidget>

namespace Ui {
class errorWin;
}

class errorWin : public QWidget
{
    Q_OBJECT

public:
    explicit errorWin(QWidget *parent = nullptr);
    ~errorWin();

private slots:
    void on_push_btn_clicked();

    void on_cancel_btn_clicked();

private:
    Ui::errorWin *ui;
};

#endif // ERRORWIN_H
