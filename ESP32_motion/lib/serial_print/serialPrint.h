#pragma once

#include <Arduino.h>
#include <iostream>
#include <micro_ros_platformio.h>
#include <std_msgs/msg/string.h>

extern void (*serial_print)(const std::string &);
