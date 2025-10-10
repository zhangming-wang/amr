#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include "../cameraNode/cameraNode.h"
#include "../common/enum.h"
#include "ui_camerawidget.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QWidget>
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

private:
    Ui::CameraWidget *ui;
    std::shared_ptr<CameraNode> camera_node_ = nullptr;
    QGraphicsPixmapItem *pixmapItem_ = nullptr;

    void on_recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
};
#endif // CAMERAWIDGET_H
