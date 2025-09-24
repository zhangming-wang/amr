#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common/enum.h"
#include "http_client/httpClient.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onHttpStatusChanged(bool connect);
    void onRecvData(QJsonObject jsonData);
    void onSetMotionMode();

    void _updateSPeedPercentLabel(double percent);

    bool update_ui_ = false;

    HttpClient *httpClient_;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
