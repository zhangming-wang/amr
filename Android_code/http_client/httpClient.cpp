#include "httpClient.h"

HttpClient::HttpClient(QObject *parent) : QObject(parent),
                                          network_access_manager_(new QNetworkAccessManager(this)),
                                          timer_(new QTimer(this)) {
    connect(network_access_manager_, &QNetworkAccessManager::finished,
            this, &HttpClient::onReplyFinished);

    timer_->setInterval(100);
    connect(timer_, &QTimer::timeout, this, &HttpClient::onTimerTimeout);
}

void HttpClient::start_timer() {
    onTimerTimeout();
    timer_->start();
}
void HttpClient::stop_timer() {
    timer_->stop();
}

void HttpClient::_checkConnect() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/ping"));
    network_access_manager_->get(request);
}

void HttpClient::moveFront() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/move_front"));
    network_access_manager_->get(request);
}

void HttpClient::moveBack() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/move_back"));
    network_access_manager_->get(request);
}
void HttpClient::moveLeft() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/move_left"));
    network_access_manager_->get(request);
}

void HttpClient::moveRight() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/move_right"));
    network_access_manager_->get(request);
}

void HttpClient::stopMove() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/stop_move"));
    network_access_manager_->get(request);
}


void HttpClient::brake() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/brake"));
    network_access_manager_->get(request);
}

void HttpClient::restart() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/restart"));
    network_access_manager_->get(request);
}

void HttpClient::save() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/save"));
    network_access_manager_->get(request);
}

void HttpClient::setSpeedPercent(float speedPercent) {
    QNetworkRequest request(QUrl(ESP32_url_ + "/set_speed_percent"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("value", QString::number(speedPercent));

    network_access_manager_->post(request, postData.query(QUrl::FullyEncoded).toUtf8());
}

void HttpClient::setMotionMode(int mode) {
    QNetworkRequest request(QUrl(ESP32_url_ + "/set_motion_mode"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("value", QString::number(mode));

    network_access_manager_->post(request, postData.query(QUrl::FullyEncoded).toUtf8());
}

void HttpClient::getData() {
    QNetworkRequest request(QUrl(ESP32_url_ + "/get_data"));
    network_access_manager_->get(request);
}

void HttpClient::onTimerTimeout() {
    if (timeout_cnt_ == 0) {
        if (is_connected_) {
            is_connected_ = false;
            if (!last_connect_status_) {
                getData();
                emit sendConnectStatus(true);
            }
            last_connect_status_ = true;
        } else {
            if (last_connect_status_)
                emit sendConnectStatus(false);
            last_connect_status_ = false;
        }
    }
    if (timeout_cnt_ >= 10) {
        timeout_cnt_ = 0;
    } else {
        timeout_cnt_ += 1;
    }

    // _checkConnect();
    getData();
}

void HttpClient::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        // 获取 Content-Type 响应头
        QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
        QString mimeType = contentType.toString();
        // qDebug() << "Content-Type:" << mimeType;

        if (mimeType.contains("application/json", Qt::CaseInsensitive) && timer_->isActive()) {
            // 处理 JSON 响应-
            is_connected_ = true;
            QJsonParseError jsonError;
            QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);
            if (jsonError.error == QJsonParseError::NoError && doc.isObject()) {
                QJsonObject obj = doc.object();
                emit sendData(obj);
                qDebug() << "Parsed JSON:" << obj;
            } else {
                qWarning() << "JSON parse error:" << jsonError.errorString();
            }
        } else if (mimeType.contains("text/plain", Qt::CaseInsensitive)) {
            // 处理纯文本响应
            QString text = QString::fromUtf8(data);
            if (text.contains("connected")) {
                is_connected_ = true;
            }
            // qDebug() << "plain/text:" << text;
        } else {
            // 其他未知类型
            qDebug() << "Unknown content type. Raw data:" << data;
        }
    } else {
        qWarning() << "Request error:" << reply->errorString();
    }
    reply->deleteLater();
}
