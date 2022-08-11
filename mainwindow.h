#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newwindow.h"
#include "errorwin.h"
#include "Led.h"
#include <QTimer>
#include <QDateTime>
#include <QtWebEngineWidgets>
#include <QDebug>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void exjson();

private slots:
    void time_update(void);

    void on_log_btn_clicked();

    void on_error_btn_clicked();

    void on_oil_btn_clicked();

    void on_input_clicked();

    void on_output_clicked();

    void on_func_clicked();

private:
    Ui::MainWindow *ui;

    bool func_flag;//调度方案信号

    bool map_flag;//地图更新信号

};
#endif // MAINWINDOW_H
