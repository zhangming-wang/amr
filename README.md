# 项目简介
本项目是制作一个两轮差速后驱导航小车，主控采用ESP32S3开发板和ESP32-s3-cam视觉模块，上位机基于ros2+qt进行开发，下位机使用vscode中的platformio插件基于Arduino框架进行开发，上层导航使用ros2中的slam_toolbox进行建图和nav2进行导航。

# 开发环境
- 系统：ubuntu22.04
- ros2：humble
- qt：5.X
- 插件：vscode中的platformio插件
- 建模软件：freecad
- 电路设计软件：嘉立创专业版

# 实物展示
## 各模块
![模块](doc/images/模块.jpg)

## 小车
![小车](doc/images/小车.jpg)

## 上位机软件
![上位机](doc/images/上位机软件.png)

## rviz2
![rviz2](doc/images/rviz2.png)

## 建图（2.5倍速播放）
![建图](doc/images/建图-2.5倍速.gif)

## 导航（2倍速播放）
![建图](doc/images/导航-2倍速.gif)


