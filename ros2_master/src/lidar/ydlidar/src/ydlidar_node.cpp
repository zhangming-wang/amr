/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS 2 Node
 *
 *  Copyright 2017 - 2020 EAI TEAM
 *  http://www.eaibot.com
 *
 */

#ifdef _MSC_VER
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#endif

#include "rclcpp/clock.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time_source.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "sensor_msgs/msg/point_cloud.hpp"
#include "src/CYdLidar.h"
#include "std_srvs/srv/empty.hpp"
#include <chrono>
#include <iostream>
#include <math.h>
#include <memory>
#include <signal.h>
#include <string>
#include <thread>
#include <vector>

#define ROS2Verision "1.0.1"

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("ydlidar_ros2_driver_node");

    RCLCPP_INFO(node->get_logger(), "[YDLIDAR INFO] Current ROS Driver Version: %s\n", ((std::string)ROS2Verision).c_str());

    CYdLidar laser;
    std::string str_optvalue = "/dev/ydlidar";
    node->declare_parameter("port", str_optvalue);
    node->get_parameter("port", str_optvalue);
    /// lidar port
    laser.setlidaropt(LidarPropSerialPort, str_optvalue.c_str(), str_optvalue.size());
    /// ignore array
    str_optvalue = "";
    node->declare_parameter("ignore_array", str_optvalue);
    node->get_parameter("ignore_array", str_optvalue);
    laser.setlidaropt(LidarPropIgnoreArray, str_optvalue.c_str(), str_optvalue.size());

    std::string frame_id = "laser_frame";
    node->declare_parameter("frame_id", frame_id);
    node->get_parameter("frame_id", frame_id);

    std::string scan_topic_name = "/scan";
    node->declare_parameter("scan_topic_name", scan_topic_name);
    node->get_parameter("scan_topic_name", scan_topic_name);

    std::string points_topic_name = "/scan/points";
    node->declare_parameter("points_topic_name", points_topic_name);
    node->get_parameter("points_topic_name", points_topic_name);

    //////////////////////int property/////////////////
    /// lidar baudrate
    int optval = 230400;
    node->declare_parameter("baudrate", optval);
    node->get_parameter("baudrate", optval);
    laser.setlidaropt(LidarPropSerialBaudrate, &optval, sizeof(int));
    /// tof lidar
    optval = TYPE_TRIANGLE;
    node->declare_parameter("lidar_type", optval);
    node->get_parameter("lidar_type", optval);
    laser.setlidaropt(LidarPropLidarType, &optval, sizeof(int));
    /// device type
    optval = YDLIDAR_TYPE_SERIAL;
    node->declare_parameter("device_type", optval);
    node->get_parameter("device_type", optval);
    laser.setlidaropt(LidarPropDeviceType, &optval, sizeof(int));
    /// sample rate
    optval = 9;
    node->declare_parameter("sample_rate", optval);
    node->get_parameter("sample_rate", optval);
    laser.setlidaropt(LidarPropSampleRate, &optval, sizeof(int));
    /// abnormal count
    optval = 4;
    node->declare_parameter("abnormal_check_count", optval);
    node->get_parameter("abnormal_check_count", optval);
    laser.setlidaropt(LidarPropAbnormalCheckCount, &optval, sizeof(int));

    /// Intenstiy bit count
    optval = 8;
    node->declare_parameter("intensity_bit", optval);
    node->get_parameter("intensity_bit", optval);
    laser.setlidaropt(LidarPropIntenstiyBit, &optval, sizeof(int));

    //////////////////////bool property/////////////////
    /// fixed angle resolution
    bool b_optvalue = false;
    node->declare_parameter("fixed_resolution", b_optvalue);
    node->get_parameter("fixed_resolution", b_optvalue);
    laser.setlidaropt(LidarPropFixedResolution, &b_optvalue, sizeof(bool));
    /// rotate 180
    b_optvalue = true;
    node->declare_parameter("reversion", b_optvalue);
    node->get_parameter("reversion", b_optvalue);
    laser.setlidaropt(LidarPropReversion, &b_optvalue, sizeof(bool));
    /// Counterclockwise
    b_optvalue = true;
    node->declare_parameter("inverted", b_optvalue);
    node->get_parameter("inverted", b_optvalue);
    laser.setlidaropt(LidarPropInverted, &b_optvalue, sizeof(bool));
    b_optvalue = true;
    node->declare_parameter("auto_reconnect", b_optvalue);
    node->get_parameter("auto_reconnect", b_optvalue);
    laser.setlidaropt(LidarPropAutoReconnect, &b_optvalue, sizeof(bool));
    /// one-way communication
    b_optvalue = false;
    node->declare_parameter("isSingleChannel", b_optvalue);
    node->get_parameter("isSingleChannel", b_optvalue);
    laser.setlidaropt(LidarPropSingleChannel, &b_optvalue, sizeof(bool));
    /// intensity
    // b_optvalue = false;
    // node->declare_parameter("intensity", b_optvalue);
    // node->get_parameter("intensity", b_optvalue);
    // laser.setlidaropt(LidarPropIntenstiy, &b_optvalue, sizeof(bool));
    laser.setAutoIntensity(true);
    /// Motor DTR
    b_optvalue = false;
    node->declare_parameter("support_motor_dtr", b_optvalue);
    node->get_parameter("support_motor_dtr", b_optvalue);
    laser.setlidaropt(LidarPropSupportMotorDtrCtrl, &b_optvalue, sizeof(bool));

    //////////////////////float property/////////////////
    /// unit: °
    float f_optvalue = 180.0f;
    node->declare_parameter("angle_max", f_optvalue);
    node->get_parameter("angle_max", f_optvalue);
    laser.setlidaropt(LidarPropMaxAngle, &f_optvalue, sizeof(float));
    f_optvalue = -180.0f;
    node->declare_parameter("angle_min", f_optvalue);
    node->get_parameter("angle_min", f_optvalue);
    laser.setlidaropt(LidarPropMinAngle, &f_optvalue, sizeof(float));
    /// unit: m
    f_optvalue = 64.f;
    node->declare_parameter("range_max", f_optvalue);
    node->get_parameter("range_max", f_optvalue);
    laser.setlidaropt(LidarPropMaxRange, &f_optvalue, sizeof(float));
    f_optvalue = 0.1f;
    node->declare_parameter("range_min", f_optvalue);
    node->get_parameter("range_min", f_optvalue);
    laser.setlidaropt(LidarPropMinRange, &f_optvalue, sizeof(float));
    /// unit: Hz
    f_optvalue = 10.f;
    node->declare_parameter("frequency", f_optvalue);
    node->get_parameter("frequency", f_optvalue);
    laser.setlidaropt(LidarPropScanFrequency, &f_optvalue, sizeof(float));

    bool invalid_range_is_inf = false;
    node->declare_parameter("invalid_range_is_inf", invalid_range_is_inf);
    node->get_parameter("invalid_range_is_inf", invalid_range_is_inf);

    auto laser_pub = node->create_publisher<sensor_msgs::msg::LaserScan>(scan_topic_name, rclcpp::SensorDataQoS());
    auto pc_pub = node->create_publisher<sensor_msgs::msg::PointCloud>(points_topic_name, rclcpp::SensorDataQoS());

    auto stop_scan_service =
        [&laser](const std::shared_ptr<rmw_request_id_t> request_header,
                 const std::shared_ptr<std_srvs::srv::Empty::Request> req,
                 std::shared_ptr<std_srvs::srv::Empty::Response> response) -> bool {
        return laser.turnOff();
    };

    auto stop_service = node->create_service<std_srvs::srv::Empty>("stop_scan", stop_scan_service);

    auto start_scan_service =
        [&laser](const std::shared_ptr<rmw_request_id_t> request_header,
                 const std::shared_ptr<std_srvs::srv::Empty::Request> req,
                 std::shared_ptr<std_srvs::srv::Empty::Response> response) -> bool {
        return laser.turnOn();
    };

    auto start_service = node->create_service<std_srvs::srv::Empty>("start_scan", start_scan_service);

    rclcpp::WallRate loop_rate(10);

    bool initialized = false, is_turnOn = false;

    while (rclcpp::ok()) {
        if (!initialized) {
            initialized = laser.initialize();
        }

        if (!is_turnOn && initialized) {
            is_turnOn = laser.turnOn();
        }

        if (initialized && is_turnOn) {
            LaserScan scan; //

            if (laser.doProcessSimple(scan)) {

                auto scan_msg = std::make_shared<sensor_msgs::msg::LaserScan>();
                auto pc_msg = std::make_shared<sensor_msgs::msg::PointCloud>();

                // Header 和基本信息依然保持不变
                scan_msg->header.stamp.sec = RCL_NS_TO_S(scan.stamp);
                scan_msg->header.stamp.nanosec = scan.stamp - RCL_S_TO_NS(scan_msg->header.stamp.sec);
                scan_msg->header.frame_id = frame_id;
                pc_msg->header = scan_msg->header;

                // --- 【修改开始】强制重采样到 490 个点 ---
                int target_points = 490;

                // 物理角度范围保持不变
                double min_angle = scan.config.min_angle;
                double max_angle = scan.config.max_angle;

                // 核心：重新计算点数固定为 490 后的角度增量
                double new_angle_increment = (max_angle - min_angle) / (target_points - 1);

                // 更新 scan_msg 的配置
                scan_msg->angle_min = min_angle;
                scan_msg->angle_max = max_angle;
                scan_msg->angle_increment = new_angle_increment;
                scan_msg->scan_time = scan.config.scan_time;
                scan_msg->time_increment = scan.config.scan_time / (target_points - 1);
                scan_msg->range_min = scan.config.min_range;
                scan_msg->range_max = scan.config.max_range;

                // 重新调整大小并初始化 ranges
                scan_msg->ranges.assign(target_points, std::numeric_limits<float>::infinity());
                scan_msg->intensities.assign(target_points, 0.0);
                // --- 【修改结束】 ---

                pc_msg->channels.resize(2);
                int idx_intensity = 0;
                pc_msg->channels[idx_intensity].name = "intensities";
                int idx_timestamp = 1;
                pc_msg->channels[idx_timestamp].name = "stamps";

                // --- 【修改开始】映射逻辑 ---
                for (size_t i = 0; i < scan.points.size(); i++) {
                    // 计算当前点落到 490 个桶中的哪一个
                    double angle = scan.points[i].angle;
                    // 使用 round 找到最近的索引
                    int index = std::round((angle - min_angle) / new_angle_increment);

                    if (index >= 0 && index < target_points) {
                        if (scan.points[i].range >= scan.config.min_range) {
                            // 如果同一个桶有多个点，为了建图稳定，通常取距离最近的点
                            if (scan.points[i].range < scan_msg->ranges[index]) {
                                scan_msg->ranges[index] = scan.points[i].range;
                                scan_msg->intensities[index] = scan.points[i].intensity;
                            }
                        }
                    }
                    // --- 【修改结束】 ---
                
                    // PointCloud 的逻辑保持不变，用于 3D 可视化
                    if (scan.points[i].range >= scan.config.min_range &&
                        scan.points[i].range <= scan.config.max_range) {
                        geometry_msgs::msg::Point32 point;
                        point.x = scan.points[i].range * cos(scan.points[i].angle);
                        point.y = scan.points[i].range * sin(scan.points[i].angle);
                        point.z = 0.0;
                        pc_msg->points.push_back(point);
                        pc_msg->channels[idx_intensity].values.push_back(scan.points[i].intensity);
                        pc_msg->channels[idx_timestamp].values.push_back(i * scan.config.time_increment);
                    }
                }
            
                laser_pub->publish(*scan_msg);
                pc_pub->publish(*pc_msg);
            } else {
                RCLCPP_ERROR(node->get_logger(), "Failed to get scan");
                initialized = false;
                is_turnOn = false;
                laser.turnOff();
                laser.disconnecting();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            rclcpp::spin_some(node);
            loop_rate.sleep();
        } else {
            RCLCPP_ERROR(node->get_logger(), "%s\n", laser.DescribeError());
            // 休眠 500 毫秒
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    RCLCPP_INFO(node->get_logger(), "[YDLIDAR INFO] Now YDLIDAR is stopping .......");
    laser.turnOff();
    laser.disconnecting();
    rclcpp::shutdown();

    return 0;
}
