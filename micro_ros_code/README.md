# 编译 micro ros 下的自定义消息和服务教程

## 克隆仓库

在当前目录打开终端执行
- ```git clone https://github.com/micro-ROS/micro_ros_setup.git```
- ```colcon build```
- ```source install/setup.bash```

## 创建工作空间
- ```ros2 run micro_ros_setup create_firmware_ws.sh freertos esp32```

## 在 firmware/mcu_ws 目录下建立指向 ros2_code 目录下的 motion_params_service 和 motion_status_msgs 的软链接
- ```ln -s ../ros2_code/motion_params_service/ ./firmware/mcu_ws/```
- ```ln -s ../ros2_code/motion_status_msgs/ ./firmware/mcu_ws/```

## 编译
- ```ros2 run micro_ros_setup configure_firmware.sh ping_pong --transport serial```（选择一个示例程序）
- ```ros2 run micro_ros_setup build_firmware.sh```
- ```ros2 run micro_ros_setup flash_firmware.sh``` (烧录命令，当前用不上)

## 拷贝
- ```cp -rf ./firmware/mcu_ws/install/include/motion_params_service/motion_params_service/ ../ESP32_code/lib/motion_params_service/```
- ```cp -f firmware/mcu_ws/install/lib/libmotion_params_service__rosidl_* ../ESP32_code/lib/motion_params_service/lib/```

- ```cp -rf ./firmware/mcu_ws/install/include/motion_status_msgs/motion_status_msgs/ ../ESP32_code/lib/motion_status_msgs/```
- ```cp -f firmware/mcu_ws/install/lib/libmotion_status_msgs__rosidl_* ../ESP32_code/lib/motion_status_msgs/lib/```