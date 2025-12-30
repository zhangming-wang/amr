#include "mainwindow/mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

    a.exec();

    rclcpp::shutdown();
}