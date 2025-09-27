#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      httpClient_(new HttpClient(this)) {
    ui->setupUi(this);

    connect(ui->pushButton_move_front, &QPushButton::clicked, httpClient_, &HttpClient::move_front);
    connect(ui->pushButton_move_back, &QPushButton::clicked, httpClient_, &HttpClient::move_back);
    connect(ui->pushButton_move_left, &QPushButton::clicked, httpClient_, &HttpClient::move_left);
    connect(ui->pushButton_move_right, &QPushButton::clicked, httpClient_, &HttpClient::move_right);
    connect(ui->pushButton_move_left_front, &QPushButton::clicked, httpClient_, &HttpClient::move_left_front);
    connect(ui->pushButton_move_right_front, &QPushButton::clicked, httpClient_, &HttpClient::move_right_front);
    connect(ui->pushButton_move_left_back, &QPushButton::clicked, httpClient_, &HttpClient::move_left_back);
    connect(ui->pushButton_move_right_back, &QPushButton::clicked, httpClient_, &HttpClient::move_right_back);
    connect(ui->pushButton_turn_left, &QPushButton::clicked, httpClient_, &HttpClient::turn_left);
    connect(ui->pushButton_turn_right, &QPushButton::clicked, httpClient_, &HttpClient::turn_right);
    connect(ui->pushButton_stop_move, &QPushButton::clicked, httpClient_, &HttpClient::stop_move);
    connect(ui->pushButton_brake, &QPushButton::clicked, httpClient_, &HttpClient::brake);
    connect(ui->pushButton_restart, &QPushButton::clicked, httpClient_, &HttpClient::restart);
    connect(ui->pushButton_save, &QPushButton::clicked, httpClient_, &HttpClient::save);

    connect(ui->horizontalSlider_speed_percent, &QSlider::sliderPressed, this, [this]() {
        speed_slider_is_pressed_ = true;
    });
    connect(ui->horizontalSlider_speed_percent, &QSlider::sliderReleased, this, [this]() {
        auto percent = ui->horizontalSlider_speed_percent->value() * 1.0 / ui->horizontalSlider_speed_percent->maximum();
        httpClient_->setSpeedPercent(percent);
        speed_slider_is_pressed_ = false;
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
    onRecvData(QJsonObject());
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
    } else {
        ui->label_connect_status->setStyleSheet(QString("background-color:red; color:white; font-size:%1px;").arg(this->font().pointSize()));
        ui->label_connect_status->setText("已断开");
        setEnabled(false);
    }
}
void MainWindow::onRecvData(QJsonObject jsonData) {
    if (jsonData.keys().contains("speed_percent") && speed_slider_is_pressed_ == false) {
        ui->horizontalSlider_speed_percent->blockSignals(true);
        ui->horizontalSlider_speed_percent->setValue(jsonData["speed_percent"].toDouble() * ui->horizontalSlider_speed_percent->maximum());
        ui->horizontalSlider_speed_percent->blockSignals(false);
        _updateSPeedPercentLabel(jsonData["speed_percent"].toDouble());
    }

    QVector<double> speedVector = {0, 0, 0}, poseVector = {0, 0, 0};
    QString text;

    if (jsonData.keys().contains("twist_linear_x") && jsonData.keys().contains("twist_linear_y") && jsonData.keys().contains("twist_angular_z")) {
        speedVector[0] = jsonData["twist_linear_x"].toDouble();
        speedVector[1] = jsonData["twist_linear_y"].toDouble();
        speedVector[2] = jsonData["twist_angular_z"].toDouble();
    }
    text = QString(
               "linear_x = %1 m/s\n"
               "linear_y = %2 m/s\n"
               "angular_z = %3 °/s")
               .arg(speedVector[0], 0, 'f', 3)
               .arg(speedVector[1], 0, 'f', 3)
               .arg(speedVector[2] * 180.0 / M_PI, 0, 'f', 3);
    ui->label_speed_status->setText(text);

    if (jsonData.keys().contains("euler_pose_x") && jsonData.keys().contains("euler_pose_y") && jsonData.keys().contains("euler_pose_yaw")) {
        poseVector[0] = jsonData["euler_pose_x"].toDouble();
        poseVector[1] = jsonData["euler_pose_y"].toDouble();
        poseVector[2] = jsonData["euler_pose_yaw"].toDouble();
    }
    text = QString(
               "pose_x = %1 m\n"
               "pose_y = %2 m\n"
               "pose_yaw = %3 °")
               .arg(poseVector[0], 0, 'f', 3)
               .arg(poseVector[1], 0, 'f', 3)
               .arg(poseVector[2] * 180.0 / M_PI, 0, 'f', 3);
    ui->label_euler_pose_status->setText(text);
}

void MainWindow::_updateSPeedPercentLabel(double percent) {
    ui->label_speed_percent->setText(QString::number(percent * 100, 'f', 1) + "%");
}
