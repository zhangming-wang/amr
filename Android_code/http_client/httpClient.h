#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QUrlQuery>

class HttpClient : public QObject {
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);

    void start_timer();
    void stop_timer();

    void restart();
    void brake();
    void stop_move();
    void move_front();
    void move_back();
    void move_left();
    void move_right();
    void move_left_front();
    void move_right_front();
    void move_left_back();
    void move_right_back();
    void turn_left();
    void turn_right();

    void setSpeedPercent(float speedPercent);
    void setMotionMode(int mode);
    void getData();
    void save();

signals:
    void sendConnectStatus(bool);
    void sendData(QJsonObject);

private:
    void onReplyFinished(QNetworkReply *reply);
    void onTimerTimeout();

    void _checkConnect();

    bool is_connected_ = false, last_connect_status_ = true;
    QNetworkAccessManager *network_access_manager_;
    QTimer *timer_;
    int timeout_cnt_ = 0;
    const QString ESP32_url_ = "http://192.168.1.190"; // ESP32 IP 地址，改成你的
};

#endif // HTTPCLIENT_H
