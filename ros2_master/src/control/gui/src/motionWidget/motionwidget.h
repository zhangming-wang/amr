#ifndef MOTIONWIDGET_H
#define MOTIONWIDGET_H

#include "../common/enum.h"
#include "../common/settings.h"
#include "../common/system.h"
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

    void set_speed_percent();
    void set_speed_plan_state();

    void clear_plot();

    void on_gamepad_button_clicked();
    void on_gamepad_axis_changed();
    void on_show_plot_changed(bool show);

    void on_write_params();
    void on_read_params();
    void on_save_params();

    void on_write_config();
    void on_read_config();
    void on_save_config();

    void on_recv_motion_status_msg(const MotionStatusMsg::SharedPtr msg);
    void on_recv_serial_msg(const std_msgs::msg::String::SharedPtr msg);
    void on_recv_motion_settings_service_response(uint64_t id, MotionSettingsSrv::Response::SharedPtr response);

    void on_update_status();

    void on_connect_changed(bool connect);
    void on_settings_show_changed(bool show);

signals:
    void nodeClosed();

private:
    Ui::MotionWidget *ui;

    std::shared_ptr<MotionNode> motionNode_;
    std::shared_ptr<QTimer> status_timer_;
    std::shared_ptr<QGamepad> gamepad_;

    QTextEdit *motion_info_text_ = nullptr;
    QCustomPlot *wheel_speed_customPlot_ = nullptr;

    QHash<uint64_t, QString> service_command_map_;

    void _ask_motion_settings_service(MotionSettingsSrv::Request::SharedPtr request, QString &cmd_string);
    void _show_service_command_state(uint64_t id, bool success);

    void _update_speed_percent_label(double percent);

    bool stop_plot_ = false;
    double reference_seconds_ = 0;

    static constexpr const char *OK_STYLESHEET = "color:green;font-size:20px;"; // background-color:green;
    static constexpr const char *ERROR_STYLESHEET = "color:red;font-size:20px;";

    inline QString _get_cmd_string_prefix() {
        return " [" + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") + "] ";
    }

    void _initTimer();
    QWidget *_initCustomPlot();
    QTextEdit *_initTextEdit();
    void _initGamepad();
    void _initMotionNode();

    QWidget *_create_customPlot_widget(QCustomPlot *customPlot, const QString &title, const QString &xLabel, const QString &yLabel, const QVector<QPair<QColor, QString>> &colorVector);
};
#endif // MOTIONWIDGET_H
