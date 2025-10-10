#include "camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CameraWidget) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene());

    pixmapItem_ = ui->graphicsView->scene()->addPixmap(QPixmap());
    pixmapItem_->setTransformationMode(Qt::SmoothTransformation);

    camera_node_ = std::make_shared<CameraNode>(pc_camera_node_name, pc_camera_node_namespace, this);
    connect(camera_node_.get(), &CameraNode::imageMsgReceived, this, &CameraWidget::on_recv_image_msg);
    camera_node_->start();
}

CameraWidget::~CameraWidget() {
    delete ui;
}

void CameraWidget::on_recv_image_msg(const sensor_msgs::msg::CompressedImage::SharedPtr msg) {
    // QString frameId = QString::fromStdString(msg->header.frame_id);
    // QString format = QString::fromStdString(msg->format);

    // // 时间戳处理
    // qint64 sec = msg->header.stamp.sec;
    // qint32 nsec = msg->header.stamp.nanosec;

    QImage image;
    if (!image.loadFromData(QByteArray(reinterpret_cast<const char *>(msg->data.data()), static_cast<int>(msg->data.size())), nullptr)) {
        qDebug() << "图像解压缩失败！可能是数据损坏或不支持的格式";
        return;
    }
    pixmapItem_->setPixmap(QPixmap::fromImage(image));
    ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
