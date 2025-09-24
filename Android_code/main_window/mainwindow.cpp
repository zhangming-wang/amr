#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      httpClient_(new HttpClient(this)) {
    ui->setupUi(this);

    connect(ui->pushButton_move_front, &QPushButton::clicked, httpClient_, &HttpClient::moveFront);
    connect(ui->pushButton_move_back, &QPushButton::clicked, httpClient_, &HttpClient::moveBack);
    connect(ui->pushButton_move_left, &QPushButton::clicked, httpClient_, &HttpClient::moveLeft);
    connect(ui->pushButton_move_right, &QPushButton::clicked, httpClient_, &HttpClient::moveRight);
    connect(ui->pushButton_stop_move, &QPushButton::clicked, httpClient_, &HttpClient::stopMove);
    connect(ui->pushButton_brake, &QPushButton::clicked, httpClient_, &HttpClient::brake);
    connect(ui->pushButton_restart, &QPushButton::clicked, httpClient_, &HttpClient::restart);
    connect(ui->pushButton_save, &QPushButton::clicked, httpClient_, &HttpClient::save);
    connect(ui->pushButton_refresh, &QPushButton::clicked, [this]() { update_ui_ = true; });

    connect(ui->radioButton_no_balance, &QRadioButton::clicked, this, &MainWindow::onSetMotionMode);
    connect(ui->radioButton_static_balance, &QRadioButton::clicked, this, &MainWindow::onSetMotionMode);
    connect(ui->radioButton_dynamic_balance, &QRadioButton::clicked, this, &MainWindow::onSetMotionMode);

    // connect(ui->horizontalSlider_speed_percent, &QSlider::sliderPressed, this, [this]() {
    //     httpClient_->stop_timer();
    // });
    connect(ui->horizontalSlider_speed_percent, &QSlider::sliderReleased, this, [this]() {
        auto percent = ui->horizontalSlider_speed_percent->value() * 1.0 / ui->horizontalSlider_speed_percent->maximum();
        httpClient_->setSpeedPercent(percent);
        // httpClient_->start_timer();
    });
    connect(ui->horizontalSlider_speed_percent, &QSlider::valueChanged, this, [this](int value) {
        auto percent = value * 1.0 / ui->horizontalSlider_speed_percent->maximum();
        _updateSPeedPercentLabel(percent);
    });
    ui->horizontalSlider_speed_percent->setStyleSheet(R"(
        QSlider::groove:horizontal {
            height: 8px;
            background: #ccc;
            border-radius: 4px;
        }

        QSlider::handle:horizontal {
            background: #0078d7;
            border: 1px solid #5c5c5c;
            width: 30px;         /* 滑块宽度 */
            height: 30px;        /* 滑块高度 */
            margin: -8px 0;      /* 让滑块垂直居中 */
            border-radius: 10px; /* 圆角滑块 */
        }

        QSlider::add-page:horizontal {
            background: #aaa;
        }

        QSlider::sub-page:horizontal {
            background: #0078d7;
        })");

    connect(httpClient_, &HttpClient::sendConnectStatus, this, &MainWindow::onHttpStatusChanged);
    connect(httpClient_, &HttpClient::sendData, this, &MainWindow::onRecvData);

    httpClient_->start_timer();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onHttpStatusChanged(bool connect) {
    if (connect) {
        ui->label_connect_status->setStyleSheet(QString("background-color:green;color:white;font-size:%1px;").arg(this->font().pointSize()));
        ui->label_connect_status->setText("已连接");
        setEnabled(true);
        update_ui_ = true;
    } else {
        ui->label_connect_status->setStyleSheet(QString("background-color:red; color:white; font-size:%1px;").arg(this->font().pointSize()));
        ui->label_connect_status->setText("已断开");
        setEnabled(false);
    }
}
void MainWindow::onRecvData(QJsonObject jsonData) {
    if (update_ui_) {
        if (jsonData.keys().contains("motion_mode")) {
            auto mode = jsonData["motion_mode"].toInt();
            ui->radioButton_no_balance->blockSignals(true);
            ui->radioButton_static_balance->blockSignals(true);
            ui->radioButton_dynamic_balance->blockSignals(true);
            if (mode == MotionMode::NoBalanceMode) {
                ui->radioButton_no_balance->click();
            } else if (mode == MotionMode::StaticBalanceMode) {
                ui->radioButton_static_balance->click();
            } else if (mode == MotionMode::DynamicBalanceMode) {
                ui->radioButton_dynamic_balance->click();
            }
            ui->radioButton_no_balance->blockSignals(false);
            ui->radioButton_static_balance->blockSignals(false);
            ui->radioButton_dynamic_balance->blockSignals(false);
        }
        if (jsonData.keys().contains("speed_percent")) {
            auto percent = jsonData["speed_percent"].toDouble();
            ui->horizontalSlider_speed_percent->blockSignals(true);
            ui->horizontalSlider_speed_percent->setValue(percent * ui->horizontalSlider_speed_percent->maximum());
            ui->horizontalSlider_speed_percent->blockSignals(false);
            _updateSPeedPercentLabel(percent);
        }
        update_ui_ = false;
    }

    if (jsonData.keys().contains("current_v") && jsonData.keys().contains("current_w") && jsonData.keys().contains("current_x") && jsonData.keys().contains("current_y") && jsonData.keys().contains("current_angle")) {
        QString text = QString(
                           "速度:\n"
                           "    v = %1 m/s\n"
                           "    w = %2 rad/s\n"
                           "位置:\n"
                           "    x = %3 m\n"
                           "    y = %4 m\n"
                           "角度:\n"
                           "    z = %5 °")
                           .arg(jsonData["current_v"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["current_w"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["current_x"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["current_y"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["current_angle"].toDouble(), 9, 'f', 2);
        ui->label_motion_status->setText(text);
    }
    if (jsonData.keys().contains("yaw") && jsonData.keys().contains("pitch") && jsonData.keys().contains("roll") && jsonData.keys().contains("gyro_x") && jsonData.keys().contains("gyro_y") && jsonData.keys().contains("gyro_z")) {
        QString text = QString(
                           "姿态角:\n"
                           "    偏航角 : %1 °\n"
                           "    俯仰角 : %2 °\n"
                           "    横滚角 : %3 °\n"
                           "角速度:\n"
                           "    X轴 : %4 °/s\n"
                           "    Y轴 : %5 °/s\n"
                           "    Z轴 : %6 °/s")
                           .arg(jsonData["yaw"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["pitch"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["roll"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["gyro_x"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["gyro_y"].toDouble(), 9, 'f', 3)
                           .arg(jsonData["gyro_z"].toDouble(), 9, 'f', 3);
        ui->label_mpu_status->setText(text);
    }
}

void MainWindow::onSetMotionMode() {
    if (ui->radioButton_no_balance->isChecked()) {
        httpClient_->setMotionMode(0);
    } else if (ui->radioButton_static_balance->isChecked()) {
        httpClient_->setMotionMode(1);
    } else if (ui->radioButton_dynamic_balance->isChecked()) {
        httpClient_->setMotionMode(2);
    }
}

void MainWindow::_updateSPeedPercentLabel(double percent) {
    ui->label_speed_percent->setText(QString::number(percent * 100, 'f', 1) + "%");
}
