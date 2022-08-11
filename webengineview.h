#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWidget>

namespace Ui {
class webengineview;
}

class webengineview : public QWidget
{
    Q_OBJECT

public:
    explicit webengineview(QWidget *parent = nullptr);
    ~webengineview();

private:
    Ui::webengineview *ui;
};

#endif // WEBENGINEVIEW_H
