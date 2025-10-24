#ifndef MOTIONWIDGET_H
#define MOTIONWIDGET_H

#include "../common/enum.h"
#include "../common/qt_tools.h"
#include "../common/settings.h"
#include "../motionNode/motionNode.h"
#include "../qcustomplot/qcustomplot.h"
#include "./ui_motionwidget.h"
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
#include <QGamepad>
#include <QHBoxLayout>
#include <QHash>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QQueue>
#include <QSplitter>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QValidator>
#include <QWidget>
#include <memory>

QT_BEGIN_NAMESPACE namespace Ui {
    class MotionWidget;
}
QT_END_NAMESPACE

class MotionWidget : public QWidget {
    Q_OBJECT

public:
    MotionWidget(QWidget *parent = nullptr);
    ~MotionWidget();

    void restart();

    void brake();
    void stop_move();

    void move_front();
    void move_back();
    void move_left();
    void move_right();
    void move_left_front();
    void move_left_back();
    void move_right_front();
    void move_right_back();
    void turn_left();
    void turn_right();

    void start_move_path();
    void stop_move_path();

    void set_speed();
    void set_speed_percent();
    void set_speed_plan_state();
    void set_enable_pub_motion_status();

    void clear_plot();

    void on_gamepad_button_clicked();
    void on_gamepad_axis_changed();

    void on_write_params();
    void on_read_params();
    void on_save_params();

    void on_write_config();
    void on_read_config();
    void on_save_config();

    void on_recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg);
    void on_recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);
    // void on_recv_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg);
    void on_recv_motion_settings_service_response(MotionSettingsSrv::Response::SharedPtr response);
    void on_command_state_changed(int64_t id, int state);

    void on_change_path_mode();
    void on_update_status();

    void on_connect_changed(bool connect);

    void onPlotShowCHanged(bool show);
    void onsettingsShowCHanged(bool show);

signals:
    void nodeClosed();

private:
    Ui::MotionWidget *ui;

    std::shared_ptr<MotionNode> motionNode_;
    std::shared_ptr<QTimer> status_timer_;
    std::shared_ptr<QGamepad> gamepad_;

    QTextEdit *motion_info_text_ = nullptr;
    QCustomPlot *linear_speed_customPlot_ = nullptr, *angular_speed_customPlot_ = nullptr, *linear_pose_customPlot_ = nullptr, *angular_pose_customPlot_ = nullptr; // acc_customPlot_

    QHash<int64_t, QString> commpand_map_;

    void _publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist, QString &cmd_string);
    void _ask_motion_settings_service(MotionSettingsSrv::Request::SharedPtr request, QString &cmd_string);

    // void _update_odom_label(double line_v = 0, double angle_v = 0, double pos_x = 0, double pos_y = 0, double yaw_deg = 0);
    void _update_cmd_status_label(const QString &cmd_string, int state);
    void _update_speed_percent_label(double percent);

    QString _get_cmd_string_prefix();

    bool stop_plot_ = false;

    double reference_sconds = 0;

    void _initTimer();
    QSplitter *_initCustomPlot();
    QSplitter *_initTextEdit();
    void _initGamepad();
    void _initMotionNode();

    QWidget *_create_customPlot_widget(QCustomPlot *customPlot, const QString &title, const QString &xLabel, const QString &yLabel, const QVector<QPair<QColor, QString>> &colorVector);
};
#endif // MOTIONWIDGET_H
