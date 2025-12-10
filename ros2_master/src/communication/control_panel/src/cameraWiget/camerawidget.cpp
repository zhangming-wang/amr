#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CameraWidget) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, false);

    ui->graphicsView->setScene(new QGraphicsScene());

    fps_vector_ = std::make_shared<QVector<double>>();

    pixmapItem_ = ui->graphicsView->scene()->addPixmap(QPixmap());
    pixmapItem_->setTransformationMode(Qt::SmoothTransformation);

    ui->graphicsView->setFixedSize(1280, 720);

    connect(ui->pushButton_capture, &QPushButton::clicked, this, &CameraWidget::capture_image);
    connect(ui->pushButton_read_config, &QPushButton::clicked, this, &CameraWidget::read_config);
    connect(ui->pushButton_write_config, &QPushButton::clicked, this, &CameraWidget::write_config);
    connect(ui->pushButton_save_config, &QPushButton::clicked, this, &CameraWidget::save_config);
    connect(ui->pushButton_read_params, &QPushButton::clicked, this, &CameraWidget::read_params);
    connect(ui->pushButton_write_params, &QPushButton::clicked, this, &CameraWidget::write_params);
    connect(ui->pushButton_save_params, &QPushButton::clicked, this, &CameraWidget::save_params);
    connect(ui->pushButton_restart, &QPushButton::clicked, this, &CameraWidget::restart);
    connect(ui->pushButton_clear_info, &QPushButton::clicked, this, [this]() { ui->textEdit_info->clear(); });
    connect(ui->checkBox_serial_capture, &QCheckBox::clicked, this, &CameraWidget::setEnableSeriesCapture);
    connect(ui->checkBox_open_settings, &QCheckBox::clicked, this, &CameraWidget::onOpenSettingsChanged);

    camera_node_ = std::make_shared<CameraNode>(pc_camera_node_name, pc_camera_node_namespace);
    connect(camera_node_.get(), &CameraNode::imageMsgReceived, this, &CameraWidget::on_recv_image_msg);
    connect(camera_node_.get(), &CameraNode::cameraSettingsServiceResponsed, this, &CameraWidget::on_recv_camera_settings_service_response);
    connect(camera_node_.get(), &CameraNode::commandStateChanged, this, &CameraWidget::on_command_state_changed);
    connect(camera_node_.get(), &CameraNode::connectedChanged, this, &CameraWidget::on_recv_connected_changed);
    connect(camera_node_.get(), &CameraNode::nodeClosed, this, &CameraWidget::nodeClosed);
    camera_node_->start();

    connect(&status_timer_, &QTimer::timeout, this, &CameraWidget::on_update_status);
    status_timer_.setInterval(500);
    status_timer_.start();

    ui->checkBox_open_settings->setChecked(false);
    onOpenSettingsChanged(false);
}

CameraWidget::~CameraWidget() {
    delete ui;
}

void CameraWidget::onOpenSettingsChanged(bool open) {
    ui->groupBox_params->setVisible(open);
    ui->groupBox_config->setVisible(open);
    ui->groupBox_cmd_info->setVisible(open);
}

void CameraWidget::restart() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::Restart;
    auto cmd_string = _get_cmd_string_prefix() + "重启配置指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::capture_image() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::Capture;
    auto cmd_string = _get_cmd_string_prefix() + "拍照指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::setEnableSeriesCapture(bool enable) {
    ui->pushButton_capture->setEnabled(!enable);

    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::SetEnableSeriesCapture;
    request->enable_series_capture = enable;
    auto cmd_string = _get_cmd_string_prefix() + "设置连拍指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::read_config() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::ReadConfig;
    auto cmd_string = _get_cmd_string_prefix() + "读取配置指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::write_config() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::WriteConfig;

    request->pin_pwdn = ui->spinBox_pin_pwdn->value();
    request->pin_reset = ui->spinBox_pin_reset->value();
    request->pin_xclk = ui->spinBox_pin_xclk->value();
    request->pin_sccb_sda = ui->spinBox_pin_sccb_sda->value();
    request->pin_sccb_scl = ui->spinBox_pin_sccb_scl->value();
    request->pin_d7 = ui->spinBox_pin_d7->value();
    request->pin_d6 = ui->spinBox_pin_d6->value();
    request->pin_d5 = ui->spinBox_pin_d5->value();
    request->pin_d4 = ui->spinBox_pin_d4->value();
    request->pin_d3 = ui->spinBox_pin_d3->value();
    request->pin_d2 = ui->spinBox_pin_d2->value();
    request->pin_d1 = ui->spinBox_pin_d1->value();
    request->pin_d0 = ui->spinBox_pin_d0->value();
    request->xclk_freq_hz = ui->spinBox_xclk_freq_hz->value();
    request->fb_count = ui->spinBox_fb_count->value();
    request->sccb_i2c_port = ui->spinBox_sccb_i2c_port->value();
    request->xclk_freq_hz = ui->spinBox_xclk_freq_hz->value();

    request->frame_size = ui->comboBox_frame_size->currentIndex();
    request->pixel_format = ui->comboBox_pixel_format->currentIndex();
    request->ledc_timer = ui->comboBox_ledc_timer->currentIndex();
    request->ledc_channel = ui->comboBox_ledc_channel->currentIndex();
    request->grab_mode = ui->comboBox_grab_mode->currentIndex();
    request->fb_location = ui->comboBox_fb_location->currentIndex();
    request->conv_mode = ui->comboBox_conv_mode->currentIndex();

    auto cmd_string = _get_cmd_string_prefix() + "写入配置指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::save_config() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::SaveConfig;
    auto cmd_string = _get_cmd_string_prefix() + "保存配置指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::read_params() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::ReadParams;
    auto cmd_string = _get_cmd_string_prefix() + "读取参数指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::write_params() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::WriteParams;
    auto cmd_string = _get_cmd_string_prefix() + "写入参数指令";

    request->milliseconds = ui->spinBox_milliseconds->value();
    request->brightness = ui->spinBox_brightness->value();
    request->sharpness = ui->spinBox_sharpness->value();
    request->contrast = ui->spinBox_contrast->value();
    request->saturation = ui->spinBox_saturation->value();
    request->denoise = ui->spinBox_denoise->value();
    request->ae_level = ui->spinBox_ae_level->value();
    request->agc_gain = ui->spinBox_agc_gain->value();
    request->aec_value = ui->spinBox_aec_value->value();
    request->quality = ui->spinBox_quality->value();

    request->pixformat = ui->comboBox_pixformat->currentIndex();
    request->framesize = ui->comboBox_framesize->currentIndex();
    request->gainceiling = ui->comboBox_gainceiling->currentIndex();
    request->special_effect = ui->comboBox_special_effect->currentIndex();
    request->awb_gain = ui->comboBox_awb_gain->currentIndex();
    request->wb_mode = ui->comboBox_wb_mode->currentIndex();
    request->awb = ui->comboBox_awb->currentIndex();
    request->dcw = ui->comboBox_dcw->currentIndex();
    request->colorbar = ui->comboBox_colorbar->currentIndex();
    request->agc = ui->comboBox_agc->currentIndex();
    request->aec = ui->comboBox_aec->currentIndex();
    request->aec2 = ui->comboBox_aec2->currentIndex();
    request->hmirror = ui->comboBox_hmirror->currentIndex();
    request->vflip = ui->comboBox_vflip->currentIndex();
    request->bpc = ui->comboBox_bpc->currentIndex();
    request->wpc = ui->comboBox_wpc->currentIndex();
    request->lenc = ui->comboBox_lenc->currentIndex();
    request->raw_gma = ui->comboBox_raw_gma->currentIndex();

    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::save_params() {
    CameraSettingsSrv::Request::SharedPtr request(std::make_shared<CameraSettingsSrv::Request>());
    request->mode = CameraService::Type::SaveParams;
    auto cmd_string = _get_cmd_string_prefix() + "保存参数指令";
    _ask_camera_settings_service(request, cmd_string);
}

void CameraWidget::on_command_state_changed(int64_t id, int state) {
    auto cmd_string = commpand_map_.value(id, QString());
    if (!cmd_string.isEmpty()) {
        _update_cmd_status_info(cmd_string, state);
        if (state == CameraNode::CommandState::Fail || state == CameraNode::CommandState::Success) {
            commpand_map_.remove(id);
        }
    }
}

void CameraWidget::on_recv_camera_settings_service_response(const CameraSettingsSrv::Response::SharedPtr response) {
    on_command_state_changed(response->id, CameraNode::CommandState::Success);

    if (response->state == CameraService::Type::ReadConfig) {
        ui->spinBox_pin_pwdn->setValue(response->pin_pwdn);
        ui->spinBox_pin_reset->setValue(response->pin_reset);
        ui->spinBox_pin_xclk->setValue(response->pin_xclk);
        ui->spinBox_pin_sccb_sda->setValue(response->pin_sccb_sda);
        ui->spinBox_pin_sccb_scl->setValue(response->pin_sccb_scl);
        ui->spinBox_pin_d7->setValue(response->pin_d7);
        ui->spinBox_pin_d6->setValue(response->pin_d6);
        ui->spinBox_pin_d5->setValue(response->pin_d5);
        ui->spinBox_pin_d4->setValue(response->pin_d4);
        ui->spinBox_pin_d3->setValue(response->pin_d3);
        ui->spinBox_pin_d2->setValue(response->pin_d2);
        ui->spinBox_pin_d1->setValue(response->pin_d1);
        ui->spinBox_pin_d0->setValue(response->pin_d0);
        ui->spinBox_xclk_freq_hz->setValue(response->xclk_freq_hz);
        ui->spinBox_fb_count->setValue(response->fb_count);
        ui->spinBox_sccb_i2c_port->setValue(response->sccb_i2c_port);

        ui->comboBox_frame_size->setCurrentIndex(response->frame_size);
        ui->comboBox_pixel_format->setCurrentIndex(response->pixel_format);
        ui->comboBox_ledc_timer->setCurrentIndex(response->ledc_timer);
        ui->comboBox_ledc_channel->setCurrentIndex(response->ledc_channel);
        ui->comboBox_grab_mode->setCurrentIndex(response->grab_mode);
        ui->comboBox_fb_location->setCurrentIndex(response->fb_location);
        ui->comboBox_conv_mode->setCurrentIndex(response->conv_mode);

    } else if (response->state == CameraService::Type::ReadParams) {
        ui->checkBox_serial_capture->setChecked(response->enable_series_capture);
        ui->pushButton_capture->setEnabled(!response->enable_series_capture);
        ui->spinBox_milliseconds->setValue(response->milliseconds);
        ui->spinBox_brightness->setValue(response->brightness);
        ui->spinBox_sharpness->setValue(response->sharpness);
        ui->spinBox_contrast->setValue(response->contrast);
        ui->spinBox_saturation->setValue(response->saturation);
        ui->spinBox_denoise->setValue(response->denoise);
        ui->spinBox_ae_level->setValue(response->ae_level);
        ui->spinBox_agc_gain->setValue(response->agc_gain);
        ui->spinBox_aec_value->setValue(response->aec_value);
        ui->spinBox_quality->setValue(response->quality);

        ui->comboBox_pixformat->setCurrentIndex(response->pixformat);
        ui->comboBox_framesize->setCurrentIndex(response->framesize);
        ui->comboBox_gainceiling->setCurrentIndex(response->gainceiling);
        ui->comboBox_special_effect->setCurrentIndex(response->special_effect);
        ui->comboBox_awb_gain->setCurrentIndex(response->awb_gain);
        ui->comboBox_wb_mode->setCurrentIndex(response->wb_mode);
        ui->comboBox_awb->setCurrentIndex(response->awb);
        ui->comboBox_dcw->setCurrentIndex(response->dcw);
        ui->comboBox_colorbar->setCurrentIndex(response->colorbar);
        ui->comboBox_agc->setCurrentIndex(response->agc);
        ui->comboBox_aec->setCurrentIndex(response->aec);
        ui->comboBox_aec2->setCurrentIndex(response->aec2);
        ui->comboBox_hmirror->setCurrentIndex(response->hmirror);
        ui->comboBox_vflip->setCurrentIndex(response->vflip);
        ui->comboBox_bpc->setCurrentIndex(response->bpc);
        ui->comboBox_wpc->setCurrentIndex(response->wpc);
        ui->comboBox_lenc->setCurrentIndex(response->lenc);
        ui->comboBox_raw_gma->setCurrentIndex(response->raw_gma);
    } else if (response->state == CameraService::Type::WriteParams) {
        ui->checkBox_serial_capture->setChecked(response->enable_series_capture);
        ui->pushButton_capture->setEnabled(!response->enable_series_capture);
        ui->spinBox_milliseconds->setValue(response->milliseconds);
        ui->spinBox_brightness->setValue(response->brightness);
        ui->spinBox_sharpness->setValue(response->sharpness);
        ui->spinBox_contrast->setValue(response->contrast);
        ui->spinBox_saturation->setValue(response->saturation);
        ui->spinBox_denoise->setValue(response->denoise);
        ui->spinBox_ae_level->setValue(response->ae_level);
        ui->spinBox_agc_gain->setValue(response->agc_gain);
        ui->spinBox_aec_value->setValue(response->aec_value);
        ui->spinBox_quality->setValue(response->quality);

        ui->comboBox_pixformat->setCurrentIndex(response->pixformat);
        ui->comboBox_framesize->setCurrentIndex(response->framesize);
        ui->comboBox_gainceiling->setCurrentIndex(response->gainceiling);
        ui->comboBox_special_effect->setCurrentIndex(response->special_effect);
        ui->comboBox_awb_gain->setCurrentIndex(response->awb_gain);
        ui->comboBox_wb_mode->setCurrentIndex(response->wb_mode);
        ui->comboBox_awb->setCurrentIndex(response->awb);
        ui->comboBox_dcw->setCurrentIndex(response->dcw);
        ui->comboBox_colorbar->setCurrentIndex(response->colorbar);
        ui->comboBox_agc->setCurrentIndex(response->agc);
        ui->comboBox_aec->setCurrentIndex(response->aec);
        ui->comboBox_aec2->setCurrentIndex(response->aec2);
        ui->comboBox_hmirror->setCurrentIndex(response->hmirror);
        ui->comboBox_vflip->setCurrentIndex(response->vflip);
        ui->comboBox_bpc->setCurrentIndex(response->bpc);
        ui->comboBox_wpc->setCurrentIndex(response->wpc);
        ui->comboBox_lenc->setCurrentIndex(response->lenc);
        ui->comboBox_raw_gma->setCurrentIndex(response->raw_gma);
    }
}

void CameraWidget::on_recv_connected_changed(bool connected) {
    if (connected) {
        read_config();
        read_params();
        ui->label_status->setStyleSheet(OK_STYLESHEET);
        ui->label_status->setText("相机节点已连接");
    } else {
        pixmapItem_->setPixmap(QPixmap::fromImage(QImage()));
        ui->label_status->setStyleSheet(ERROR_STYLESHEET);
        ui->label_status->setText("相机节点未连接");
    }
}

void CameraWidget::on_recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    QImage image;
    if (!image.loadFromData(QByteArray(reinterpret_cast<const char *>(msg->data.data()), static_cast<int>(msg->data.size())), nullptr)) {
        qDebug() << "图像解压缩失败！可能是数据损坏或不支持的格式";
        return;
    }

    pixmapItem_->setPixmap(QPixmap::fromImage(image));
    ui->graphicsView->scene()->setSceneRect(pixmapItem_->boundingRect());
    if (ui->graphicsView->width() != image.width() || ui->graphicsView->height() != image.height()) {
        ui->graphicsView->setFixedSize(image.width(), image.height());
        ui->graphicsView->fitInView(pixmapItem_, Qt::KeepAspectRatio);
    }

    fps_vector_->push_back(1000.0 / fps_timer_.restart());
}

void CameraWidget::on_update_status() {
    double average_fps = 0;
    if (fps_vector_ && !fps_vector_->isEmpty()) {
        double sum = std::accumulate(fps_vector_->begin(), fps_vector_->end(), 0);
        average_fps = sum / fps_vector_->size();
        fps_vector_->clear();
    }
    ui->label_fps->setText("帧率:" + QString::number(average_fps, 10, 2));
}

void CameraWidget::_ask_camera_settings_service(CameraSettingsSrv::Request::SharedPtr request, QString &cmd_string) {
    QThread::msleep(1);
    auto id = QDateTime::currentMSecsSinceEpoch();
    commpand_map_.insert(id, cmd_string);
    request->id = id;
    if (camera_node_->add_camera_settings_service(id, request)) {
        on_command_state_changed(id, CameraNode::CommandState::Add);
    } else {
        on_command_state_changed(id, CameraNode::CommandState::Fail);
    }
}

void CameraWidget::_update_cmd_status_info(const QString &cmd_string, int state) {
    QString html_string, cmd_string_tmp;
    if (state == CameraNode::CommandState::Success) {
        cmd_string_tmp = cmd_string + "执行成功！";
        html_string = QString("<span style='color:green;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped());
    } else if (state == CameraNode::CommandState::Add) {
        cmd_string_tmp = cmd_string + "等待执行...";
        html_string = QString("<span style='color:#FFB300;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped()); //
    } else if (state == CameraNode::CommandState::Running) {
        cmd_string_tmp = cmd_string + "运行中...";
        html_string = QString("<span style='color:#CCCC00;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped()); //
    } else if (state == CameraNode::CommandState::Fail) {
        cmd_string_tmp = cmd_string + "执行失败.";
        html_string = QString("<span style='color:red;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped());
    } else {
        cmd_string_tmp = _get_cmd_string_prefix() + "未知指令";
        html_string = QString("<span style='color:black;'>%1</span>").arg(cmd_string_tmp.toHtmlEscaped());
    }

    ui->textEdit_info->append(html_string);
    ui->textEdit_info->moveCursor(QTextCursor::End);
}
