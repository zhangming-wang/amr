#include "motionwidget.h"

MotionWidget::MotionWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MotionWidget) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, false);

    ui->widget_plot->setLayout(new QVBoxLayout());
    QSplitter *main_splitter = new QSplitter(Qt::Horizontal);

    main_splitter->addWidget(_initCustomPlot());
    main_splitter->addWidget(_initTextEdit());
    main_splitter->setCollapsible(0, false);
    ui->widget_plot->layout()->addWidget(main_splitter);
    main_splitter->setSizes({1000, 0});

    connect(ui->pushButton_restart, &QPushButton::clicked, this, &MotionWidget::restart);
    connect(ui->pushButton_brake, &QPushButton::clicked, this, &MotionWidget::brake);
    connect(ui->pushButton_stop_move, &QPushButton::clicked, this, &MotionWidget::stop_move);
    connect(ui->pushButton_move_front, &QPushButton::clicked, this, &MotionWidget::move_front);
    connect(ui->pushButton_move_back, &QPushButton::clicked, this, &MotionWidget::move_back);
    connect(ui->pushButton_move_left, &QPushButton::clicked, this, &MotionWidget::move_left);
    connect(ui->pushButton_move_right, &QPushButton::clicked, this, &MotionWidget::move_right);
    connect(ui->pushButton_move_left_front, &QPushButton::clicked, this, &MotionWidget::move_left_front);
    connect(ui->pushButton_move_left_back, &QPushButton::clicked, this, &MotionWidget::move_left_back);
    connect(ui->pushButton_move_right_front, &QPushButton::clicked, this, &MotionWidget::move_right_front);
    connect(ui->pushButton_move_right_back, &QPushButton::clicked, this, &MotionWidget::move_right_back);
    connect(ui->pushButton_turn_left, &QPushButton::clicked, this, &MotionWidget::turn_left);
    connect(ui->pushButton_turn_right, &QPushButton::clicked, this, &MotionWidget::turn_right);

    connect(ui->pushButton_write_params, &QPushButton::clicked, this, &MotionWidget::on_write_params);
    connect(ui->pushButton_read_params, &QPushButton::clicked, this, &MotionWidget::on_read_params);
    connect(ui->pushButton_save_params, &QPushButton::clicked, this, &MotionWidget::on_save_params);

    connect(ui->pushButton_write_config, &QPushButton::clicked, this, &MotionWidget::on_write_config);
    connect(ui->pushButton_read_config, &QPushButton::clicked, this, &MotionWidget::on_read_config);
    connect(ui->pushButton_save_config, &QPushButton::clicked, this, &MotionWidget::on_save_config);

    connect(ui->pushButton_clear_plot, &QPushButton::clicked, this, &MotionWidget::clear_plot);
    connect(ui->pushButton_clear_cmd_info, &QPushButton::clicked, this, [this]() { ui->textEdit_cmd->clear(); });

    connect(ui->horizontalSlider_speed_percent, &QSlider::sliderReleased, this, &MotionWidget::set_speed_percent);
    connect(ui->checkBox_enable_speed_plan, &QCheckBox::stateChanged, this, &MotionWidget::set_speed_plan_state);

    connect(ui->checkBox_show_plot, &QCheckBox::stateChanged, this, &MotionWidget::on_show_plot_changed);
    connect(ui->checkBox_open_settings, &QCheckBox::stateChanged, this, &MotionWidget::on_settings_show_changed);

    _initGamepad();
    _initMotionNode();
    _initTimer();

    ui->tabWidget_motion->setCurrentIndex(0);
    ui->tabWidget_settings->setCurrentIndex(0);

    ui->checkBox_open_settings->setChecked(false);
    ui->checkBox_show_plot->setChecked(false);

    on_show_plot_changed(false);
    on_settings_show_changed(false);

    on_update_status();
    on_connect_changed(false);
    on_show_plot_changed(false);

    motionNode_->start();
    status_timer_->start();
}

MotionWidget::~MotionWidget() {
    delete ui;
}

void MotionWidget::on_show_plot_changed(bool show) {
    ui->widget_plot->setVisible(show);
    ui->groupBox_plot->setVisible(show);
}

void MotionWidget::on_settings_show_changed(bool show) {
    ui->tabWidget_settings->setVisible(show);
}

void MotionWidget::_initTimer() {
    status_timer_ = std::make_shared<QTimer>();
    status_timer_->setInterval(500);
    connect(status_timer_.get(), &QTimer::timeout, this, &MotionWidget::on_update_status);
}

void MotionWidget::_initMotionNode() {
    motionNode_ = std::make_shared<MotionNode>();
    connect(motionNode_.get(), &MotionNode::motionStatusMsgChanged, this, &MotionWidget::on_recv_motion_status_msg);
    connect(motionNode_.get(), &MotionNode::serviceResponsed, this, &MotionWidget::on_recv_motion_settings_service_response);
    connect(motionNode_.get(), &MotionNode::serialMsgChanged, this, &MotionWidget::on_recv_serial_msg);
    connect(motionNode_.get(), &MotionNode::connectChanged, this, &MotionWidget::on_connect_changed);
    connect(motionNode_.get(), &MotionNode::nodeClosed, this, &MotionWidget::nodeClosed);
}

QWidget *MotionWidget::_initCustomPlot() {
    wheel_speed_customPlot_ = new QCustomPlot();

    QVector<QColor> colorVector = {
        QColor(0, 122, 255),
        QColor(255, 149, 0),
        QColor(52, 199, 89),
        QColor(255, 59, 48),
        QColor(175, 82, 222),
        QColor(0, 199, 255),
        QColor(142, 142, 147),
        QColor(255, 105, 180),
    };

    // 速度
    QVector<QPair<QColor, QString>> wheelSpeedColorVector = {
        {colorVector[0], "左前轮实际速度"},
        {colorVector[1], "左前轮目标速度"},
        {colorVector[2], "左后轮实际速度"},
        {colorVector[3], "左后轮目标速度"},
        {colorVector[4], "右前轮实际速度"},
        {colorVector[5], "右前轮目标速度"},
        {colorVector[6], "右后轮实际速度"},
        {colorVector[7], "右后轮目标速度"},
    };

    return _create_customPlot_widget(wheel_speed_customPlot_, "速度曲线", "时间 (s)", "速度 (m/s)", wheelSpeedColorVector);
}

QWidget *MotionWidget::_create_customPlot_widget(QCustomPlot *customPlot, const QString &title, const QString &xLabel, const QString &yLabel, const QVector<QPair<QColor, QString>> &colorVector) {
    QWidget *widget = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout *checkBoxLayout = new QVBoxLayout();
    QVector<QCheckBox *> checkBoxVector;

    customPlot->setWindowTitle(title);
    customPlot->xAxis->setLabel(xLabel);
    customPlot->xAxis->setNumberPrecision(3);
    customPlot->yAxis->setLabel(yLabel);
    customPlot->yAxis->setNumberPrecision(3);
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iMultiSelect | QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectItems | QCP::iSelectOther | QCP::iSelectPlottablesBeyondAxisRect);
    customPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for (int i = 0; i < colorVector.size(); ++i) {
        QCPGraph *graph = customPlot->addGraph();
        graph->setPen(QPen(colorVector[i].first));
        QPen pen(colorVector[i].first);
        if (i % 2 == 0)
            pen.setStyle(Qt::SolidLine); // 设置为实线样式
        else
            pen.setStyle(Qt::DashLine); // 设置为虚线样式
        graph->setPen(pen);
        graph->setName(colorVector[i].second);

        QCheckBox *checkBox = new QCheckBox("曲线" + QString::number(i + 1));
        checkBox->setChecked(true);
        checkBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        checkBox->setStyleSheet("color: rgb(" + QString::number(colorVector[i].first.red()) + "," + QString::number(colorVector[i].first.green()) + "," + QString::number(colorVector[i].first.blue()) + ");");
        checkBoxLayout->addWidget(checkBox);
        checkBoxVector.append(checkBox);
    }

    for (auto checkBox : checkBoxVector) {
        connect(checkBox, &QCheckBox::clicked, this, [this, customPlot, checkBoxVector]() {
            for (int i = 0; i < checkBoxVector.size(); ++i) {
                customPlot->graph(i)->setVisible(checkBoxVector[i]->isChecked());
            }
        });
    }

    checkBoxLayout->addStretch(1);
    mainLayout->addWidget(customPlot);
    mainLayout->addLayout(checkBoxLayout);
    widget->setLayout(mainLayout);

    return widget;
}

QTextEdit *MotionWidget::_initTextEdit() {
    motion_info_text_ = new QTextEdit();
    motion_info_text_->setReadOnly(true);
    return motion_info_text_;
}

void MotionWidget::_initGamepad() {
    gamepad_ = std::make_shared<QGamepad>(-1);

    connect(gamepad_.get(), &QGamepad::buttonGuideChanged, this, &MotionWidget::brake);
    connect(gamepad_.get(), &QGamepad::buttonXChanged, this, &MotionWidget::on_gamepad_button_clicked);
    connect(gamepad_.get(), &QGamepad::buttonYChanged, this, &MotionWidget::on_gamepad_button_clicked);
    connect(gamepad_.get(), &QGamepad::buttonAChanged, this, &MotionWidget::on_gamepad_button_clicked);
    connect(gamepad_.get(), &QGamepad::buttonBChanged, this, &MotionWidget::on_gamepad_button_clicked);
    connect(gamepad_.get(), &QGamepad::buttonL1Changed, this, &MotionWidget::on_gamepad_button_clicked);
    connect(gamepad_.get(), &QGamepad::buttonR1Changed, this, &MotionWidget::on_gamepad_button_clicked);
    connect(gamepad_.get(), &QGamepad::axisLeftXChanged, this, &MotionWidget::on_gamepad_axis_changed);
    connect(gamepad_.get(), &QGamepad::axisLeftYChanged, this, &MotionWidget::on_gamepad_axis_changed);
    connect(gamepad_.get(), &QGamepad::axisRightXChanged, this, &MotionWidget::on_gamepad_axis_changed);
    connect(gamepad_.get(), &QGamepad::axisRightYChanged, this, &MotionWidget::on_gamepad_axis_changed);

    auto change_spd = [this](bool add) {
        double min_step = 0.05;
        double percent = 1.0 * ui->horizontalSlider_speed_percent->value() / ui->horizontalSlider_speed_percent->maximum();
        if (add) {
            percent += min_step;
            if (percent > 1) {
                percent = 1;
            }
        } else {
            percent -= min_step;
            if (percent < min_step) {
                percent = min_step;
            }
        }
        ui->horizontalSlider_speed_percent->setValue(percent * ui->horizontalSlider_speed_percent->maximum());
        set_speed_percent();
    };

    connect(gamepad_.get(), &QGamepad::buttonUpChanged, this, [change_spd](bool value) {
        if (value)
            change_spd(true);
    });
    connect(gamepad_.get(), &QGamepad::buttonDownChanged, this, [change_spd](bool value) {
        if (value)
            change_spd(false);
    });
}

void MotionWidget::on_gamepad_button_clicked() {
    if (!gamepad_->buttonX() && gamepad_->buttonY() && !gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_front->click();
    } else if (!gamepad_->buttonX() && !gamepad_->buttonY() && gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_back->click();
    } else if (gamepad_->buttonX() && !gamepad_->buttonY() && !gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_left->click();
    } else if (!gamepad_->buttonX() && !gamepad_->buttonY() && !gamepad_->buttonA() && gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_right->click();
    } else if (gamepad_->buttonX() && gamepad_->buttonY() && !gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_left_front->click();
    } else if (gamepad_->buttonX() && !gamepad_->buttonY() && gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_left_back->click();
    } else if (!gamepad_->buttonX() && gamepad_->buttonY() && !gamepad_->buttonA() && gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_right_front->click();
    } else if (!gamepad_->buttonX() && !gamepad_->buttonY() && gamepad_->buttonA() && gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_move_right_back->click();
    } else if (!gamepad_->buttonX() && !gamepad_->buttonY() && !gamepad_->buttonA() && !gamepad_->buttonB() && gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_turn_left->click();
    } else if (!gamepad_->buttonX() && !gamepad_->buttonY() && !gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && gamepad_->buttonR1()) {
        ui->pushButton_turn_right->click();
    } else if (!gamepad_->buttonX() && !gamepad_->buttonY() && !gamepad_->buttonA() && !gamepad_->buttonB() && !gamepad_->buttonL1() && !gamepad_->buttonR1()) {
        ui->pushButton_stop_move->click();
    }
}

void MotionWidget::on_gamepad_axis_changed() {
    std::shared_ptr<geometry_msgs::msg::Twist> twist = std::make_shared<geometry_msgs::msg::Twist>();

    double axixLeftX_value = gamepad_->axisLeftX();
    double axixLeftY_value = gamepad_->axisLeftY();
    double axixRightX_value = gamepad_->axisRightX();

    const double MIN_VALUE = 0.1;

    if (fabs(axixLeftX_value) < MIN_VALUE)
        axixLeftX_value = 0;
    if (fabs(axixLeftY_value) < MIN_VALUE)
        axixLeftY_value = 0;
    if (fabs(axixRightX_value) < MIN_VALUE)
        axixRightX_value = 0;

    twist->linear.x = axixLeftX_value * ui->doubleSpinBox_max_v->value();
    twist->linear.y = -1.0 * axixLeftY_value * ui->doubleSpinBox_max_v->value();
    twist->linear.z = 0;
    twist->angular.x = 0;
    twist->angular.y = 0;
    twist->angular.z = -1.0 * axixRightX_value * 2.0 * ui->doubleSpinBox_max_v->value() / ((ui->spinBox_track_width->value() + ui->spinBox_track_width->value()) / 1000.0);

    motionNode_->publish_twist(twist);
}

void MotionWidget::restart() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::Restart;
    auto cmd_string = _get_cmd_string_prefix() + "重启指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::brake() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::Brake;
    auto cmd_string = _get_cmd_string_prefix() + "刹车指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::stop_move() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::StopMove;
    auto cmd_string = _get_cmd_string_prefix() + "停止指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::move_front() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveFront;
    auto cmd_string = _get_cmd_string_prefix() + "前进指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::move_back() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveBack;
    auto cmd_string = _get_cmd_string_prefix() + "后退指令";
    _ask_motion_settings_service(request, cmd_string);
}
void MotionWidget::move_left() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveLeft;
    auto cmd_string = _get_cmd_string_prefix() + "左移指令";
    _ask_motion_settings_service(request, cmd_string);
}
void MotionWidget::move_right() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveRight;
    auto cmd_string = _get_cmd_string_prefix() + "右移指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::move_left_front() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveLeftFront;
    auto cmd_string = _get_cmd_string_prefix() + "左前移指令";
    _ask_motion_settings_service(request, cmd_string);
}
void MotionWidget::move_left_back() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveLeftBack;
    auto cmd_string = _get_cmd_string_prefix() + "左后移指令";
    _ask_motion_settings_service(request, cmd_string);
}
void MotionWidget::move_right_front() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveRightFront;
    auto cmd_string = _get_cmd_string_prefix() + "右前移指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::move_right_back() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::MoveRightBack;
    auto cmd_string = _get_cmd_string_prefix() + "右后移指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::turn_left() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::TurnLeft;
    auto cmd_string = _get_cmd_string_prefix() + "左转指令";
    _ask_motion_settings_service(request, cmd_string);
}
void MotionWidget::turn_right() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::TurnRight;
    auto cmd_string = _get_cmd_string_prefix() + "右转指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::set_speed_percent() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::SetSpeedPercent;
    request->speed_percent = ui->horizontalSlider_speed_percent->value() * 1.0 / ui->horizontalSlider_speed_percent->maximum();
    _update_speed_percent_label(request->speed_percent);
    auto cmd_string = _get_cmd_string_prefix() + "设置速度指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::set_speed_plan_state() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::SetSpeedPlanState;
    request->enable_speed_plan = ui->checkBox_enable_speed_plan->isChecked();
    auto cmd_string = _get_cmd_string_prefix() + "设置速度规划指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::on_read_params() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::ReadParams;
    auto cmd_string = _get_cmd_string_prefix() + "读取参数指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::on_write_params() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::WriteParams;

    request->motor_enable_flags = 0;
    if (ui->checkBox_enable_left_front_motor->isChecked())
        request->motor_enable_flags |= 0x01;
    if (ui->checkBox_enable_left_back_motor->isChecked())
        request->motor_enable_flags |= 0x02;
    if (ui->checkBox_enable_right_front_motor->isChecked())
        request->motor_enable_flags |= 0x04;
    if (ui->checkBox_enable_right_back_motor->isChecked())
        request->motor_enable_flags |= 0x08;

    request->left_front_motor_p = ui->doubleSpinBox_left_front_motor_p->value();
    request->left_front_motor_i = ui->doubleSpinBox_left_front_motor_i->value();
    request->left_front_motor_d = ui->doubleSpinBox_left_front_motor_d->value();
    request->left_front_motor_max_total_integral = ui->doubleSpinBox_left_front_motor_max_total_integral->value();

    request->left_back_motor_p = ui->doubleSpinBox_left_back_motor_p->value();
    request->left_back_motor_i = ui->doubleSpinBox_left_back_motor_i->value();
    request->left_back_motor_d = ui->doubleSpinBox_left_back_motor_d->value();
    request->left_back_motor_max_total_integral = ui->doubleSpinBox_left_back_motor_max_total_integral->value();

    request->right_front_motor_p = ui->doubleSpinBox_right_front_motor_p->value();
    request->right_front_motor_i = ui->doubleSpinBox_right_front_motor_i->value();
    request->right_front_motor_d = ui->doubleSpinBox_right_front_motor_d->value();
    request->right_front_motor_max_total_integral = ui->doubleSpinBox_right_front_motor_max_total_integral->value();

    request->right_back_motor_p = ui->doubleSpinBox_right_back_motor_p->value();
    request->right_back_motor_i = ui->doubleSpinBox_right_back_motor_i->value();
    request->right_back_motor_d = ui->doubleSpinBox_right_back_motor_d->value();
    request->right_back_motor_max_total_integral = ui->doubleSpinBox_right_back_motor_max_total_integral->value();

    request->max_v = ui->doubleSpinBox_max_v->value();
    request->max_acc = ui->doubleSpinBox_max_acc->value();
    request->jerk = ui->doubleSpinBox_jerk->value();

    request->milliseconds = ui->spinBox_millseconds->value();

    auto cmd_string = _get_cmd_string_prefix() + "写入参数指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::on_save_params() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::SaveParams;
    auto cmd_string = _get_cmd_string_prefix() + "保存参数指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::on_read_config() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::ReadConfig;
    auto cmd_string = _get_cmd_string_prefix() + "读取配置指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::on_write_config() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::WriteConfig;

    request->is_mecanum_wheel = ui->checkBox_is_mecanum_wheel->isChecked();
    request->wheel_width = ui->spinBox_wheel_width->value() / 1000.0;
    request->track_width = ui->spinBox_track_width->value() / 1000.0;

    request->left_front_motor_pina = ui->spinBox_left_front_motor_pin0->value();
    request->left_front_motor_pinb = ui->spinBox_left_front_motor_pin1->value();
    request->left_front_motor_pinpwm = ui->spinBox_left_front_motor_pinPwm->value();
    request->left_front_motor_pluses_per_revolution = ui->spinBox_left_front_motor_pluses_per_revolution->value();
    request->left_front_motor_revolutions_per_minute = ui->spinBox_left_front_motor_revolutions_per_minute->value();
    request->left_front_motor_wheel_diameter = ui->spinBox_left_front_motor_wheel_diameter->value() / 1000.0;

    request->left_front_encoder_pina = ui->spinBox_left_front_encoder_pin0->value();
    request->left_front_encoder_pinb = ui->spinBox_left_front_encoder_pin1->value();

    request->left_back_motor_pina = ui->spinBox_left_back_motor_pin0->value();
    request->left_back_motor_pinb = ui->spinBox_left_back_motor_pin1->value();
    request->left_back_motor_pinpwm = ui->spinBox_left_back_motor_pinPwm->value();
    request->left_back_motor_pluses_per_revolution = ui->spinBox_left_back_motor_pluses_per_revolution->value();
    request->left_back_motor_revolutions_per_minute = ui->spinBox_left_back_motor_revolutions_per_minute->value();
    request->left_back_motor_wheel_diameter = ui->spinBox_left_back_motor_wheel_diameter->value() / 1000.0;

    request->left_back_encoder_pina = ui->spinBox_left_back_encoder_pin0->value();
    request->left_back_encoder_pinb = ui->spinBox_left_back_encoder_pin1->value();

    request->right_front_motor_pina = ui->spinBox_right_front_motor_pin0->value();
    request->right_front_motor_pinb = ui->spinBox_right_front_motor_pin1->value();
    request->right_front_motor_pinpwm = ui->spinBox_right_front_motor_pinPwm->value();
    request->right_front_motor_pluses_per_revolution = ui->spinBox_right_front_motor_pluses_per_revolution->value();
    request->right_front_motor_revolutions_per_minute = ui->spinBox_right_front_motor_revolutions_per_minute->value();
    request->right_front_motor_wheel_diameter = ui->spinBox_right_front_motor_wheel_diameter->value() / 1000.0;

    request->right_front_encoder_pina = ui->spinBox_right_front_encoder_pin0->value();
    request->right_front_encoder_pinb = ui->spinBox_right_front_encoder_pin1->value();

    request->right_back_motor_pina = ui->spinBox_right_back_motor_pin0->value();
    request->right_back_motor_pinb = ui->spinBox_right_back_motor_pin1->value();
    request->right_back_motor_pinpwm = ui->spinBox_right_back_motor_pinPwm->value();
    request->right_back_motor_pluses_per_revolution = ui->spinBox_right_back_motor_pluses_per_revolution->value();
    request->right_back_motor_revolutions_per_minute = ui->spinBox_right_back_motor_revolutions_per_minute->value();
    request->right_back_motor_wheel_diameter = ui->spinBox_right_back_motor_wheel_diameter->value() / 1000.0;

    request->right_back_encoder_pina = ui->spinBox_right_back_encoder_pin0->value();
    request->right_back_encoder_pinb = ui->spinBox_right_back_encoder_pin1->value();

    auto cmd_string = _get_cmd_string_prefix() + "写入配置指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::on_save_config() {
    MotionSettingsSrv::Request::SharedPtr request(std::make_shared<MotionSettingsSrv::Request>());
    request->mode = MotionService::Type::SaveConfig;
    auto cmd_string = _get_cmd_string_prefix() + "保存配置指令";
    _ask_motion_settings_service(request, cmd_string);
}

void MotionWidget::_ask_motion_settings_service(MotionSettingsSrv::Request::SharedPtr request, QString &cmd_string) {
    QThread::msleep(1);
    auto id = QDateTime::currentMSecsSinceEpoch();
    service_command_map_.insert(id, cmd_string);
    request->id = id;
    motionNode_->ask_service_response(request);
}

void MotionWidget::_show_service_command_state(uint64_t id, bool success) {
    auto cmd_string = service_command_map_.value(id, QString());
    service_command_map_.remove(id);
    if (!cmd_string.isEmpty()) {
        QString html_string, cmd_string_tmp;
        if (success) {
            cmd_string_tmp = cmd_string + "执行成功！";
            html_string = QString("<span style='color:green;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped());
        } else {
            cmd_string_tmp = cmd_string + "执行失败.";
            html_string = QString("<span style='color:red;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped());
        }
        ui->textEdit_cmd->append(html_string);
        ui->textEdit_cmd->moveCursor(QTextCursor::End);
    }
}

void MotionWidget::on_recv_motion_settings_service_response(uint64_t id, MotionSettingsSrv::Response::SharedPtr response) {
    if (response == nullptr) {
        _show_service_command_state(id, false);
        return;
    } else {
        _show_service_command_state(id, true);
    }

    if (response->state == MotionService::Type::ReadParams) {
        ui->spinBox_millseconds->setValue(response->milliseconds);

        ui->checkBox_enable_speed_plan->blockSignals(true);
        ui->checkBox_enable_speed_plan->setChecked(response->enable_speed_plan);
        ui->checkBox_enable_speed_plan->blockSignals(false);

        ui->checkBox_enable_left_front_motor->setChecked(response->motor_enable_flags & 0x01);
        ui->checkBox_enable_left_back_motor->setChecked(response->motor_enable_flags & 0x02);
        ui->checkBox_enable_right_front_motor->setChecked(response->motor_enable_flags & 0x04);
        ui->checkBox_enable_right_back_motor->setChecked(response->motor_enable_flags & 0x08);

        ui->horizontalSlider_speed_percent->blockSignals(true);
        ui->horizontalSlider_speed_percent->setValue(response->speed_percent * ui->horizontalSlider_speed_percent->maximum());
        ui->horizontalSlider_speed_percent->blockSignals(false);
        _update_speed_percent_label(response->speed_percent);

        ui->doubleSpinBox_max_v->setValue(response->max_v);
        ui->doubleSpinBox_max_acc->setValue(response->max_acc);
        ui->doubleSpinBox_jerk->setValue(response->jerk);

        ui->doubleSpinBox_left_front_motor_p->setValue(response->left_front_motor_p);
        ui->doubleSpinBox_left_front_motor_i->setValue(response->left_front_motor_i);
        ui->doubleSpinBox_left_front_motor_d->setValue(response->left_front_motor_d);
        ui->doubleSpinBox_left_front_motor_max_total_integral->setValue(response->left_front_motor_max_total_integral);

        ui->doubleSpinBox_left_back_motor_p->setValue(response->left_back_motor_p);
        ui->doubleSpinBox_left_back_motor_i->setValue(response->left_back_motor_i);
        ui->doubleSpinBox_left_back_motor_d->setValue(response->left_back_motor_d);
        ui->doubleSpinBox_left_back_motor_max_total_integral->setValue(response->left_back_motor_max_total_integral);

        ui->doubleSpinBox_right_front_motor_p->setValue(response->right_front_motor_p);
        ui->doubleSpinBox_right_front_motor_i->setValue(response->right_front_motor_i);
        ui->doubleSpinBox_right_front_motor_d->setValue(response->right_front_motor_d);
        ui->doubleSpinBox_right_front_motor_max_total_integral->setValue(response->right_front_motor_max_total_integral);

        ui->doubleSpinBox_right_back_motor_p->setValue(response->right_back_motor_p);
        ui->doubleSpinBox_right_back_motor_i->setValue(response->right_back_motor_i);
        ui->doubleSpinBox_right_back_motor_d->setValue(response->right_back_motor_d);
        ui->doubleSpinBox_right_back_motor_max_total_integral->setValue(response->right_back_motor_max_total_integral);
    } else if (response->state == MotionService::Type::WriteParams || response->state == MotionService::Type::SetSpeedPercent) {
        ui->horizontalSlider_speed_percent->blockSignals(true);
        ui->horizontalSlider_speed_percent->setValue(response->speed_percent * ui->horizontalSlider_speed_percent->maximum());
        ui->horizontalSlider_speed_percent->blockSignals(false);
        ui->doubleSpinBox_max_v->setValue(response->max_v);
        _update_speed_percent_label(response->speed_percent);
    } else if (response->state == MotionService::Type::ReadConfig) {
        ui->checkBox_is_mecanum_wheel->blockSignals(true);
        ui->checkBox_is_mecanum_wheel->setChecked(response->is_mecanum_wheel);
        ui->checkBox_is_mecanum_wheel->blockSignals(false);

        ui->spinBox_wheel_width->setValue(response->wheel_width * 1000);
        ui->spinBox_track_width->setValue(response->track_width * 1000);

        ui->spinBox_left_front_motor_pin0->setValue(response->left_front_motor_pina);
        ui->spinBox_left_front_motor_pin1->setValue(response->left_front_motor_pinb);
        ui->spinBox_left_front_motor_pinPwm->setValue(response->left_front_motor_pinpwm);
        ui->spinBox_left_front_motor_pluses_per_revolution->setValue(response->left_front_motor_pluses_per_revolution);
        ui->spinBox_left_front_motor_revolutions_per_minute->setValue(response->left_front_motor_revolutions_per_minute);
        ui->spinBox_left_front_motor_wheel_diameter->setValue(response->left_front_motor_wheel_diameter * 1000);

        ui->spinBox_left_front_encoder_pin0->setValue(response->left_front_encoder_pina);
        ui->spinBox_left_front_encoder_pin1->setValue(response->left_front_encoder_pinb);

        ui->spinBox_left_back_motor_pin0->setValue(response->left_back_motor_pina);
        ui->spinBox_left_back_motor_pin1->setValue(response->left_back_motor_pinb);
        ui->spinBox_left_back_motor_pinPwm->setValue(response->left_back_motor_pinpwm);
        ui->spinBox_left_back_motor_pluses_per_revolution->setValue(response->left_back_motor_pluses_per_revolution);
        ui->spinBox_left_back_motor_revolutions_per_minute->setValue(response->left_back_motor_revolutions_per_minute);
        ui->spinBox_left_back_motor_wheel_diameter->setValue(response->left_back_motor_wheel_diameter * 1000);

        ui->spinBox_left_back_encoder_pin0->setValue(response->left_back_encoder_pina);
        ui->spinBox_left_back_encoder_pin1->setValue(response->left_back_encoder_pinb);

        ui->spinBox_right_front_motor_pin0->setValue(response->right_front_motor_pina);
        ui->spinBox_right_front_motor_pin1->setValue(response->right_front_motor_pinb);
        ui->spinBox_right_front_motor_pinPwm->setValue(response->right_front_motor_pinpwm);
        ui->spinBox_right_front_motor_pluses_per_revolution->setValue(response->right_front_motor_pluses_per_revolution);
        ui->spinBox_right_front_motor_revolutions_per_minute->setValue(response->right_front_motor_revolutions_per_minute);
        ui->spinBox_right_front_motor_wheel_diameter->setValue(response->right_front_motor_wheel_diameter * 1000);

        ui->spinBox_right_front_encoder_pin0->setValue(response->right_front_encoder_pina);
        ui->spinBox_right_front_encoder_pin1->setValue(response->right_front_encoder_pinb);

        ui->spinBox_right_back_motor_pin0->setValue(response->right_back_motor_pina);
        ui->spinBox_right_back_motor_pin1->setValue(response->right_back_motor_pinb);
        ui->spinBox_right_back_motor_pinPwm->setValue(response->right_back_motor_pinpwm);
        ui->spinBox_right_back_motor_pluses_per_revolution->setValue(response->right_back_motor_pluses_per_revolution);
        ui->spinBox_right_back_motor_revolutions_per_minute->setValue(response->right_back_motor_revolutions_per_minute);
        ui->spinBox_right_back_motor_wheel_diameter->setValue(response->right_back_motor_wheel_diameter * 1000);

        ui->spinBox_right_back_encoder_pin0->setValue(response->right_back_encoder_pina);
        ui->spinBox_right_back_encoder_pin1->setValue(response->right_back_encoder_pinb);
    }

    if (response->state == MotionService::Type::ReadConfig || response->state == MotionService::Type::WriteConfig) {
        motionNode_->set_model_param(ui->spinBox_track_width->value() / 1000.0, ui->spinBox_wheel_width->value() / 1000.0, ui->checkBox_is_mecanum_wheel->isChecked());
    }
}

void MotionWidget::on_connect_changed(bool connect) {
    if (connect) {
        on_read_params();
        on_read_config();
        clear_plot();
        ui->label_motion_node_status->setText("运动节点已连接");
        ui->label_motion_node_status->setStyleSheet(OK_STYLESHEET);
    } else {
        ui->label_motion_node_status->setText("运动节点未连接");
        ui->label_motion_node_status->setStyleSheet(ERROR_STYLESHEET);
    }
}

void MotionWidget::on_update_status() {
    if (!gamepad_->isConnected()) {
        ui->label_gamepad_status->setText(" 手柄未连接");
        ui->label_gamepad_status->setStyleSheet(ERROR_STYLESHEET);

        QList<int> validIds;
        QGamepadManager *manager = QGamepadManager::instance();
        QList<int> allIds = manager->connectedGamepads();

        for (int id : allIds) {
            QGamepad tempPad(id);
            QString deviceName = tempPad.name();
            // 过滤掉键鼠设备（根据设备名称关键词）
            if (!deviceName.contains("Keyboard", Qt::CaseInsensitive) &&
                !deviceName.contains("Mouse", Qt::CaseInsensitive) &&
                !deviceName.contains("HID", Qt::CaseInsensitive) && // 部分键鼠标注为 HID 设备
                !deviceName.isEmpty()) {
                gamepad_->setDeviceId(id);
                break;
            }
        }
    } else {
        ui->label_gamepad_status->setText(" 手柄已连接: " + gamepad_->name() + " (ID:" + QString::number(gamepad_->deviceId()) + ")");
        ui->label_gamepad_status->setStyleSheet(OK_STYLESHEET);
    }
}

void MotionWidget::on_recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg) {
    if (ui->checkBox_show_plot->isChecked() == false) {
        return;
    }

    if (ui->checkBox_dynamic_refresh->isChecked() == false) {
        return;
    }

    double minValue = pow(10, -6);
    if (qFabs(msg->left_front_current_v) > minValue ||
        qFabs(msg->left_front_target_v) > minValue ||
        qFabs(msg->left_back_current_v) > minValue ||
        qFabs(msg->left_back_target_v) > minValue ||
        qFabs(msg->right_front_current_v) > minValue ||
        qFabs(msg->right_front_target_v) > minValue ||
        qFabs(msg->right_back_current_v) > minValue ||
        qFabs(msg->right_back_target_v) > minValue) {
        if (stop_plot_) {
            stop_plot_ = false;
        }
    }

    if (stop_plot_) {
        return;
    }

    if (wheel_speed_customPlot_->graph(0)->dataCount() >= 10000) {
        clear_plot();
    }

    if (wheel_speed_customPlot_->graph(0)->dataCount() == 0) {
        reference_seconds_ = msg->stamp * 1e-9;
    }

    wheel_speed_customPlot_->graph(0)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->left_front_current_v);
    wheel_speed_customPlot_->graph(1)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->left_front_target_v);
    wheel_speed_customPlot_->graph(2)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->left_back_current_v);
    wheel_speed_customPlot_->graph(3)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->left_back_target_v);
    wheel_speed_customPlot_->graph(4)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->right_front_current_v);
    wheel_speed_customPlot_->graph(5)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->right_front_target_v);
    wheel_speed_customPlot_->graph(6)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->right_back_current_v);
    wheel_speed_customPlot_->graph(7)->addData(msg->stamp * 1e-9 - reference_seconds_, msg->right_back_target_v);

    if (ui->checkBox_dynamic_follow->isChecked()) {
        if (wheel_speed_customPlot_->isVisible()) {
            wheel_speed_customPlot_->rescaleAxes(); // 自动缩放坐标轴，包含所有数据
        }
    }
    if (wheel_speed_customPlot_->isVisible()) {
        wheel_speed_customPlot_->replot(); // 刷新绘图
    }
    QString line = QString("t= %1\n"
                           "left_front_current_v= %2,  left_front_target_v= %3,  left_back_current_v= %4,  left_back_target_v= %5\n"
                           "right_front_current_v= %6,  right_front_target_v= %7,  right_back_current_v= %8,  right_back_target_v= %9\n")
                       .arg(reference_seconds_, 0, 'f', 3)
                       .arg(msg->left_front_current_v, 0, 'f', 3)
                       .arg(msg->left_front_target_v, 0, 'f', 3)
                       .arg(msg->left_back_current_v, 0, 'f', 3)
                       .arg(msg->left_back_target_v, 0, 'f', 3)
                       .arg(msg->right_front_current_v, 0, 'f', 3)
                       .arg(msg->right_front_target_v, 0, 'f', 3)
                       .arg(msg->right_back_current_v, 0, 'f', 3)
                       .arg(msg->right_back_target_v, 0, 'f', 3);
    motion_info_text_->append(line);

    if (qFabs(msg->left_front_current_v) < minValue &&
        qFabs(msg->left_front_target_v) < minValue &&
        qFabs(msg->left_back_current_v) < minValue &&
        qFabs(msg->left_back_target_v) < minValue &&
        qFabs(msg->right_front_current_v) < minValue &&
        qFabs(msg->right_front_target_v) < minValue &&
        qFabs(msg->right_back_current_v) < minValue &&
        qFabs(msg->right_back_target_v) < minValue) {
        stop_plot_ = true;
    }
    ui->groupBox_plot->setTitle(QString(("绘图设置（%1个点）")).arg(wheel_speed_customPlot_->graph(0)->dataCount()));
}

void MotionWidget::on_recv_serial_msg(const std_msgs::msg::String::SharedPtr msg) {
    QString serial_msg = QString::fromStdString(msg->data);
    QString html_string = QString("<span style='color:black;'>%1</span>").arg(serial_msg.toHtmlEscaped());
    ui->textEdit_cmd->append(html_string);
    ui->textEdit_cmd->moveCursor(QTextCursor::End);
}

void MotionWidget::clear_plot() {
    for (int i = 0; i < wheel_speed_customPlot_->graphCount(); i++) {
        wheel_speed_customPlot_->graph(i)->data()->clear();
    }
    wheel_speed_customPlot_->rescaleAxes(); // 自动缩放坐标轴，包含所有数据
    wheel_speed_customPlot_->replot();      // 刷新绘图
    reference_seconds_ = 0;

    motion_info_text_->clear();

    ui->groupBox_plot->setTitle(QString(("绘图设置（%1个点）")).arg(wheel_speed_customPlot_->graph(0)->dataCount()));
}

void MotionWidget::_update_speed_percent_label(double percent) {
    ui->label_speed_percent->setText(QString::number(percent * 100, 'f', 1) + "%");
}
