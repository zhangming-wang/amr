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

    QHash<int64_t, QString> commpand_map_;
    double fps_ = 0;
    QTimer status_timer_;
    QElapsedTimer fps_timer_;
    std::shared_ptr<QVector<double>> fps_vector_;

    static constexpr const char *OK_STYLESHEET = "color:green;font-size:20px;"; // background-color:green;
    static constexpr const char *ERROR_STYLESHEET = "color:red;font-size:20px;";

    inline QString _get_cmd_string_prefix() {
        return " [" + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") + "] ";
    }

    void _ask_camera_settings_service(CameraSettingsSrv::Request::SharedPtr request, QString &cmd_string);
    void _update_cmd_status_info(const QString &cmd_string, int state);

    void on_recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
    void on_recv_camera_settings_service_response(const CameraSettingsSrv::Response::SharedPtr response);
    void on_recv_connected_changed(bool connected);
    void on_command_state_changed(int64_t id, int state);

    void on_update_status();
};
#endif // CAMERAWIDGET_H
