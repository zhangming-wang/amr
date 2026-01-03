#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(std::make_shared<Ui::MainWindow>()) {
    ui->setupUi(this);
    setWindowTitle("差速小车控制系统");

    camera_widget_ = std::make_shared<CameraWidget>();
    motion_widget_ = std::make_shared<MotionWidget>();

    connect(camera_widget_.get(), &CameraWidget::nodeClosed, this, &MainWindow::on_node_closed_sig);
    connect(motion_widget_.get(), &MotionWidget::nodeClosed, this, &MainWindow::on_node_closed_sig);

    connect(ui->action_cascade, &QAction::triggered, ui->mdiArea, &QMdiArea::cascadeSubWindows);
    connect(ui->action_tile, &QAction::triggered, ui->mdiArea, &QMdiArea::tileSubWindows);

    auto subWin = ui->mdiArea->addSubWindow(motion_widget_.get());
    subWin->setWindowFlags(Qt::SubWindow | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    subWin = ui->mdiArea->addSubWindow(camera_widget_.get());
    subWin->setWindowFlags(Qt::SubWindow | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    camera_widget_->show();
    motion_widget_->show();
    // 平铺 MDI 区域中的所有子窗口
    ui->mdiArea->tileSubWindows();
}

MainWindow::~MainWindow() {
}
void MainWindow::closeEvent(QCloseEvent *event) {
    // if (rclcpp::ok()) {
    //     try {
    //         rclcpp::shutdown();
    //     } catch (const std::exception &e) {
    //         qWarning() << "Error during ROS shutdown:" << e.what();
    //     }
    // }

    event->accept();                // 明确接受事件
    QMainWindow::closeEvent(event); // 调用父类逻辑，释放资源
}
void MainWindow::on_node_closed_sig() {
    QTimer::singleShot(100, [this]() {
        qApp->quit(); // 延迟100ms后退出应用
    });
}

// void MainWindow::_readConfigJson() {
//     QFile file(CONFIG_FILE_PATH);
//     if (file.exists()) {
//         if (!file.open(QIODevice::ReadOnly)) {
//             QMessageBox::critical(this, "错误", "读取配置文件失败");
//             return;
//         }

//         QByteArray data = file.readAll();
//         file.close();

//         QJsonParseError error;
//         QJsonDocument doc = QJsonDocument::fromJson(data, &error);
//         if (error.error != QJsonParseError::NoError) {
//             QMessageBox::critical(this, "错误", "读取配置文件失败");
//             return;
//         }

//         if (!doc.isObject()) {
//             QMessageBox::critical(this, "错误", "读取配置文件失败");
//             return;
//         }

//         QJsonObject obj = doc.object();
//         ui->doubleSpinBox_p->setValue(obj["p"].toDouble());
//         ui->doubleSpinBox_i->setValue(obj["i"].toDouble());
//         ui->doubleSpinBox_d->setValue(obj["d"].toDouble());
//         ui->doubleSpinBox_max_total_integral->setValue(obj["max_total_i"].toDouble());
//         ui->spinBox_millseconds->setValue(obj["millseconds"].toInt());
//         ui->doubleSpinBox_max_v->setValue(obj["max_v"].toDouble());
//         ui->doubleSpinBox_max_acc->setValue(obj["max_acc"].toDouble());
//         ui->doubleSpinBox_jerk->setValue(obj["jerk"].toDouble());
//     }
// }

// void MainWindow::_writeConfigJson() {
//     QJsonObject obj;
//     obj["p"] = ui->doubleSpinBox_p->value();
//     obj["i"] = ui->doubleSpinBox_i->value();
//     obj["d"] = ui->doubleSpinBox_d->value();
//     obj["max_total_i"] = ui->doubleSpinBox_max_total_integral->value();
//     obj["millseconds"] = ui->spinBox_millseconds->value();
//     obj["max_v"] = ui->doubleSpinBox_max_v->value();
//     obj["max_acc"] = ui->doubleSpinBox_max_acc->value();
//     obj["jerk"] = ui->doubleSpinBox_jerk->value();

//     QJsonDocument doc(obj);

//     QString configFolder = QFileInfo(CONFIG_FILE_PATH).absolutePath();
//     QDir dir(configFolder);
//     if (!dir.exists()) {
//         dir.mkpath("."); // 创建目录
//     }

//     QFile file(CONFIG_FILE_PATH);
//     if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
//         QMessageBox::critical(this, "错误", "写入配置文件失败");
//         return;
//     }
//     file.write(doc.toJson(QJsonDocument::Indented)); // 或 Compact
//     file.close();
// }
