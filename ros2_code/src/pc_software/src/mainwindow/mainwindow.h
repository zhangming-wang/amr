#pragma once
#include "../cameraWiget/camerawidget.h"
#include "../motionWidget/motionwidget.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

    void on_node_closed_sig();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    std::shared_ptr<Ui::MainWindow> ui;
    std::shared_ptr<CameraWidget> camera_widget_;
    std::shared_ptr<MotionWidget> motion_widget_;

    const QString CONFIG_FILE_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/" + "." + QCoreApplication::applicationName() + "/settings.json";

    // void _readConfigJson();
    // void _writeConfigJson();
};