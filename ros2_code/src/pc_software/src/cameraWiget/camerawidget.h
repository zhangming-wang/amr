#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include "../cameraNode/cameraNode.h"
#include "../common/enum.h"
#include "../common/qt_tools.h"
#include "ui_camerawidget.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <numeric> // std::accumulate

QT_BEGIN_NAMESPACE
namespace Ui {
    class CameraWidget;
}
QT_END_NAMESPACE

class CameraWidget : public QWidget {
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();

    void restart();
    void capture_image();

    void setEnableSeriesCapture(bool enable);

    void read_config();
    void write_config();
    void save_config();

    void read_params();
    void write_params();
    void save_params();

    // private slots:

private:
    Ui::CameraWidget *ui;
    std::shared_ptr<CameraNode> camera_node_ = nullptr;
    QGraphicsPixmapItem *pixmapItem_ = nullptr;

    QHash<int64_t, QString> commpand_map_;
    double fps_ = 0;
    QTimer status_timer_;
    QElapsedTimer fps_timer_;

    std::shared_ptr<QVector<double>> fps_vector_;

    void _ask_motion_params_service(CameraNode::CameraSettingsSrv::Request::SharedPtr request, QString &cmd_string);
    void _update_cmd_status_info(const QString &cmd_string, int state);

    void on_recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void on_recv_camera_settings_service_response(const camera_settings_service::srv::CameraSettingsService::Response::SharedPtr response);
    void on_recv_connected_changed(bool connected);
    void on_command_state_changed(int64_t id, int state);

    void on_update_status();
};
#endif // CAMERAWIDGET_H
