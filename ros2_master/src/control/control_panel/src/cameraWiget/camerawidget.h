#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include "../cameraNode/cameraNode.h"
#include "../common/enum.h"
#include "../common/system.h"
#include "ui_camerawidget.h"
#include <QDateTime>
#include <QDebug>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
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

    void onOpenSettingsChanged(bool open);

signals:
    void nodeClosed();

private:
    Ui::CameraWidget *ui;
    std::shared_ptr<CameraNode> camera_node_ = nullptr;
    QGraphicsPixmapItem *pixmapItem_ = nullptr;

    QHash<uint64_t, QString> service_command_map_;
    double fps_ = 0;
    QTimer status_timer_;
    QElapsedTimer fps_timer_;
    std::shared_ptr<QVector<double>> fps_vector_;
    cv_bridge::CvImagePtr cv_ptr_ = nullptr;
    sensor_msgs::msg::Image::SharedPtr image_msg_ = nullptr;

    static constexpr const char *OK_STYLESHEET = "color:green;font-size:20px;"; // background-color:green;
    static constexpr const char *ERROR_STYLESHEET = "color:red;font-size:20px;";

    inline QString _get_cmd_string_prefix() {
        return " [" + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") + "] ";
    }

    void _ask_camera_settings_service(CameraSettingsSrv::Request::SharedPtr request, QString &cmd_string);
    void _show_service_command_state(uint64_t id, bool success);

    void on_recv_compressed_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void on_recv_raw_image_msg(const sensor_msgs::msg::Image::SharedPtr msg);
    void on_recv_camera_settings_service_response(uint64_t id, const CameraSettingsSrv::Response::SharedPtr response);
    void on_recv_connected_changed(bool connected);
    void on_recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);

    void on_update_status();

    void _update_image_display(const QImage &image);
};
#endif // CAMERAWIDGET_H
