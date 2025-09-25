#pragma once
#include "../common/enum.h"
#include "../nodeqthread/nodeqthread.h"
#include "../qcustomplot/qcustomplot.h"
#include "ui_mainwindow.h"
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
#include <memory>

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

    void on_gamepad_set_move();

    void on_write_params();
    void on_read_params();
    void on_save_params();

    void on_write_settings();
    void on_read_settings();
    void on_save_settings();

    void on_recv_motion_status_msg(const motion_status_msgs::msg::MotionStatus::SharedPtr msg);
    void on_recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);
    // void on_recv_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg);
    void on_recv_motion_params_service_response(motion_params_service::srv::MotionParamsService::Response::SharedPtr response);
    void on_command_state_changed(int64_t id, int state);

    void on_change_path_mode();
    void on_update_status();
    // void on_graph_visible_changed();

private:
    std::shared_ptr<Ui::MainWindow> ui;
    std::shared_ptr<NodeQThread> nodeThread_;
    std::shared_ptr<QCustomPlot> linear_speed_customPlot_, angular_speed_customPlot_, linear_pose_customPlot_, angular_pose_customPlot_; // acc_customPlot_

    std::shared_ptr<QTimer> status_timer_, cmd_status_timer_;
    std::shared_ptr<QProcess> agent_process_;
    std::shared_ptr<QTextEdit> agent_info_textEdit_, motion_info_text_;
    std::shared_ptr<QGamepad> gamepad_;
    std::shared_ptr<QLabel> micro_ros_status_label_, gamepad_status_label_, cmd_status_label_;

    QHash<int64_t, QString> commpand_map_;

    const QString CONFIG_FILE_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/" + "." + QCoreApplication::applicationName() + "/settings.json";

    void _publish_twist(std::shared_ptr<geometry_msgs::msg::Twist> twist, QString &cmd_string);
    void _ask_motion_params_service(motion_params_service::srv::MotionParamsService::Request::SharedPtr request, QString &cmd_string);

    // void _update_odom_label(double line_v = 0, double angle_v = 0, double pos_x = 0, double pos_y = 0, double yaw_deg = 0);
    void _update_cmd_status_label(const QString &cmd_string, int state);
    void _update_speed_percent_label(double percent);

    QString _get_cmd_string_prefix();

    bool stop_plot_ = false;

    double reference_sconds = 0;

    void _initTimer();
    QSplitter *_initCustomPlot();
    QSplitter *_initTextEdit();
    void _initStatusBar();
    void _initGamepad();
    void _initNodeThread();

    QWidget *_create_customPlot_widget(std::shared_ptr<QCustomPlot> customPlot, const QString &title, const QString &xLabel, const QString &yLabel, const QVector<QPair<QColor, QString>> &colorVector);

    // void _readConfigJson();
    // void _writeConfigJson();
};